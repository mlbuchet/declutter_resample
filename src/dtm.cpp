/*
* File: dtm.cpp
* Author: Mickaël Buchet
*
* Created on Januray 15, 2013
*
* Computation of the distance to a measure from a point cloud. See manual for more details
*/

#include "dtm.h"

namespace dtm {

    PointSet::PointSet() {
        points;
        weights;
    }

    PointSet::PointSet(const char* file, const bool weighted) {
        std::ifstream filestream;
        filestream.open(file, std::ifstream::in);
        std::string line;
        points;
        weights;
        while(!filestream.eof()) {
            std::getline(filestream, line);
            if(line.size()!=0) {
                std::istringstream reader(line);
                Point pt;
                while(!reader.eof()) {
                    double aux;
                    reader >> aux;
                    pt.push_back(aux);
                }
                if(weighted) {
                    weights.push_back(pt.back());
                    pt.pop_back();
                }
                points.push_back(pt);
            }
        }
    }

    int PointSet::size() const {
        return points.size();
    }

    Point PointSet::get_point(const int index) const {
        return points[index];
    }

    double PointSet::get_weight(const int index) const {
        return weights[index];
    }

    int PointSet::dimension() const {
        return points.front().size();
    }

    void PointSet::exportPoints(const char* file, const bool weighted) const {
        std::ofstream writer;
        writer.open(file, std::ofstream::out);
        for(int i=0; i<size(); i++) {
            for(int j=0; j<dimension()-1;j++) {
                writer << get_point(i)[j] << '\t';
            }
            writer << get_point(i)[dimension()-1];
            if(weighted) writer << '\t' << get_weight(i);
            writer << '\n';
        }
        writer.close();
    }

    ANNpointArray PointSet::toANNArray() const {
        ANNpointArray result = annAllocPts(size(),dimension());
        for(int i=0; i<size(); i++) {
            for(int j=0; j<dimension(); j++) {
                result[i][j] = points[i][j];
            }
        }
        return result;
    }

    void PointSet::addPoint(const Point& pt) {
        points.push_back(pt);
    }

    Point PointSet::barycenter(const int k, const int idx[]) const {
        Point bar(dimension(),0);

        for(int i=0; i < k; i++) {
            for(int j=0; j < dimension(); j++) {
                bar[j] += points[idx[i]][j];
            }
        }

        for(int j=0; j < dimension(); j++) {
            bar[j] /= k;
        }

        return bar;
    }

    PointSet PointSet::exactComputation(const int k) const {
        if(k > size()) throw "Impossible to compute when k is larger than the size of the input";
        int indices[k];
        for(int i=0; i < k; i++) indices[i] = i;
        PointSet result;
        do{
            Point pt = barycenter(k, indices);
            result.addPoint(pt);
            result.weights.push_back(sqrt(cellEnergy(pt, k, indices)));
        } while(nextUpplet(indices, k, size()));
        return result;
    }

    double PointSet::cellEnergy(const Point& b, const int k, const int idx[]) const {
        double energy=0;
        for(int i=0; i<k; i++) energy += squareDist(b,points[idx[i]]);
        return energy/k;
    }

    std::vector<double> PointSet::samplingBox() const {
        std::vector<double> lbound(dimension(), 0);
        std::vector<double> ubound(dimension(), 0);
        Point q = points[0];
        for(int j = 0; j < dimension(); j++) {
            lbound[j] = q[j];
            ubound[j] = q[j];
        }

        for(auto q : points) {
            for(int j = 0; j < dimension(); j++) {
                if(q[j] < lbound[j]) lbound[j] = q[j];
                if(q[j] > ubound[j]) ubound[j] = q[j];
            }
        }

        std::vector<double> diameter(dimension(), 0);
        for(int j = 0; j < dimension(); j++) diameter[j] = ubound[j]-lbound[j];
        std::vector<double> result(2*dimension(), 0);
        for(int j = 0; j < dimension(); j++) {
            result[j] = lbound[j]-(diameter[j]/2);
            result[dimension()+j] = ubound[j]+(diameter[j]/2);
        }
        return result;
    }

    PointSet PointSet::samplingBarycentres(const int k, const int samplingSize) const {
        srand(time(NULL));
        ANNkd_tree* tree = new ANNkd_tree(toANNArray() ,size(), dimension());
        std::vector<double> box = samplingBox();
        PointSet results;
        ANNidxArray index = new ANNidx[k];
        ANNdistArray dists = new ANNdist[k];

        for(int i=0; i < samplingSize; i++) {
            ANNpoint query = randomPoint(box, dimension());
            tree->annkSearch(query,k,index,dists,0.0);
            Point bar = barycenter(k, index);
            if(!results.contains(bar)) {
                results.addPoint(bar);
                results.weights.push_back(cellEnergy(bar, k, index));
            }
        }
        delete tree;
        return results;
    }

    bool PointSet::contains(const Point& query) const {
        if(points.empty()) return false;
        if(dimension() != query.size()) throw "Impossible to look up a point in set of different dimension.";
        for(auto pt : points) {
            bool found = true;
            for(int i = 0; i < query.size(); i++) {
                found &= query[i] == pt[i];
            }
            if(found) return true;
        }
        return false;
    }

    PointSet PointSet::witnessedKDistance(const int k) const {
        ANNpointArray pts = toANNArray();
        ANNkd_tree* tree = new ANNkd_tree(pts, size(), dimension());
        PointSet results;
        ANNidxArray index = new ANNidx[k];
        ANNdistArray dists = new ANNdist[k];

        for(int i = 0; i < size(); i++) {
            tree->annkSearch(pts[i],k,index,dists,0.0);
            Point bar = barycenter(k, index);
            if(!results.contains(bar)) {
                results.addPoint(bar);
                results.weights.push_back(sqrt(cellEnergy(bar, k, index)));
            }
        }
        delete tree;
        return results;
    }

    PointSet PointSet::witnessingPoints(const int k) {
        ANNpointArray pts = toANNArray();
        ANNkd_tree* tree = new ANNkd_tree(pts, size(), dimension());
        ANNidxArray index=new ANNidx[k];
        ANNdistArray dists=new ANNdist[k];
        weights = std::vector<double>(size());

        for(int i=0; i < size(); i++) {
            tree->annkSearch(pts[i], k, index, dists, 0.0);
            weights[i]=sqrt(cellEnergy(get_point(i), k, index));
        }
        delete tree;
        return *this;
    }

    void PointSet::sort() {
        for(int i=0; i < size(); i++) {
            for(int j=0; j < size()-1; j++) {
                if(weights[j+1] < weights[j]) {
                    Point auxp = points[j];
                    double auxw = weights[j];
                    points[j] = points[j+1];
                    weights[j] = weights[j+1];
                    points[j+1] = auxp;
                    weights[j+1] = auxw;
                }
            }
        }
    }

    void PointSet::declutter(const double dc) {
        sort();
        int n = size();
        ANNpointArray pts = toANNArray();
        ANNkd_tree* tree = new ANNkd_tree(pts, n, dimension());
        ANNidxArray index=new ANNidx[n];
        ANNdistArray dists=new ANNdist[n];
        selects = std::vector<bool>(size(), false);
        for(int i=0; i < n; i++) {
            tree->annkFRSearch(pts[i], dc*dc*weights[i]*weights[i], n, index, dists);
            bool witnessed = false;
            int j = 0;
            while (index[j] >= 0 && !witnessed && j < n) {
                witnessed = selects[index[j]];
                j++;
            }
            if(!witnessed) selects[i] = true;
        }
        delete tree;
    }

    void PointSet::resample(const double sc) {
        std::vector<bool> neoselects(size(), false);
        ANNpointArray pts = toANNArray();
        ANNkd_tree* tree = new ANNkd_tree(pts, size(), dimension());
        ANNidxArray index=new ANNidx[size()];
        ANNdistArray dists=new ANNdist[size()];
        int nrange = size();
        for(int i=0; i < nrange; i++) {
            if(selects[i]) {
                tree->annkFRSearch(pts[i], sc*sc*weights[i]*weights[i], nrange, index, dists);
                for(int j=0; index[j] >= 0 && j < nrange; j++) neoselects[index[j]] = true;
            }
        }
        selects = neoselects;
        delete tree;
    }

    void PointSet::eliminate() {
        std::vector<Point> neopoints;
        std::vector<double> neoweights;
        std::vector<bool> neoselects;
        for(int i=0; i < size(); i++) {
            if(selects[i]) {
                neopoints.push_back(points[i]);
                neoweights.push_back(weights[i]);
                neoselects.push_back(selects[i]);
            }
        }
        points = neopoints;
        weights = neoweights;
        selects = neoselects;
    }

    void PointSet::denoise(const double dc, const double sc) {
        int k = 1;
        int n = size();
        while(k <= n) k = k*2;
        k = k/2;
        while(k > 1) {
            witnessingPoints(k);
            declutter(dc);
            resample(sc);
            eliminate();
            k = k/2;
        }
    }

    double squareDist(const Point& p, const Point& q) {
        double dist = 0;
        if(p.size() != q.size()) throw "Impossible to compute the distance between two points of different dimensions.";
        for(int i=0; i<p.size(); i++) {
            dist+=(p[i]-q[i])*(p[i]-q[i]);
        }
        return dist;
    }

    ANNpoint randomPoint(const std::vector<double>& box, const int d) {
        ANNpoint p=annAllocPt(d,0);
        for(int i=0;i<d;i++) {
            double x=rand()%1000000;
            x=x/1000000.;
            p[i]=box[i]+(x*(box[d+i]-box[i]));
        }
        return p;
    }

    bool nextUpplet(int ind[], const int k, const int n){
        if(k==0) return false;
        ind[k-1]++;
        if(ind[k-1]<n) return true;
        else {
            if(!nextUpplet(ind,k-1,n-1)) return false;
            ind[k-1]=ind[k-2]+1;
            return true;
        }
    }

}

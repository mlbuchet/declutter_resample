/*
* File: dtm.h
* Author: Mickaël Buchet
*
* Created on Januray 15, 2013
*
* Computation of the distance to a measure from a point cloud. See manual for more details
*/

#ifndef DTM_H
#define DTM_H

#include <cstdlib>
#include "ANN/ANN.h"
#include <ctime>
#include <cstring>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

namespace dtm {

    /** Typedef for the definiton of a point.
    **/
    typedef std::vector<double> Point;

    /** Class containing a point set and operations on it.
    **/
    class PointSet{

    public:

        /** Empty default constructor
        **/
        PointSet();

        /** Constructor importing points from a file.
        * @param
        *   file    : File to be read from.
        *   weighted : Indicate if the file contains weighted points.
        **/
        PointSet(const char* file, const bool weighted = false);

        /** Computes the number of points in the point set.
        * @return   : Number of points of the point set.
        **/
        int size() const;

        /** Returns the point at the index.
        * @param
        *   index   : Index of the point to be returned.
        * @return   : Point whose index is index.
        **/
        Point get_point(const int index) const;

        /** Returns the weight of point with the index.
        * @param
        *   index   : Index of the point whose weight is requested.
        * @return   : Weight of point index.
        **/
        double get_weight(const int index) const;

        /** Returns the dimension of the points in the set.
        * @return   : Dimension of the first point in the set.
        **/
        int dimension() const;

        /** Exports the point set to a file.
        * @param
        *   file    : File where the point set should be written.
        *   weighted    : Indicates whether the point set is weighted or not.
        **/
        void exportPoints(const char* file, const bool weighted) const ;

        /** Conversion to an array for use with the ANN library.
        * @return   : The point set in the ANN compatible format.
        **/
        ANNpointArray toANNArray() const;

        /** Adds a point to the point set.
        * @param
        *   pt  : Point to be added to the point set.
        **/
        void addPoint(const Point& pt);

        /** Computes a sampling box around the point cloud.
        * @return : Coordinates of the sampling box.
        **/
        std::vector<double> samplingBox() const;

        /** Computes the set of all barycenters of k-points and their respective weights
        * @param
        *   k   : Value of k to consider.
        * @return   Set of all weighted barycenters.
        **/
        PointSet exactComputation(const int k) const;

        //! Computes the barycenter of a set of k points.
        /*! The points are given by their indices in the array of points.
            The number of indices can be longer than the numberof neighbors in which case the extra indices are igonred.
            \param k    The number of neighbors to consider.
            \param idx  The set of indices to consider.
            \return     The barycenter of the points corresponding to the k firts indices.
        */
        Point barycenter(const int k, const int idx[]) const;

        //! Computes the cell energy of a barycenter from the indices.
        /*! This corresponds to the sum of the square of the distances between b and the k first points given by the indices in idx.
            \param b    Center considered.
            \param k    Number of points considered.
         	\param idx  Indices in the point array.
            \return     The average square distance between the point b and the k first points given by the indices in idx.
        **/
        double cellEnergy(const Point& b, const int k, const int idx[]) const;

        //! Samples randomly the barycenters having a non-empty k-order Voronoi cell.
        /*! Some barycenters can be smapled multiple time and are only saved once.
            \param k    Order of the Voronoi diagram.
            \param size Maximal number of barycenters to be sampled.
            \return     Set of sampled barycenters.
        **/
        PointSet samplingBarycentres(const int k, const int samplingSize) const;

        //! Tests if the point set contains the query point.
        /*! Throws an exception if the dimension of point set and the dimension of the query point do not match.
            \param query    Query point to be looked up.
            \return         True if query is in the point set.
        **/
        bool contains(const Point& query) const;

        //! Computes the witnessed k-distance.
        /*! Computes all the barycenters of the k nearest neighbors of the input points amd the cell energy.
         	\param k    Number of nearest neighbors considered
            \return     The weighted set of barycenters.
        **/
        PointSet witnessedKDistance(const int k) const;

        //! Computes the witnessing points of the point set.
        /*! This is equivalent to computing the distance to a measure for every point in the set.
            The function works directly with the current point set, changing the weight of every point.
            \param k    Number of nearest neighbors to consider.
            \return     The input points weighted by their distance to a measure.
        */
        PointSet witnessingPoints(const int k);

        //! Sorts the point set according to the increasing value of its weights.
        void sort();

        //! Declutters a point set using the weights as the distance function.
        /*! Be carefult that the method first sort the points according to their weights, therefore invalidating the indices.
            The decluttered set is obtained by taking the points whose flag is set to true.
            \param dc   Decluttering constant. Values at 2 by default and should be used as that unless for specific purposes.
        */
        void declutter(const double dc = 2);

        //! Resamples the point set using the weights as the distance function and the points flagged as the seed.
        /*! Sets all points within distance ds*weight(p) of p for all p with flag set to true.
            \param sc   Resampling constant set to 4 by default.
        */
        void resample(const double sc = 4);

        //! Removes all points with a flag set to false as well as their weights and flags.
        void eliminate();

        //! Runs the parameter free denoising algorithm called declutter and resample.
        /*! The constant values for the denoising and resampling operations can be set manually but have default values.
            \param dc   Decluttering constant, by default 2.
            \param sc   Resampling constant, by default 4.
        */
        void denoise(const double dc = 2, const double sc = 4);

    private:

        /** Private field containing the coordinates of the points.
        **/
        std::vector<Point> points;

        /** Private field for the weights of the point set.
        **/
        std::vector<double> weights;

        //! Fields used to flag selections in declutter and resampple processes.
        std::vector<bool> selects;
    };

    //! Compute the square of the distance between two points
    /*! Throws an exception if the points have different dimensions.
        \param p    : First point.
        \param q    : Second point.
        \return     : Square of the distance between p and q.
    */
    double squareDist(const Point& p, const Point& q);

    /**
    * Query a random point in a box
    * @param :
    * 	box : box where the query is made
    * 	d : dimension
    * 	@return : query point
    **/
    ANNpoint randomPoint(const std::vector<double>& box,const int d);

    /**
    * Get to the next step of a upplet
    * @param :
    * 	ind : current upplet.
    * 	k : number of elements of upplet.
    * 	n : total number of elements.
    * 	@return : true if there exists a next upplet.
    **/
    bool nextUpplet(int ind[], const int k, const int n);
}

#endif

#define CATCH_CONFIG_MAIN
#include "../src/dtm.h"
#include "catch.hpp"

namespace dtm {

    TEST_CASE("Import export of points") {
        PointSet instance = PointSet("test/test_dtm_in.tio", false);
        REQUIRE(instance.size() == 2);
        REQUIRE(instance.dimension() == 4);
        REQUIRE(instance.get_point(0).size() == 4);
        REQUIRE(instance.get_point(1).size() == 4);
        REQUIRE(instance.get_point(0)[0] == 1.5);
        REQUIRE(instance.get_point(0)[1] == 2);
        REQUIRE(instance.get_point(0)[2] == 2.3);
        REQUIRE(instance.get_point(0)[3] == 4);
        REQUIRE(instance.get_point(1)[0] == 3);
        REQUIRE(instance.get_point(1)[1] == 1);
        REQUIRE(instance.get_point(1)[2] == 2);
        REQUIRE(instance.get_point(1)[3] == 0);
        instance = PointSet("test/test_dtm_in.tio", true);
        REQUIRE(instance.size() == 2);
        REQUIRE(instance.dimension() == 3);
        REQUIRE(instance.get_point(0).size() == 3);
        REQUIRE(instance.get_point(1).size() == 3);
        REQUIRE(instance.get_point(0)[0] == 1.5);
        REQUIRE(instance.get_point(0)[1] == 2);
        REQUIRE(instance.get_point(0)[2] == 2.3);
        REQUIRE(instance.get_weight(0) == 4);
        REQUIRE(instance.get_point(1)[0] == 3);
        REQUIRE(instance.get_point(1)[1] == 1);
        REQUIRE(instance.get_point(1)[2] == 2);
        REQUIRE(instance.get_weight(1) == 0);
        instance.exportPoints("test/test_dtm_out.tio", false);
        PointSet instance2 = PointSet("test/test_dtm_out.tio", true);
        REQUIRE(instance2.size() == 2);
        REQUIRE(instance2.dimension() == 2);
        REQUIRE(instance2.get_point(0).size() == 2);
        REQUIRE(instance2.get_point(1).size() == 2);
        REQUIRE(instance2.get_point(0)[0] == 1.5);
        REQUIRE(instance2.get_point(0)[1] == 2);
        REQUIRE(instance2.get_weight(0) == 2.3);
        REQUIRE(instance2.get_point(1)[0] == 3);
        REQUIRE(instance2.get_point(1)[1] == 1);
        REQUIRE(instance2.get_weight(1) == 2);
        instance.exportPoints("test/test_dtm_out.tio", true);
        instance2 = PointSet("test/test_dtm_out.tio", true);
        REQUIRE(instance2.size() == 2);
        REQUIRE(instance2.dimension() == 3);
        REQUIRE(instance2.get_point(0).size() == 3);
        REQUIRE(instance2.get_point(1).size() == 3);
        REQUIRE(instance2.get_point(0)[0] == 1.5);
        REQUIRE(instance2.get_point(0)[1] == 2);
        REQUIRE(instance2.get_point(0)[2] == 2.3);
        REQUIRE(instance2.get_weight(0) == 4);
        REQUIRE(instance2.get_point(1)[0] == 3);
        REQUIRE(instance2.get_point(1)[1] == 1);
        REQUIRE(instance2.get_point(1)[2] == 2);
        REQUIRE(instance2.get_weight(1) == 0);
    }

    TEST_CASE("Basic operations") {

        SECTION("Enumerating upplets") {
            int instance[4] = {4,5,7,8};
            REQUIRE(nextUpplet(instance,4,10) == true);
            int control[4] = {4,5,7,9};
            REQUIRE(instance[0] == control[0]);
            REQUIRE(instance[1] == control[1]);
            REQUIRE(instance[2] == control[2]);
            REQUIRE(instance[3] == control[3]);
            REQUIRE(nextUpplet(instance,4,10) == true);
            control[2] = 8;
            REQUIRE(instance[0] == control[0]);
            REQUIRE(instance[1] == control[1]);
            REQUIRE(instance[2] == control[2]);
            REQUIRE(instance[3] == control[3]);
            REQUIRE(nextUpplet(instance,4,10) == true);
            control[1] = 6;
            control[2] = 7;
            control[3] = 8;
            REQUIRE(instance[0] == control[0]);
            REQUIRE(instance[1] == control[1]);
            REQUIRE(instance[2] == control[2]);
            REQUIRE(instance[3] == control[3]);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            REQUIRE(nextUpplet(instance,4,10) == true);
            control[0] = 6;
            control[1] = 7;
            control[2] = 8;
            control[3] = 9;
            REQUIRE(instance[0] == control[0]);
            REQUIRE(instance[1] == control[1]);
            REQUIRE(instance[2] == control[2]);
            REQUIRE(instance[3] == control[3]);
            REQUIRE(nextUpplet(instance,4,10) == false);
        }

        SECTION("Random sampling of a point in a box") {
            srand(time(NULL));
            std::vector<double> box;
            box.push_back(-1.5);
            box.push_back(1);
            box.push_back(2);
            box.push_back(1.3);
            ANNpoint p = randomPoint(box, 2);
            REQUIRE(p[0] >= - 1.5);
            REQUIRE(p[0] <= 2);
            REQUIRE(p[1] >= 1);
            REQUIRE(p[1] <= 1.3);
            p = randomPoint(box, 2);
            REQUIRE(p[0] >= - 1.5);
            REQUIRE(p[0] <= 2);
            REQUIRE(p[1] >= 1);
            REQUIRE(p[1] <= 1.3);
            p = randomPoint(box, 2);
            REQUIRE(p[0] >= - 1.5);
            REQUIRE(p[0] <= 2);
            REQUIRE(p[1] >= 1);
            REQUIRE(p[1] <= 1.3);
            p = randomPoint(box, 2);
            REQUIRE(p[0] >= - 1.5);
            REQUIRE(p[0] <= 2);
            REQUIRE(p[1] >= 1);
            REQUIRE(p[1] <= 1.3);
            p = randomPoint(box, 2);
            REQUIRE(p[0] >= - 1.5);
            REQUIRE(p[0] <= 2);
            REQUIRE(p[1] >= 1);
            REQUIRE(p[1] <= 1.3);
        }

        SECTION("Testing if a point is in a point set") {
            PointSet points;
            Point pt(3);
            pt[0] = 1;
            pt[1] = 1;
            pt[2] = 2;
            points.addPoint(pt);
            pt[0] = 1;
            pt[1] = 0;
            pt[2] = 0;
            points.addPoint(pt);
            pt[0] = -1.5;
            pt[1] = -.2;
            pt[2] = 1;
            points.addPoint(pt);

            pt[0] = 1;
            pt[1] = 1;
            pt[2] = 2;
            REQUIRE(points.contains(pt));
            pt[0] = 1;
            pt[1] = 0;
            pt[2] = 1;
            REQUIRE(!points.contains(pt));
            pt[0] = -1.5;
            pt[1] = -.2;
            pt[2] = 1;
            REQUIRE(points.contains(pt));
            pt.resize(2);
            REQUIRE_THROWS(points.contains(pt));
        }

    }

    TEST_CASE("12 points corresponding to the pointed cube figure centered at the origin") {
        PointSet points;
        Point pt(3);
        pt[0] = -1;
        pt[1] = -1;
        pt[2] = -1;
        points.addPoint(pt);
        pt[0] = -1;
        pt[1] = -1;
        pt[2] = 1;
        points.addPoint(pt);
        pt[0] = -1;
        pt[1] = 1;
        pt[2] = -1;
        points.addPoint(pt);
        pt[0] = 1;
        pt[1] = -1;
        pt[2] = -1;
        points.addPoint(pt);
        pt[0] = -1;
        pt[1] = 1;
        pt[2] = 1;
        points.addPoint(pt);
        pt[0] = 1;
        pt[1] = -1;
        pt[2] = 1;
        points.addPoint(pt);
        pt[0] = 1;
        pt[1] = 1;
        pt[2] = -1;
        points.addPoint(pt);
        pt[0] = 1;
        pt[1] = 1;
        pt[2] = 1;
        points.addPoint(pt);
        pt[0] = -1;
        pt[1] = 0;
        pt[2] = 0;
        points.addPoint(pt);
        pt[0] = 1;
        pt[1] = 0;
        pt[2] = 0;
        points.addPoint(pt);
        pt[0] = 0;
        pt[1] = -1;
        pt[2] = 0;
        points.addPoint(pt);
        pt[0] = 0;
        pt[1] = 1;
        pt[2] = 0;
        points.addPoint(pt);

        SECTION("Conversion to an ANN array") {
            ANNpointArray pts = points.toANNArray();
            REQUIRE(pts[0][0] == -1);
            REQUIRE(pts[0][1] == -1);
            REQUIRE(pts[0][2] == -1);
            REQUIRE(pts[1][0] == -1);
            REQUIRE(pts[1][1] == -1);
            REQUIRE(pts[1][2] == 1);
            REQUIRE(pts[2][0] == -1);
            REQUIRE(pts[2][1] == 1);
            REQUIRE(pts[2][2] == -1);
            REQUIRE(pts[3][0] == 1);
            REQUIRE(pts[3][1] == -1);
            REQUIRE(pts[3][2] == -1);
            REQUIRE(pts[4][0] == -1);
            REQUIRE(pts[4][1] == 1);
            REQUIRE(pts[4][2] == 1);
            REQUIRE(pts[5][0] == 1);
            REQUIRE(pts[5][1] == -1);
            REQUIRE(pts[5][2] == 1);
            REQUIRE(pts[6][0] == 1);
            REQUIRE(pts[6][1] == 1);
            REQUIRE(pts[6][2] == -1);
            REQUIRE(pts[7][0] == 1);
            REQUIRE(pts[7][1] == 1);
            REQUIRE(pts[7][2] == 1);
            REQUIRE(pts[8][0] == -1);
            REQUIRE(pts[8][1] == 0);
            REQUIRE(pts[8][2] == 0);
            REQUIRE(pts[9][0] == 1);
            REQUIRE(pts[9][1] == 0);
            REQUIRE(pts[9][2] == 0);
            REQUIRE(pts[10][0] == 0);
            REQUIRE(pts[10][1] == -1);
            REQUIRE(pts[10][2] == 0);
            REQUIRE(pts[11][0] == 0);
            REQUIRE(pts[11][1] == 1);
            REQUIRE(pts[11][2] == 0);
        }

        SECTION("Computation of the bounding box for sampling") {
            std::vector<double> instance = points.samplingBox();
            REQUIRE(instance.size() == 6);
            REQUIRE(instance[0] == Approx(-2));
            REQUIRE(instance[1] == Approx(-2));
            REQUIRE(instance[2] == Approx(-2));
            REQUIRE(instance[3] == Approx(2));
            REQUIRE(instance[4] == Approx(2));
            REQUIRE(instance[5] == Approx(2));
        }

        SECTION("Computation of the square distance between two points") {
            REQUIRE(squareDist(points.get_point(0), points.get_point(1)) == Approx(4));
            REQUIRE(squareDist(points.get_point(10), points.get_point(0)) == Approx(2));
        }

        SECTION("Computation of the energy of a point given a set of indices") {
            int indices[5];
            indices[0] = 0;
            indices[1] = 4;
            indices[2] = 5;
            indices[3] = 10;
            indices[4] = 3;
            REQUIRE(points.cellEnergy(points.get_point(2), 2, indices) == Approx(4));
            REQUIRE(points.cellEnergy(points.get_point(2), 4, indices) == Approx(6.5));
            REQUIRE(points.cellEnergy(points.get_point(2), 5, indices) == Approx(6.8));
        }

        SECTION("Computation of the barycenter of k points") {
            int indices[5];
            indices[0] = 0;
            indices[1] = 4;
            indices[2] = 5;
            indices[3] = 10;
            indices[4] = 3;
            Point instance = points.barycenter(2,indices);
            REQUIRE(instance[0] == Approx(-1));
            REQUIRE(instance[1] == Approx(0));
            REQUIRE(instance[2] == Approx(0));
            instance = points.barycenter(5, indices);
            REQUIRE(instance[0] == Approx(0));
            REQUIRE(instance[1] == Approx(-.6));
            REQUIRE(instance[2] == Approx(0));
        }

        SECTION("Computation of the distance to a measure") {
            PointSet instance = points.witnessingPoints(1);
            REQUIRE(instance.get_point(7)[0] == points.get_point(7)[0]);
            REQUIRE(instance.get_point(7)[1] == points.get_point(7)[1]);
            REQUIRE(instance.get_point(7)[2] == points.get_point(7)[2]);
            REQUIRE(instance.get_weight(7) == Approx(0));
            instance = points.witnessingPoints(2);
            REQUIRE(instance.get_point(7)[0] == points.get_point(7)[0]);
            REQUIRE(instance.get_point(7)[1] == points.get_point(7)[1]);
            REQUIRE(instance.get_point(7)[2] == points.get_point(7)[2]);
            REQUIRE(instance.get_weight(3) == Approx(1));
            REQUIRE(instance.get_weight(7) == Approx(1));
            REQUIRE(instance.get_weight(9) == Approx(1));
            REQUIRE(instance.get_weight(11) == Approx(1));
        }
    }

    TEST_CASE("32 points on a roughly noisy circle as in the presentation") {
        PointSet points;
        Point pt(2);
        pt[0] = 1.62;
        pt[1] = 0.96;
        points.addPoint(pt);
        pt[0] = 1.00;
        pt[1] = 2.30;
        points.addPoint(pt);
        pt[0] = 2.18;
        pt[1] = 0.66;
        points.addPoint(pt);
        pt[0] = 1.00;
        pt[1] = 2.00;
        points.addPoint(pt);
        pt[0] = 3.00;
        pt[1] = 0.54;
        points.addPoint(pt);
        pt[0] = 1.28;
        pt[1] = 1.74;
        points.addPoint(pt);
        pt[0] = 2.66;
        pt[1] = 0.60;
        points.addPoint(pt);
        pt[0] = 0.72;
        pt[1] = 1.42;
        points.addPoint(pt);
        pt[0] = 2.00;
        pt[1] = 1.00;
        points.addPoint(pt);
        pt[0] = 1.06;
        pt[1] = 1.24;
        points.addPoint(pt);
        pt[0] = 1.86;
        pt[1] = 0.64;
        points.addPoint(pt);
        pt[0] = 2.44;
        pt[1] = 2.00;
        points.addPoint(pt);
        pt[0] = 3.36;
        pt[1] = 0.64;
        points.addPoint(pt);
        pt[0] = 3.90;
        pt[1] = 1.84;
        points.addPoint(pt);
        pt[0] = 3.72;
        pt[1] = 0.86;
        points.addPoint(pt);
        pt[0] = 5.68;
        pt[1] = 5.40;
        points.addPoint(pt);
        pt[0] = 4.08;
        pt[1] = 0.60;
        points.addPoint(pt);
        pt[0] = 4.18;
        pt[1] = 1.12;
        points.addPoint(pt);
        pt[0] = 4.64;
        pt[1] = 1.02;
        points.addPoint(pt);
        pt[0] = 4.74;
        pt[1] = 1.74;
        points.addPoint(pt);
        pt[0] = 4.78;
        pt[1] = 2.52;
        points.addPoint(pt);
        pt[0] = 4.58;
        pt[1] = 3.20;
        points.addPoint(pt);
        pt[0] = 4.28;
        pt[1] = 3.90;
        points.addPoint(pt);
        pt[0] = 3.96;
        pt[1] = 4.16;
        points.addPoint(pt);
        pt[0] = 3.70;
        pt[1] = 4.38;
        points.addPoint(pt);
        pt[0] = 2.38;
        pt[1] = 4.28;
        points.addPoint(pt);
        pt[0] = 2.00;
        pt[1] = 4.00;
        points.addPoint(pt);
        pt[0] = 2.90;
        pt[1] = 4.48;
        points.addPoint(pt);
        pt[0] = 1.74;
        pt[1] = 3.44;
        points.addPoint(pt);
        pt[0] = 3.30;
        pt[1] = 4.70;
        points.addPoint(pt);
        pt[0] = 1.34;
        pt[1] = 2.98;
        points.addPoint(pt);
        pt[0] = 1.16;
        pt[1] = 2.64;
        points.addPoint(pt);

        REQUIRE(points.size() == 32);
        REQUIRE(points.dimension() == 2);

        SECTION("Computation of the bounding box for sampling") {
            std::vector<double> instance = points.samplingBox();
            REQUIRE(instance.size() == 4);
            REQUIRE(instance[0] == Approx(-1.76));
            REQUIRE(instance[1] == Approx(-1.89));
            REQUIRE(instance[2] == Approx(8.16));
            REQUIRE(instance[3] == Approx(7.83));
        }

        SECTION("Computation of square distances") {
            REQUIRE(squareDist(points.get_point(0), points.get_point(1)) == Approx(2.18));
            REQUIRE(squareDist(points.get_point(0), points.get_point(2)) == Approx(0.4036));
            Point pt(3);
            REQUIRE_THROWS(squareDist(points.get_point(0),pt));
            REQUIRE_THROWS(squareDist(pt,points.get_point(0)));
        }

        SECTION("Computation of the energy of a point given a set of indices") {
            int indices[5];
            indices[0] = 0;
            indices[1] = 4;
            indices[2] = 5;
            indices[3] = 10;
            indices[4] = 3;
            REQUIRE(points.cellEnergy(points.get_point(2), 5, indices) == Approx(1.27152));
            REQUIRE(points.cellEnergy(points.get_point(30), 5, indices) == Approx(4.24624));
            REQUIRE(points.cellEnergy(points.get_point(19), 5, indices) == Approx(10.06832));
        }

        SECTION("Computation of the barycenter of k points") {
            int indices[5];
            indices[0] = 0;
            indices[1] = 4;
            indices[2] = 5;
            indices[3] = 10;
            indices[4] = 3;
            Point instance = points.barycenter(2, indices);
            REQUIRE(instance[0] == Approx(2.31));
            REQUIRE(instance[1] == Approx(.75));
            instance = points.barycenter(4, indices);
            REQUIRE(instance[0] == Approx(1.94));
            REQUIRE(instance[1] == Approx(.97));
            instance = points.barycenter(5, indices);
            REQUIRE(instance[0] == Approx(1.752));
            REQUIRE(instance[1] == Approx(1.176));
        }

        SECTION("Computation of the distance to a measure for all input points") {
            PointSet instance = points.witnessingPoints(5);
            REQUIRE(instance.get_point(10)[0] == Approx(1.86));
            REQUIRE(instance.get_point(10)[1] == Approx(0.64));
            REQUIRE(instance.get_weight(10) == Approx(sqrt(0.21072)));
            REQUIRE(instance.get_point(17)[0] == Approx(4.18));
            REQUIRE(instance.get_point(17)[1] == Approx(1.12));
            REQUIRE(instance.get_weight(17) == Approx(sqrt(0.2756)));
            REQUIRE(instance.get_point(23)[0] == Approx(3.96));
            REQUIRE(instance.get_point(23)[1] == Approx(4.16));
            REQUIRE(instance.get_weight(23) == Approx(sqrt(0.44784)));
        }

        SECTION("Computation of the witnessed k-distance") {
            PointSet instance = points.witnessedKDistance(5);
            REQUIRE(instance.size() == 27);
            REQUIRE(instance.get_point(10)[0] == Approx(4.236));
            REQUIRE(instance.get_point(10)[1] == Approx(1.316));
            REQUIRE(instance.get_weight(10) == Approx(sqrt(0.317568)));
            REQUIRE(instance.get_point(17)[0] == Approx(4.456));
            REQUIRE(instance.get_point(17)[1] == Approx(2.64));
            REQUIRE(instance.get_weight(17) == Approx(sqrt(0.781344)));
            REQUIRE(instance.get_point(23)[0] == Approx(2.856));
            REQUIRE(instance.get_point(23)[1] == Approx(4.368));
            REQUIRE(instance.get_weight(23) == Approx(sqrt(0.42736)));
        }

        SECTION("Random sampling of the barycenter") {
            PointSet instance = points.samplingBarycentres(5, 125);
            REQUIRE(instance.size() <= 125);
            instance = points.samplingBarycentres(5, 25);
            REQUIRE(instance.size() <= 25);
            REQUIRE(instance.get_point(0)[0] > -1.76);
            REQUIRE(instance.get_point(0)[1] > -1.89);
            REQUIRE(instance.get_point(0)[0] < 8.16);
            REQUIRE(instance.get_point(0)[1] < 7.83);
        }

        SECTION("Computation of the whole set of barycenters for the distance to a measure") {
            PointSet instance = points.exactComputation(5);
            REQUIRE(instance.size() == 201376);
            REQUIRE(instance.get_point(0)[0] == Approx(1.76));
            REQUIRE(instance.get_point(0)[1] == Approx(1.292));
            REQUIRE(instance.get_weight(0) == Approx(sqrt(1.096256)));
            REQUIRE(instance.get_point(27)[0] == Approx(1.392));
            REQUIRE(instance.get_point(27)[1] == Approx(1.712));
            REQUIRE(instance.get_weight(27) == Approx(sqrt(0.799232)));
            REQUIRE(instance.get_point(28)[0] == Approx(1.816));
            REQUIRE(instance.get_point(28)[1] == Approx(1.24));
            REQUIRE(instance.get_weight(28) == Approx(sqrt(0.960864)));
        }

        SECTION("Sorting operation for weighted point sets") {
            points.witnessingPoints(2);
            points.sort();
            REQUIRE(points.get_weight(0) == Approx(0.212132));
            REQUIRE(points.get_weight(3) == Approx(0.226716));
            REQUIRE(points.get_point(9)[0] == Approx(1.16));
            REQUIRE(points.get_point(9)[1] == Approx(2.64));
            REQUIRE(points.get_weight(9) == Approx(0.265707));
        }

        SECTION("Declutter, and eliminate") {
            points.witnessingPoints(2);
            points.declutter();
            points.eliminate();
            REQUIRE(points.size() == 13);
        }

        SECTION("Resampling") {
            points.witnessingPoints(2);
            points.declutter();
            points.resample();
            points.eliminate();
            REQUIRE(points.size() == 30);
        }

        SECTION("Denoise operation of a point set") {
            points.denoise();
            REQUIRE(points.size() == 31);
        }

    }
}

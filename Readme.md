Repository created on June 1st, 2018 by Mickaël Buchet.

The purpose of this repository is to contains releasable versions of various old softwares developed for research.

Testing is done using the catch framework.

Programs included:
 * Computation of the distance to a measure and its approximations.
 * Declutter and resample algorithm for outliers denoising.

Programs to be added in the future:
 * Tools related to the computation of various variants of the rips filtration.
 * Tools related to the computation of weighted alpha shapes.
 * Various miscellaneous tools used to generate data sets.

How to install:
 * Install the ANN library if not already installed on your system (http://www.cs.umd.edu/~mount/ANN/).
 * Modify the Makefile if needed by choosing a compiler and the path to the ANN library.
 * make build

Other building rules:
 * make debug       : Outputs a version of the files with the debugging flags enabled.
 * make dtm         : Only computes the dtm file containing the PointSet class.
 * make test        : Computes the tests files and run the tests.
 * make doc         : Generates the documentation files using doxygen.
 * make clean       : Cleans the binaries, objects and test files.
 * make clean-doc   : Cleans the documentation files.

Detailed instruction for the various programs:

 * dtm:
dtm computes the distance to a measure of a point set or one of its approximations. It requires at least 3 options to be set, the input, output and the value of k.
    Options:
        -i file     : Sets the input file.
        -o file     : Sets the ouput file.
        -k v        : Sets k to be v. k represents the number of nearest neighors.
        -c cmd      : Sets the operation to be performed. If not set the program will output the input point set weighted by their distance to a measure. This corresponds to the witnessing points approximation of the function distance to a measure.
                * e : Computes the exact distance to a measure by computing the energy of all barycenters of k points.
                * s : Samples random points within a bounding box and returns all the barycenters corresponding to the k-order Voronoi cells hit by the sampled points. Requires the sampling size to be set by another option.
                * w : Computes the witnessed k-distance.
                * p : Computes the witnessing points. This is default operation.
        -s v        : Sets the sampling size to v.

examples:
    dtm -i input -k 2 -o output
    dtm -i input -o output -c p -k 2
        - Computes the distance to a measure of every point in input for k=2 and writes the result on output.

    dtm -o output -c s -k 5 -i input -s 500
        - Samples 500 points in a box around the points in input and returns the barycenters and energies of the order 5 Voronoi cells hit by the sampled points.

 * denoise:
 denoise runs the declutter and resampling algorithm for denoising. At least the input and output files must be set.
    Options:
        -i file     : Sets the input file.
        -o file     : Sets the output file.
        -d v        : Sets the decluttering constant to v. The default value is 2.
        -s v        : Sets the resampling constant to s. The default value is 4.

examples:
    denoise -i input -o output
        - Denoise the input using the universal parameter and writes the result in output.

    denoise -i input -o output -d 2 -s 14
        - Denoise the input using overly safe constant (declutter at 2 and resample at 14) guaranteeing that no erosion happens.
 

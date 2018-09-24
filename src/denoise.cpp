/*
 * File: dtm.cpp
 * Author: Mickaël Buchet
 *
 * Created on August 29, 2018
 *
 * Implementation of the declutter-resampling algorithm.
 */

#include "dtm.h"
#include <unistd.h>

using namespace dtm;

int main(int argc,char** argv) {
    PointSet points;        // Input Points
    char* input;            // Input file
    char* output;           // Output file
    double dec = 2;         // Decluterring constant
    double smp = 4;         // Resampling constant

    int copt;
    while ((copt = getopt (argc, argv, "i:o:d:s:")) != -1) {
        switch(copt) {
            case 'i': input = optarg; break;
            case 'o': output = optarg; break;
            case 'd': dec = atof(optarg); break;
            case 's': smp = atof(optarg); break;
        }
    }

    // Checking arguments
    if(input == NULL || output == NULL) throw "Invalid arguments. Both the input and ouput must be set.";

    // Reading input
    points=PointSet(input);
    points.denoise(dec, smp);
    points.exportPoints(output, false);
    return 0;
}

/*
 * File: dtm.cpp
 * Author: Mickaël Buchet
 *
 * Created on June 1, 2018
 *
 * Computation of the distance to a measure from a point cloud. See manual for more details
 */

#include "dtm.h"
#include <unistd.h>

using namespace dtm;

/*
 * Main function
 */

int main(int argc,char** argv) {
    int k = -1;             // Number of nearest neighbors considered
    int op = 3;             // Operation selected
    int samplingSize = -1;  // Number of points to be sampled in case of sampling
    PointSet points;        // Input Points
    char* input = NULL;     // Input file
    char* output = NULL;    // Output file
    PointSet results;       // Resuting point set.

    int copt;
    while ((copt = getopt (argc, argv, "k:i:o:c:ws:")) != -1) {
        switch(copt) {
            case 'k': k = atoi(optarg); break;
            case 'i': input = optarg; break;
            case 'o': output = optarg; break;
            case 'c': switch(optarg[0]) {
                case 'e': op = 0; break;
                case 's': op = 1; break;
                case 'w': op = 2; break;
                case 'p': op = 3; break;
            }
            case 's': samplingSize = atoi(optarg); break;
        }
    }

    // Checking the arguments.
    if(input == NULL || k == -1 || output == NULL) throw "Invalid arguments. At least an input file, an output file and a value for k must be set.";
    if(op == 1 && samplingSize == -1) throw "Invalid arguments. When the sampling operation is selected, the sampling size must also be set.";

    // Reading input
    points=PointSet(input);

    // Doing operations
    switch(op) {
        case 0: results = points.exactComputation(k);
                break;
	    case 1: results = points.samplingBarycentres(k, samplingSize);
                break;
        case 2: results = points.witnessedKDistance(k);
                break;
        case 3: results = points.witnessingPoints(k);
                break;
    }

    results.exportPoints(output, true);
    return 0;
}

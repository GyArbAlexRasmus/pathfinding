
#include "pathfinder.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include "tests.cpp"

namespace tests {
    
    /// Tests a given algorithm
    /// \param algorithm The algorithm to test
    /// \return A TestResults struct containing the results of the test, or null if data was not initialized.
    TestResults RunTest(pathfinder::algorithm algorithm) {
        TestResults results;
        
        std::clock_t start = std::clock();
        algorithm.findWay();
        
        return results;
    }
    
    /// \param results A TestResults struct containing the results of the test
    void PrintResults(TestResults results) {
        printf("Time to find path: %ull\n", results.time_elapsed);
        printf("Edges: %uh\n", results.edges);
        printf("Total distance of path: %f.0\n", results.distance);
    }
    
    /// Initializes data from a .osm.pbf file
    /// \param path The path to the file containing the data
    /// \return A buffer object containing data from the file
    osmium::memory::Buffer Initialize(std::string path) {
        
    }
}
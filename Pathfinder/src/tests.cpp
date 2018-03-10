#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

#include "fileio.hpp"
#include "pathfinder.hpp"
#include "tests.hpp"

namespace pathfinder {
    
    objects::Graph* Tests::graph;
    
    /// Tests a given algorithm
    /// \param alg The algorithm to test
    /// \return A TestResults struct containing the results of the test, or
    /// null if data was not initialized.
    Tests::TestResults Tests::RunTests(Algorithm* alg) {
        TestResults results;

        std::clock_t start = std::clock();
        alg->findWay();

        return results;
    }

    ///Prints the results of a test.
    /// \param results A TestResults struct containing the results of the test
    void Tests::PrintResults(TestResults results) {
        printf("Time to find path: %lu\n", results.time_elapsed);
        printf("Nodes: %u\n", results.nodes);
        printf("Total distance of path: %f.0\n", results.distance);
    }

    /// Initializes data from a .osm.pbf file
    /// \param path The path to the file containing the data
    void Tests::Initialize(std::string path) {
        Tests::graph = new objects::Graph();
        fileio::Reader reader(Tests::graph,
                              path + "/nodes.csv",
                              path + "/edges.csv");
        
        reader.Fill();
    }
}
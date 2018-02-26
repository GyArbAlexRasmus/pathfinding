#include <cstdlib>
#include <iostream>
#include <string>

#include "fileio.hpp"
#include "pathfinder.hpp"
#include "tests.hpp"

namespace pathfinder {
    /// Tests a given algorithm
    /// \param alg The algorithm to test
    /// \return A TestResults struct containing the results of the test, or
    /// null if data was not initialized.
    TestResults Tests::RunTest(pathfinder::algorithm* alg) {
        TestResults results;

        std::clock_t start = std::clock();
        algorithm->findWay();

        return results;
    }

    ///Prints the results of a test.
    /// \param results A TestResults struct containing the results of the test
    void Tests::PrintResults(TestResults results) {
        printf("Time to find path: %ull\n", results.time_elapsed);
        printf("Nodes: %uh\n", results.edges);
        printf("Total distance of path: %f.0\n", results.distance);
    }

    /// Initializes data from a .osm.pbf file
    /// \param path The path to the file containing the data
    void Tests::Initialize(std::string path) {
        graph = new objects::Graph();
        fileio::Reader reader = new fileio::Reader(&graph, path);
        
        reader.Fill();
    }
}
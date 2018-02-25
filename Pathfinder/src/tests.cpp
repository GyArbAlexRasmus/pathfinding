#include <cstdlib>
#include <iostream>
#include <string>

#include "pathfinder.hpp"
#include "tests.hpp"

/*! \file tests.cpp
    \brief Implements the functions in tests.hpp
*/

/// Initializes data from a .osm.pbf file into map
/// \param path The path to the file containing the data
static void pathfinder::tests::Initialize(std::string path) {
    map = new objects::Graph();
    
}

/// Prints the results of a test.
/// \param results A TestResults struct containing the results of the test
static void pathfinder::tests::PrintResults(TestResults results) {
    printf("Time to find path: %ull\n", results.time_elapsed);
    printf("Nodes: %uh\n", results.edges);
    printf("Total distance of path: %f.0\n", results.distance);
}

/// Tests a given algorithm
/// \param alg The algorithm to test
/// \return A TestResults struct containing the results of the test, or null if data was not initialized.
static TestResults pathfinder::tests::RunTest(pathfinder::Algorithm* alg) {
    TestResults results;
    
    std::clock_t start = std::clock();
    algorithm->findWay();

    return results;
}
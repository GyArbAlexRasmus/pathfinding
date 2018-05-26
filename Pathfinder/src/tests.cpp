#include <cstdlib>
#include <iostream>
#include <random>
#include <utility>

#include "algorithm.hpp"
#include "fileio.hpp"
#include "tests.hpp"

namespace pathfinder {
    using namespace objects;
    
    Graph* Tests::graph;

    /// Tests a given algorithm
    /// \param alg The algorithm to test
    /// \return A TestResults struct containing the results of the test, or
    /// null if data was not initialized.
    Tests::TestResults Tests::RunTests(algorithms::Algorithm* alg,
                                       id_t src,
                                       id_t target) {

        TestResults results = pathfinder::Tests::TestResults();
        try {
            printf("Testing algorithm \"%s\" from node %lu to node %lu\n",
                   alg->GetName().c_str(), src, target);

            clock_t start = std::clock();
            auto path = alg->FindWay(src, target);
            clock_t stop = std::clock();

            results.name = alg->GetName();
            results.time_elapsed = (stop - start) * 1000.0 / CLOCKS_PER_SEC;
            results.nodes = path.Size();
            results.cost = path.GetCost();
            results.found = path.IsConnected();
        } catch (std::logic_error& e) {
            results.name = alg->GetName();
            results.found = false;
        }

        return results;
    }
    
    /// Prints some diagnostics data, including the number of loaded nodes and
    /// edges.
    void Tests::PrintDiagnostics() {
        
        printf("Nodes in graph: %lu\n", graph->CountNodes());
        printf("Edges in graph: %lu\n", graph->CountEdges());
    }
    
    ///Prints the results of a test.
    /// \param results A TestResults struct containing the results of the test
    void Tests::PrintResults(TestResults results) {
        if(results.found) {
            printf("\n\n-------------------- Results --------------------\n");
            printf("Algorithm: %s\n", results.name.c_str());
            printf("Time to find path: %lums\n", results.time_elapsed);
            printf("Nodes: %lu\n", results.nodes);
            printf("Total cost of path: %f\n", results.cost);
            printf("-------------------------------------------------");
        } else {
            printf("\n\nNo path found for algorithm %s\n", results.name.c_str());
        }
    }

    /// Initializes data from a .osm.pbf file
    /// \param path The path to the file containing the data
    void Tests::Initialize(std::string path) {
        Tests::graph = new Graph();
        fileio::Reader reader(Tests::graph,
                              path + "/nodes.csv",
                              path + "/edges.csv");
        
        reader.Fill();
    }

    void Tests::DeInitialize() {
        delete graph;
    }
}
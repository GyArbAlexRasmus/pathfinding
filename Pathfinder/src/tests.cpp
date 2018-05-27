#include <cstdlib>
#include <iostream>
#include <random>
#include <utility>
#include <assert.h>

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
    void Tests::RunTests(algorithms::Algorithm* alg, id_t src, id_t target) {
        try {
            printf("Testing algorithm \"%s\" from node %lu to node %lu\n",
                   alg->GetName().c_str(), src, target);

            auto path = alg->FindWay(src, target);

            assert(path.IsConnected());
            assert(path.Top() == target);
            assert(path.FirstNode() == src);
        } catch (std::logic_error& e) {
            std::cout << "No path found.\n";
        }
    }
    
    /// Prints some diagnostics data, including the number of loaded nodes and
    /// edges.
    void Tests::PrintDiagnostics() {
        
        printf("Nodes in graph: %lu\n", graph->CountNodes());
        printf("Edges in graph: %lu\n", graph->CountEdges());
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
#ifndef TESTS_HPP
#define TESTS_HPP

#include <chrono>
#include <string>
#include <vector>

#include "algorithm.hpp"
#include "node.hpp"

namespace pathfinder {
    class Tests {
    public:
        /// \struct TestResults
        /// \brief Contains the results of a test.
        struct TestResults {
            std::string name; ///< Algorithm name
            uint64_t time_elapsed; ///< Time elapsed while finding path
            size_t nodes; ///< number of nodes in path
            objects::cost_t cost; ///< Total distance for path
            bool found; ///< Whether the algorithm found a path
        };
        
        static objects::Graph* graph; ///< Contains the map data.

        static TestResults RunTests(algorithms::Algorithm* alg,
                                    objects::id_t src,
                                    objects::id_t target);

        static void PrintDiagnostics();
        static void PrintResults(TestResults results);
        static void Initialize(std::string path);
        static void DeInitialize();
    };
}
#endif /* TESTS_HPP */
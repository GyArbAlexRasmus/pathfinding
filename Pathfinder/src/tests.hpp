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
            uint64_t time_elapsed; ///< Time elapsed while finding path
            uint32_t nodes; ///< number of nodes in path
            objects::cost_t distance; ///< Total distance for path
        };
        
        static objects::Graph* graph; ///< Contains the map data.
        
        static TestResults RunTests(pathfinder::Algorithm* alg);
        static void PrintDiagnostics();
        static void PrintResults(TestResults results);
        static void Initialize(std::string path);
    };
}
#endif /* TESTS_HPP */
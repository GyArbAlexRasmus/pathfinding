#ifndef TESTS_HPP

#define TESTS_HPP

#include <chrono>

#include "pathfinder.hpp"

namespace pathfinder {
    namespace tests {
        
        static objects::Graph graph; ///< Contains the map data.
        
        /// \struct TestResults
        /// \brief Contains the results of a test.
        struct TestResults {
            uint64_t time_elapsed; ///< Time elapsed while finding path
            uint32_t nodes; ///< number of nodes in path
            double distance; ///< Total distance for path
        };
        
        TestResults RunTests(pathfinder::Algorithm* alg);
        void PrintResults(TestResults results);
    }
}
#endif /* TESTS_HPP */
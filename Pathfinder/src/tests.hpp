#ifndef TESTS_HPP

#define TESTS_HPP

#include <chrono>

#include "pathfinder.hpp"
/*! \file tests.hpp
    \brief Contains the definitions necessary to test algorithms.
*/

/// \namespace pathfinder
/// \brief Contains most of the program.
namespace pathfinder {
    
    /// \namespace pathfinder::tests
    /// \brief Contains test logic.
    namespace tests {
        
        static objects::Graph map; ///< This contains all the information about the map.
        
        /// \struct TestResults
        /// \brief Contains the results of a test.
        struct TestResults {
            uint64_t time_elapsed; ///< Time elapsed while finding path
            uint32_t nodes; ///< number of nodes in path
            double distance; ///< Total distance for path
        };
        
        static void Initialize(std::string path);
        static TestResults PrintResults(TestResults results);
        static void RunTests(pathfinder::Algorithm* alg);
        
    }
}
#endif /* TESTS_HPP */
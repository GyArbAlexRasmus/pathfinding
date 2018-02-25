#ifndef TESTS_HPP

#define TESTS_HPP

#include <chrono>

#include "pathfinder.hpp"

namespace pathfinder {
    namespace tests {
        
        ///\struct Contains the results of a test
        struct TestResults {
            uint64_t time_elapsed;
            uint32_t nodes;
            double distance;
        };
        
        TestResults RunTests(pathfinder::algorithm alg);
        void PrintResults(TestResults results);
    }
}
#endif /* TESTS_HPP */
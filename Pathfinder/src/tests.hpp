#ifndef TESTS_H

#define TESTS_H

#include <chrono>
#include <osmium/memory/buffer.hpp>

namespace tests {
    
    ///\struct Contains the results of a test
    struct TestResults {
        uint64_t time_elapsed;
        uint16_t edges;
        double distance;
    };
    
    TestResults RunTests();
    void PrintResults(TestResults results);
    osmium::memory::Buffer Initialize();
    
}

#endif /* TESTS_H */


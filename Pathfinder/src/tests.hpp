#ifndef TESTS_HPP
#define TESTS_HPP

#include <chrono>
#include <string>
#include <vector>

#include "algorithm.hpp"
#include "node.hpp"

namespace pathfinder {
    using namespace objects;
    
    class Tests {
    public:
        static Graph* graph; ///< Contains the map data.

        static void RunTests(algorithms::Algorithm* alg, id_t src, id_t target);

        static void PrintDiagnostics();
        static void Initialize(std::string path);
        static void DeInitialize();
    };
}
#endif /* TESTS_HPP */
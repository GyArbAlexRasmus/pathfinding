#include "algorithm.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;

        Algorithm::Algorithm(Graph* g, std::string name) : collection(name) {
            graph = g;
            this->name = name;
        }

        std::string Algorithm::GetName() {
            return name;
        }
    }
}
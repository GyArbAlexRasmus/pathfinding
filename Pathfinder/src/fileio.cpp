#include "fileio.hpp"

namespace pathfinder {
    namespace fileio {
        Reader::Reader(objects::Graph* graph) {
            this->graph = graph;
        }
    }
}
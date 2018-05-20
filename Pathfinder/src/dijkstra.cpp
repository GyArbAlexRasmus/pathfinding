#include "dijkstra.hpp"

namespace pathfinder {
    namespace algorithms {
        objects::cost_t Dijkstra::Heuristic(objects::id_t src,
                                  objects::id_t target) {
            return 0; // Dijkstra's algorithm is a special case of A* where
                      // the heuristic always returns 0
        }

        Dijkstra::Dijkstra(objects::Graph *g) : AStar(g) { }

        std::string Dijkstra::GetName() {
            return "Dijkstra's Algorithm";
        }
    }
}
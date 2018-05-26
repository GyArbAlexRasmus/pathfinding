#include "dijkstra.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;

        cost_t Dijkstra::Heuristic(id_t src,
                                   id_t target) {
            return 0; // Dijkstra's algorithm is a special case of A* where
                      // the heuristic always returns 0
        }

        Dijkstra::Dijkstra(Graph *g) : AStar(g) { }

        std::string Dijkstra::GetName() {
            return "Dijkstra's Algorithm";
        }
    }
}
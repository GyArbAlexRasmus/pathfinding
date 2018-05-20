#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "astar.hpp"

namespace pathfinder {
    namespace algorithms {
        class Dijkstra : public AStar {
        protected:
            objects::cost_t Heuristic(objects::id_t src,
                                      objects::id_t target);
        public:
            Dijkstra(objects::Graph* g);

            std::string GetName();
        };
    }
}
#endif /* DIJKSTRA_HPP */

#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "astar.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;
        
        class Dijkstra : public AStar {
        protected:
            cost_t Heuristic(id_t src,
                             id_t target);
        public:
            Dijkstra(Graph* g);

            std::string GetName();
        };
    }
}
#endif /* DIJKSTRA_HPP */

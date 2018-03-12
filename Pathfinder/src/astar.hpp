#ifndef ASTAR_HPP
#define ASTAR_HPP

namespace pathfinder {
    namespace algorithms {
        class AStar : public Algorithm {
        private:
            // The nodes which have already been checked
            std::vector<objects::id_t> closedSet;

            // The set of discovered nodes that have not been checked.
            std::vector<objects::id_t> openSet;

            // Contains the node from which a given node is best reached
            std::map<objects::id_t, objects::id_t> bestReachedFrom;

            // The lowest cost to get to a given node from src
            std::map<objects::id_t, objects::cost_t> costToMap;

            // The cost to get from the given node to the end
            std::map<objects::id_t, objects::cost_t> costFromMap;

            objects::cost_t GetCostFrom(objects::id_t target);
            objects::cost_t GetCostTo(objects::id_t target);
            objects::id_t GetCheapestNodeInOpenSet();
            bool IsInClosedSet(objects::id_t);
            bool IsInOpenSet(objects::id_t);
            objects::cost_t Heuristic(objects::id_t src, objects::id_t target);
            objects::Path ReconstructPath(objects::id_t src, objects::id_t target);

        public:
            AStar(objects::Graph* g);

            std::string GetName();
            objects::Path FindWay(objects::id_t src,
                                  objects::id_t target);
        };
    }
}
#endif /* ASTAR_HPP */
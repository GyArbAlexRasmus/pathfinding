#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <map>
#include <vector>

#include "path.hpp"

namespace pathfinder {
    namespace algorithms {
        /// \class Algorithm
        /// \brief Describes a pathfinding algorithm.
        class Algorithm {
        protected:
            objects::Graph* graph;
        public:
            virtual std::string GetName() = 0;

            Algorithm(objects::Graph* g);

            /// Find a path between two nodes on a graph
            /// \param src The source node ID
            /// \param target The target node ID
            /// \param graph A pointer to the graph on which the algorithm
            /// should attempt to find a path
            /// \return A Path object describing a path between two nodes
            virtual objects::Path FindWay(objects::id_t src,
                                          objects::id_t target) = 0;
        };

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

#endif /* ALGORITHM_HPP */
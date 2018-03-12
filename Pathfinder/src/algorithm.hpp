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


    }
}

#endif /* ALGORITHM_HPP */
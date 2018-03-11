#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "path.hpp"

namespace pathfinder {
    namespace algorithms {
        /// \class Algorithm
        /// \brief Describes a pathfinding algorithm.
        class Algorithm {
        public:
            /// Find a path between two nodes
            /// \return A Path object describing a path between two nodes
            virtual objects::Path FindWay(id_t src, id_t target) = 0;
        };

        class AStar : Algorithm {
        private:
            objects::cost_t Heuristic(id_t src, id_t target);
        public:
            objects::Path FindWay(id_t src, id_t target);
        };
    }
}

#endif /* ALGORITHM_HPP */
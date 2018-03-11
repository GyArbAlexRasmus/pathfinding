#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "path.hpp"

namespace pathfinder {
    /// \class Algorithm
    /// \brief Describes a pathfinding algorithm.
    class Algorithm {
    public:
        /// Find a path between two nodes
        /// \return A Path object describing a path between two nodes
        virtual objects::Path FindWay(id_t src, id_t target) = 0;
    };
}

#endif /* ALGORITHM_HPP */
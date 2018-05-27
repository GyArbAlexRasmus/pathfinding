#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <map>
#include <vector>

#include "path.hpp"
#include "statistics.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;
        
        /// \class Algorithm
        /// \brief Describes a pathfinding algorithm.
        class Algorithm {
        protected:
            Graph* graph;
            std::string name;
        public:
            StatisticsCollection collection;


            Algorithm(Graph* g, std::string name);


            /// Find a path between two nodes on a graph
            /// \param src The source node ID
            /// \param target The target node ID
            /// \param graph A pointer to the graph on which the algorithm
            /// should attempt to find a path
            /// \return A Path object describing a path between two nodes
            virtual Path FindWay(id_t src,
                                 id_t target) = 0;

            std::string GetName();
        };


    }
}

#endif /* ALGORITHM_HPP */
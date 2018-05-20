#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>

#include "node.hpp"

namespace pathfinder {
    namespace objects {
        /// \class Graph
        /// \brief Describes a graph.
        class Graph {
        private:
            typedef std::unordered_map<id_t, Node*> nmap_t;
            nmap_t nodemap; ///< Contains all nodes in the graph

        public:
            Graph();
            ~Graph();

            void AddNode(Node& node);
            void AddEdge(id_t src, id_t target, cost_t cost);

            uint64_t CountEdges();
            uint64_t CountNodes();

            Node* GetNode(id_t id);
            cost_t GetCost(id_t src, id_t target);

            bool HasNode(id_t id);

            id_t RandomID();

            void RemoveNode(id_t id);
            void RemoveEdge(id_t src, id_t target);

        };
    }
}


#endif /* GRAPH_HPP */
#include <algorithm>
#include <boost/format.hpp>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <stack>

#include "graph.hpp"

namespace pathfinder {
    namespace objects {

        /// Constructs a graph.
        Graph::Graph() :
                nodemap() {
        }

        Graph::~Graph() {
            for(std::pair<id_t, objects::Node*> pair : nodemap) {
                delete pair.second;
            }
        }

        /// Adds a node
        /// \param node A reference to the node to add.
        void Graph::AddNode(Node& node) {
            // If nodemap does not contain a node with the same id
            if (nodemap.find(node.id) == nodemap.end()) {
                nodemap[node.id] = &node;
            } else {
                std::cout << "Node with ID " << node.id << " already exists!";
            }
        }

        /// Adds an edge from from_id to to_id with the given cost
        /// \param from_id Source node ID
        /// \param to_id Target node ID
        /// \param cost The cost of the edge
        void Graph::AddEdge(id_t from_id, id_t to_id, cost_t cost) {
            Node* from_node = nodemap.find(from_id)->second;
            Node* to_node = nodemap.find(to_id)->second;

            objects::edge edge = std::make_pair(cost, to_node);

            from_node->adjacent.push_back(edge);
        }

        /// Counts the number of edges in the graph
        /// \return The number of edges in the graph.
        uint64_t Graph::CountEdges() {
            uint64_t count = 0;
            for (std::pair<id_t, objects::Node*> pair : nodemap) {
                count += pair.second->adjacent.size();
            }

            return count;
        }

        /// Counts the number of nodes in the graph
        /// \return The number of nodes in the graph.
        uint64_t Graph::CountNodes() {
            return nodemap.size();
        }

        /// Gets a pointer to a node with a certain ID
        /// \param id The node to find
        /// \return A pointer to the Node with the given ID, or NULL if there
        /// is no such node.
        Node* Graph::GetNode(id_t id) {
            auto node_iter = nodemap.find(id);
            return node_iter != nodemap.end() ? node_iter->second : NULL;
        }

        /// Gets the cost of the edge between two nodes
        /// \param src Source node ID
        /// \param target Target node ID
        /// \return The cost of the cheapest edge between src and target, or
        /// INFINITY if there is no such edge.
        cost_t Graph::GetCost(id_t src, id_t target) {
            Node* src_n = GetNode(src);

            if(src_n == nullptr)
                return INFINITY;

            auto iter = src_n->adjacent.begin();
            auto end  = src_n->adjacent.end();
            cost_t cheapest = INFINITY;
            // Iterates through every edge for the src node
            for (; iter != end; iter++) {
                if (iter->second->id == target && iter->first < cheapest)
                    cheapest = iter->first;
            }

            return cheapest;
        }

        /// Checks if the graph has a node with a certain ID
        /// \param id ID of node to look for
        /// \return True if graph has a node with given ID; otherwise false
        bool Graph::HasNode(id_t id) {
            return GetNode(id) != nullptr;
        }

        /// Gets the ID of a random node in the graph.
        /// \return The ID of a random node in the graph.
        id_t Graph::RandomID() {
            // It Works™
            return (*std::next(std::begin(nodemap), rand() % nodemap.size())).first;
        }

        /// Removes the node with the given ID.
        /// \param id The ID of the node to remove
        void Graph::RemoveNode(id_t id) {
            // Return if nodemap does not contain a node with that id
            if (nodemap.find(id) == nodemap.end())
                return;

            nodemap.erase(id);

            // Make sure all edges are cleaned up
            auto iter = nodemap.begin();
            auto end = nodemap.end();

            for (; iter != end; iter++) {
                Node* node = iter->second;
                auto iterAdj = node->adjacent.begin();
                auto endAdj  = node->adjacent.end();

                // Iterates through every edge for the current node
                for (; iterAdj != endAdj; iterAdj++) {
                    if (iter->second->id == id)
                        node->adjacent.erase(iterAdj);
                }
            }
        }

        /// Removes all edges between src and target
        /// \param src Source node ID
        /// \param target Target node ID
        void Graph::RemoveEdge(id_t src, id_t target) {
            // Return if nodemap does not contain a node with given id
            if (nodemap.find(src) == nodemap.end() ||
                nodemap.find(target) == nodemap.end())
                return;

            Node* src_n = nodemap.find(src)->second;
            auto iter = src_n->adjacent.begin();
            auto end  = src_n->adjacent.end();

            // Iterates through every edge for the src node
            for (; iter != end; iter++) {
                if (iter->second->id == target)
                    src_n->adjacent.erase(iter);
            }
        }

    }
}
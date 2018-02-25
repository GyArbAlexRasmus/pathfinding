#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>

#include "pathfinder.hpp"

namespace pathfinder {
    namespace objects {
        
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
        /// \param from_id
        /// \param to_id
        /// \param cost
        void Graph::AddEdge(id_t from_id, id_t to_id, cost_t cost) {
            Node* from_node = nodemap.find(from_id)->second;
            Node* to_node = nodemap.find(to_id)->second;
            
            objects::edge edge = std::make_pair(cost, to_node);
            
            from_node->adjacent.push_back(edge);
        }
        
        /// Removes the node with the given ID.
        /// \param id
        void Graph::RemoveNode(id_t id) {
            // Return if nodemap does not contain a node with that id 
            if (nodemap.find(id) == nodemap.end()) 
                return;
            
            nodemap.erase(id);
            
            // Iterates through every Node* in nodemap
            for (Node* node : nodemap) {
                auto iter = node->adjacent.begin();
                auto end  = node->adjacent.end();
                
                // Iterates through every edge for the current node
                for (; iter != end; iter++) {
                    if (iter->second->id == id) 
                        node->adjacent.erase(iter);
                }
            }
        }
        
        /// Removes all edges between src and target
        /// \param src The source node ID
        /// \param target The target node ID
        void Graph::RemoveEdge(id_t src, id_t target) {
            // Return if nodemap does not contain a node with given id
            if (nodemap.find(src) == nodemap.end() ||
                nodemap.find(target) == nodemap.end()) 
                return;
            
            auto iter = nodemap.find(src)->adjacent.begin();
            auto end  = nodemap.find(src)->adjacent.end();

            // Iterates through every edge for the src node
            for (; iter != end; iter++) {
                if (iter->second->id == target) 
                    src->adjacent.erase(iter);
            }
        }
        
        /// \param id The node to find
        /// \return A pointer to the Node with the given ID
        Node* Graph::GetNode(id_t id) {
            auto node_iter = nodemap.find(id);
            return node_iter != nodemap.end ? &(*node_iter) : NULL;
        }
        
        /// \param src Source node ID
        /// \param target Target node ID
        /// \return The cost of the cheapest edge between src and target, or
        /// NULL if there is no such edge.
        cost_t Graph::GetCost(id_t src, id_t target) {
            Node* src_n = GetNode(src);
            
            if(src_n == NULL)
                return INFINITY;
            
            auto iter = src_n->adjacent.begin();
            auto end  = src_n->adjacent.end();

            // Iterates through every edge for the src node
            for (; iter != end; iter++) {
                if (iter->second->id == target) 
                    return iter->first;
            }
            
            return INFINITY;
        }
    }
}
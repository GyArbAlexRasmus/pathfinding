#include <algorithm>
#include <iostream>
#include <vector>

#include "pathfinder.hpp"

namespace pathfinder {
    namespace objects {
        void Graph::AddNode(Node& node) {
            // If nodemap does not contain a node with the same id
            if (nodemap.find(node.id) == nodemap.end()) { 
                nodemap[node.id] = &node;
            } else {
                std::cout << "Node with ID " << node.id << " already exists!";
            }
        }
        
        void Graph::AddEdge(uint64_t from_id, uint64_t to_id, double cost) {
            Node* from_node = nodemap.find(from_id)->second;
            Node* to_node = nodemap.find(to_id)->second;
            
            objects::edge edge = std::make_pair(cost, to_node);
            
            from_node->adjacent.push_back(edge);
        }
        
        void Graph::RemoveNode(uint64_t id) {
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
        
        void Graph::RemoveEdge(uint64_t src, uint64_t target) {
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
    }
}
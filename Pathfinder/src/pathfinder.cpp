#include <algorithm>
#include <boost/format.hpp>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <utility>
#include <stack>
#include <stdexcept>

#include "pathfinder.hpp"

namespace pathfinder {
    namespace objects {
        
        /// Constructs a graph.
        Graph::Graph() :
            nodemap() {
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

        uint64_t Graph::CountEdges() {
            uint64_t count;
            for (std::pair<id_t, objects::Node*> pair : nodemap) {
                count += pair.second->adjacent.size();
            }
            
            return count;
        }

        uint64_t Graph::CountNodes() {
            return nodemap.size();
        }
        
        /// \param id The node to find
        /// \return A pointer to the Node with the given ID, or NULL if there
        /// is no such node.
        Node* Graph::GetNode(id_t id) {
            auto node_iter = nodemap.find(id);
            return node_iter != nodemap.end() ? node_iter->second : NULL;
        }
        
        /// \param src Source node ID
        /// \param target Target node ID
        /// \return The cost of the cheapest edge between src and target, or
        /// INFINITY if there is no such edge.
        cost_t Graph::GetCost(id_t src, id_t target) {
            Node* src_n = GetNode(src);
            
            if(src_n == NULL)
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
        
        /// \param id ID of node to look for
        /// \return True if graph has a node with given ID; otherwise false
        bool Graph::HasNode(id_t id) {
            return this->GetNode(id) != NULL;
        }

        /// Removes the node with the given ID.
        /// \param id The ID of the node to remove
        void Graph::RemoveNode(id_t id) {
            // Return if nodemap does not contain a node with that id 
            if (nodemap.find(id) == nodemap.end()) 
                return;
            
            nodemap.erase(id);
            
            // Iterates through every Node* in nodemap
            
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
        
        Path::Path(Graph* graph) :
            nodes() {
            this->graph = graph;
        }
        
        bool Path::IsConnected() {
            for(int i = 0; i < Size() - 1; i++) {
                
                // We found a missing link, return false
                if(graph->GetCost(nodes[i], nodes[i + 1]) == INFINITY)
                    return false;
            }
            
            return true;
        }

        objects::cost_t Path::GetCost() {
            cost_t cost = 0;
            
            for(int i = 0; i < Size() - 1; i++) {
                cost_t newCost = graph->GetCost(nodes[i], nodes[i + 1]);
                
                // We found a missing link
                if(newCost == INFINITY)
                    return cost;
                
                cost += newCost;
            }
            
            return cost;
        }

        void Path::Pop() {
            nodes.pop_back();
        }
        
        void Path::Push(id_t id) {
            if(!graph->HasNode(id))
                throw std::logic_error("Path::Push: No node with given ID");
            
            if(graph->GetCost(Top(), id) == INFINITY) 
                throw std::logic_error("Path::Push: No edge between nodes");
            
            nodes.push_back(id);
        }
        
        id_t Path::Top() {
            return nodes[nodes.size() - 1];
        }
        
        size_t Path::Size() {
            return nodes.size();
        }
    }
}
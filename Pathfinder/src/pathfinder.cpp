#include <algorithm>
#include <boost/format.hpp>
#include <iostream>
#include <map>
#include <cmath>
#include <stack>

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
            return this->GetNode(id) != nullptr;
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

        /// \param graph A pointer to the \c Graph on which to build the path
        Path::Path(Graph* graph) :
            nodes() {
            this->graph = graph;
        }

        /// Checks if the path is fully connected
        /// \return True if the path is fully connected, otherwise false
        bool Path::IsConnected() {
            for(int i = 0; i < Size() - 1; i++) {
                
                // We found a missing link, return false
                if(graph->GetCost(nodes[i], nodes[i + 1]) == INFINITY)
                    return false;
            }
            
            return true;
        }

        /// Gets the total cost of the path
        /// \return The total cost of the path
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

        /// Removes the last node from the path
        void Path::Pop() {
            nodes.pop_back();
        }

        /// Adds a node to the path
        /// \param id The ID of a node to add
        /// \throws std::logic_error if there is no node with the given ID or
        /// if there's no valid edge between the current top node and the given
        /// node
        void Path::Push(id_t id) {
            if(!graph->HasNode(id))
                throw std::logic_error("Path::Push: No node with given ID");
            
            if(graph->GetCost(Top(), id) == INFINITY) 
                throw std::logic_error("Path::Push: No edge between nodes");
            
            nodes.push_back(id);
        }

        /// Gets the top node ID
        /// \return The ID of the top node
        id_t Path::Top() {
            return nodes[nodes.size() - 1];
        }

        /// Gets the total number of nodes in the path
        /// \return The number of nodes in the path
        size_t Path::Size() {
            return nodes.size();
        }
    }
}
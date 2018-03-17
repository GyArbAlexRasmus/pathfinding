#include <boost/format.hpp>
#include <cmath>

#include "graph.hpp"
#include "tests.hpp"

namespace pathfinder {
    namespace objects {
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
            objects::cost_t cost = 0;

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

            if (Size() > 0) {
                if(graph->GetCost(Top(), id) == INFINITY)
                    throw std::logic_error("Path::Push: No edge between nodes");
            }

            nodes.push_back(id);
        }

        /// Gets the top node ID
        /// \return The ID of the top node
        objects::id_t Path::Top() {
            return nodes[nodes.size() - 1];
        }

        /// Gets the total number of nodes in the path
        /// \return The number of nodes in the path
        size_t Path::Size() {
            return nodes.size();
        }
    }
}
#include <algorithm>
#include <cmath>

#include "algorithm.hpp"
#include "astar.hpp"
#include "math.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;

        cost_t AStar::Heuristic(id_t src,
                                id_t target) {
            return HeuristicFunction(*(graph->GetNode(src)),
                                     *(graph->GetNode(target)));
        }

        inline cost_t AStar::GetCostTo(id_t target) {
            return costTo[target];
        }

        bool AStar::IsInClosedSet(id_t id) {
            return closedSet[id];
        }

        inline bool AStar::IsInOpenSet(id_t id) {
            return GetCostTo(id) != INFINITY;
        }

        Path AStar::ReconstructPath(id_t src,
                                    id_t target) {
            Path path = Path(graph);
            std::vector<id_t> nodes;

            // Build nodes vector
            id_t current = target;
            do {
                nodes.push_back(current);
                current = bestReachedFrom[current];
            } while(current != src);

            nodes.push_back(current); // Make sure to get src, too

            std::reverse(nodes.begin(), nodes.end());

            for(id_t node : nodes) {
                path.Push(node);
            }

            return path;
        }

        void AStar::Reset() {
            uint64_t count = graph->CountNodes();

            closedSet.clear();
            closedSet.resize(count);

            openSet.clear();

            bestReachedFrom.clear();
            bestReachedFrom.resize(count);

            costTo.clear();
            costTo.resize(count, INFINITY);
        }

        std::string AStar::GetName() {
            return "A*";
        }

        Path AStar::FindWay(id_t src,
                            id_t target) {
            Reset();
            // Initially, src is the only discovered node.
            openSet.push(src, 0);

            // Cost to src is 0.
            costTo[src] = 0;

            while(!openSet.empty()) {
                // Get the top node
                id_t current = openSet.get();

                if(current == target)
                    return ReconstructPath(src, target);

                // Add current node to closed set
                closedSet[current] = true;

                // For every neighbor of current node
                for(edge edge : graph->GetNode(current)->adjacent) {
                    id_t neighbor = edge.second->id;
                    if(IsInClosedSet(neighbor))
                        continue; // Already evaluated the current edge.

                    auto tentative_cost = GetCostTo(current) + edge.first;

                    // If we found a new node or new best path, save it
                    if(!IsInOpenSet(neighbor) ||
                       tentative_cost < costTo[neighbor]) {
                        cost_t costFrom = tentative_cost +
                                Heuristic(neighbor, target);

                        costTo[neighbor] = tentative_cost;
                        openSet.push(neighbor, costFrom);
                        bestReachedFrom[neighbor] = current;
                    }
                }
            }

            throw std::logic_error("No path found");
        }

        AStar::AStar(Graph* g) : Algorithm(g) {
            HeuristicFunction = math::Haversine;
        }


        AStar::AStar(Graph* g,
                     cost_t (*heuristic)(const Node&,
                                         const Node&))
                     : Algorithm(g) {
            HeuristicFunction = heuristic;
        }
    }
}

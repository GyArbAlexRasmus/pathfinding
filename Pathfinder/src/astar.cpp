#include <algorithm>
#include <cmath>

#include "algorithm.hpp"
#include "astar.hpp"
#include "math.hpp"

namespace pathfinder {
    namespace algorithms {

        objects::cost_t AStar::Heuristic(objects::id_t src, objects::id_t target) {
            return pathfinder::math::Haversine(*(graph->GetNode(src)),
                                               *(graph->GetNode(target)));
        }

        inline objects::cost_t AStar::GetCostTo(objects::id_t target) {
            return costToMap.find(target) != costToMap.end() ?
                   costToMap[target] :
                   INFINITY;
        }

        bool AStar::IsInClosedSet(objects::id_t id) {
            for(objects::id_t current : closedSet) {
                if(current == id)
                    return true;
            }

            return false;
        }

        inline bool AStar::IsInOpenSet(objects::id_t id) {
            return costToMap.find(id) != costToMap.end();
        }

        objects::Path AStar::ReconstructPath(objects::id_t src, objects::id_t target) {
            objects::Path path = objects::Path(graph);
            std::vector<objects::id_t> nodes;

            // Build nodes vector
            objects::id_t current = target;
            do {
                nodes.push_back(current);
                current = bestReachedFrom[current];
            } while(current != src);

            nodes.push_back(current); // Make sure to get src, too

            std::reverse(nodes.begin(), nodes.end());

            for(objects::id_t node : nodes) {
                path.Push(node);
            }

            return path;
        }

        std::string AStar::GetName() {
            return "A*";
        }

        objects::Path AStar::FindWay(objects::id_t src,
                                     objects::id_t target) {

            // Initially, src is the only discovered node.
            openSet.push(src, 0);

            // Cost to src is 0.
            costToMap[src] = 0;

            while(!openSet.empty()) {
                // Get the top node
                objects::id_t current = openSet.get();

                if(current == target)
                    return ReconstructPath(src, target);

                // Add current node to closed set
                closedSet.push_back(current);

                // For every neighbor of current node
                for(objects::edge edge : graph->GetNode(current)->adjacent) {
                    objects::id_t neighbor = edge.second->id;
                    if(IsInClosedSet(neighbor))
                        continue; // Already evaluated the current edge.

                    auto tentative_cost = GetCostTo(current) + edge.first;

                    // If we found a new node or new best path, save it
                    if(!IsInOpenSet(neighbor) ||
                       tentative_cost < costToMap[neighbor]) {
                        objects::cost_t costFrom = tentative_cost +
                                Heuristic(neighbor, target);

                        costToMap[neighbor] = tentative_cost;
                        openSet.push(neighbor, costFrom);
                        bestReachedFrom[neighbor] = current;
                    }
                }
            }

            throw std::logic_error("No path found");
        }

        AStar::AStar(objects::Graph* g) : Algorithm(g) { }
    }
}

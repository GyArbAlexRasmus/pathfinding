

#include <algorithm>
#include <cmath>

#include "algorithm.hpp"
#include "math.hpp"

namespace pathfinder {
    namespace algorithms {

        objects::cost_t AStar::Heuristic(objects::id_t src, objects::id_t target) {
            return pathfinder::math::Haversine(*(graph->GetNode(src)),
                                               *(graph->GetNode(target)));
        }

        inline objects::cost_t AStar::GetCostFrom(objects::id_t target) {
            return costFromMap.find(target) != costFromMap.end() ?
                   costFromMap[target] :
                   INFINITY;
        }

        inline objects::cost_t AStar::GetCostTo(objects::id_t target) {
            return costToMap.find(target) != costToMap.end() ?
                   costToMap[target] :
                   INFINITY;
        }

        objects::id_t AStar::GetCheapestNodeInOpenSet() {
            objects::id_t cheapest;
            objects::cost_t cost = INFINITY;

            for(objects::id_t node : openSet) {
                if(GetCostFrom(node) < cost) {
                    cheapest = node;
                    cost = GetCostFrom(node);
                }
            }

            return cheapest;
        }

        bool AStar::IsInClosedSet(objects::id_t id) {
            for(objects::id_t current : closedSet) {
                if(current == id)
                    return true;
            }

            return false;
        }

        bool AStar::IsInOpenSet(objects::id_t id) {
            for(objects::id_t current : openSet) {
                if(current == id)
                    return true;
            }

            return false;
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
            openSet.push_back(src);

            // Cost to src is 0.
            costToMap[src] = 0;

            // Cost from src is entirely heuristic.
            costFromMap[src] = Heuristic(src, target);

            while(!openSet.empty()) {
                objects::id_t current = GetCheapestNodeInOpenSet();

                if(current == target)
                    return ReconstructPath(src, target);

                // Remove current node from open set
                for(auto iter = openSet.begin(); iter < openSet.end(); iter++) {
                    if(*iter == current)
                        openSet.erase(iter);
                }

                // Add current node to closed set
                closedSet.push_back(current);

                // For every neighbor of current node
                for(objects::edge edge: graph->GetNode(current)->adjacent) {
                    objects::id_t neighbor = edge.second->id;
                    if(IsInClosedSet(neighbor))
                        continue; // Already evaluated the current edge.

                    // Found a new node
                    if(!IsInOpenSet(neighbor))
                        openSet.push_back(neighbor);

                    auto tentative_cost = GetCostTo(current) + edge.first;

                    if(tentative_cost >= GetCostTo(neighbor))
                        continue; // Path is not better

                    // Path is the best yet, record it
                    bestReachedFrom[neighbor] = current;
                    costToMap[neighbor] = tentative_cost;
                    costFromMap[neighbor] =
                            tentative_cost + Heuristic(neighbor, target);
                }
            }
        }

        AStar::AStar(objects::Graph* g) : Algorithm(g) { }
    }
}

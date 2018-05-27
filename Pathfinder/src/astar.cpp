#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>

#include "algorithm.hpp"
#include "astar.hpp"
#include "math.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;

        cost_t AStar::Heuristic(id_t src,
                                id_t target) {
            hCalls++;
            return HeuristicFunction(*(graph->GetNode(src)),
                                     *(graph->GetNode(target)));
        }


        void AStar::AddStatistics() {
            collection.AddStatistic("nodes_expanded");
            collection.AddStatistic("nodes_visited");
            collection.AddStatistic("iterations");
            collection.AddStatistic("heuristic_calls");
            collection.AddStatistic("path_length");
            collection.AddStatistic("path_nodes");
            collection.AddStatistic("run_time");
        }

        Path AStar::FinishSearch(id_t src, id_t target) {
            clock_t stopTime = std::clock();
            double run_time = (stopTime - startTime) * 1000.0 / CLOCKS_PER_SEC;

            Path path = ReconstructPath(src, target);

            collection.AddValue("nodes_expanded", nodesExpanded);
            collection.AddValue("nodes_visited", nodesVisited);
            collection.AddValue("iterations", iteration);
            collection.AddValue("heuristic_calls", hCalls);
            collection.AddValue("path_length", path.GetCost());
            collection.AddValue("path_nodes", path.NodeCount());
            collection.AddValue("run_time", run_time);

            return path;
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
            hCalls = 0;
            iteration = 0;
            nodesExpanded = 0;
            nodesVisited = 0;
            uint64_t count = graph->CountNodes();

            closedSet.clear();
            closedSet.resize(count);

            openSet.clear();

            bestReachedFrom.clear();
            bestReachedFrom.resize(count);

            costTo.clear();
            costTo.resize(count, INFINITY);
        }

        Path AStar::FindWay(id_t src,
                            id_t target) {
            Reset();

            startTime = std::clock();
            // Initially, src is the only discovered node.
            openSet.push(src, 0);

            // Cost to src is 0.
            costTo[src] = 0;

            while(!openSet.empty()) {
                iteration++;
                // Get the top node
                id_t current = openSet.get();

                nodesVisited++;

                if(current == target) {
                    return FinishSearch(src, target);
                }

                nodesExpanded++;

                // Add current node to closed set
                closedSet[current] = true;


                // For every neighbor of current node
                for(edge edge : graph->GetNode(current)->adjacent) {
                    id_t neighbor = edge.second->id;
                    if(IsInClosedSet(neighbor)){
                        continue; // Already evaluated the current edge.
                    }

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

        AStar::AStar(Graph* g, std::string name)
                : Algorithm(g, name) {
            HeuristicFunction = math::Haversine;

            AddStatistics();
        }


        AStar::AStar(Graph* g,
                     cost_t (*heuristic)(const Node&,
                                         const Node&))
                     : Algorithm(g, "AStar") {
            HeuristicFunction = heuristic;

            AddStatistics();
        }
    }
}

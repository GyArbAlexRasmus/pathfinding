#include <algorithm>
#include <list>
#include <cmath>
#include <assert.h>
#include <iostream>
#include <ctime>

#include "fringe.hpp"
#include "math.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;

        void FringeSearch::AddCache(id_t id, cost_t g,
                                    uint64_t iter, id_t parent) {
            CacheEntry& entry = GetFromCache(id);
            entry.g = g;
            if(!hasCache[id]) {
                entry.h = Heuristic(id, target);
            }
            entry.iteration = iter;
            entry.parent = parent;

            hasCache[id] = true;
        }

        bool FringeSearch::CheckCache(id_t id, cost_t g, uint64_t iter) {
            if(!HasCache(id)) {
                return false;
            }

            CacheEntry& entry = GetFromCache(id);
            cost_t cachedG = entry.g;
            if(g > cachedG) {
                return true;
            }

            // If the node has the same g, but the cache is outdated,
            // it should be updated.
            return g == cachedG && iter == entry.iteration;
        }

        FringeSearch::CacheEntry& FringeSearch::GetFromCache(id_t id) {
            cacheFetches++;
            return cache[id];
        }

        void FringeSearch::GetFromCache(id_t id, cost_t& g, cost_t& h,
                                        id_t& parent) {
            CacheEntry& entry = GetFromCache(id);

            g = entry.g;
            h = entry.h;
            parent = entry.parent;
        }

        bool FringeSearch::HasCache(id_t id) {
            return hasCache[id];
        }

        cost_t FringeSearch::Heuristic(id_t src,
                                       id_t target) {
            hCalls++;
            return heuristicFunction(*(graph->GetNode(src)),
                                     *(graph->GetNode(target)));
        }

        void FringeSearch::Init() {

            uint64_t count = graph->CountNodes();

            cacheFetches = 0;
            hCalls = 0;
            nodesExpanded = 0;
            nodesVisited = 0;

            fringe.Init(count);

            cache.clear();
            cache.resize(count);

            hasCache.clear();
            hasCache.resize(count);
        }

        Path FringeSearch::ReconstructPath(id_t src, id_t target) {
            Path path = Path(graph);
            std::vector<id_t> nodes;

            // Build nodes vector
            id_t current = target;
            do {
                nodes.push_back(current);
                current = GetFromCache(current).parent;
            } while(current != src);

            nodes.push_back(current); // Make sure to get src, too

            std::reverse(nodes.begin(), nodes.end());

            for(id_t node : nodes) {
                path.Push(node);
            }

            return path;
        }

        FringeSearch::FringeSearch(Graph* g,
                                   cost_t (*heuristic)(const Node&, const Node&))
                : Algorithm(g, "FringeSearch") {
            heuristicFunction = heuristic;
            collection.AddStatistic("nodes_expanded");
            collection.AddStatistic("nodes_visited");
            collection.AddStatistic("iterations");
            collection.AddStatistic("heuristic_calls");
            collection.AddStatistic("cache_fetches");
            collection.AddStatistic("path_length");
            collection.AddStatistic("path_nodes");
            collection.AddStatistic("run_time");
        }

        void FringeSearch::Iterate(uint64_t iteration, cost_t fLimit,
                                   cost_t &fMin) {
            fringe.StartIteration();
            while(true) {
                id_t n_id = fringe.GetCurrentNode();
                if(n_id == NO_NODE) {
                    return;
                }

                nodesVisited++;

                cost_t g, h;
                id_t parent;
                GetFromCache(n_id, g, h, parent); // (g, parent) <- C[n]

                if(n_id == target) { // Found the target
                    return;
                }

                cost_t f = g + h; // f <- g + h(n)

                if(f > fLimit) {
                    if(f < fMin) { // fMin = min(f, fLimit)
                        fMin = f;
                    }
                    fringe.NextNode();
                    continue;
                }

                // iterate over s : successors(n) from right to left
                auto edges = graph->GetNode(n_id)->adjacent;
                for(uint64_t i = edges.size(); i--; ) {
                    const edge edge = edges[i];
                    id_t successorId = edge.second->id;
                    cost_t successorG = g + edge.first;

                    // If cache already contains a better g-value for target
                    // node, check next node
                    if(CheckCache(successorId, successorG, iteration))
                        continue;

                    fringe.InsertNode(successorId);
                    AddCache(successorId, successorG, iteration, n_id);
                    nodesExpanded++;
                }

                fringe.RemoveCurrentNode(); // Remove n from F
                fringe.NextNode();
            }
        }

        Path FringeSearch::FindWay(id_t src, id_t target) {
            Init();

            clock_t start = std::clock();

            this->target = target;

            uint64_t iteration = 1;
            // The maximum cost for the current iteration
            cost_t fLimit = Heuristic(src, target);

            fringe.InsertNode(src);
            AddCache(src, 0, 0, NO_NODE);
            while(!HasCache(target)) {
                cost_t fMin = INFINITY;
                Iterate(iteration, fLimit, fMin);
                fLimit = fMin;
                assert(iteration != UINT64_MAX);
                iteration++;
                if(fringe.IsEmpty()) {
                    throw std::logic_error("No path found!");
                }
            }

            Path path = ReconstructPath(src, target);

            clock_t stop = std::clock();

            double run_time = (stop - start) * 1000.0 / CLOCKS_PER_SEC;

            collection.AddValue("nodes_expanded", nodesExpanded);
            collection.AddValue("nodes_visited", nodesVisited);
            collection.AddValue("iterations", iteration);
            collection.AddValue("heuristic_calls", hCalls);
            collection.AddValue("cache_fetches", cacheFetches);
            collection.AddValue("path_length", path.GetCost());
            collection.AddValue("path_nodes", path.NodeCount());
            collection.AddValue("run_time", run_time);

            return path;
        }
    }
}
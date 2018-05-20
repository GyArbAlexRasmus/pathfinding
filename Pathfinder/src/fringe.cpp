#include <algorithm>
#include <list>
#include <cmath>
#include <assert.h>
#include <climits>

#include "fringe.hpp"
#include "fringelist.hpp"
#include "math.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;
        cost_t FringeSearch::Heuristic(id_t src,
                                       id_t target) {
            return math::Haversine(*graph->GetNode(src),
                                   *graph->GetNode(target));
        }

        void FringeSearch::AddCache(id_t id, cost_t g, uint64_t iter, id_t parent) {
            CacheEntry& entry = GetFromCache(id);
            entry.g = g;
            entry.iteration = iter;
            entry.parent = parent;
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

            // If the node has the same g, but the cache is outdated, proceed
            return g == cachedG && iter == entry.iteration;
        }

        FringeSearch::CacheEntry& FringeSearch::GetFromCache(id_t id) {
            auto i = cacheTable.find(id);
            uint64_t cacheId;
            if(i == cacheTable.end()) {
                cacheId = currentCacheEntry++;
                cacheTable[id] = cacheId;
            } else {
                cacheId = i->second;
            }

            return cache[cacheId];
        }

        void FringeSearch::GetFromCache(id_t id, cost_t& g, id_t& parent) {
            CacheEntry& entry = GetFromCache(id);

            g = entry.g;
            parent = entry.parent;
        }

        bool FringeSearch::HasCache(id_t id) {
            auto iter = cacheTable.find(id);
            return iter != cacheTable.end();
        }

        void FringeSearch::Init() {
            fringe.Init(graph->CountNodes());
            cache.resize(graph->CountNodes());
            cacheTable.clear();
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

        FringeSearch::FringeSearch(Graph* g) : Algorithm(g) { }

        void FringeSearch::Iterate(uint64_t iteration, cost_t fLimit, cost_t &fMin,
                                   id_t target) {
            fringe.StartIteration();
            while(true) {
                id_t n_id = fringe.GetCurrentNode();
                if(n_id == NO_NODE) {
                    return;
                }

                cost_t g;
                id_t parent;
                GetFromCache(n_id, g, parent); // (g, parent) <- C[n]

                if(n_id == target) { // Found the target
                    return;
                }

                cost_t f = g + Heuristic(n_id, target); // f <- g + h(n)

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
                }

                fringe.RemoveCurrentNode(); // Remove n from F
                fringe.NextNode();
            }
        }

        Path FringeSearch::FindWay(id_t src, id_t target) {
            Init();

            uint64_t iteration = 1;
            // The maximum cost for the current iteration
            cost_t fLimit = Heuristic(src, target);

            fringe.InsertNode(src);
            AddCache(src, 0, 0, NO_NODE);
            while(!HasCache(target)) {
                cost_t fMin = INFINITY;
                Iterate(iteration, fLimit, fMin, target);
                fLimit = fMin;
                assert(iteration != UINT64_MAX);
                iteration++;
            }

            Path path = ReconstructPath(src, target);
            return path;
        }

        std::string FringeSearch::GetName() {
            return "Fringe Search";
        }
    }
}
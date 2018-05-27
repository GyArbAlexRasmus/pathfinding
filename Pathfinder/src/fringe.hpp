#ifndef FRINGE_HPP
#define FRINGE_HPP

#include "algorithm.hpp"
#include "fringelist.hpp"
#include "graph.hpp"

#define NO_NODE UINT64_MAX

namespace pathfinder {
    namespace algorithms {
        using namespace objects;

        class FringeSearch : public Algorithm {
        private:
            struct CacheEntry {
                cost_t g;
                cost_t h;
                uint64_t iteration;
                id_t parent;
            };
            FringeList fringe;
            std::vector<CacheEntry> cache;
            std::vector<bool> hasCache;
            cost_t (*heuristicFunction)(const Node& node1, const Node& node2);
            id_t target = NO_NODE;

            uint64_t cacheFetches = 0;
            uint64_t hCalls = 0;
            uint64_t nodesExpanded = 0;
            uint64_t nodesVisited = 0;

            void AddCache(id_t id, cost_t g,
                          uint64_t iter, id_t parent);
            bool CheckCache(id_t id, cost_t g, uint64_t iter);
            CacheEntry& GetFromCache(id_t id);
            void GetFromCache(id_t id, cost_t& g, cost_t& h, id_t& parent);
            bool HasCache(id_t id);
            objects::cost_t Heuristic(id_t src, id_t target);
            void Init();
            void Iterate(uint64_t iteration, cost_t fLimit, cost_t& fMin);
            Path ReconstructPath(id_t src, id_t target);


        protected:

        public:
            FringeSearch(Graph* g,
                         cost_t (*heuristic)(const Node&, const Node&));
            Path FindWay(id_t src, id_t target);
        };
    }
}

#endif /* FRINGE_HPP */
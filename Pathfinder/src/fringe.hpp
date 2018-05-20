#ifndef FRINGE_HPP
#define FRINGE_HPP

#include "algorithm.hpp"
#include "fringelist.hpp"
#include "graph.hpp"

#define NO_NODE 0

namespace pathfinder {
    namespace algorithms {
        using namespace objects;
        class FringeSearch : public Algorithm {
        private:
            struct CacheEntry {
                cost_t g;
                uint64_t iteration;
                id_t parent;
            };
            FringeList fringe;
            std::vector<CacheEntry> cache;
            std::vector<bool> hasCache;

            void AddCache(id_t id, cost_t g, uint64_t iter, id_t parent);
            bool CheckCache(id_t id, cost_t g, uint64_t iter);
            CacheEntry& GetFromCache(id_t id);
            void GetFromCache(id_t id, cost_t& g, id_t& parent);
            bool HasCache(id_t id);
            void Init();
            void Iterate(uint64_t iteration, cost_t fLimit, cost_t& fMin,
                         id_t target);
            Path ReconstructPath(id_t src, id_t target);
        protected:
            cost_t Heuristic(id_t src, id_t target);

        public:
            FringeSearch(Graph* g);
            Path FindWay(id_t src, id_t target);
            std::string GetName();
        };
    }
}

#endif /* FRINGE_HPP */
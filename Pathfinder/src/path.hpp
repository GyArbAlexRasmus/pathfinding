#ifndef PATH_HPP
#define PATH_HPP

#include "graph.hpp"

namespace pathfinder {
    namespace objects {
        using namespace objects;

        /// \class Path
        /// \brief Describes a path.
        struct Path {
        private:
            std::vector<id_t> nodes;
            Graph* graph;
        public:
            explicit Path(Graph* graph);

            id_t FirstNode();
            cost_t GetCost();
            bool IsConnected();
            size_t NodeCount();
            void Pop();
            void Push(id_t id);
            id_t Top();
        };
    }
}

#endif /* PATH_HPP */
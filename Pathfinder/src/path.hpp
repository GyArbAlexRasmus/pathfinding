#ifndef PATH_HPP
#define PATH_HPP

#include "graph.hpp"

namespace pathfinder {
    namespace objects {
        /// \class Path
        /// \brief Describes a path.
        struct Path {
        private:
            std::vector<id_t> nodes;
            Graph* graph;
        public:
            Path(Graph* graph);

            bool IsConnected();
            cost_t GetCost();
            void Pop();
            void Push(id_t id);
            id_t Top();
            size_t Size();
        };
    }
}

#endif /* PATH_HPP */
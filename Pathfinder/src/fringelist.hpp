#ifndef FRINGELIST_HPP
#define FRINGELIST_HPP

#include "node.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;
        class FringeList {
        public:
            FringeList();
            id_t GetCurrentNode();
            void Init(uint64_t count);
            void InsertNode(id_t id);
            void NextNode();
            void RemoveCurrentNode() {
                RemoveNode(currentNode);
            }
            void StartIteration();

        private:

            class ListMember {
            public:
                id_t next, previous;
            };

            id_t currentNode;
            id_t head;

            std::vector<bool> isInList;
            std::vector<ListMember> nodes;

            ListMember& GetNode(id_t id) {
                assert(id < nodes.size());
                return nodes[id];
            }

            void RemoveNode(id_t id);
        };
    }
}
#endif //FRINGELIST_HPP

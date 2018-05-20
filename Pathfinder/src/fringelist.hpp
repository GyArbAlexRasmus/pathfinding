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
                id_t id;
                uint64_t next, previous;
            };

            uint64_t currentNode;
            uint64_t head;
            uint64_t nodeCount;
            uint64_t internalCount;

            std::vector<bool> isInList;
            std::vector<ListMember> nodes;
            std::map<id_t, uint64_t> translationTable;

            ListMember& GetNode(uint64_t id) {
                return nodes[id];
            }

            uint64_t ExternalToInternalID(id_t id);
            void RemoveNode(uint64_t id);
        };
    }
}
#endif //FRINGELIST_HPP

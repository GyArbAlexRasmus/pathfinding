//
// Created by rasmus on 2018-05-15.
//

#include <assert.h>
#include "fringe.hpp"

namespace pathfinder {
    namespace algorithms {
        FringeList::FringeList() {
            nodeCount = 0;
            internalCount = 1;
        }

        id_t FringeList::GetCurrentNode() {
            if(!isInList[currentNode])
                return NO_NODE;

            return GetNode(currentNode).id;
        }
        void FringeList::Init(uint64_t count) {
            nodes.resize(count);
            translationTable.clear();
            isInList.clear();
            isInList.resize(count, false);
            nodeCount = count;
            currentNode = NO_NODE;
            head = NO_NODE;
            internalCount = 1;
        }

        void FringeList::InsertNode(id_t id) {
            uint64_t nodeId = ExternalToInternalID(id);
            if(isInList[nodeId]) {
                RemoveNode(nodeId);
            }

            isInList[nodeId] = true;

            ListMember& newNode = GetNode(nodeId);

            if(head != NO_NODE) {
                ListMember& current = GetNode(currentNode);
                uint64_t next = current.next;
                newNode.previous = currentNode;
                newNode.next = next;
                if(next != NO_NODE) {
                    GetNode(next).previous = nodeId;
                }

                current.next = nodeId;
            }
        }

        uint64_t FringeList::ExternalToInternalID(id_t id) {
            auto iter = translationTable.find(id);

            if(iter == translationTable.end()) {
                translationTable[id] = internalCount;
                return internalCount++;
            }

            return iter->second;
        }

        void FringeList::NextNode() {
            assert(currentNode != NO_NODE);
            currentNode = GetNode(currentNode).next;
            assert(currentNode == NO_NODE || isInList[currentNode]);
        }

        void FringeList::StartIteration() {
            currentNode = head;
        }

        void FringeList::RemoveNode(uint64_t id) {
            assert(id != NO_NODE);
            assert(isInList[id]);

            ListMember& node = GetNode(id);
            uint64_t previous = node.previous;
            uint64_t next = node.next;

            if(previous != NO_NODE) {
                GetNode(id).next = next;
            } else {
                head = next;
            }

            if(next != NO_NODE) {
                GetNode(id).previous = previous;
            }

            isInList[id] = false;
        }
    }
}

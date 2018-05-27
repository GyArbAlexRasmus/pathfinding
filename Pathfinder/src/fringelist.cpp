//
// Created by rasmus on 2018-05-15.
//

#include <assert.h>
#include <iostream>
#include "fringe.hpp"

namespace pathfinder {
    namespace algorithms {
        FringeList::FringeList() : isInList() {
            currentNode = NO_NODE;
            head = NO_NODE;
        }

        id_t FringeList::GetCurrentNode() {
            return currentNode;
        }

        void FringeList::Init(uint64_t count) {
            nodes.clear();
            nodes.resize(count);

            isInList.clear();
            isInList.resize(count, false);

            currentNode = NO_NODE;
            head = NO_NODE;
        }

        void FringeList::InsertNode(id_t id) {
            if(isInList[id]) {
                RemoveNode(id);
            }

            isInList[id] = true;

            ListMember& newNode = GetNode(id);

            // List already has nodes
            if(head != NO_NODE) {
                ListMember& current = GetNode(currentNode);
                id_t next = current.next;
                newNode.previous = currentNode;
                newNode.next = next;
                if(next != NO_NODE) {
                    GetNode(next).previous = id;
                }

                current.next = id;
            } else {
                head = id;
                newNode.previous = NO_NODE;
                newNode.next = NO_NODE;
            }
        }

        bool FringeList::IsEmpty() {
            return head == NO_NODE;
        }

        void FringeList::NextNode() {
            assert(currentNode != NO_NODE);
            currentNode = GetNode(currentNode).next;
            assert(currentNode == NO_NODE || isInList[currentNode]);
        }

        void FringeList::StartIteration() {
            currentNode = head;
        }

        void FringeList::RemoveNode(id_t id) {
            assert(id != NO_NODE);
            assert(isInList[id]);

            ListMember& node = GetNode(id);
            id_t previous = node.previous;
            id_t next = node.next;

            if(previous != NO_NODE) {
                GetNode(previous).next = next;
            } else {
                head = next;
            }

            if(next != NO_NODE) {
                GetNode(next).previous = previous;
            }

            isInList[id] = false;
        }
    }
}

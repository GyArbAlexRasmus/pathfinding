#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <queue>

#include "algorithm.hpp"
#include "graph.hpp"
#include "node.hpp"

namespace pathfinder {
    namespace algorithms {
        class AStar : public Algorithm {
        private:
            struct CustomPrioQueue {
                typedef std::pair<objects::id_t, objects::cost_t> pair;

                struct comp {
                    bool operator()(const pair a, const pair b) {
                        return a.second > b.second;
                    }
                };

                std::priority_queue<pair, std::vector<pair>, comp> prioqueue;

                inline bool empty() {
                    return prioqueue.empty();
                }

                void clear()  {
                    prioqueue = std::priority_queue<pair,
                                                    std::vector<pair>,
                                                    comp>();
                }

                inline objects::id_t get() {
                    objects::id_t id = top();
                    pop();

                    return id;
                }

                inline objects::id_t top() {
                    return prioqueue.top().first;
                }

                inline void pop() {
                    prioqueue.pop();
                }

                inline void push(objects::id_t id, objects::cost_t cost) {
                    pair p(id, cost);
                    prioqueue.push(p);
                }
            };

            // The nodes which have already been checked
            std::vector<bool> closedSet;

            // The set of discovered nodes that have not been checked.
            CustomPrioQueue openSet;

            // Contains the node from which a given node is best reached
            std::vector<objects::id_t> bestReachedFrom;

            // The lowest cost to get to a given node from src
            std::vector<objects::cost_t> costTo;

            // A function pointer to the heuristic
            objects::cost_t (*HeuristicFunction)(const objects::Node& node1,
                                                 const objects::Node& node2);

            objects::cost_t GetCostTo(objects::id_t target);
            bool IsInClosedSet(objects::id_t);
            bool IsInOpenSet(objects::id_t);
            objects::Path ReconstructPath(objects::id_t src,
                                          objects::id_t target);
            void Reset();
        protected:

            virtual objects::cost_t Heuristic(objects::id_t src,
                                              objects::id_t target);
        public:
            AStar(objects::Graph* g);
            AStar(objects::Graph* g,
                  objects::cost_t (*heuristic)(const objects::Node&,
                                               const objects::Node&));

            std::string GetName();
            objects::Path FindWay(objects::id_t src,
                                  objects::id_t target);
        };
    }
}
#endif /* ASTAR_HPP */
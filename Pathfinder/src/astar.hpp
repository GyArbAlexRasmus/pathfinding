#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <queue>

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
            std::vector<objects::id_t> closedSet;

            // The set of discovered nodes that have not been checked.
            CustomPrioQueue openSet;

            // Contains the node from which a given node is best reached
            std::map<objects::id_t, objects::id_t> bestReachedFrom;

            // The lowest cost to get to a given node from src
            std::map<objects::id_t, objects::cost_t> costToMap;

            objects::cost_t GetCostTo(objects::id_t target);
            bool IsInClosedSet(objects::id_t);
            bool IsInOpenSet(objects::id_t);
            objects::cost_t Heuristic(objects::id_t src, objects::id_t target);
            objects::Path ReconstructPath(objects::id_t src, objects::id_t target);

        public:
            AStar(objects::Graph* g);

            std::string GetName();
            objects::Path FindWay(objects::id_t src,
                                  objects::id_t target);
        };
    }
}
#endif /* ASTAR_HPP */
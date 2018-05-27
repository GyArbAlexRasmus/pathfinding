#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <queue>

#include "algorithm.hpp"
#include "graph.hpp"
#include "node.hpp"

namespace pathfinder {
    namespace algorithms {
        using namespace objects;
        
        class AStar : public Algorithm {
        private:
            struct CustomPrioQueue {
                typedef std::pair<id_t, cost_t> pair;

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

                inline id_t get() {
                    id_t id = top();
                    pop();

                    return id;
                }

                inline id_t top() {
                    return prioqueue.top().first;
                }

                inline void pop() {
                    prioqueue.pop();
                }

                inline void push(id_t id, cost_t cost) {
                    pair p(id, cost);
                    prioqueue.push(p);
                }
            };

            // The nodes which have already been checked
            std::vector<bool> closedSet;

            // The set of discovered nodes that have not been checked.
            CustomPrioQueue openSet;

            // Contains the node from which a given node is best reached
            std::vector<id_t> bestReachedFrom;

            // The lowest cost to get to a given node from src
            std::vector<cost_t> costTo;

            uint64_t hCalls = 0;
            uint64_t iteration = 0;
            uint64_t nodesExpanded = 0;
            uint64_t nodesVisited = 0;
            clock_t startTime;

            // A function pointer to the heuristic
            cost_t (*HeuristicFunction)(const Node& node1,
                                        const Node& node2);

            void AddStatistics();
            Path FinishSearch(id_t src, id_t target);
            cost_t GetCostTo(id_t target);
            bool IsInClosedSet(id_t);
            bool IsInOpenSet(id_t);
            Path ReconstructPath(id_t src,
                                 id_t target);
            void Reset();

        protected:
            AStar(Graph* g, std::string name);
            virtual cost_t Heuristic(id_t src, id_t target);
        public:
            AStar(Graph* g,
                  cost_t (*heuristic)(const Node&,
                                      const Node&));

            Path FindWay(id_t src,
                         id_t target);
        };
    }
}
#endif /* ASTAR_HPP */
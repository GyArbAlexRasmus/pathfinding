#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <map>
#include <stack>
#include <utility>
#include <vector>

namespace pathfinder {
    namespace objects {
        struct Node;
        typedef uint64_t id_t; ///< A node ID.
        typedef double cost_t; ///< The cost of an edge.
        typedef std::pair<cost_t, Node*> edge; ///< An edge.
        
        /// \struct Node
        /// \brief A node.
        struct Node {
            std::vector<edge> adjacent; ///< Contains all edges connected to the node
            id_t id; ///< The node's ID
            double lat; ///< Node location latitude
            double lon; ///< Node location longitude
        };
        
        /// \class Graph
        /// \brief Describes a graph.
        class Graph {
        public:
            Graph();
            typedef std::map<id_t, Node*> nmap_t;
            
            void AddNode(Node& node);
            void AddEdge(id_t src, id_t target, cost_t cost);
            
            uint64_t CountEdges();
            uint64_t CountNodes();
            
            Node* GetNode(id_t id);
            cost_t GetCost(id_t src, id_t target);
            
            bool HasNode(id_t id);
            
            void RemoveNode(id_t id);
            void RemoveEdge(id_t src, id_t target);
            
        private:
            nmap_t nodemap; ///< Contains all nodes in the graph
        
        };
        
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
    
    /// \class Algorithm
    /// \brief Describes a pathfinding algorithm.
    class Algorithm {
        public:
            /// \return 
            virtual objects::Path findWay() = 0;
    };
}


#endif /* PATHFINDER_HPP */
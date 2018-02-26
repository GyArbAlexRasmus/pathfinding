#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

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
            nmap_t nodemap; ///< Contains all nodes in the graph
            
            void AddNode(Node& node);
            void AddEdge(id_t src, id_t target, cost_t cost);
            
            void RemoveNode(id_t id);
            void RemoveEdge(id_t src, id_t target);
            
            Node* GetNode(id_t id);
            cost_t GetCost(id_t src, id_t target);
        };
        
        /// \class Path 
        /// \brief Describes a path.
        class Path {
        public:
            
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
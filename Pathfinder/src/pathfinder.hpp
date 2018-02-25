#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

namespace pathfinder {
    namespace objects {
        struct Node;
        typedef uint64_t id_t;
        typedef double cost_t;
        typedef std::pair<cost_t, Node*> edge; // Cost, target
        
        struct Node {
            std::vector<edge> adjacent;
            id_t id;
            double lon;
            double lat;
        };
        
        class Graph {
        public:
            typedef std::map<id_t, Node*> nmap_t;
            nmap_t nodemap;
            
            void AddNode(Node& node);
            void AddEdge(id_t src, id_t target, cost_t cost);
            
            void RemoveNode(id_t id);
            void RemoveEdge(id_t src, id_t target);
            
            Node* GetNode(id_t id);
            cost_t GetCost(id_t src, id_t target);
        };
        
        // TODO
        class Path {
        public:
            
        };
    }
    class algorithm {
        public:
            /// \return 
            virtual objects::Path findWay() = 0;
    };
}


#endif /* PATHFINDER_HPP */
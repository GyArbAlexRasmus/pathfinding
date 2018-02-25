#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

namespace pathfinder {
    namespace objects {
        
        typedef std::pair<double, Node*> edge; // Cost, target
        
        struct Node {
            std::vector<edge> adjacent;
            uint64_t id;
            double lon;
            double lat;
        };
        
        class Graph {
        public:
            typedef std::map<uint64_t, Node*> nmap_t;
            nmap_t nodemap;
            void AddNode(Node& node);
            void AddEdge(uint64_t src, uint64_t target, double cost);
            void RemoveNode(uint64_t id);
            void RemoveEdge(uint64_t src, uint64_t target);
        };
        
        class Path : public std::stack<id_t, std::vector> {
        public:
            
        };
    }
    class algorithm {
        public:
            /// \return 
            objects::Path findWay() = 0;
    };
}


#endif /* PATHFINDER_HPP */
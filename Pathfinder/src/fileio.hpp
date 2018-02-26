#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "pathfinder.hpp"

namespace pathfinder {
    namespace fileio {
        
        /// \struct IOEdge
        /// \brief A temporary container used to hold data about an edge
        struct IOEdge {
            objects::id_t src_id;
            objects::id_t target_id;
            objects::cost_t cost;
            bool accessible_fwd;
            bool accessible_bwd;
        };
        
        class Reader {
        public:
            Reader(objects::Graph* graph);
            void Fill();
        private:
            std::ifstream nodefile;
            std::ifstream edgefile;
            objects::Graph* graph;
            objects::Node* ReadNode();
            IOEdge* ReadEdge();
            std::vector<std::string> ReadValues(std::ifstream& stream);
        };
        
    }
}

#endif /* FILEIO_HPP */


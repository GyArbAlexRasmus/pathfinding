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
            bool accessible;
        };
        
        class Reader {
        public:
            Reader(objects::Graph* graph);
            void Fill();
        private:
            objects::Graph* graph;
            objects::Node* ReadNode();
            IOEdge* ReadEdge();
        };
        
    }
}

#endif /* FILEIO_HPP */


#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <fstream>
#include <string>

#include "graph.hpp"
#include "node.hpp"

namespace pathfinder {
    namespace fileio {
        using namespace objects;
        
        /// \struct IOEdge
        /// \brief A temporary container used to hold data about an edge
        struct IOEdge {
            id_t src_id;
            id_t target_id;
            cost_t cost;
            bool accessible_fwd;
            bool accessible_bwd;
        };
        
        class Reader {
        public:
            Reader(Graph* graph,
                   std::string nodepath,
                   std::string edgepath);
            void Fill();
        private:
            std::ifstream nodefile;
            std::ifstream edgefile;
            id_t currentNode = 0;
            Graph* graph;
            Node* ReadNode();
            IOEdge* ReadEdge();
            std::map<id_t, id_t> translationTable;
            std::vector<std::string> ReadValues(std::ifstream& stream);
        };
    }
}

#endif /* FILEIO_HPP */


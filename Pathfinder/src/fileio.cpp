#include <boost/algorithm/string.hpp>
#include <vector>
#include <fstream>

#include "fileio.hpp"

namespace pathfinder {
    namespace fileio {
        Reader::Reader(objects::Graph* graph, std::string nodepath, std::string edgepath) {
            this->graph = graph;
            
            nodefile = std::ifstream(nodepath);
            edgefile = std::ifstream(edgepath);
            
            // First line is garbage, skip it
            nodefile.getline();
            edgefile.getline();
            
            Fill();
        }
        
        void Reader::Fill() {
            objects::Node* cur_n;
            IOEdge* cur_e;
            
            while((cur_n = ReadNode()) != NULL) {
                graph->AddNode(*cur_n);
            }
            
            while((cur_e = ReadEdge()) != NULL) {
                if(cur_e->accessible_fwd) 
                    graph->AddEdge(cur_e->src_id, cur_e->target_id, cur_e->cost);
                if(cur_e->accessible_bwd)
                    graph->AddEdge(cur_e->target_id, cur_e->src_id, cur_e->cost);
                
                delete cur_e; // prevent mem leaks
            }
        }
        
        IOEdge* Reader::ReadEdge() {
            IOEdge* edge = new objects::Node();
            
            std::vector<std::string> vec = ReadValues(nodefile);
            
            if (vec.size() == 0)
                    return NULL;
            if (vec.size() < 7) 
                    throw new std::exception("Edge lines should have at least 7 data values");
            
            edge->src_id         = std::stoull(vec[1]);
            edge->target_id      = std::stoull(vec[2]);
            edge->cost           = std::stod(vec[3]);
            edge->accessible_fwd = std::stoi(vec[5]) > 0;
            edge->accessible_bwd = std::stoi(vec[6]) > 0;
            
            return edge;
        }
        
        objects::Node* Reader::ReadNode() {
            objects::Node* node = new objects::Node();
            
            std::vector<std::string> vec = ReadValues(nodefile);
            
            if (vec.size() == 0)
                    return NULL;
            if (vec.size() != 3) 
                    throw new std::exception("Node lines should have 3 data values");
            
            node->id  = std::stoull(vec[0]);
            node->lat = std::stod(vec[1]);
            node->lon = std::stod(vec[2]);
        }
        
        std::vector<std::string> Reader::ReadValues(std::ifstream& stream) {
            std::vector<std::string> vec;
            std::string str = stream.getline();
            
            boost::split(vec, str, boost::is_any_of(","));
            
            return vec;
        }
    }
}
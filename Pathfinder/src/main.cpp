#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>

int main(int argc, char* argv[]) {
    std::string filename;
    po::variables_map vm;
    
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "get version of Pathfinder")
            ("astar,a", "enable testing of A*")
            ("dfs,d", "enable testing of DFS")
            ("bfs,d", "enable testing of BFS")
            ("dijkstra,D", "enable testing of Dijkstra's algorithm")
            ("file,f", po::value<std::string>(&filename), "file from which to extract OSM data")
        ;

        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        
    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    } catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }
    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    if (vm.count("version")) {
        std::cout << "Pathfinder version " << PATHFINDER_VERSION << ".\n";
        return 0;
    }

    if (vm.count("file")) {
        std::cout << "Set OSM file to " << filename << "\n";
    } else {
        std::cout << "You must set a file using --file (-f).\n";
        return 1;
    }
    
    
    
    return 0;
}
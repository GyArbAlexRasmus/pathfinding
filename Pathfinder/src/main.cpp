#include <boost/program_options.hpp>

#include <iostream>
#include <random>

#include "tests.hpp"
#include "astar.hpp"

namespace po = boost::program_options;
namespace pf = pathfinder;
namespace objs = pf::objects;

int main(int argc, char* argv[]) {
    std::string path;
    po::variables_map vm;
    po::options_description desc("Allowed options");
    std::vector<pf::algorithms::Algorithm*> algs;
    std::vector<pf::Tests::TestResults> results;
    try {
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "get version of Pathfinder")
            ("astar,a", "enable testing of A*")
            ("dijkstra,d", "enable testing of Dijkstra's algorithm")
            ("path,p", po::value<std::string>(&path), "path in which OSM data is stored")
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

    //TODO errchecking
    if (vm.count("path")) {
        std::cout << "Set OSM path to " << path << "\n";
    } else {
        std::cout << "You must set a path using --path (-p).\n";
        return 1;
    }
    
    pf::Tests::Initialize(path);
    pf::Tests::PrintDiagnostics();

    if (vm.count("astar")) {
        pf::algorithms::Algorithm* astar = new
                pf::algorithms::AStar(pf::Tests::graph);

        algs.push_back(astar);
    }

    // TODO implement testing for argument-specified nodes
    objs::id_t src, target;

    //Initialize seed
    srand(std::random_device()());

    src    = pf::Tests::graph->RandomID();
    target = pf::Tests::graph->RandomID();

    for(pf::algorithms::Algorithm* alg : algs) {
        results.push_back(pf::Tests::RunTests(alg, src, target));
    }

    for(pf::Tests::TestResults res : results) {
        pf::Tests::PrintResults(res);
    }

    pf::Tests::DeInitialize();

    return 0;
}
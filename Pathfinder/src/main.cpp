#include <boost/program_options.hpp>

#include <iostream>
#include <random>

#include "astar.hpp"
#include "dijkstra.hpp"
#include "fringe.hpp"
#include "tests.hpp"
#include "math.hpp"


namespace po = boost::program_options;
namespace pf = pathfinder;
namespace objs = pf::objects;

int main(int argc, char* argv[]) {
    std::string path, heuristic;
    po::variables_map vm;
    po::options_description desc("Allowed options");
    std::vector<pf::algorithms::Algorithm*> algs;
    std::vector<pf::Tests::TestResults> results;
    pf::objects::cost_t (*heuristicFunction)(const pf::objects::Node& node1,
                                             const pf::objects::Node& node2);

    try {
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "get version of Pathfinder")
            ("astar,a", "enable testing of A*")
            ("dijkstra,d", "enable testing of Dijkstra's algorithm")
            ("fringe,f", "enable testing of Fringe Search")
            ("heuristic,H", po::value<std::string>(&heuristic),
             "heuristic function, h is haversine, e is euclidean")
            ("path,p", po::value<std::string>(&path),
             "path in which OSM data is stored")
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

    if (vm.count("heuristic")) {
        if(heuristic == "h") {
            std::cout << "Using haversine heuristic.";
            heuristicFunction = pf::math::Haversine;
        } else if (heuristic == "e") {
            std::cout << "Using euclidean heuristic.";
            heuristicFunction = pf::math::Euclidean;
        } else {
            std::cout << "Invalid heuristic identifier,"
                         "proceeding using haversine heuristic.\n";
            heuristicFunction = pf::math::Haversine;
        }
    } else {
        std::cout << "Using haversine heuristic.";
        heuristicFunction = pf::math::Haversine;
    }
    
    pf::Tests::Initialize(path);
    pf::Tests::PrintDiagnostics();

    if (vm.count("astar")) {
        pf::algorithms::Algorithm* astar = new
                pf::algorithms::AStar(pf::Tests::graph, heuristicFunction);

        algs.push_back(astar);
    }

    if (vm.count("dijkstra")) {
        pf::algorithms::Algorithm* dijkstra = new
                pf::algorithms::Dijkstra(pf::Tests::graph);

        algs.push_back(dijkstra);
    }
  
    if (vm.count("fringe")) {
        pf::algorithms::Algorithm* fringe = new
                pf::algorithms::FringeSearch(pf::Tests::graph,
                                             heuristicFunction);

        algs.push_back(fringe);
    }

    // TODO implement testing for argument-specified nodes
    objs::id_t src, target;

    //Initialize seed
    srand(std::random_device()());

    srand(1234);

    for(int i = 0; i < 25; i++) {

        src    = pf::Tests::graph->RandomID();
        target = pf::Tests::graph->RandomID();

        for(pf::algorithms::Algorithm* alg : algs) {
            results.push_back(pf::Tests::RunTests(alg, src, target));
        }

        std::cout << "\n";
    }

    for(pf::Tests::TestResults res : results) {
        pf::Tests::PrintResults(res);
    }

    pf::Tests::DeInitialize();

    return 0;
}
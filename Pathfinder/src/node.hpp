#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <stack>
#include <utility>
#include <vector>

namespace pathfinder {
    namespace objects {
        struct Node; // Forward declaration
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
    }
}

#endif /* NODE_HPP */
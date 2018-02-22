#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <osmium/osm/way.hpp>

namespace pathfinder {
    class algorithm {
        public:
            /// \return 
            osmium::WayNodeList findWay() = 0;
    };
}


#endif /* PATHFINDER_H */


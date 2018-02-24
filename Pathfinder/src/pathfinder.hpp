#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

namespace pathfinder {
    namespace objects {
        /// \enum Describes car accessibility.
        enum Car_Accessibility {
            FORBIDDEN,
            RESIDENTIAL,
            TERTIARY,
            SECONDARY,
            PRIMARY,
            TRUNK,
            MOTORWAY
        };
        
        /// \enum Describes bike accessibility.
        enum Bike_Accessibility {
            FORBIDDEN,
            OPPOSITE_OF_CAR, // bike lane in the opposite direction of the car flow
            ALLOWED, // allowed without specific equipment
            CYCLING_LANE,
            BUS_LANE_ALLOWED, // bus lane allowed for cycles
            CYCLING_TRACK
        };
        
        /// \enum Describes accessibility on foot.
        enum Foot_Accessibility {
            FORBIDDEN,
            ALLOWED
        };
        
        struct Node {
            uint64_t id;
            double lon;
            double lat;
        };
        
        struct Edge {
            uint64_t id;
            uint64_t source_id;
            uint64_t target_id;
            double length;
            Car_Accessibility car_access;
            Car_Accessibility car_reverse_access;
            Bike_Accessibility bike_access;
            Bike_Accessibility bike_reverse_access;
            Foot_Accessibility foot_access;
            std::string geometry; // In WKT format
        };
        
    }
    class algorithm {
        public:
            /// \return 
            osmium::WayNodeList findWay() = 0;
    };
}


#endif /* PATHFINDER_HPP */
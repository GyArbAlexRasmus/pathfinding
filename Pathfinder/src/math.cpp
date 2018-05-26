#include <cmath>

#include "math.hpp"

namespace pathfinder {
    namespace math {
        using namespace objects;
        
        double Euclidean(const Node& node1, const Node& node2) {
            return Euclidean(node1.lat, node1.lon, node2.lat, node2.lon);
        }

        double Euclidean(double lat1, double lon1, double lat2, double lon2) {
            double dx = lat1 - lat2;
            double dy = (lon1 - lon2) * cos(lat2);

            return R_EARTH * sqrt(dx*dx + dy*dy);
        }

        /// Calculates the distance between two nodes
        /// \param node1 The first node
        /// \param node2 The second node
        /// \return The distance between the two nodes
        double Haversine(const Node& node1, const Node& node2) {
            return Haversine(node1.lat, node1.lon, node2.lat, node2.lon);
        }

        /// Calculates the distance between two sets of coordinates on the earth
        /// \param lat1 Coordinate 1's longitude, in radians
        /// \param lon1 Coordinate 1's latitude, in radians
        /// \param lat2 Coordinate 2's longitude, in radians
        /// \param lon2 Coordinate 2's latitude, in radians
        /// \return The distance between the two coordinates
        double Haversine(double lat1, double lon1, double lat2, double lon2) {
            double deltaLat = lat2 - lat1;
            double deltaLon = lon2 - lon1;

            double a = (sin(deltaLat / 2) * sin(deltaLat / 2)) +
                       (cos(lat1) * cos(lat2) *
                        sin(deltaLon / 2) * sin(deltaLon / 2));

            double c = 2 * atan2(sqrt(a), sqrt(1 - a));

            return R_EARTH * c;
        }

        /// Convert a value from degrees to radians
        /// \param deg The value in degrees
        /// \return The angle in radians
        double DegToRad(double deg) {
            return deg * (M_PI / 180);
        }

        /// Convert a value from radians to degrees
        /// \param rad The angle in radians
        /// \return The value in degrees
        double RadToDeg(double rad) {
            return rad * (180 / M_PI);
        }
    }
}


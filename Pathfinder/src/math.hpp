#ifndef MATH_HPP
#define MATH_HPP

#include "node.hpp"

#define R_EARTH 6371e3
namespace pathfinder {
    namespace math {
        double Haversine(const objects::Node& node1, const objects::Node& node2);
        double Haversine(double lat1, double lon1, double lat2, double lon2);
        double DegToRad(double deg);
        double RadToDeg(double rad);
    }
}

#endif /* MATH_HPP */

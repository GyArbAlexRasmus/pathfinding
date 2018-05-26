#ifndef MATH_HPP
#define MATH_HPP

#include "node.hpp"

#define R_EARTH 6371e3
namespace pathfinder {
    namespace math {
        using namespace objects;
        
        double Euclidean(const Node& node1, const Node& node2);
        double Euclidean(double lat1, double lon1, double lat2, double lon2);

        double Haversine(const Node& node1, const Node& node2);
        double Haversine(double lat1, double lon1, double lat2, double lon2);

        double DegToRad(double deg);
        double RadToDeg(double rad);
    }
}

#endif /* MATH_HPP */

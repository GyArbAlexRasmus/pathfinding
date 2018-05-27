#include <cmath>
#include <iostream>
#include <iomanip>

#include "statistics.hpp"

namespace pathfinder {
    Statistic::Statistic() : values() { }

    void Statistic::AddValue(double val) {
        values.push_back(val);
        sum += val;
        squaredSum += val * val;

        max = val > max ? val : max;
        min = val < min ? val : min;
    }

    void Statistic::Clear() {
        values.clear();
        sum = 0;
        squaredSum = 0;
        max = -1 * INFINITY;
        min = INFINITY;
    }

    double Statistic::GetMax() {
        return max;
    }

    double Statistic::GetMean() {
        return sum / values.size();
    }

    double Statistic::GetMin() {
        return min;
    }

    double Statistic::GetStdDev() {
        double mean = GetMean();
        return sqrt((squaredSum / values.size()) - (mean * mean));
    }


    double Statistic::GetSum() {
        return sum;
    }

    void Statistic::Print() {
        std::cout << std::setw(20) << std::left << "mean: " << GetMean() << "\n";
        std::cout << std::setw(20) << std::left << "sum: " << GetSum() << "\n";
        std::cout << "standard deviation: " << GetStdDev() << "\n";
        std::cout << std::setw(20) << std::left << "min: " << GetMin() << "\n";
        std::cout << std::setw(20) << std::left << "max: " << GetMax() << "\n\n";

    }

    StatisticsCollection::StatisticsCollection(std::string name)
            : statistics() {
        algorithmName = name;
    }

    void StatisticsCollection::AddStatistic(std::string name) {
        statistics[name] = Statistic();
    }

    void StatisticsCollection::AddValue(std::string name, double val) {
        statistics[name].AddValue(val);
    }

    void StatisticsCollection::Print() {
        auto iter = statistics.begin();

        std::cout << "------------- results -------------\n";
        std::cout << "algorithm: " << algorithmName << "\n\n";

        while(iter != statistics.end()) {
            std::cout << "--- " << iter->first << " ---\n";
            iter->second.Print();

            iter++;
        }
    }
}
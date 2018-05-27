#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>

#include "statistics.hpp"

namespace pathfinder {
    Statistic::Statistic() : values() {
        printFlags.set();
    }

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

    size_t Statistic::GetCount() {
        return values.size();
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

    const std::vector<double>& Statistic::GetValues() {
        return values;
    }

    void Statistic::Print() {
        if(printFlags[STATISTIC_PRINTFLAG_MEAN]) {
            std::cout << std::setw(20) << std::left
                      << "mean: " << GetMean() << "\n";
        }

        if(printFlags[STATISTIC_PRINTFLAG_SUM]) {
            std::cout << std::setw(20) << std::left
                      << "sum: " << GetSum() << "\n";
        }


        if(printFlags[STATISTIC_PRINTFLAG_STDDEV]) {
            std::cout << "standard deviation: " << GetStdDev() << "\n";
        }


        if(printFlags[STATISTIC_PRINTFLAG_MINMAX]) {
            std::cout << std::setw(20) << std::left
                      << "min: " << GetMin() << "\n";

            std::cout << std::setw(20) << std::left
                      << "max: " << GetMax() << "\n\n";
        }
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

    void StatisticsCollection::DumpCSV(std::ofstream& stream) {
        std::vector<std::vector<std::string>> values;

        for(auto iter = statistics.begin(); iter != statistics.end(); iter++) {
            Statistic statistic = iter->second;
            std::vector<std::string> currentValues;

            // Add name
            currentValues.push_back(iter->first);

            // Add values
            for(double value : statistic.GetValues()) {
                currentValues.push_back(
                        boost::lexical_cast<std::string>(value));
            }

            values.push_back(currentValues);
        }

        std::vector<std::string> lines;
        for(int i = 0; i < values.size() - 1; i++) {
            for(int j = 0; j < values[i].size(); j++) {
                if(j >= lines.size()) {
                    lines.push_back(values[i][j] + ",");
                } else {
                    lines[j] += values[i][j] + ",";
                }
            }
        }

        for(int i = 0; i < values[values.size() - 1].size(); i++) {
            lines[i] += values[values.size() - 1][i] + "\n";
        }

        for(std::string line : lines) {
            stream.write(line.c_str(), line.size());
        }
    }

    std::string StatisticsCollection::GetName() {
        return algorithmName;
    }

    Statistic& StatisticsCollection::GetStatistic(std::string name) {
        auto iter = statistics.find(name);

        assert(iter != statistics.end());

        return iter->second;
    }

    void StatisticsCollection::Print() {
        auto iter = statistics.begin();

        std::cout << "------------- results -------------\n";
        std::cout << "algorithm: " << algorithmName << "\n\n";

        while(iter != statistics.end()) {
            if(iter->second.printFlags.any()) {
                std::cout << "--- " << iter->first << " ---\n";
                iter->second.Print();
            }

            iter++;
        }
    }
}
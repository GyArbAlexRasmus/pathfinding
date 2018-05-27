#ifndef STATISTICS
#define STATISTICS

#include <map>
#include <vector>

namespace pathfinder {
    struct Statistic {
    public:
        Statistic();

        void AddValue(double val);
        void Clear();

        double GetMax();
        double GetMean();
        double GetMin();
        double GetStdDev();
        double GetSum();

        void Print();

    private:
        std::vector<double> values;
        double sum = 0;
        double squaredSum = 0;
        double max = -1 * INFINITY;
        double min = INFINITY;
    };
    class StatisticsCollection {
    public:
        StatisticsCollection(std::string name);

        void AddStatistic(std::string name);
        void AddValue(std::string name, double val);

        void Print();
    private:
        std::string algorithmName;
        std::map<std::string, Statistic> statistics;
    };

}

#endif /* STATISTICS */

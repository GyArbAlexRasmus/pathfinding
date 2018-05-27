#ifndef STATISTICS
#define STATISTICS

#include <cmath>
#include <map>
#include <vector>
#include <bitset>

#define STATISTIC_PRINTFLAG_MEAN 0
#define STATISTIC_PRINTFLAG_SUM 1
#define STATISTIC_PRINTFLAG_STDDEV 2
#define STATISTIC_PRINTFLAG_MINMAX 3


namespace pathfinder {
    struct Statistic {
    public:
        std::bitset<4> printFlags;

        Statistic();

        void AddValue(double val);
        void Clear();

        size_t GetCount();
        double GetMax();
        double GetMean();
        double GetMin();
        double GetStdDev();
        double GetSum();

        const std::vector<double>& GetValues();

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
        explicit StatisticsCollection(std::string name);

        void AddStatistic(std::string name);
        void AddValue(std::string name, double val);
        void DumpCSV(std::ofstream& stream);
        std::string GetName();
        Statistic& GetStatistic(std::string name);

        void Print();
    private:
        std::string algorithmName;
        std::map<std::string, Statistic> statistics;
    };

}

#endif /* STATISTICS */

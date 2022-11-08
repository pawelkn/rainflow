#ifndef RAINFLOW_H
#define RAINFLOW_H

#include <vector>
#include <map>
#include <cmath>

namespace RainFlow {

struct Cycle {
    double range;
    double mean;
    double count;
    long unsigned int start_index;
    long unsigned int end_index;
};

typedef std::vector<double> Series;
typedef std::map<double, double> Counts;
typedef std::vector<Cycle> Cycles;

Counts count_cycles( const Series& series, double binSize = NAN );
Cycles extract_cycles( const Series& series );

}; // namespace RainFlow

#endif // RAINFLOW_H

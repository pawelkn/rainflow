#ifndef RAINFLOW_H
#define RAINFLOW_H

#include <vector>
#include <deque>
#include <map>
#include <cmath>

class RainFlow
{
public:
    struct Count {
        double range;
        double cycles;
    };

    struct Cycle {
        double range;
        double mean;
        double count;
        long unsigned int start_index;
        long unsigned int end_index;
    };

    typedef std::vector<double> Series;
    typedef std::vector<Count> Counts;
    typedef std::vector<Cycle> Cycles;
    
    static Counts count_cycles( const Series& series, double binsize = NAN );
    static Cycles extract_cycles( const Series& series );

private:
    struct Reversal {
        long unsigned int index;
        double value;
    };

    typedef std::deque<Reversal> Reversals;
    typedef std::map<double, double> CountsMap;

    static Reversals reversals( const Series& series );
};

#endif // RAINFLOW_H
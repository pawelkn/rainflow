#include "rainflow.h"
#include <deque>

struct Reversal {
    long unsigned int index;
    double value;
};

typedef std::deque<Reversal> Reversals;

static Reversals reversals(const RainFlow::Series& series) {
    Reversals reversals;

    if (series.size() <= 2)
        return reversals;

    auto index = 0UL;
    auto x_last = series[0];
    auto x = series[1];

    reversals.push_back({ index, x_last });

    auto d_last = x - x_last;
    auto x_next = x;

    while (++index < series.size() - 1) {
        x_next = series[index + 1];
        if (x_next == x)
            continue;

        auto d_next = x_next - x;
        if (d_next * d_last < 0)
            reversals.push_back({ index, x });

        x_last = x;
        x = x_next;
        d_last = d_next;
    }

    if (series.size() > 2)
        reversals.push_back({ index, x_next });

    return reversals;
}

RainFlow::Cycles RainFlow::extract_cycles(const RainFlow::Series& series) {
    RainFlow::Cycles cycles;
    Reversals points;

    auto format_output = [] (Reversals::iterator it, double count) {
        auto i1 = it->index;
        auto x1 = it->value; ++it;
        auto i2 = it->index;
        auto x2 = it->value;
        auto rng = std::abs(x1 - x2);
        auto mean = (x1 + x2) / 2;
        return RainFlow::Cycle { rng, mean, count, i1, i2 };
    };

    for (auto point: reversals(series)) {
        points.push_back(point);

        while (points.size() >= 3) {
            // Form ranges X and Y from the three most recent points
            auto end = points.end() - 1;
            auto x3 = end->value; --end;
            auto x2 = end->value; --end;
            auto x1 = end->value;

            auto X = std::abs(x3 - x2);
            auto Y = std::abs(x2 - x1);

            if (X < Y) {
                // Read the next point
                break;
            } else if (points.size() == 3) {
                // Y contains the starting point
                // Count Y as one-half cycle and discard the first point
                cycles.push_back(format_output(points.begin(), 0.5));
                points.pop_front();
            } else {
                // Count Y as one cycle and discard the peak and the valley of Y
                cycles.push_back(format_output(points.end() - 3, 1.0));
                auto last = points.back();
                points.pop_back();
                points.pop_back();
                points.pop_back();
                points.push_back(last);
            }
        }
    }

    // Count the remaining ranges as one-half cycles
    while (points.size() > 1) {
        cycles.push_back(format_output(points.begin(), 0.5));
        points.pop_front();
    }

    return cycles;
}

RainFlow::Counts RainFlow::count_cycles(const RainFlow::Series& series, double binSize) {
    RainFlow::Counts counts;

    if (! std::isnan(binSize)) {
        auto nmax = 0.0;

        for (auto cycle: extract_cycles(series)) {
            auto n = std::ceil(cycle.range / binSize);
            if (n > nmax)
                nmax = n;

            auto range = n * binSize;
            counts[range] += cycle.count;
        }

        for (auto n = 1; n < nmax; ++n) {
            auto range = n * binSize;
            counts.emplace(range, 0.0);
        }
    } else {
        for (auto cycle: extract_cycles(series)) {
            counts[cycle.range] += cycle.count;
        }
    }

    return counts;
}

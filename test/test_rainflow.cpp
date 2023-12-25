#include <gtest/gtest.h>

#include "rainflow.h"

static const RainFlow::Series SERIES_1 {
    -2, 1, -3, 5, -1, 3, -4, 4, -2
};

static const RainFlow::Series SERIES_2 {
    -1.5, 1.0, -3.0, 10.0, -1.0, 3.0, -8.0, 4.0, -2.0, 6.0,
    -1.0, -4.0, -8.0, 2.0, 1.0, -5.0, 0.0, 2.5, -4.0, 1.0,
    0.0, 2.0, -0.5
};

void VERIFY_CYCLES(const RainFlow::Cycles& cycles, RainFlow::Cycles ref) {
    EXPECT_EQ(cycles.size(), ref.size());
    for (auto i = 0UL; i < cycles.size(); ++i) {
        EXPECT_FLOAT_EQ(cycles[i].range, ref[i].range);
        EXPECT_FLOAT_EQ(cycles[i].mean, ref[i].mean);
        EXPECT_FLOAT_EQ(cycles[i].count, ref[i].count);
        EXPECT_EQ(cycles[i].start_index, ref[i].start_index);
        EXPECT_EQ(cycles[i].end_index, ref[i].end_index);
    }
};

void VERIFY_COUNTS(const RainFlow::Counts& counts, RainFlow::Counts ref) {
    EXPECT_EQ(counts.size(), ref.size());
    auto countsItr = counts.begin();
    auto refItr = ref.begin();
    for (; countsItr != counts.end(); ++countsItr, ++refItr) {
        EXPECT_FLOAT_EQ(countsItr->first, refItr->first);
        EXPECT_FLOAT_EQ(countsItr->second, refItr->second);
    }
};

TEST(RainFlowTest, TestExtractCycles1) {
    auto cycles = RainFlow::extract_cycles({});
    VERIFY_CYCLES(cycles, RainFlow::Cycles {});
}

TEST(RainFlowTest, TestExtractCycles2) {
    auto cycles = RainFlow::extract_cycles({ 1 });
    VERIFY_CYCLES(cycles, RainFlow::Cycles {});
}

TEST(RainFlowTest, TestExtractCycles3) {
    auto cycles = RainFlow::extract_cycles({ 1, 2 });
    VERIFY_CYCLES(cycles, RainFlow::Cycles {});
}

TEST(RainFlowTest, TestExtractCycles4) {
    auto cycles = RainFlow::extract_cycles({ 1, 2, 3 });
    VERIFY_CYCLES(cycles, RainFlow::Cycles {
        { 2, 2.0, 0.5, 0, 2 }
    });
}

TEST(RainFlowTest, TestExtractCycles5) {
    auto cycles = RainFlow::extract_cycles(SERIES_1);
    VERIFY_CYCLES(cycles, RainFlow::Cycles {
        { 3, -0.5, 0.5, 0, 1 },
        { 4, -1.0, 0.5, 1, 2 },
        { 4, 1.0, 1.0, 4, 5 },
        { 8, 1.0, 0.5, 2, 3 },
        { 9, 0.5, 0.5, 3, 6 },
        { 8, 0.0, 0.5, 6, 7 },
        { 6, 1.0, 0.5, 7, 8 },
    });
}

TEST(RainFlowTest, TestExtractCycles6) {
    auto cycles = RainFlow::extract_cycles(SERIES_2);
    VERIFY_CYCLES(cycles, RainFlow::Cycles {
        { 2.5, -0.25, 0.5, 0, 1 },
        { 4.0, -1.00, 0.5, 1, 2 },
        { 4.0, 1.00, 1.0, 4, 5 },
        { 13.0, 3.50, 0.5, 2, 3 },
        { 6.0, 1.00, 1.0, 7, 8 },
        { 14.0, -1.00, 1.0, 6, 9 },
        { 7.0, -1.50, 1.0, 13, 15 },
        { 1.0, 0.50, 1.0, 19, 20 },
        { 18.0, 1.00, 0.5, 3, 12 },
        { 10.5, -2.75, 0.5, 12, 17 },
        { 6.5, -0.75, 0.5, 17, 18 },
        { 6.0, -1.00, 0.5, 18, 21 },
        { 2.5, 0.75, 0.5, 21, 22 },
    });
}

TEST(RainFlowTest, TestCountCycles1) {
    auto counts = RainFlow::count_cycles(SERIES_1, 10);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 10, 4.0 }
    });
}

TEST(RainFlowTest, TestCountCycles2) {
    auto counts = RainFlow::count_cycles(SERIES_1, 9);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 9, 4.0 }
    });
}

TEST(RainFlowTest, TestCountCycles3) {
    auto counts = RainFlow::count_cycles(SERIES_1, 5);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 5, 2.0 },
        { 10, 2.0 }
    });
}

TEST(RainFlowTest, TestCountCycles4) {
    auto counts = RainFlow::count_cycles(SERIES_1, 3);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 3, 0.5 },
        { 6, 2.0 },
        { 9, 1.5 }
    });
}

TEST(RainFlowTest, TestCountCycles5) {
    auto counts = RainFlow::count_cycles(SERIES_1, 2);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 2, 0.0 },
        { 4, 2.0 },
        { 6, 0.5 },
        { 8, 1.0 },
        { 10, 0.5 }
    });
}

TEST(RainFlowTest, TestCountCycles6) {
    auto counts = RainFlow::count_cycles(SERIES_1, 1);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 1, 0.0 },
        { 2, 0.0 },
        { 3, 0.5 },
        { 4, 1.5 },
        { 5, 0.0 },
        { 6, 0.5 },
        { 7, 0.0 },
        { 8, 1.0 },
        { 9, 0.5 }
    });
}

TEST(RainFlowTest, TestCountCycles7) {
    auto counts = RainFlow::count_cycles(SERIES_2);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 1.0, 1.0 },
        { 2.5, 1.0 },
        { 4.0, 1.5 },
        { 6.0, 1.5 },
        { 6.5, 0.5 },
        { 7.0, 1.0 },
        { 10.5, 0.5 },
        { 13.0, 0.5 },
        { 14.0, 1.0 },
        { 18.0, 0.5 }
    });
}

TEST(RainFlowTest, TestCountCycles8) {
    RainFlow::Series series;
    for (auto i = 0; i < 1001; ++i)
        series.push_back(0.8 * std::sin(0.01 * M_PI * i) + 0.2 * std::sin(0.032 * M_PI * i));

    auto counts = RainFlow::count_cycles(series, 0.2);
    VERIFY_COUNTS(counts, RainFlow::Counts {
        { 0.2, 4.0 },
        { 0.4, 0.0 },
        { 0.6, 0.0 },
        { 0.8, 1.0 },
        { 1.0, 0.0 },
        { 1.2, 0.0 },
        { 1.4, 0.0 },
        { 1.6, 0.0 },
        { 1.8, 2.0 },
        { 2.0, 2.5 }
    });
}

//benchmark.cpp - timing code for Section 5.2
//Run from a folder that has NO data/ subfolder, so no saved files are loaded.
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <streambuf>
#include <string>
#include <vector>
#include "hashTable.h"
#include "quickSort.h"

using Clock = std::chrono::steady_clock;

//Discards everything written to it (silences the structures' own messages)
class NullBuf : public std::streambuf {
public:
    int overflow(int c) override { return c; }
};

static double elapsedMs(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

int main() {
    const int sizes[] = {100, 1000, 10000, 100000};
    const int RUNS = 5;
    const int LOOKUPS = 1000;

    std::mt19937 rng(12345);
    NullBuf nullBuf;
    std::streambuf* original = std::cout.rdbuf();
    std::ostream out(original);      //results are printed through this
    std::cout.rdbuf(&nullBuf);       //everything else sent to cout is discarded

    long long sink = 0;              //keeps the compiler from removing the searches
    out << std::fixed << std::setprecision(3);
    out << "n,hash_search_ms,quicksort_ms\n";

    for (int n : sizes) {
        double tHash = 0, tSort = 0;

        for (int r = 0; r < RUNS; ++r) {
            std::vector<int> ids(n);
            for (int i = 0; i < n; ++i) ids[i] = i + 1;
            std::shuffle(ids.begin(), ids.end(), rng);

            //1. Hash search: LOOKUPS lookups in a table holding n accounts
            {
                HashTable table;
                std::vector<std::string> plates(n);
                for (int i = 0; i < n; ++i) plates[i] = "PLT" + std::to_string(ids[i]);
                for (int i = 0; i < n; ++i) table.insertAcc(plates[i], "Driver", 100.0);

                std::uniform_int_distribution<int> pick(0, n - 1);
                std::vector<int> targets(LOOKUPS);
                for (int& t : targets) t = pick(rng);

                std::string name;
                double balance;
                auto s = Clock::now();
                for (int t : targets) sink += table.searchAcc(plates[t], name, balance);
                tHash += elapsedMs(s, Clock::now());
            }

            //2. Quick sort: n transactions
            {
                std::uniform_real_distribution<double> kwh(0.0, 500.0);
                std::vector<Trans> data(n);
                for (Trans& t : data) t = Trans{"PLT000", kwh(rng), 0.0};

                QuickSort qs;
                auto s = Clock::now();
                qs.sortTrans(data);
                tSort += elapsedMs(s, Clock::now());
            }
        }

        out << n << "," << tHash / RUNS << "," << tSort / RUNS << "\n";
    }

    std::cout.rdbuf(original);
    out << "(checksum: " << sink << ")\n";
    return 0;
}
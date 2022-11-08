#include "rainflow.h"
#include <iostream>
#include <iterator>
#include <fstream>

int main( int argc, char *argv[] )
{
    if( argc < 2 ) {
        std::cout << "Usage: example_rainflow [FILE]" << std::endl;
        return 1;
    }

    std::ifstream is { argv[1] };
    if( ! is ) {
        std::cerr << "Cannot open the file: " << argv[1] << std::endl;
        return 1;
    }

    std::istream_iterator<double> start { is }, end;
    RainFlow::Series series { start, end };

    auto binSize { 10 };
    auto counts { RainFlow::count_cycles( series, binSize ) };

    std::cout << "counted cycles (binSize=" << binSize << "):" << std::endl;
    for( auto count : counts )
        std::cout << '(' << count.first << ", " << count.second << ')' << std::endl;

    return 0;
}
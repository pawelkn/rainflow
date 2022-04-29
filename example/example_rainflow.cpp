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
        
    auto binsize { 10 };
    auto counts { RainFlow::count_cycles( series, binsize ) };

    std::cout << "counted cycles (binsize=" << binsize << "):" << std::endl;
    for( auto count : counts )
        std::cout << '(' << count.range << ", " << count.cycles << ')' << std::endl;

    return 0;
}
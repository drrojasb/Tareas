#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>
#include <map>
#include <fstream>

int main (int argc, char **argv){
    //read vector size
    const int N = std::atoi(argv[1]);

    //declare and fill vector
    std::vector<int> v(N);
    std::iota(v.begin(), v.end(), 10);

    //print vector using a lambda function
    auto print_vector = [v](){for(auto ii : v){std::cout << ii << ' ';}};
    print_vector();

    //count elements greater than 25
    int count_25 = std::count_if(v.begin(), v.end(), [](int ii){return ii > 25;});
    std::cout << '\n' << count_25;

    //count elements divisible by 3 and 5
    int count_div_3_5 = std::count_if(v.begin(), v.end(), [](int ii){return ii%3 + ii%5 == 0;});
    std::cout << '\n' << count_div_3_5;

    //find if any of the elements is divisible by 7 and 13
    std::cout << '\n' << std::any_of(v.begin(), v.end(), [](int ii){return ii%7 + ii%13 == 0;}) << '\n';

    //reverse the order of elements and print 10 of them
    std::reverse(v.begin(), v.end());
    for (int ii = 0; ii < 10; ii++){
        std::cout << v[ii] << ' '; 
    }
    
    //compute the average and measure time elapsed
    auto start = std::chrono::steady_clock::now();
    double average = (std::accumulate(v.begin(), v.end(), 0.0))/N;
    std::cout << '\n' << average << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;
    std::cout << elapsed_time.count() << '\n';
    
    //generate random numbers with normal distribution
    const int SEED = 5;
    std::mt19937 gen(SEED);
    std::normal_distribution<> d{5,2};
 
    //create histogram
    std::map<int, int> hist{};
    for(int n = 0; n < 10000; ++n) {
        ++hist[std::round(d(gen))];
    }

    // Print the histogram to a file
    std::ofstream fout("histo.txt");
    for (auto x : hist) {
        fout << x.first << ' ' << x.second << "\n";
    }
    fout.close();

    return 0;
}
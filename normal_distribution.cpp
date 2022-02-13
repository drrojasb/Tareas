#include <random>
#include <cmath>
#include <iostream>
#include <vector>

void print_numbers(std::vector<double> &numbers, int n);
void generate_numbers(std::vector<double> &numbers, int n, int seed);
void histogram(std::vector<double> &numbers);

int main ()
{
    int N = 10000;
    int SEED = 10;
    std::vector<double> NUMBERS(N);
    generate_numbers(NUMBERS, N, SEED);
    print_numbers(NUMBERS, N);
    
}

void generate_numbers(std::vector<double> &numbers, int n, int seed){
    std::mt19937 gen(seed);
    std::normal_distribution<double> dist{0.0, 1.0};
    for (int ii = 0; ii < n; ++ii){
        numbers[ii] = dist(gen);
    }
}

void print_numbers(std::vector<double> &numbers, int n){
    for(int ii = 0; ii < n; ++ii){
        std::cout << ii << ' ' << numbers[ii] << '\n';
    }
}
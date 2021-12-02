#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3);

int main(int argc, char **argv) {
  // read parameters
  const int N = std::atoi(argv[1]);
  const int SEED = std::atoi(argv[2]);

  // data structs
  std::vector<double> A(N*N, 0.0), B(N*N, 0.0), C(N*N, 0.0);

  // fill matrices A and B, using random numbers betwwen 0 and 1
  std::mt19937 gen(SEED);
  std::uniform_real_distribution<> dist(0.,1.);
  // lambda function: a local function that captures [] something, receives something (), and return something {}
  // See: https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/
  std::generate(A.begin(), A.end(), [&gen, &dist](){ return dist(gen); }); // uses a lambda function
  std::generate(B.begin(), B.end(), [&gen, &dist](){ return dist(gen); }); // uses a lambda function

  // multiply the matrices A and B and save the result into C. Measure time
  auto start = std::chrono::high_resolution_clock::now();
  multiply(A, B, C);
  auto stop = std::chrono::high_resolution_clock::now();

  // use the matrix to avoid the compiler removing it
  std::cout << C[N/2] << std::endl;

  // print time
  auto elapsed = std::chrono::duration<double>(stop - start);
  std::cout << elapsed.count() << "\n";

  return 0;
}

// implementations
void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3)
{
  const int N = std::sqrt(m1.size()); // assumes square matrices

  for(int ii = 0; ii < N; ii++){
      for(int jj = 0; jj < N; jj++){
        for (int kk = 0; kk < N; kk++){
            m3[ii*N + jj] += m1[ii*N + kk]*m2[kk*N + jj];
        }
      }
    } 
}
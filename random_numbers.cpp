#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<double> Matriz; // este?

double random_generator (unsigned int x, unsigned int a, unsigned int c, unsigned int m);
void print (Matriz &trip);
void fill (Matriz &trip);


int main(){
  const unsigned int X0 = 1;
  const unsigned int A = 1664525;
  const unsigned int C = 1013904223;
  const unsigned int M = 4294967296;

  Matriz Tripleta(1000*3); 
  Tripleta[0] = random_generator(X0, A, C, M);
  for (int ii = 0; ii < 1000; ++ii){
    for (int jj = 0; jj< 3; ++jj){
      Tripleta[ii*3 + jj + 1] = random_generator(Tripleta[ii*3 + jj], A, C, M);
    }
  }
  print(Tripleta);
}

double random_generator (unsigned int x, unsigned int a, unsigned int c, unsigned int m){
  return (1.0)*((a*x + c)%m)/(m-1);
}

void print (Matriz &trip){
  for (int ii = 0; ii < 1000; ++ii){
    for (int jj = 0; jj < 3; ++jj){
      std::cout << trip[ii*3 + jj] <<' ';
    }
    std::cout << '\n';
  }
}
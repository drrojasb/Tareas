#include <iostream>
#include <vector>
#include <cmath>

// constants
const double DELTA = 0.05;
const double Lx = 1.479;
const double Ly = 1.4*Lx;
const int M = int(Ly/DELTA) + 1; //M = 42
const int N = int(Lx/DELTA) + 1; //N = 30
const int STEPS = 200;

typedef std::vector<double> Matrix; // alias

void initial_conditions(Matrix & m);
void boundary_conditions(Matrix & m);
void evolve(Matrix & m);
void print(const Matrix & m);
void init_gnuplot(void);
void plot_gnuplot(const Matrix & m);

int main(void)
{
  Matrix data(M*N);
  initial_conditions(data);
  boundary_conditions(data);

  init_gnuplot();
  for (int istep = 0; istep < STEPS; ++istep) {
    evolve(data);
    plot_gnuplot(data);
  }

  return 0;
}
void initial_conditions(Matrix & m)
{
  for(int ii=0; ii<M; ++ii) {
    for(int jj=0; jj<N; ++jj) {
      m[ii*N + jj] = 1.0;
    }
  }
}
void boundary_conditions(Matrix & m)
{
  //conditions for the walls
  int ii = 0, jj = 0;
  for (jj = 0; jj < N; ++jj)
    m[ii*N + jj] = 100;

  ii = M-1;
  for (jj = 0; jj < N; ++jj)
    m[ii*N + jj] = 0;

  jj = 0;
  for (ii = 1; ii < M-1; ++ii)
    m[ii*N + jj] = 0;

  jj = N-1;
  for (ii = 1; ii < M-1; ++ii)
    m[ii*N + jj] = 0;
  
  //conditions for the plates
  jj = N/3;
  for (ii = M/4; ii < 3*M/4; ++ii){
    m[ii*N +jj] = 75;
  }

  jj = 2*N/3;
  for (ii = M/4; ii < 3*M/4; ++ii){
    m[ii*N +jj] = -75;
  }
}

void evolve(Matrix & m)
{
  for(int ii=0; ii<M; ++ii) {
    for(int jj=0; jj<N; ++jj) {
      // check if boundary for walls
      if(ii == 0) continue;
      if(ii == M-1) continue;
      if(jj == 0) continue;
      if(jj == N-1) continue;
      // check if boundary for plates
      if(jj == N/3){
        if(M/4 <= ii < 3*M/4) continue;
      }
      if(jj == 2*N/3){
        if(M/4 <= ii < 3*M/4) continue;
      }
      // evolve non boundary
      m[ii*N+jj] = (m[(ii+1)*N + jj] +
                    m[(ii-1)*N + jj] +
                    m[ii*N + jj + 1] +
                    m[ii*N + jj - 1] )/4.0;
    }
  }
}

void print(const Matrix & m)
{
  for(int ii=0; ii<M; ++ii) {
    for(int jj=0; jj<N; ++jj) {
      std::cout << ii*DELTA << " " << jj*DELTA << " " << m[ii*N + jj] << "\n";
    }
    std::cout << "\n";
  }  
}

void init_gnuplot(void)
{
  std::cout << "set contour " << std::endl;
  std::cout << "set terminal gif animate " << std::endl;
  std::cout << "set out 'anim.gif' " << std::endl;
}

void plot_gnuplot(const Matrix & m)
{
  std::cout << "splot '-' w pm3d " << std::endl;
  print(m);
  std::cout << "e" << std::endl;
}

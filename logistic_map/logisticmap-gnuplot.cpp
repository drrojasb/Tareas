#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>
#include <fstream>

typedef std::vector<double> vector; //alias

// declaration
void signal(vector & lm, double xi, double a, int n); //sequence of a signal for a fixed value of 'a'
vector lag_signal(vector & lm, int n, int tau);
void print_signal(vector & lm, int n); 
void print_map(vector & lm, int n);
void lyapunov(vector & lm, int n); 
void auto_correlation(vector & lm, vector & Rxx, int n); //sequence of correlation
double compute_sum1(vector & lm, int t, int n);
double compute_sum2(vector & lm, int n);

const int L = 100; 
const int N = 300;  //vector size for the signals of the logistic map
const int S = 1024; //vector size for the signals of lyapunov and autocorrelation
const double XI = 0.75;
double A = 3;

// main
int main(int argc, char **argv)
{
  /*const double XI = std::atof(argv[1]); // initial value [0,1]
  const int S = std::atoi(argv[2]);     // Size of the signal vector
  const double A = std::atof(argv[3]);  // parameter 'a' [1,4]
  
	if (XI < 0 or XI > 1 or A < 1  or A > 4) {
		std::cout << "Input is invalid. 'Initial value' (First value) must pertain to [0,1] and 'a' (Third value) to [1,4]. Exitting program...";
		return 0;
		}*/
  
  vector LM(N); //signal vector for lyapunov and autocorrelation 
  vector RXX(S); //Autocorrelation vector
  print_map(LM, N); 
  
  // gnuplot commands
  //system("gnuplot -p -e \"set xlabel 'n'\" -p -e \"set ylabel 'x'\" -p -e \"set title 'Individual Signal'\" -p -e \"plot 'signal.txt' w lp pt 7 ps 0.1\"");
  system("gnuplot -p -e \"set xlabel 'a'\" -p -e \"set ylabel 'x'\" -p -e \"set title 'Logistic Map'\" -p -e \"plot 'map.txt' w p pt 7 ps 0.05\""); // plot logistic map
	//system("gnuplot -p -e \"set xlabel 'a'\" -p -e \"set ylabel 'λ'\" -p -e \"set title 'Lyapunov exponent'\" -p -e \"plot 'lyapunov.txt' w linespoints pt 7 ps 0.1\""); // plot lyapunov exponent
	//system("gnuplot -p -e \"set xlabel 'N'\" -p -e \"set ylabel 'Rxx'\" -p -e \"set title 'Autocorrelation'\" -p -e \"plot 'autocorrelation.txt' w lp pt 7 ps 0.1\""); // plot autocorrelation
  return 0;
} 


// implementation

void signal(vector & lm, double xi, double a, int n) 
{
  lm[0] = xi;
  for(int ii = 1 ; ii < n ; ii++){
    lm[ii] = a*lm[ii - 1]*(1 - lm[ii - 1]);
  }
}

void print_signal(vector & lm, int n){
  std::ofstream fout; 
  fout.open("signal.txt"); // opening file
  for(int ii = 0; ii < n; ii++){ 
    fout << lm[ii] << '\n';
  }
  fout.close();
}

void print_map(vector & lm, int n){

  double xi = 0.75;
  double a = 1.0;
  double h_xi = 0.2;
  double h_a = 0.001;
  double steps_xi = (1.0 - 0.0)/h_xi;
  double steps_a = (4.0 - 1.0)/h_a;
	std::ofstream fout;
	
  fout.open("map.txt"); // opening file
  
  for(int ii = 0; ii <= steps_xi; ii++){
    xi = ii*h_xi;
    for(int jj = 0; jj <= steps_a; jj++){
      a = 1.0 + jj*h_a;
      signal(lm, xi, a, n);
      for(int kk = n - L; kk < n; kk++){  //prints the last L values of the sequence
        fout << a << ' ' << lm[kk] << '\n'; 
      }
    }
  }
  fout.close(); //Closing file
}

void lyapunov(vector & lm, int n){
  double xi = 0.75;
  double a = 1.0;
  double h = 0.001;
  double steps = (4.0 - 3.5)/h;
  std::ofstream fout;
   
  fout.open("lyapunov.txt"); //opening file
  
  for(int ii = 0; ii <= steps; ii++){
    double sum = 0.0;
    a = 3.5 + ii*h;
    signal(lm, xi, a, n);
    for(int jj = n - L; jj < n; jj++){
      sum += log(std::fabs(a -2*a*lm[jj])); 
    }
    fout << a << ' ' << (1.0/L)*sum << '\n';
  }
  fout.close(); //closing file
}

vector lag_signal(vector & lm, int n, int tau){
  vector ls(n);
  for(int ii = 0; ii < n; ii++){
    ls[ii] = lm[ii + tau];
  }
  return ls;
}

double compute_sum1(vector & lm, int tau, int n){
    vector ls(n);
    ls = lag_signal(lm, n/2, tau);
    double sum1 = 0.0;
    for (int ii = 0; ii < n/2 ; ii++){
        sum1 = sum1 + lm[ii]*ls[ii];
    }
    return sum1;
}
double compute_sum2(vector & lm, int n){
    double sum2 = 0.0;
    for(int ii = 0 ; ii < n/2; ii++){
        sum2 = lm[ii]*lm[ii];
    }
    return sum2;
}

void auto_correlation(vector & lm, vector & Rxx, int n)
{
    double xi = 0.75;
    double a = 3;
    signal(lm, xi, a, n);
    double SUM2 = compute_sum2(lm, n);
    std::ofstream fout;
    
    fout.open("autocorrelation.txt"); //opening file
    
    for(int tau = 0 ; tau < n/2; tau++){
        Rxx[tau] = (1.0/n)*compute_sum1(lm, tau, n) - (1.0/n)*(SUM2);
        fout << Rxx[tau] << '\n';
    }
    fout.close(); //closing file
}


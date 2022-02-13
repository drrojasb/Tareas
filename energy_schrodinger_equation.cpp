#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

typedef std::vector<double> state_t; // alias for state type

//constants
const int N = 2;
const double X0 = 0;
const double XF = M_PI/2;
const double DX = 0.01;

void print(const state_t & y, double time);
void fderiv(const state_t & y, state_t & dydt, double t);
template <class fptr>
double newton(double x0, fptr fun, double eps, int & niter);

int main(int argc, char **argv)
{
  //read parameters
  const double E0 = std::atof(argv[1]);
  const double phi0 = std::atof(argv[2]);
  const double phidot0 = std::atof(argv[3]);

  state_t y(N); // (phi, z), z = dphi/dx

  // functor : A class or struct with overloaded ()
  // behaves as a function (but richer, includes a parameter in this case)
  // to declare use:
  // Fderiv func; func.E = value;
  struct Fderiv {
    double E_ = 0; //internal parameter
    void operator()(const state_t & y, state_t & dydt, double t) { //external interface, is a function
      // vector is : y = (y0, y1) = (phi, z), z = dphi/dx
      dydt[0] = y[1];
      dydt[1] = -E_*y[0];
    }
  };

  // create lambda function: receives one arg (Energy) and return the final T value minus the expected one.
  auto faux = [&y, phi0, phidot0](double E){
    y[0] = phi0; y[1] = phidot0;
    Fderiv j; j.E_ = E; // declare functor and assing internal var E  to lambda argument
    boost::numeric::odeint::integrate(j, y, X0, XF, DX);
    return y[0] - 0;};

  // perform a Newton-Raphson procedure to find the root
  // compute numerically the derivative
  int nsteps = 0;
  double E  = newton(E0, faux, 0.000001, nsteps);

  // print final data
  Fderiv j; j.E_ = E;
  boost::numeric::odeint::integrate(j, y, X0, XF, DX, print);
  std::cerr << E << std::endl;
  return 0;
}

//print function
void print(const state_t & y, double time)
{
   std::cout << time << "\t" << y[0] << "\t" << y[1] << std::endl;
}

//newton method
template <class fptr>
double newton(double x0, fptr fun, double eps, int & niter)
{
  double h = 0.00001;
  double xr = x0;
  int iter = 1;
  while(std::fabs(fun(xr)) > eps) {
    double fderiv =  (fun(xr+h/2) - fun(xr-h/2))/h;
    xr = xr - fun(xr)/fderiv;
    iter++;
  }
  niter = iter;
  return xr;
}

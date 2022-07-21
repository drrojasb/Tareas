#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

//constants
const double g = 9.8; //acceleration of gravity
const double pi = std::acos(-1);
const double NSTEPS = 10000;
const double h = (2*pi)/NSTEPS; //step size for E<=2mgl
const double h_1 = (10*pi)/(5*NSTEPS); //step size for E>2mgl 

//functions declaration
template <class fptr>
void plot(fptr fun, double e, double k, double a);
double angular_momentum(double e, double theta, double k, double a);

int main(int argc, char **argv)
{
    const double m = std::atof(argv[1]); // masa
    const double l = std::atof(argv[2]); // longitud
    const double E = std::atof(argv[3]); // energia
    const double K = std::sqrt(2*m*l*l); // K = sqrt(2ml^2)
    const double A = 2*m*g*l; // A = 2mgl

    plot(angular_momentum, E, K, A);  

    return 0;
}

template <class fptr>
void plot(fptr fun, double e, double k, double a){
    if(e < a){ // E<2mgl
        std::ofstream f1out("data1.txt"); 
        double E1 = e/6.0;
        for (int n = 0; n <= NSTEPS; n++){
            double THETA = -pi + n*h;
            if(E1 - a*(1.0 - std::cos(-pi + n*h))/2.0 >= 0){
                f1out << THETA << " " << fun(E1, THETA, k, a) << '\n';
                f1out << THETA << " " << (-1.0)*fun(E1, THETA, k, a) << '\n';
            }
            else{
                f1out << THETA << " NaN" << '\n';
            }
        }
        f1out.close();

        std::ofstream f2out("data2.txt"); 
        double E2 = 2*E1;
        for (int n = 0; n <= NSTEPS; n++){
            double THETA = -pi + n*h;
            if(E2 - a*(1.0 - std::cos(-pi + n*h))/2.0 >= 0){
                f2out << THETA << " " << fun(E2, THETA, k, a) << '\n';
                f2out << THETA << " " << (-1.0)*fun(E2, THETA, k, a) << '\n';
            }
            else{
                f2out << THETA << " NaN" << '\n';
            }
        }
        f2out.close();

        std::ofstream f3out("data3.txt"); 
        double E3 = 3*E1;
        for (int n = 0; n <= NSTEPS; n++){
            double THETA = -pi + n*h;
            if(E3 - a*(1.0 - std::cos(-pi + n*h))/2.0 >= 0){
                f3out << THETA << " " << fun(E3, THETA, k, a) << '\n';
                f3out << THETA << " " << (-1.0)*fun(E3, THETA, k, a) << '\n';
            }
            else{
                f3out << THETA << " NaN" << '\n';
            }
        }
        f3out.close();

        std::ofstream f4out("data4.txt"); 
        double E4 = 4*E1;
        for (int n = 0; n <= NSTEPS; n++){
            double THETA = -pi + n*h;
            if(E4 - a*(1.0 - std::cos(-pi + n*h))/2.0 >= 0){
                f4out << THETA << " " << fun(E4, THETA, k, a) << '\n';
                f4out << THETA << " " << (-1.0)*fun(E4, THETA, k, a) << '\n';
            }
            else{
                f4out << THETA << " NaN" << '\n';
            }
        }
        f4out.close();

        std::ofstream f5out("data5.txt"); 
        double E5 = 5*E1;
        for (int n = 0; n <= NSTEPS; n++){
            double THETA = -pi + n*h;
            if(E5 - a*(1.0 - std::cos(-pi + n*h))/2.0 >= 0){
                f5out << THETA << " " << fun(E5, THETA, k, a) << '\n';
                f5out << THETA << " " << (-1.0)*fun(E5, THETA, k, a) << '\n';
            }
            else{
                f5out << THETA << " NaN" << '\n';
            }
        }
        f5out.close();
    }
    if(e == a){ // E=2mgl
        std::ofstream f1out("data1.txt"); 
        double E1 = e;
        for (int n = 0; n <= NSTEPS; n++){
            double THETA = -pi + n*h;
            f1out << THETA << " " << fun(E1, THETA, k, a) << '\n';
            f1out << THETA << " " << (-1.0)*fun(E1, THETA, k, a) << '\n';
        }
        f1out.close();
    }
    if(e > a){ // E>2mgl
        std::ofstream f1out("data1.txt"); 
        double E1 = e;
        for (int n = 0; n <= 5*NSTEPS; n++){
            double THETA = -5*pi + n*h_1;
            f1out << THETA << " " << fun(E1, THETA, k, a) << '\n';
            f1out << THETA << " " << (-1.0)*fun(E1, THETA, k, a) << '\n';
        }
        f1out.close();

        std::ofstream f2out("data2.txt"); 
        double E2 = 1.4*E1;
        for (int n = 0; n <= 5*NSTEPS; n++){
            double THETA = -5*pi + n*h_1;
            f2out << THETA << " " << fun(E2, THETA, k, a) << '\n';
            f2out << THETA << " " << (-1.0)*fun(E2, THETA, k, a) << '\n';
        }
        f2out.close();

        std::ofstream f3out("data3.txt"); 
        double E3 = 1.8*E1;
        for (int n = 0; n <= 5*NSTEPS; n++){
            double THETA = -5*pi + n*h_1;
            f3out << THETA << " " << fun(E3, THETA, k, a) << '\n';
            f3out << THETA << " " << (-1.0)*fun(E3, THETA, k, a) << '\n';
            
        }
        f3out.close();

        std::ofstream f4out("data4.txt"); 
        double E4 = 2.2*E1;
        for (int n = 0; n <= 5*NSTEPS; n++){
            double THETA = -5*pi + n*h_1;
            f4out << THETA << " " << fun(E4, THETA, k, a) << '\n';
            f4out << THETA << " " << (-1.0)*fun(E4, THETA, k, a) << '\n';
        }
        f4out.close();

        std::ofstream f5out("data5.txt"); 
        double E5 = 2.6*E1;
        for (int n = 0; n <= 5*NSTEPS; n++){
            double THETA = -5*pi + n*h_1;
            f5out << THETA << " " << fun(E5, THETA, k, a) << '\n';
            f5out << THETA << " " << (-1.0)*fun(E5, THETA, k, a) << '\n';
            f5out.close();
        }
    }
}

double angular_momentum(double e, double theta, double k, double a){  //p_theta = sqrt(2ml^2)sqrt(E-mgl(1-cos(theta)))
    double p_theta = k*std::sqrt(e - a*(1.0 - std::cos(theta))/2.0);
    return p_theta;
}
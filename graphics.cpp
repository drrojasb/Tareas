#include <iostream>
#include <fstream>
#include <cmath>

//constants
const double v = 1.25;
const double beta = 2.47e-7;
const double r0 = 25e-3;
const int TF = 4441;

double angular_velocity(int t);
double angular_acceleration(int t);
template <class fptr>
void plot(fptr fun);

int main(int argc, char **argv){
    int printf1 = std::atoi(argv[1]);

    if(printf1){
        plot(angular_velocity);
    }
    else{
        plot(angular_acceleration);
    }
    
}

double angular_velocity(int t){
    double omega = (v/beta)*pow(((r0/beta)*(r0/beta)+(2*v*t)/beta), -0.5);
    return omega;
}

double angular_acceleration(int t){
    double alfa = -(v/beta)*(v/beta)*pow(((r0/beta)*(r0/beta)+(2*v*t)/beta), -1.5);
    return alfa;
}

template <class fptr>
void plot(fptr fun){
    std::ofstream fout("datos.txt"); 
    for (int T = 0; T < TF; T++){
        if (T == 0 or T%60 == 0){
            fout << fun(T) << '\n';
        }
    }
    fout.close();
}

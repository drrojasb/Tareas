#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <vector>

//instantiation
double density_fun(double x);

int main(int argc, char **argv)
{
    //read parameters
    const int SEED = std::atoi(argv[1]);
    const int SAMPLES = std::atoi(argv[2]);
    const double XMIN = std::atoi(argv[3]);
    const double XMAX = std::atoi(argv[4]);
    const int NBINS = std::atoi(argv[5]);

    const double DX = (XMAX-XMIN)/NBINS;
    std::vector<double> histo(NBINS, 0.0);

    //rejection method
    std::mt19937 gen(SEED);
    std::uniform_real_distribution<double> distx(-1.0, 1.0); //generate random numbers for x in (-1.0, 1.0)
    std::uniform_real_distribution<double> disty(0.0, 0.75); //generate random numbers for y in (0.0, 0.75)
    std::ofstream fout("datos.txt"); 
    for (int ii = 0; ii < SAMPLES; ii++){
        double x = distx(gen);
        double y = disty(gen);
        if (y < density_fun(x)){
            fout << x << '\n'; //print to 'datos.txt'
            int bin = int((x - XMIN)/DX);
            if (0 <= bin && bin < NBINS) { //assigns a bin to each x
                histo[bin]++;
            }
        }
        else {
            ii--; //ii only increases when y < density_fun(x)
        }
    }
    fout.close();

    fout.open("density.txt");
    for (int ii = 0; ii < NBINS; ii++) {
        fout << XMIN + ii*DX << "\t" << histo[ii]/(DX*SAMPLES) << "\n"; //print to 'density.txt'
    }
    fout.close();

    return 0;
}

//Declaration
double density_fun(double x){
    return (1 - (x*x))*3.0/4.0;
}


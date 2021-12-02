#include <iostream>

struct Vector3D
{
    double x{};
    double y{};
    double z{};

    Vector3D(){ //constructor por defecto
        x = 0.0;
        y = 0.0;
        z = 0.0;
    } 
    ~Vector3D(){}; //destructor
    
    Vector3D operator + (Vector3D const &obj){ //Se sobrecarga el operador + para que sume vectores en 3D
        Vector3D sum;
        sum.x = x + obj.x;
        sum.y = y + obj.y;
        sum.z = z + obj.z;
        return sum;
    }

    double operator * (Vector3D const &obj){ //se sobrecarga el operador para que haga producto punto de vectores en 3D
        double dot = x*obj.x + y*obj.y + z*obj.z;
        return dot;
    }
};

void printVector(Vector3D result);

int main (int argc, char **argv)
{
    Vector3D vec3d{}; //se implementa el constructor
    printVector(vec3d);
    //lectura de parámetros 
    double X1 = std::atof(argv[1]);
    double Y1 = std::atof(argv[2]);
    double Z1 = std::atof(argv[3]);
    double X2 = std::atof(argv[4]);
    double Y2 = std::atof(argv[5]);
    double Z2 = std::atof(argv[6]);

    //Declaración de vectores
    Vector3D A;
    A.x = X1;
    A.y = Y1;
    A.z = Z1;

    Vector3D B;
    B.x = X2;
    B.y = Y2;
    B.z = Z2;

    Vector3D SUM = A + B; //suma de vectores
    double DOT = A*B;   //producto de vectores

    //Impresión de resultados
    printVector(SUM);
    std::cout << DOT << std::endl;
    
    return 0;
}

void printVector(Vector3D result){
    std::cout << result.x << " " << result.y << " " << result.z << std::endl;
}
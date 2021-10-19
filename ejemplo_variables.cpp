#include <iostream>

int main ()
{
  //Declaración de variables
  
  float a;
  float b = 1.0e40 ;
  bool c = false;
  double d;

  //Impresión de variables

  std::cout << "a: "<< a << "\n";
  std::cout << "c: "<< c << "\n";
  std::cout << "Dirección de la variable d: "<< &d << "\n";
  std::cout << "Tamaño de la variable d: "<< sizeof(d) << "\n";
  std::cout << "b: "<< b << "\n";
  
  //Al imprimir la variable b aparece el mensaje "inf" en consola
  //Explicación: Este mensaje aparece por que el valor con el que se inicializó
  //la variable float, excede el tamaño del que disponen las variables de este    tipo en memoria.
  
  return 0;
}

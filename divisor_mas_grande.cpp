
//¿Cuál es el divisor más grande de N=600851475147, que no sea el mismo N?

#include <iostream>
int main ()
{
  long N = 600851475147;
  std::cout<< "N = " << N << "\n";
  bool div = false;
  for (long n = 2; !div ; n++){
    if (N % n == 0){
      div = true;
      std::cout << "El divisor más grande de N es: " << N / n << "\n";
    }
  }
  return 0; 
}

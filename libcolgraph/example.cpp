#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

int main()
{
   using namespace boost::multiprecision;

   // int128_t v = 1;

   // // Do some fixed precision arithmetic:
   // for(unsigned i = 1; i <= 20; ++i)
   //    v *= i;

   // std::cout << v << std::endl; // prints 2432902008176640000 (i.e. 20!)

   // // Repeat at arbitrary precision:
   // cpp_int u = 1;
   // for(unsigned i = 1; i <= 100; ++i)
   //    u *= i;

   // std::cout << u << std::endl;

   // int128_t w = 4;
   // int128_t x = 7;

   // int a = 4;
   // int b = 7;
   
   // std::cout << w + x << std::endl;
   // std::cout << w * x << std::endl;
   // std::cout << (w | x) << std::endl;
   // std::cout << (w & x) << std::endl;
   // std::cout << (w ^ x) << std::endl;
   // std::cout << (x << b) << std::endl;
   // std::cout << (a << b) << std::endl;

   int128_t r = 34;
   int numBits = 6;
   for (int i = 0; i < numBits; i++)
      std::cout << bit_test(r, i);

   return 0;

}

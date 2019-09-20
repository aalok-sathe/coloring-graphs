#include <bitset>

#include <iostream>

int main()
{
   
   std::bitset<128> foo;
   foo = 6;
   std::cout << foo << std::endl;

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

   // int128_t r = 34;
   // int numBits = 6;
   // for (int i = 0; i < numBits; i++)
   //    std::cout << bit_test(r, i);

   // int128_t c = 127;
   // int num = ((1 << 3) - 1) ^ ((1 << (1 - 1)) - 1);
   // std::cout << (c ^ num) << std::endl;

   return 0;

}

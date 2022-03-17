#include <iostream>

template<typename T>
requires (!std::is_pointer_v<T>)
  T maxValue(T a, T b)
{
    return b < a ? a : b;
}

int main(){

  int x = 42;
  int y = 77;
  std::cout << maxValue(x, y) << '\n';      // OK: maximum value of ints
//  std::cout << maxValue(&x, &y) << '\n';    // ERROR: constraint not met

  return 0;
}

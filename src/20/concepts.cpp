#include <iostream>

/* before using concept*/
template<typename T>
requires (!std::is_pointer_v<T>)
  T maxValue(T a, T b)
{
    return b < a ? a : b;
}

template<typename T>
concept IsPointer = std::is_pointer_v<T>;

/*after using concept*/

template<typename T>
requires (!IsPointer<T>)
T maxValue_concept(T a, T b)
{
    return b < a ? a : b;
}

/* overloading */
template<typename T>
requires (IsPointer<T>)
  T maxValue_concept(T a, T b)
{
  return maxValue(*a,*b);
}

/* using type constraint*/
template<IsPointer T>
auto maxValue_concept2(T a, T b)
{
  return maxValue(*a,*b);
}
/* same but using auto */
auto maxValue_concept3(IsPointer auto a, IsPointer auto b)
{
  return maxValue(*a,*b);
}

/* more constraint ( the value should be comparable ) */
auto maxValue(IsPointer auto a, IsPointer auto b)
  requires std::three_way_comparable_with<decltype(*a), decltype(*b)>
{
  return maxValue(*a, *b);
}

/* includes object that has *operator */
template<typename T>
concept IsPointerObject = requires(T p) { *p; };




int main(){

  int x = 42;
  int y = 77;
  std::cout << maxValue(x, y) << '\n';      // OK: maximum value of ints
  std::cout << maxValue_concept(x, y) << '\n';      // OK: maximum value of ints
//  std::cout << maxValue(&x, &y) << '\n';    // ERROR: constraint not met
  std::cout << maxValue_concept(&x, &y) << '\n';    // ERROR: constraint not met

  return 0;
}

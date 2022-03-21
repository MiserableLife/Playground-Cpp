#include <iostream>
#include <vector>
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



/* nawrrowing occurs */
template<typename F, typename T>
requires std::convertible_to<F, T>
void add(F, T)
{
     std::cout << "may be narrowing\n";
}

/* without narrowing constrain*/
/* Because it uses convertible_to and more, it subsumes above template ... so, it is more constrained  */
template<typename From, typename To>
concept ConvertsWithoutNarrowing =
    std::convertible_to<From, To> &&
        requires (From&& x) {
                { std::type_identity_t<To[]>{std::forward<From>(x)} }
                         -> std::same_as<To[1]>;
                             };

template<typename Coll, typename T>
requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
void add(Coll& coll, const T& val)
{
  std::cout<<"without narrowing"<<std::endl;
  coll.push_back(val);
}


int main(){
#if 0
  int x = 42;
  int y = 77;
  std::cout << maxValue(x, y) << '\n';      // OK: maximum value of ints
  std::cout << maxValue_concept(x, y) << '\n';      // OK: maximum value of ints
//  std::cout << maxValue(&x, &y) << '\n';    // ERROR: constraint not met
  std::cout << maxValue_concept(&x, &y) << '\n';    // ERROR: constraint not met
#endif
  std::vector<int> xx;
  add(xx, 1);
//  add(xx,1ul);
  return 0;
}

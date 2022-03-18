#include <iostream>
#include <vector>
#include <atomic>
#include <set>
//#define BC
#ifdef BC
template<typename Coll, typename T>
void add(Coll c, T t){
  c.push_back(t);
}
#else

template<typename Coll, typename T>
concept SupportsPushBack = requires(Coll c, T v) {
      c.push_back(v);
};

template<typename Coll, typename T>
requires std::convertible_to<T, typename Coll::value_type> && SupportsPushBack<Coll,T>
void add(Coll& coll, const T& val)
{
    coll.push_back(val);
}

#endif
int main(){

  std::vector<int> vec;
  add(vec, 42);       // OK
  add(vec, "hello");  // ERROR: no conversion from string literal to int

  std::set<int> coll;
  add(coll, 42);      // ERROR: no push_back() supported by std::set<>

  std::vector<std::atomic<int>> aiVec;
  std::atomic<int> ai{42};
  add(aiVec, ai);     // ERROR: cannot copy/move atomics


   return 0;

}

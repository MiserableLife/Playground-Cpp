#include <iostream>
#include <vector>
#include <set>
#include <ranges>
#include <atomic>

template <typename From, typename To>
concept ConvertsWithoutNarrowing = std::convertible_to<From,To> && requires(From&& x){
  {
  std::type_identity_t<To[]>{std::forward<From>(x)}} -> std::same_as<To[1]>;
};

template<typename T>
concept SupportsPushBack = requires(T coll) { 
  coll.push_back(std::declval<typename T::value_type>());
};

template<typename Coll, typename T>
requires ConvertsWithoutNarrowing<T, typename Coll::value_type>
void add(Coll& coll, const T& val){
  if constexpr(SupportsPushBack<Coll>){
    coll.push_back(val);
  }
  else
  {
    coll.insert(val);
  }
}

template<typename Coll, std::ranges::input_range T>
requires ConvertsWithoutNarrowing<std::ranges::range_value_t<T>,
         typename Coll::value_type>
void add(Coll& coll, const T& val){
  if constexpr(SupportsPushBack<Coll>){
    coll.insert(coll.end(), std::ranges::begin(val),
        std::ranges::end(val));
  }
  else{
    coll.insert(std::ranges::begin(val), std::ranges::end(val));
  }
}
int main(){
  std::vector<int> iVec;
  add(iVec, 42);
  std::set<int> iSet;
  add(iSet, 42);

  short s  = 42;
  add(iVec,s);

  long long ll = 42;

  std::vector<double> dVec;
  add(dVec, 0.7);
  add(dVec, 0.7f);

  add(iVec,iSet);
  add(iSet,iVec);

  int vals[] = {0,8,18};
  add(iVec,vals);

}


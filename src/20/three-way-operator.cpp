#include <iostream>
#include <compare>
#include <vector>
class Ops{

  public:
    int val;
    Ops(int v) : val(v) {}
    auto operator<=>(const Ops& rhs) const = default;
    bool operator==(const Ops& rhs) const = default;

};
int main(){

  Ops a(1), b(2), c(9), d(5);

  /*spaceshipt operator is called*/
  if( a< b ) {
    std::cout<< "a is less than b"<<std::endl;
  }

  /* the return value is one of the strong_ordering type */
  if( a<=>b  == std::strong_ordering::less) {
    std::cout<<"std::strong_ordering::less"<<std::endl;
  }
  else {
    std::cout<<"other return value"<<std::endl;
  }

  /* we could convert*/
  if( std::compare_strong_order_fallback(2.818, 3.14) == std::strong_ordering::less) {
    std::cout<<"Get std::strong_ordering::less from two floating operands "<<std::endl;
   }
  else{
    std::cout<<"something's wrong"<<std::endl;
  }

  /* we can sort objects because we defined comparison operators*/
  std::vector<Ops> v{std::move(a), std::move(b), std::move(c) , std::move(d)};
  std::sort(v.begin(), v.end());
  for(auto& o : v){
    std::cout<<o.val << " ";
  }
  std::cout<<std::endl;



  return 0;
}

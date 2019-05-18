#include <iostream>
#include <vector>
#include "base/Range.hpp"

int main()
{
  std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
  auto b1 = v.begin();
  auto b2 = v.begin()+3;
  auto b3 = v.begin()+6;

  auto e1 = v.begin()+3;
  auto e2 = v.begin()+6;
  auto e3 = v.end();

  auto R = addRange(b1,e1,2).addRange(b2,e2,2).addRange(b3,e3,2);

  for(auto it=R.begin;it!=R.end;++it)
  {
    std::cout << *it << std::endl;
  }


  auto previous = R.previous;
  for(auto it=previous.begin;it!=previous.end;++it)
  {
    std::cout << *it << std::endl;
  }

  auto previous2 = previous.previous;
  for(auto it=previous2.begin;it!=previous2.end;++it)
  {
    std::cout << *it << std::endl;
  }

  return 0;
}

// q2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <array>
#include <iterator>
#include <iostream>

#include <boost/range/adaptor/indirected.hpp>
#include <map>
#include <string>
#include <utility>

struct X {
  int val;
  X(int v) : val(v) {}
};

using namespace boost::adaptors;

int main()
{
  std::vector<X> input; // = { 0,1,2,3,4,5,6,7,8,9 };
  for(int i=0; i<10; i++) 
    input.push_back(X(i));

  boost::random_shuffle(input);

  for (const auto& elem : input )
    std::cout << elem.val << '\n';
  std::cout << '\n';

  for (const auto& elem : stride(input, 2))
    std::cout << elem.val << '\n';

  std::cout << boost::size(stride(input, 2));
  std::cout << '\n';

  // Counting with boost::count()
  /*
  std::array<int, 6> a{ 0, 1, 0, 1, 0, 1 };
  std::cout << boost::count(a, 0) << '\n';
  */

  // Filtering a range with boost::adaptors::filter()
  /*
  std::array<int, 6> a{ { 0, 5, 2, 1, 3, 4 } };
  boost::copy(boost::adaptors::filter(a, [](int i) { return i > 2; }),
    std::ostream_iterator<int>{std::cout, ","});
  */

  // Using keys(), values() and indirect()
  /*
  std::array<int, 3> a{ 0, 1, 2 };
  std::map<std::string, int*> m;   // m stores pointers to the values
  m.insert(std::make_pair("a", &a[0]));
  m.insert(std::make_pair("b", &a[1]));
  m.insert(std::make_pair("c", &a[2]));
  
  boost::copy(boost::adaptors::keys(m), std::ostream_iterator<std::string>{std::cout, ","});
  // boost::copy(boost::adaptors::indirect(boost::adaptors::values(m)), std::ostream_iterator<int>{std::cout, ","});
  boost::copy(boost::adaptors::values(m) | boost::adaptors::indirected, std::ostream_iterator<int>(std::cout, ","));
  */

  /*
  std::string s = "The Boost C++ Libraries";
  boost::regex expr{ "[\\w+]+" };
  boost::copy(boost::adaptors::tokenize(s, expr, 0,
    boost::regex_constants::match_default),
    std::ostream_iterator<std::string>{std::cout, ","});
  */

}

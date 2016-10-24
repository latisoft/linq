// captures_lambda_expression.cpp
// compile with: /EHsc
#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

// fibonacci in compile time by constexpr
constexpr int fabonacci(int n) {
  return (n < 2) ? 0 : 
    (fabonacci(n - 1) + fabonacci(n - 2));
}

// fibonacci in compile time by meta-function
template <int N>
struct fab_meta {
  enum { val = fab_meta<N - 2>::val + fab_meta<N - 1>::val };
};
template <> struct fab_meta<0> { enum { val = 1 }; };
template <> struct fab_meta<1> { enum { val = 1 }; };

using namespace std;
int main()
{
  const int N = 10;
  vector<int> vec(2, 1);
  for (int i = 2; i < N; i++) {
    vec.push_back(vec[i - 2] + vec[i - 1]);
  }
  auto show = [](int i) { cout << i << " "; };
  std::for_each(vec.begin(), vec.end(), show) { };
  cout << endl;

  vector<int> series;
  series = { fabonacci(0), fabonacci(1),  fabonacci(3),  fabonacci(4),  fabonacci(5), };
  for (int fn : vec) 
    cout << fn << ",";
  cout << endl;

  series = { fab_meta<0>::val, fab_meta<1>::val,  fab_meta<2>::val,  fab_meta<3>::val,  fab_meta<4>::val, fab_meta<5>::val };
  for (auto fn : vec)
    cout << fn << ",";
}




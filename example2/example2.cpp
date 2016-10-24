/*
#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
  std::string line;
  boost::regex pat("^Subject: (Re: |Aw: )*(.*)");

  while (std::cin)
  {
    std::getline(std::cin, line);
    boost::smatch matches;
    if (boost::regex_match(line, matches, pat))
      std::cout << matches[2] << std::endl;
  }
}
*/
template <typename CType>
class SafeArray 
{
  CType *_array;
  bool isSafe(int i) { return (0 <= i && i < length) ? true : false; }
public:
  int   length;
  SafeArray(int len) {
    length = len;
    _array = new CType[len];
  }
  ~SafeArray() { delete[] _array; };

  CType get(int);
  void set(int, CType);
};

template <class CType>
inline CType SafeArray<CType>::get(int i) {
  if (isSafe(i)) {
    return _array[i];
  }
  else { cout << "Get: Out of range!!"; return -1; }
}
template <class CType>
inline void SafeArray<CType>::set(int i, CType value) {
  if (isSafe(i)) {
    _array[i] = value;
  }
  else { cout << "Set: Out of range!!"; }
}


#include <iostream> 
using namespace std;
int main() 
{
  SafeArray<int> safeArray1(10);
  SafeArray<double> safeArray2(10);

  for (int i = 0; i < safeArray1.length; i++) {
    safeArray1.set(i, (i + 1) * 10);
  }
  for (int i = 0; i < safeArray1.length; i++) {
    cout << safeArray1.get(i) << " ";
  }
  cout << endl;

  for (int i = 0; i < safeArray2.length; i++) {
    safeArray2.set(i, (i + 1) * 0.1);
  }
  for (int i = 0; i < safeArray2.length; i++) {
    cout << safeArray2.get(i) << " ";
  }
  cout << endl;
  return 0;
}
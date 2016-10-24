#include <boost/assign.hpp>
#include <iterator>
#include <iostream>
#include <vector>

#include <boost/range.hpp>
#include <boost/range/any_range.hpp>


template< typename R >
struct myRange : 
  public boost::iterator_range< typename boost::range_iterator<R>::type >
{
  typedef boost::iterator_range< typename boost::range_iterator<R>::type > base;
  typedef typename boost::range_iterator<R>::type iterator;

  myRange(R& r) : base(iterator(boost::begin(r)), iterator(boost::end(r))) {}
};

struct myAdaptor_Clamp {
  int n0, n1;
  myAdaptor_Clamp(int tmp0, int tmp1) { n0 = tmp0; n1 = tmp1; }
  ~myAdaptor_Clamp() {}
};

template<typename Rng>
inline myRange<Rng> 
operator|(Rng& r, myAdaptor_Clamp clamp)
{
  for (auto& elem : r) {

    if (elem.val > clamp.n1)
      elem.val = clamp.n1;
    else if (elem.val > clamp.n0) {
      // KEEP
    }
    else
      elem.val = clamp.n0;
  }
  return myRange<Rng>(r);
}

// RandomAccessRng > BidirectionalRng > ForwardRng > SinglePassRng
struct XX {
  int val;
public:
  XX(int v) { val = v; }
  ~XX() {}
};

int main()
{
  const myAdaptor_Clamp clamp(20, 80); // = detail::x(10, 100);
  std::cout << "SinglePassRng: Clamp the data into 20~80.\n";

  std::vector<XX> input = { XX(96), XX(48), XX(15), XX(75) };

  // boost::any_range<int, boost::forward_traversal_tag, XEntity&, std::ptrdiff_t> elems = (input | myX);
  for (const auto& elem : input | clamp)
    std::cout << elem.val << ' ';
  std::cout << '\n';

  return 0;
}
// Output: 80 40 20 75
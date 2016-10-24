

// #include <boost/range/adaptor/reversed.hpp>
// #include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <iterator>
#include <iostream>
#include <vector>
#include <array>

// 1. Provide a range for your return type, for example:
template< typename R >
struct reverse_range :
  boost::iterator_range<
  boost::reverse_iterator<
  typename boost::range_iterator<R>::type> >
{
private:
  typedef boost::iterator_range<
    boost::reverse_iterator<
    typename boost::range_iterator<R>::type> > base;

public:
  typedef boost::reverse_iterator<
    typename boost::range_iterator<R>::type > iterator;

  reverse_range(R& r)
    : base(iterator(boost::end(r)), iterator(boost::begin(r)))
  { 
    
  }
};
// 2. Provide a tag to uniquely identify your adaptor in the operator| function overload set
namespace detail {
  struct reverse_forwarder {};
}
// 3. Implement operator|
template< class BidirectionalRng >
inline reverse_range<BidirectionalRng>
operator|(BidirectionalRng& r, detail::reverse_forwarder)
{
  return reverse_range<BidirectionalRng>(r);
}

template< class BidirectionalRng >
inline reverse_range<const BidirectionalRng>
operator|(const BidirectionalRng& r, detail::reverse_forwarder)
{
  return reverse_range<const BidirectionalRng>(r);
}
int main()
{
  // 4. Declare the adaptor itself(it is a variable of the tag type).  
  const detail::reverse_forwarder reversed = detail::reverse_forwarder();

  std::vector<int> input { 1, 2, 3, 4 };

  for (const auto& elem : input | reversed )
    std::cout << elem << ' ';
  std::cout << '\n';
  return 0;
}



// 1. Provide a range for your return type, for example:
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include <boost/assign.hpp>
#include <iterator>
#include <iostream>
#include <vector>
#include <array>

template<typename Value>
class replace_value
{
public:
  typedef const Value& result_type;
  typedef const Value& argument_type;

  replace_value(const Value& from, const Value& to)
    : m_from(from), m_to(to)
  {
  }
  const Value& operator()(const Value& x) const
  {
    return (x == m_from) ? m_to : x;
  }
private:
  Value m_from;
  Value m_to;
};

template<typename Range>
class replace_range
  : public boost::iterator_range<
  boost::transform_iterator<
  replace_value<typename boost::range_value<Range>::type>,
  typename boost::range_iterator<Range>::type> >
{
private:
  typedef typename boost::range_value<Range>::type value_type;
  typedef typename boost::range_iterator<Range>::type iterator_base;
  typedef replace_value<value_type> Fn;
  typedef boost::transform_iterator<Fn, iterator_base> replaced_iterator;
  typedef boost::iterator_range<replaced_iterator> base_t;

public:
  replace_range(Range& rng, value_type from, value_type to)
    : base_t(replaced_iterator(boost::begin(rng), Fn(from, to)),
      replaced_iterator(boost::end(rng), Fn(from, to)))
  {
  }
};

// 2. Implement a holder class to hold the arguments required to construct the RangeAdaptor.
//    The holder combines multiple parameters into one that can be passed as the right operand of operator|().
template<typename T>
class replace_holder : public boost::range_detail::holder2<T>
{
public:
  replace_holder(const T& from, const T& to)
    : boost::range_detail::holder2<T>(from, to)
  { }
private:
  void operator=(const replace_holder&) {};
};

// 4. Define operator|
template<typename SinglePassRange>
inline replace_range<SinglePassRange>
operator|(SinglePassRange& rng,
  const replace_holder<typename boost::range_value<SinglePassRange>::type>& f)
{
  return replace_range<SinglePassRange>(rng, f.val1, f.val2);
}

template<typename SinglePassRange>
inline replace_range<const SinglePassRange>
operator|(const SinglePassRange& rng,
  const replace_holder<typename boost::range_value<SinglePassRange>::type>& f)
{
  return replace_range<const SinglePassRange>(rng, f.val1, f.val2);
}

int main()
{
  // 3. Define an instance of the holder with the name of the adaptor
  static boost::range_detail::forwarder2<replace_holder>
    replaced = boost::range_detail::forwarder2<replace_holder>();

  std::vector<int> input{ 1, 2, 3, 4 };

  for (const auto& elem : input | replaced(2,0)) // from 2 to 0
    std::cout << elem << ' ';
  std::cout << '\n';
  return 0;
}



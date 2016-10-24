
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
using namespace boost::adaptors;
#include <boost/range/numeric.hpp>
using boost::accumulate;

#include <iostream> 
#include <string>
#include <vector>
#include <functional>
using namespace std;

struct OrderItem {
  string product;
  int amount;
  double price;
  OrderItem(string product, int amount, double price) : product(product), amount(amount), price(price) {}
};
vector<OrderItem> order {
  { "Apple",  4, 2.0 },
  { "Banana", 2, 1.5 },
  { "Orange", 7, 0.4 },
  { "Apple",  6, 3.0 },
};

struct sumItemCost
{
  sumItemCost(string product) : product(product) {}

  double operator()(const OrderItem& item) const {
    return (item.product == product) ? item.amount * item.price : 0;
  }
private:
  string product;
};


int main()
{
  double sum = 0.0;
  for (const auto& item : order) {
      if (item.product == "Apple")
        sum += item.amount * item.price;
  }
  cout << "1. sum = " << sum << endl;
  
  sum = accumulate(
      order
      | filtered([](const OrderItem& item) { return item.product == "Apple"; })
      | transformed(function<double(const OrderItem&)>([](const OrderItem& item) {
        return item.amount * item.price; })), 0.0 );
  cout << "2. sum = " << sum << endl;
  
  sum = accumulate(
    order | transformed(sumItemCost("Apple")),
    0.0);
  cout << "3. sum = " << sum << endl;

  /* C# Version
  var tmp = from item in order
  where item.product == "Apple"
    select item.amount * item.price;
  double sum = tmp.Sum();
  */
}
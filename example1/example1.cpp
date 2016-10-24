  
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
using namespace boost::adaptors;
// using boost::accumulate;

#include <iostream> 
#include <string>
#include <vector>
#include <functional>
using namespace std;

struct OrderItem {
  string  product;
  double  price;
  int     amount;
  OrderItem(string name, int q, double m) : 
    product(name), amount(q), price(m) {}
};
struct Order {
  double discountPercent;
  vector<OrderItem> orderItems;
  Order(double discountPercent, vector<OrderItem> orderItems) : 
    discountPercent(discountPercent), orderItems(orderItems) {}
};

struct SumOrderCost : public unary_function<const Order, double> 
{
  SumOrderCost(string product) : product(product) {}

  double operator()(const Order& order) const {
    auto wanted = [=](const OrderItem& item) { 
                      return item.product == product;
                  };
    auto total  = function<double(const OrderItem&)>([](const OrderItem& item) { 
                      return item.amount * item.price; 
                  });
    return accumulate(order.orderItems | filtered(wanted) | transformed(total), 0.0) * (1.0 - order.discountPercent / 100.0);
  }
private:
  string product;
};

// (3+1)*1.75*0.9 + (36+4)*1.75*10*0.8 + 18*1.75*0.8 = 6.3 + 56 + 25.2 = 87.5
vector<Order> orders{
  { 10,{ { "Apple",  3, 1.75 },{ "Apple",  1, 1.75 },{ "Orange", 14, 1.25 },{ "Papaya", 2, 10.05 } } }, // Normal
  { 20,{ { "Apple", 36, 1.75 },{ "Apple",  4, 1.75 },{ "Orange", 14, 1.25 },{ "Cherry", 2, 20.05} } },  // Normal
  { 20,{ { "Apple", 18, 1.75 },{ "Grapes", 2, 8.40 } } }                                                // VIP
};

int main()
{
  double sum = 0.0;
  for (const auto& order : orders) {
    for (const auto& item : order.orderItems) {
      if (item.product == "Apple")
        sum += item.amount * item.price * (1.0 - order.discountPercent / 100.0);
    }
  }
  std::cout << "1. sum = " << sum << endl;

  sum = 0.0;
  for (const auto& order : orders) {
    sum += accumulate(
      order.orderItems
      | filtered([](const OrderItem& item) {
        return item.product == "Apple"; })
      | transformed(function<double(const OrderItem&)>([&order](const OrderItem& item) {
        return item.amount * item.price * (1.0 - order.discountPercent / 100.0); })),
        0.0
    );
  }
  std::cout << "2. sum = " << sum << endl;

  sum = accumulate(
    orders | transformed(SumOrderCost("Apple")),
    0.0
  );
  std::cout << "3. sum = " << sum << endl;
}
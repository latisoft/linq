#pragma once

class resource {
  int x = 0;
};
class RuleOf5
{
  resource* p;
public:
  RuleOf5() : p{ new resource{} }
  { }

  // copy constructor
  RuleOf5(const RuleOf5& other) : p{ new resource{ *(other.p) } }
  { }

  // copy assignment operator
  RuleOf5& operator=(const RuleOf5& other) {
    if (&other != this) {
      delete p;
      p = nullptr;
      p = new resource{ *(other.p) };
    }
    return *this;
  }

  // destructor
  ~RuleOf5() { delete p; }

  // move constructor
  RuleOf5(RuleOf5&& other) : p{ other.p }
  {
    other.p = nullptr;
  }

  // move assignment operator
  RuleOf5& operator=(RuleOf5&& other) {
    if (&other != this) {
      delete p;
      p = other.p;
      other.p = nullptr;
    }
    return *this;
  }
};
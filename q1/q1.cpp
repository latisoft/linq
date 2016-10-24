// q1.cpp : Defines the entry point for the console application.
//

#include  "stdafx.h"
#include  "MemoryBlock.h"
#include  "RuleOf5.h"


#define   Memory_Block    0
#define   Rule_Of_5       1

using namespace std;
void test(int item) 
{
  switch (item) {
    case Memory_Block: 
      { MemoryBlock mb(100); }
      break;

    case Rule_Of_5: 
      { RuleOf5 ro5; }
      break;
  }

}
int main()
{
    test(Memory_Block);
    test(Rule_Of_5);
    return 0;
}


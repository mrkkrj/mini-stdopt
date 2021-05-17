
#include <MiniStdOptional.h>

#include <iostream>
#include <string>
#include <cassert>


namespace opt = ibkrj::stdopt_wrap;


// helpers

template <class T>
void check(const opt::optional<T>& opt, const std::string& typeStrg = typeid(T).name())
{
   if (opt)
   {
      std::cout << "optional(" << typeStrg << ") has a value";
      std::cout << ", value=" << opt.value() << "\n";
   }
   else
   {
      std::cout << "optional(" << typeStrg << ") is empty (nullopt)\n";
   }
}


struct TestStruct
{
   int i;
   double d;
   TestStruct() : i(1), d(1.11) {};
   TestStruct(int ival, double dval) : i(ival), d(dval) {};
   ~TestStruct() {
      i = 0;
      d = 0.0;
   };
   friend std::ostream& operator<<(std::ostream& os, const TestStruct& ts);
};

std::ostream& operator<<(std::ostream& os, const TestStruct& ts)
{
   os << ts.i << '/' << ts.d;
   return os;
}


// tests

int main()
{
   // Note: _std::optional_ or _ibkrj::utils::MinStdOptional_ will be used here for _opt::optional_:
   //   1. depending on the Microsoft compiler version
   //   2. depending on COMPILER_HAS_NO_STD_OPTIONAL definition

   // built-ins
   opt::optional<int> optInt(1);
   assert(optInt.has_value());
   check<int>(optInt);

   optInt = opt::nullopt;
   check<int>(optInt);

   optInt.emplace(44);
   check<int>(optInt);

   // PODT
   opt::optional<TestStruct> optStruct;
   check<TestStruct>(optStruct);

   TestStruct testStruct;
   optStruct = testStruct;
   check<TestStruct>(optStruct);

   optStruct.emplace(44, 44.44);
   check<TestStruct>(optStruct);

   // full C++ class
   opt::optional<std::string> optStrg;
   assert(!optStrg.has_value());
   check<std::string>(optStrg, "string");

   std::string strg = "TEST strg 1"; 
   optStrg = strg; 
   assert(optStrg.has_value());
   check<std::string>(optStrg, strg);

   optStrg = "TEST strg 2";
   check<std::string>(optStrg, "string");

   optStrg.emplace("TEST strg 3");
   assert(optStrg.has_value());
   check<std::string>(optStrg, "string");

   // finito
   std::cout << "TEST::: finished ---";
}

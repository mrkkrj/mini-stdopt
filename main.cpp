
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
   TestStruct() : i(1), d(1.0) {};
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


int main()
{
   // std::optional or MinStdOptional will be used for opt::optional (depending on the compiler)!

   opt::optional<int> optInt(1);
   assert(optInt.has_value());
   check<int>(optInt);

   optInt = opt::nullopt;
   check<int>(optInt);

   optInt.emplace(44);
   check<int>(optInt);


   opt::optional<std::string> optStrg;
   check<std::string>(optStrg, "string");

#if 0
   //optStrg = "TEST!!!"; // OPEN TODO:: conversion!!!
   std::string strg = "TEST!!!"; 
   optStrg = strg; // OPEN TODO::: not working yet!!!
#endif

   optStrg.emplace("TEST!!!");
   assert(optStrg.has_value());
   check<std::string>(optStrg, "string");

   opt::optional<TestStruct> optStruct;
   check<TestStruct>(optStruct);

   TestStruct testStruct;
   optStruct = testStruct;
   check<TestStruct>(optStruct);

   optStruct.emplace(44, 44.44);
   check<TestStruct>(optStruct);
}

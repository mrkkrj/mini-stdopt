# mini-stdopt
An "in-place" replacement of std::optional for ancient (Microsoft...;) compilers.

WIP!!! -> std::string not quite working yet, add VisualStudio 2015 example

##Example:

    #include <MiniStdOptional.h>

    namespace opt = ibkrj::stdopt_wrap;

    void optTest()
    {
       opt::optional<int> optInt(1);
       assert(optInt.has_value());
       auto val = optInt.value();

       optInt = opt::nullopt;
       assert(!optInt.has_value());
    }

# TODO:
 - get the example to run with std::string
 - add (more) tests
 - add description
 - add CMake support

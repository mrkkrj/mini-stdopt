# mini-stdopt
An "in-place" replacement of std::optional for ancient (Microsoft...;) compilers.

**WIP!!!** -> _std::string_ not quite working yet, add _VisualStudio 2015_ example

## Example:

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
 - get the example to run with _std::string_
 - add (more) tests
 - add description
 - add CMake support

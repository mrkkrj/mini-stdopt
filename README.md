# mini-stdopt
An "in-place" replacement of _std::optional_ for ancient (Microsoft... ;) compilers. Your compiler will need C++11 support though (as C++98 wasn't tested)!

** WIP!!! ** -> _VisualStudio 2015_ example missing, much more tests needed!

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
 - add _VisualStudio 2015_ example
 - add (more) tests
 - add description
 - add CMake support

/** @file   MiniStdOptional.cpp
   @author  Marek Krajewski (mrkkrj) - www.ib-krajewski.de
   @date    26.11.2020

   @brief Needed global variables for "in-place" replacement of std::optional for 
          ancient (Microsoft...;) compilers.

   @copyright  Copyright 2021, Marek Krajewski, released under the terms of LGPL v3
*/

#include <MiniStdOptional.h>

namespace ibkrj { namespace stdopt_wrap {

#if (defined(_MSC_VER) && _MSC_VER <= 1900) || (!defined(_MSC_VER) &&  __cplusplus <= 201103L) || \
     defined(COMPILER_HAS_NO_STD_OPTIONAL) 

// Visual Studio 2015 or older, C++11 or older!
const ibkrj::utils::Nullopt_Impl_Type nullopt = ibkrj::utils::g_Nullopt_Impl;

#else

// a modern compiler
const ibkrj::utils::Nullopt_Impl_Type nullopt = std::nullopt;

#endif

} }


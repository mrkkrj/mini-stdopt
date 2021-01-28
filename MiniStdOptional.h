/** @file   MiniStdOptional.h
   @author  Marek Krajewski EXT (www.ib-krajewski.de)
   @date    26.11.2020

   @brief An "in-place" replacement of std::optional for ancient (Microsoft...;) compilers.

   @copyright  Copyright 2021, Marek Krajewski, released under the terms of LGPL v3
*/

#pragma once


// -- TEST:: force usage of MinStdOptional!
#define COMPILER_HAS_NO_STD_OPTIONAL


#if (defined(_MSC_VER) && _MSC_VER <= 1900) || (!defined(_MSC_VER) &&  __cplusplus <= 201103L) || \
     defined(COMPILER_HAS_NO_STD_OPTIONAL) 

// Visual Studio 2015 or older, C++11 or older!
#include <exception>
#include <cassert>


namespace ibkrj { 
   namespace utils { 

   /**
      @brief: Disengaged state indicator
    */
   struct MinStdNulloptFakeType
   {
      struct init {};
      constexpr explicit MinStdNulloptFakeType(init) {}
   };
   
   constexpr MinStdNulloptFakeType g_Nullopt_Impl{ MinStdNulloptFakeType::init() };
   typedef MinStdNulloptFakeType Nullopt_Impl_Type;


   /**
      @brief: Exception for the minimal option class
    */
   class MinStdBadOptAccessExc 
      : public std::exception {
   public:
      /*[[nodiscard]]*/ virtual const char* what() const noexcept override {
         return "Bad optional access";
      }
   };

   typedef MinStdBadOptAccessExc MinStdBadOptAccessExc_Impl;


   /**
      @brief: A minimal implementation for option<T> type - implements only functions 
              currently used in code of the project where it was extracted from!
    */
   template <class T> 
      class MinStdOptionImpl 
   {
   public:
      MinStdOptionImpl(T val) 
         : m_value(val), m_initialized(true) {
      }
      MinStdOptionImpl() 
         : m_constructDummy{}, m_initialized(false) {
      }
      MinStdOptionImpl(const MinStdNulloptFakeType&) 
         : m_constructDummy{}, m_initialized(false) {
      }

      ~MinStdOptionImpl() {
         clear();
      }

      bool has_value() const { 
         return m_initialized; 
      }

      T value() const { 
         if (m_initialized) {
            return m_value;
         }
         throw MinStdBadOptAccessExc();
      }

      template< class... Args > T& emplace(Args&&... args) {
         clear();

         // must use placement new
         auto dataptr = static_cast<const void*>(std::addressof(m_value));
         ::new (const_cast<void*>(dataptr)) T(std::forward<Args>(args)...);
         
         m_initialized = true;
         return m_value;
      }

      MinStdOptionImpl& operator=(MinStdNulloptFakeType) noexcept {
         clear();
         return *this;
      }

      operator T () {
         assert(m_initialized);
         return m_value;
      }
      
      explicit constexpr operator bool() const noexcept { 
         return m_initialized == true;
      }

      constexpr T const& operator *() const& {
         assert(m_initialized);
         return m_value;
      }

   private:
      void clear() {
         // placement new was used!
         if (m_initialized) {
            m_value.T::~T();
         }
         m_initialized = false;
      }

      union {
         char m_constructDummy;
         T m_value;
      };      
      bool m_initialized;
   }; 


   // equality operators

   template <class T> constexpr 
      bool operator==(const MinStdOptionImpl<T>& lhs, const MinStdOptionImpl<T>& rhs)
   {
      return bool(lhs) != bool(rhs) ? false : bool(lhs) == false ? true : *lhs == *rhs;
   }

   template <class T> constexpr 
      bool operator!=(const MinStdOptionImpl<T>& lhs, const MinStdOptionImpl<T>& rhs)
   {
      return !(lhs == rhs);
   }

#if 0 // not yet used in code...
   // comparison
   template <class T> constexpr 
      bool operator<(const MinStdOptionImpl<T>& lhs, const MinStdOptionImpl<T>& rhs)
   {
      return (!rhs) ? false : (!lhs) ? true : *lhs < *rhs;
   }

   template <class T> constexpr 
      bool operator>(const MinStdOptionImpl<T>& lhs, const MinStdOptionImpl<T>& rhs)
   {
      return (rhs < lhs);
   }
#endif


   // comparison with nullopt

   template <class T> constexpr 
      bool operator==(const MinStdOptionImpl<T>& lhs, MinStdNulloptFakeType) noexcept
   {
      return (!lhs);
   }

   template <class T> constexpr 
      bool operator==(MinStdNulloptFakeType, const MinStdOptionImpl<T>& rhs) noexcept
   {
      return (!rhs);
   }

   template <class T> constexpr 
      bool operator!=(const MinStdOptionImpl<T>& lhs, MinStdNulloptFakeType) noexcept
   {
      return bool(lhs);
   }

   template <class T> constexpr 
      bool operator!=(MinStdNulloptFakeType, const MinStdOptionImpl<T>& rhs) noexcept  
   {
      return bool(rhs);
   }

   // comparison with T
   template <class T> constexpr 
      bool operator>(const T& val, const MinStdOptionImpl<T>& rhs)
   {
      return bool(rhs) ? val > *rhs : true;
   }

   template <class T> constexpr 
      bool operator>(const MinStdOptionImpl<T>& lhs, const T& val)
   {
      return bool(lhs) ? *lhs > val : false;
   }

   template <class T> constexpr 
      bool operator<(const MinStdOptionImpl<T>& lhs, const T& val)
   {
      return bool(lhs) ? *lhs < val : true;
   }

   template <class T> constexpr 
      bool operator<(const T& val, const MinStdOptionImpl<T>& lhs)
   {
      return bool(lhs) ? val < *lhs : false;
   }


   // export

   template <class T>
      using MinStdOptClass_Impl = MinStdOptionImpl<T>;
   
} } 

#else

// A modern compiler
#include <optional>

namespace ibkrj {
   namespace utils {

   template <class T>
      using MinStdOptClass_Impl = std::optional<T>;

   typedef std::nullopt_t Nullopt_Impl_Type;
   constexpr std::nullopt_t g_Nullopt_Impl{ std::nullopt };

   typedef std::bad_optional_access MinStdBadOptAccessExc_Impl;

   } 
}

#endif


namespace ibkrj { namespace stdopt_wrap {

   // typedefs and constants to be used in widgets' code:
   template <class T>
      using optional = ibkrj::utils::MinStdOptClass_Impl<T>;
   
   extern const ibkrj::utils::Nullopt_Impl_Type nullopt;

   typedef ibkrj::utils::MinStdBadOptAccessExc_Impl bad_optional_access;

} }


#if 0 
// prepare the usage with Qt Widgets!

#include <QtCore/QMetaType>

// declare our optional<> alias for Qt usage!
Q_DECLARE_METATYPE(ibkrj::utils::optional<double>);
#endif


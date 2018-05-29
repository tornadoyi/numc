// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_CXX_H__
#define __NC_MACROS_CXX_H__



#if NC_GNUC_AT_MOST(4,3) && !NC_COMP_CLANG
// see bug 89
  #define NC_SAFE_TO_USE_STANDARD_ASSERT_MACRO 0
#else
#define NC_SAFE_TO_USE_STANDARD_ASSERT_MACRO 1
#endif


// Cross compiler wrapper around LLVM's __has_builtin
#ifdef __has_builtin
#  define NC_HAS_BUILTIN(x) __has_builtin(x)
#else
#  define NC_HAS_BUILTIN(x) 0
#endif

// A Clang feature extension to determine compiler features.
// We use it to determine 'cxx_rvalue_references'
#ifndef __has_feature
# define __has_feature(x) 0
#endif

// Some old compilers do not support template specializations like:
// template<typename T,int N> void foo(const T x[N]);
#if !( NC_COMP_CLANG && ((NC_COMP_CLANG<309) || defined(__apple_build_version__)) || NC_COMP_GNUC_STRICT && NC_COMP_GNUC<49)
#define NC_HAS_STATIC_ARRAY_TEMPLATE 1
#else
#define NC_HAS_STATIC_ARRAY_TEMPLATE 0
#endif

// Upperbound on the C++ version to use.
// Expected values are 03, 11, 14, 17, etc.
// By default, let's use an arbitrarily large C++ version.
#ifndef NC_MAX_CPP_VER
#define NC_MAX_CPP_VER 99
#endif

#if NC_MAX_CPP_VER>=11 && (defined(__cplusplus) && (__cplusplus >= 201103L) || NC_COMP_MSVC >= 1900)
#define NC_HAS_CXX11 1
#else
#define NC_HAS_CXX11 0
#endif

#if NC_MAX_CPP_VER>=14 && (defined(__cplusplus) && (__cplusplus > 201103L) || NC_COMP_MSVC >= 1910)
#define NC_HAS_CXX14 1
#else
#define NC_HAS_CXX14 0
#endif

// Do we support r-value references?
#ifndef NC_HAS_RVALUE_REFERENCES
#if NC_MAX_CPP_VER>=11 && \
    (__has_feature(cxx_rvalue_references) || \
    (defined(__cplusplus) && __cplusplus >= 201103L) || \
    (NC_COMP_MSVC >= 1600))
#define NC_HAS_RVALUE_REFERENCES 1
#else
#define NC_HAS_RVALUE_REFERENCES 0
#endif
#endif

// Does the compiler support C99?
#ifndef NC_HAS_C99_MATH
#if NC_MAX_CPP_VER>=11 && \
    ((defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901))       \
  || (defined(__GNUC__) && defined(_GLIBCXX_USE_C99)) \
  || (defined(_LIBCPP_VERSION) && !defined(_MSC_VER)) \
  || (NC_COMP_MSVC >= 1900) || defined(__SYCL_DEVICE_ONLY__))
#define NC_HAS_C99_MATH 1
#else
#define NC_HAS_C99_MATH 0
#endif
#endif

// Does the compiler support result_of?
#ifndef NC_HAS_STD_RESULT_OF
#if NC_MAX_CPP_VER>=11 && ((__has_feature(cxx_lambdas) || (defined(__cplusplus) && __cplusplus >= 201103L)))
#define NC_HAS_STD_RESULT_OF 1
#else
#define NC_HAS_STD_RESULT_OF 0
#endif
#endif

// Does the compiler support type_trais?
#ifndef NC_HAS_TYPE_TRAITS
#if NC_MAX_CPP_VER>=11 && (NC_HAS_CXX11 || NC_COMP_MSVC >= 1700)
#define NC_HAS_TYPE_TRAITS 1
#define NC_INCLUDE_TYPE_TRAITS
#else
#define NC_HAS_TYPE_TRAITS 0
#endif
#endif

// Does the compiler support variadic templates?
#ifndef NC_HAS_VARIADIC_TEMPLATES
#if NC_MAX_CPP_VER>=11 && (__cplusplus > 199711L || NC_COMP_MSVC >= 1900) \
  && (!defined(__NVCC__) || !NC_ARCH_ARM_OR_ARM64 || (NC_CUDACC_VER >= 80000) )
// ^^ Disable the use of variadic templates when compiling with versions of nvcc older than 8.0 on ARM devices:
//    this prevents nvcc from crashing when compiling Eigen on Tegra X1
#define NC_HAS_VARIADIC_TEMPLATES 1
#elif  NC_MAX_CPP_VER>=11 && (__cplusplus > 199711L || NC_COMP_MSVC >= 1900) && defined(__SYCL_DEVICE_ONLY__)
#define NC_HAS_VARIADIC_TEMPLATES 1
#else
#define NC_HAS_VARIADIC_TEMPLATES 0
#endif
#endif

// Does the compiler fully support const expressions? (as in c++14)
#ifndef NC_HAS_CONSTEXPR

#if defined(NC_CUDACC)
// Const expressions are supported provided that c++11 is enabled and we're using either clang or nvcc 7.5 or above
#if NC_MAX_CPP_VER>=14 && (__cplusplus > 199711L && (NC_COMP_CLANG || NC_CUDACC_VER >= 70500))
  #define NC_HAS_CONSTEXPR 1
#endif
#elif NC_MAX_CPP_VER>=14 && (__has_feature(cxx_relaxed_constexpr) || (defined(__cplusplus) && __cplusplus >= 201402L) || \
  (NC_GNUC_AT_LEAST(4,8) && (__cplusplus > 199711L)) || \
  (NC_COMP_CLANG >= 306 && (__cplusplus > 199711L)))
#define NC_HAS_CONSTEXPR 1
#endif

#ifndef NC_HAS_CONSTEXPR
#define NC_HAS_CONSTEXPR 0
#endif

#endif

// Does the compiler support C++11 math?
// Let's be conservative and enable the default C++11 implementation only if we are sure it exists
#ifndef NC_HAS_CXX11_MATH
#if NC_MAX_CPP_VER>=11 && ((__cplusplus > 201103L) || (__cplusplus >= 201103L) && (NC_COMP_GNUC_STRICT || NC_COMP_CLANG || NC_COMP_MSVC || NC_COMP_ICC)  \
      && (NC_ARCH_i386_OR_x86_64) && (NC_OS_GNULINUX || NC_OS_WIN_STRICT || NC_OS_MAC))
#define NC_HAS_CXX11_MATH 1
#else
#define NC_HAS_CXX11_MATH 0
#endif
#endif

// Does the compiler support proper C++11 containers?
#ifndef NC_HAS_CXX11_CONTAINERS
#if    NC_MAX_CPP_VER>=11 && \
         ((__cplusplus > 201103L) \
      || ((__cplusplus >= 201103L) && (NC_COMP_GNUC_STRICT || NC_COMP_CLANG || NC_COMP_ICC>=1400)) \
      || NC_COMP_MSVC >= 1900)
#define NC_HAS_CXX11_CONTAINERS 1
#else
#define NC_HAS_CXX11_CONTAINERS 0
#endif
#endif

// Does the compiler support C++11 noexcept?
#ifndef NC_HAS_CXX11_NOEXCEPT
#if    NC_MAX_CPP_VER>=11 && \
         (__has_feature(cxx_noexcept) \
      || (__cplusplus > 201103L) \
      || ((__cplusplus >= 201103L) && (NC_COMP_GNUC_STRICT || NC_COMP_CLANG || NC_COMP_ICC>=1400)) \
      || NC_COMP_MSVC >= 1900)
#define NC_HAS_CXX11_NOEXCEPT 1
#else
#define NC_HAS_CXX11_NOEXCEPT 0
#endif
#endif



#ifdef NC_EXCEPTIONS
#  define NC_THROW_X(X) throw X
#  define NC_THROW throw
#  define NC_TRY try
#  define NC_CATCH(X) catch (X)
#else
#  ifdef NC_CUDA_ARCH
#    define NC_THROW_X(X) asm("trap;")
#    define NC_THROW asm("trap;")
#  else
#    define NC_THROW_X(X) std::abort()
#    define NC_THROW std::abort()
#  endif
#  define NC_TRY if (true)
#  define NC_CATCH(X) else
#endif


#if NC_HAS_CXX11_NOEXCEPT
#   define NC_INCLUDE_TYPE_TRAITS
#   define NC_NOEXCEPT noexcept
#   define NC_NOEXCEPT_IF(x) noexcept(x)
#   define NC_NO_THROW noexcept(true)
#   define NC_EXCEPTION_SPEC(X) noexcept(false)
#else
#   define NC_NOEXCEPT
#   define NC_NOEXCEPT_IF(x)
#   define NC_NO_THROW throw()
#   define NC_EXCEPTION_SPEC(X) throw(X)
#endif

#endif

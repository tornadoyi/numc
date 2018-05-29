// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_UTILS_H__
#define __NC_MACROS_UTILS_H__


// Define name space

#define NS_BEGIN namespace numc {
#define NS_END }

#define NS_INTERNAL_BEGIN NS_BEGIN namespace internal {
#define NS_INTERNAL_END }}





/** Allows to disable some optimizations which might affect the accuracy of the result.
  * Such optimization are enabled by default, and set NC_FAST_MATH to 0 to disable them.
  * They currently include:
  *   - single precision ArrayBase::sin() and ArrayBase::cos() for SSE and AVX vectorization.
  */
#ifndef NC_FAST_MATH
#define NC_FAST_MATH 1
#endif

#define NC_DEBUG_VAR(x) std::cerr << #x << " = " << x << std::endl;

// concatenate two tokens
#define NC_CAT2(a,b) a ## b
#define NC_CAT(a,b) NC_CAT2(a,b)

#define NC_COMMA ,

// convert a token to a string
#define NC_MAKESTRING2(a) #a
#define NC_MAKESTRING(a) NC_MAKESTRING2(a)

// NC_STRONG_INLINE is a stronger version of the inline, using __forceinline on MSVC,
// but it still doesn't use GCC's always_inline. This is useful in (common) situations where MSVC needs forceinline
// but GCC is still doing fine with just inline.
#ifndef NC_STRONG_INLINE
#if NC_COMP_MSVC || NC_COMP_ICC
#define NC_STRONG_INLINE __forceinline
#else
#define NC_STRONG_INLINE inline
#endif
#endif

// NC_ALWAYS_INLINE is the stronget, it has the effect of making the function inline and adding every possible
// attribute to maximize inlining. This should only be used when really necessary: in particular,
// it uses __attribute__((always_inline)) on GCC, which most of the time is useless and can severely harm compile times.
// FIXME with the always_inline attribute,
// gcc 3.4.x and 4.1 reports the following compilation error:
//   Eval.h:91: sorry, unimplemented: inlining failed in call to 'const Eigen::Eval<Derived> Eigen::MatrixBase<Scalar, Derived>::eval() const'
//    : function body not available
//   See also bug 1367
#if NC_GNUC_AT_LEAST(4,2)
#define NC_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#define NC_ALWAYS_INLINE NC_STRONG_INLINE
#endif

#if NC_COMP_GNUC
#define NC_DONT_INLINE __attribute__((noinline))
#elif NC_COMP_MSVC
#define NC_DONT_INLINE __declspec(noinline)
#else
#define NC_DONT_INLINE
#endif

#if NC_COMP_GNUC
#define NC_PERMISSIVE_EXPR __extension__
#else
#define NC_PERMISSIVE_EXPR
#endif




#ifdef NDEBUG
# ifndef NC_NO_DEBUG
#  define NC_NO_DEBUG
# endif
#endif

// NC_plain_assert is where we implement the workaround for the assert() bug in GCC <= 4.3, see bug 89
#ifdef NC_NO_DEBUG
#define NC_plain_assert(x)
#else
#if NC_SAFE_TO_USE_STANDARD_ASSERT_MACRO
NS_INTERNAL_BEGIN
    inline bool copy_bool(bool b) { return b; }
NS_INTERNAL_END
    #define nc_plain_assert(x) assert(x)
#else
// work around bug 89
#include <cstdlib>   // for abort
#include <iostream>  // for std::cerr

NS_INTERNAL_BEGIN
    // trivial function copying a bool. Must be NC_DONT_INLINE, so we implement it after including Eigen headers.
    // see bug 89.
    namespace {
        NC_DONT_INLINE bool copy_bool(bool b) { return b; }
    }
    inline void assert_fail(const char *condition, const char *function, const char *file, int line)
    {
        std::cerr << "assertion failed: " << condition << " in function " << function << " at " << file << ":" << line << std::endl;
        abort();
    }
NS_INTERNAL_END
#define nc_plain_assert(x) \
      do { \
        if(!numc::internal::copy_bool(x)) \
          numc::internal::assert_fail(NC_MAKESTRING(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); \
      } while(false)
#endif
#endif

// NC_assert can be overridden
#ifndef nc_assert
#define nc_assert(x) nc_plain_assert(x)
#endif

#ifdef NC_INTERNAL_DEBUGGING
#define nc_internal_assert(x) nc_assert(x)
#else
#define nc_internal_assert(x)
#endif

#ifdef NC_NO_DEBUG
#define NC_ONLY_USED_FOR_DEBUG(x) NC_UNUSED_VARIABLE(x)
#else
#define NC_ONLY_USED_FOR_DEBUG(x)
#endif

#ifndef NC_NO_DEPRECATED_WARNING
#if NC_COMP_GNUC
#define NC_DEPRECATED __attribute__((deprecated))
#elif NC_COMP_MSVC
#define NC_DEPRECATED __declspec(deprecated)
#else
#define NC_DEPRECATED
#endif
#else
#define NC_DEPRECATED
#endif

#if NC_COMP_GNUC
#define NC_UNUSED __attribute__((unused))
#else
#define NC_UNUSED
#endif

// Suppresses 'unused variable' warnings.
NS_INTERNAL_BEGIN
    template<typename T> NC_DEVICE_FUNC void ignore_unused_variable(const T&) {}
NS_INTERNAL_END
#define NC_UNUSED_VARIABLE(var) Eigen::internal::ignore_unused_variable(var);

#if !defined(NC_ASM_COMMENT)
#if NC_COMP_GNUC && (NC_ARCH_i386_OR_x86_64 || NC_ARCH_ARM_OR_ARM64)
#define NC_ASM_COMMENT(X)  __asm__("#" X)
#else
#define NC_ASM_COMMENT(X)
#endif
#endif


#if NC_COMP_MSVC
// NOTE MSVC often gives C4127 warnings with compiletime if statements. See bug 1362.
  // This workaround is ugly, but it does the job.
#  define NC_CONST_CONDITIONAL(cond)  (void)0, cond
#else
#  define NC_CONST_CONDITIONAL(cond)  cond
#endif


#endif
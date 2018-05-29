// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_VECTORIZE_H__
#define __NC_MACROS_VECTORIZE_H__



// if alignment is disabled, then disable vectorization. Note: NC_MAX_ALIGN_BYTES is the proper check, it takes into
// account both the user's will (NC_MAX_ALIGN_BYTES,NC_DONT_ALIGN) and our own platform checks
#if NC_MAX_ALIGN_BYTES==0
#ifndef NC_DONT_VECTORIZE
#define NC_DONT_VECTORIZE
#endif
#endif

#if NC_COMP_MSVC
#include <malloc.h> // for _aligned_malloc -- need it regardless of whether vectorization is enabled
  #if (NC_COMP_MSVC >= 1500) // 2008 or later
    // Remember that usage of defined() in a #define is undefined by the standard.
    // a user reported that in 64-bit mode, MSVC doesn't care to define _M_IX86_FP.
    #if (defined(_M_IX86_FP) && (_M_IX86_FP >= 2)) || NC_ARCH_x86_64
      #define NC_SSE2_ON_MSVC_2008_OR_LATER
    #endif
  #endif
#else
// Remember that usage of defined() in a #define is undefined by the standard
#if (defined __SSE2__) && ( (!NC_COMP_GNUC) || NC_COMP_ICC || NC_GNUC_AT_LEAST(4,2) )
#define NC_SSE2_ON_NON_MSVC_BUT_NOT_OLD_GCC
#endif
#endif

#ifndef NC_DONT_VECTORIZE

#if defined (NC_SSE2_ON_NON_MSVC_BUT_NOT_OLD_GCC) || defined(NC_SSE2_ON_MSVC_2008_OR_LATER)

    // Defines symbols for compile-time detection of which instructions are
    // used.
    // NC_VECTORIZE_YY is defined if and only if the instruction set YY is used
    #define NC_VECTORIZE
    #define NC_VECTORIZE_SSE
    #define NC_VECTORIZE_SSE2

    // Detect sse3/ssse3/sse4:
    // gcc and icc defines __SSE3__, ...
    // there is no way to know about this on msvc. You can define NC_VECTORIZE_SSE* if you
    // want to force the use of those instructions with msvc.
    #ifdef __SSE3__
      #define NC_VECTORIZE_SSE3
    #endif
    #ifdef __SSSE3__
      #define NC_VECTORIZE_SSSE3
    #endif
    #ifdef __SSE4_1__
      #define NC_VECTORIZE_SSE4_1
    #endif
    #ifdef __SSE4_2__
      #define NC_VECTORIZE_SSE4_2
    #endif
    #ifdef __AVX__
      #define NC_VECTORIZE_AVX
      #define NC_VECTORIZE_SSE3
      #define NC_VECTORIZE_SSSE3
      #define NC_VECTORIZE_SSE4_1
      #define NC_VECTORIZE_SSE4_2
    #endif
    #ifdef __AVX2__
      #define NC_VECTORIZE_AVX2
      #define NC_VECTORIZE_AVX
      #define NC_VECTORIZE_SSE3
      #define NC_VECTORIZE_SSSE3
      #define NC_VECTORIZE_SSE4_1
      #define NC_VECTORIZE_SSE4_2
    #endif
    #ifdef __FMA__
      #define NC_VECTORIZE_FMA
    #endif
    #if defined(__AVX512F__)
      #define NC_VECTORIZE_AVX512
      #define NC_VECTORIZE_AVX2
      #define NC_VECTORIZE_AVX
      #define NC_VECTORIZE_FMA
      #define NC_VECTORIZE_SSE3
      #define NC_VECTORIZE_SSSE3
      #define NC_VECTORIZE_SSE4_1
      #define NC_VECTORIZE_SSE4_2
      #ifdef __AVX512DQ__
        #define NC_VECTORIZE_AVX512DQ
      #endif
      #ifdef __AVX512ER__
        #define NC_VECTORIZE_AVX512ER
      #endif
    #endif

    // include files

    // This extern "C" works around a MINGW-w64 compilation issue
    // https://sourceforge.net/tracker/index.php?func=detail&aid=3018394&group_id=202880&atid=983354
    // In essence, intrin.h is included by windows.h and also declares intrinsics (just as emmintrin.h etc. below do).
    // However, intrin.h uses an extern "C" declaration, and g++ thus complains of duplicate declarations
    // with conflicting linkage.  The linkage for intrinsics doesn't matter, but at that stage the compiler doesn't know;
    // so, to avoid compile errors when windows.h is included after Eigen/Core, ensure intrinsics are extern "C" here too.
    // notice that since these are C headers, the extern "C" is theoretically needed anyways.
    extern "C" {
      // In theory we should only include immintrin.h and not the other *mmintrin.h header files directly.
      // Doing so triggers some issues with ICC. However old gcc versions seems to not have this file, thus:
      #if NC_COMP_ICC >= 1110
        #include <immintrin.h>
      #else
        #include <mmintrin.h>
        #include <emmintrin.h>
        #include <xmmintrin.h>
        #ifdef  NC_VECTORIZE_SSE3
        #include <pmmintrin.h>
        #endif
        #ifdef NC_VECTORIZE_SSSE3
        #include <tmmintrin.h>
        #endif
        #ifdef NC_VECTORIZE_SSE4_1
        #include <smmintrin.h>
        #endif
        #ifdef NC_VECTORIZE_SSE4_2
        #include <nmmintrin.h>
        #endif
        #if defined(NC_VECTORIZE_AVX) || defined(NC_VECTORIZE_AVX512)
        #include <immintrin.h>
        #endif
      #endif
    } // end extern "C"
  #elif defined __VSX__
    #define NC_VECTORIZE
    #define NC_VECTORIZE_VSX
    #include <altivec.h>
    // We need to #undef all these ugly tokens defined in <altivec.h>
    // => use __vector instead of vector
    #undef bool
    #undef vector
    #undef pixel
  #elif defined __ALTIVEC__
    #define NC_VECTORIZE
    #define NC_VECTORIZE_ALTIVEC
    #include <altivec.h>
    // We need to #undef all these ugly tokens defined in <altivec.h>
    // => use __vector instead of vector
    #undef bool
    #undef vector
    #undef pixel
  #elif (defined  __ARM_NEON) || (defined __ARM_NEON__)
    #define NC_VECTORIZE
    #define NC_VECTORIZE_NEON
    #include <arm_neon.h>
  #elif (defined __s390x__ && defined __VEC__)
    #define NC_VECTORIZE
    #define NC_VECTORIZE_ZVECTOR
    #include <vecintrin.h>
  #endif
#endif

#if defined(__F16C__) && !defined(NC_COMP_CLANG)
// We can use the optimized fp16 to float and float to fp16 conversion routines
#define NC_HAS_FP16_C
#endif

#if defined NC_CUDACC
#define NC_VECTORIZE_CUDA
  #include <vector_types.h>
  #if NC_CUDACC_VER >= 70500
    #define NC_HAS_CUDA_FP16
  #endif
#endif

#if defined NC_HAS_CUDA_FP16
#include <host_defines.h>
  #include <cuda_fp16.h>
#endif

#if (defined _OPENMP) && (!defined NC_DONT_PARALLELIZE)
#define NC_HAS_OPENMP
#endif

#ifdef NC_HAS_OPENMP
#include <omp.h>
#endif

// MSVC for windows mobile does not have the errno.h file
#if !(NC_COMP_MSVC && NC_OS_WINCE) && !NC_COMP_ARM
#define NC_HAS_ERRNO
#endif

#ifdef NC_HAS_ERRNO
#include <cerrno>
#endif
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <functional>
#include <iosfwd>
#include <cstring>
#include <string>
#include <limits>
#include <climits> // for CHAR_BIT
// for min/max:
#include <algorithm>

// for std::is_nothrow_move_assignable
#ifdef NC_INCLUDE_TYPE_TRAITS
#include <type_traits>
#endif

// for outputting debug info
#ifdef NC_DEBUG_ASSIGN
#include <iostream>
#endif

// required for __cpuid, needs to be included after cmath
#if NC_COMP_MSVC && NC_ARCH_i386_OR_x86_64 && !NC_OS_WINCE
#include <intrin.h>
#endif

#if defined(__SYCL_DEVICE_ONLY__)
#undef min
  #undef max
  #undef isnan
  #undef isinf
  #undef isfinite
  #include <SYCL/sycl.hpp>
#endif

/** \brief Namespace containing all symbols from the %Eigen library. */
NS_BEGIN

    inline static const char *simd_instruction_sets_in_use(void) {
#if defined(NC_VECTORIZE_AVX512)
        return "AVX512, FMA, AVX2, AVX, SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2";
#elif defined(NC_VECTORIZE_AVX)
        return "AVX SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2";
#elif defined(NC_VECTORIZE_SSE4_2)
        return "SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2";
#elif defined(NC_VECTORIZE_SSE4_1)
        return "SSE, SSE2, SSE3, SSSE3, SSE4.1";
#elif defined(NC_VECTORIZE_SSSE3)
        return "SSE, SSE2, SSE3, SSSE3";
#elif defined(NC_VECTORIZE_SSE3)
        return "SSE, SSE2, SSE3";
#elif defined(NC_VECTORIZE_SSE2)
        return "SSE, SSE2";
#elif defined(NC_VECTORIZE_ALTIVEC)
        return "AltiVec";
#elif defined(NC_VECTORIZE_VSX)
        return "VSX";
#elif defined(NC_VECTORIZE_NEON)
        return "ARM NEON";
#elif defined(NC_VECTORIZE_ZVECTOR)
        return "S390X ZVECTOR";
#else
        return "None";
#endif
    }

NS_END


#endif
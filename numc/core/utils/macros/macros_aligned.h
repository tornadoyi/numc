// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_ALIGNED_H__
#define __NC_MACROS_ALIGNED_H__


//------------------------------------------------------------------------------------------
// Static and dynamic alignment control
//
// The main purpose of this section is to define NC_MAX_ALIGN_BYTES and NC_MAX_STATIC_ALIGN_BYTES
// as the maximal boundary in bytes on which dynamically and statically allocated data may be alignment respectively.
// The values of NC_MAX_ALIGN_BYTES and NC_MAX_STATIC_ALIGN_BYTES can be specified by the user. If not,
// a default value is automatically computed based on architecture, compiler, and OS.
//
// This section also defines macros NC_ALIGN_TO_BOUNDARY(N) and the shortcuts NC_ALIGN{8,16,32,_MAX}
// to be used to declare statically aligned buffers.
//------------------------------------------------------------------------------------------


/* NC_ALIGN_TO_BOUNDARY(n) forces data to be n-byte aligned. This is used to satisfy SIMD requirements.
 * However, we do that EVEN if vectorization (NC_VECTORIZE) is disabled,
 * so that vectorization doesn't affect binary compatibility.
 *
 * If we made alignment depend on whether or not NC_VECTORIZE is defined, it would be impossible to link
 * vectorized and non-vectorized code.
 */
#if (defined NC_CUDACC)
#define NC_ALIGN_TO_BOUNDARY(n) __align__(n)
#elif NC_COMP_GNUC || NC_COMP_PGI || NC_COMP_IBM || NC_COMP_ARM
#define NC_ALIGN_TO_BOUNDARY(n) __attribute__((aligned(n)))
#elif NC_COMP_MSVC
#define NC_ALIGN_TO_BOUNDARY(n) __declspec(align(n))
#elif NC_COMP_SUNCC
// FIXME not sure about this one:
  #define NC_ALIGN_TO_BOUNDARY(n) __attribute__((aligned(n)))
#else
#error Please tell me what is the equivalent of __attribute__((aligned(n))) for your compiler
#endif

// If the user explicitly disable vectorization, then we also disable alignment
#if defined(NC_DONT_VECTORIZE)
#define NC_IDEAL_MAX_ALIGN_BYTES 0
#elif defined(NC_VECTORIZE_AVX512)
// 64 bytes static alignment is preferred only if really required
  #define NC_IDEAL_MAX_ALIGN_BYTES 64
#elif defined(__AVX__)
// 32 bytes static alignment is preferred only if really required
#define NC_IDEAL_MAX_ALIGN_BYTES 32
#else
#define NC_IDEAL_MAX_ALIGN_BYTES 16
#endif


// NC_MIN_ALIGN_BYTES defines the minimal value for which the notion of explicit alignment makes sense
#define NC_MIN_ALIGN_BYTES 16

// Defined the boundary (in bytes) on which the data needs to be aligned. Note
// that unless NC_ALIGN is defined and not equal to 0, the data may not be
// aligned at all regardless of the value of this #define.

#if (defined(NC_DONT_ALIGN_STATICALLY) || defined(NC_DONT_ALIGN))  && defined(NC_MAX_STATIC_ALIGN_BYTES) && NC_MAX_STATIC_ALIGN_BYTES>0
#error NC_MAX_STATIC_ALIGN_BYTES and NC_DONT_ALIGN[_STATICALLY] are both defined with NC_MAX_STATIC_ALIGN_BYTES!=0. Use NC_MAX_STATIC_ALIGN_BYTES=0 as a synonym of NC_DONT_ALIGN_STATICALLY.
#endif

// NC_DONT_ALIGN_STATICALLY and NC_DONT_ALIGN are deprecated
// They imply NC_MAX_STATIC_ALIGN_BYTES=0
#if defined(NC_DONT_ALIGN_STATICALLY) || defined(NC_DONT_ALIGN)
#ifdef NC_MAX_STATIC_ALIGN_BYTES
    #undef NC_MAX_STATIC_ALIGN_BYTES
  #endif
  #define NC_MAX_STATIC_ALIGN_BYTES 0
#endif

#ifndef NC_MAX_STATIC_ALIGN_BYTES

// Try to automatically guess what is the best default value for NC_MAX_STATIC_ALIGN_BYTES

// 16 byte alignment is only useful for vectorization. Since it affects the ABI, we need to enable
// 16 byte alignment on all platforms where vectorization might be enabled. In theory we could always
// enable alignment, but it can be a cause of problems on some platforms, so we just disable it in
// certain common platform (compiler+architecture combinations) to avoid these problems.
// Only static alignment is really problematic (relies on nonstandard compiler extensions),
// try to keep heap alignment even when we have to disable static alignment.
#if NC_COMP_GNUC && !(NC_ARCH_i386_OR_x86_64 || NC_ARCH_ARM_OR_ARM64 || NC_ARCH_PPC || NC_ARCH_IA64)
#define NC_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT 1
#elif NC_ARCH_ARM_OR_ARM64 && NC_COMP_GNUC_STRICT && NC_GNUC_AT_MOST(4, 6)
// Old versions of GCC on ARM, at least 4.4, were once seen to have buggy static alignment support.
  // Not sure which version fixed it, hopefully it doesn't affect 4.7, which is still somewhat in use.
  // 4.8 and newer seem definitely unaffected.
  #define NC_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT 1
#else
#define NC_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT 0
#endif

// static alignment is completely disabled with GCC 3, Sun Studio, and QCC/QNX
#if !NC_GCC_AND_ARCH_DOESNT_WANT_STACK_ALIGNMENT \
  && !NC_GCC3_OR_OLDER \
  && !NC_COMP_SUNCC \
  && !NC_OS_QNX
#define NC_ARCH_WANTS_STACK_ALIGNMENT 1
#else
#define NC_ARCH_WANTS_STACK_ALIGNMENT 0
#endif

#if NC_ARCH_WANTS_STACK_ALIGNMENT
#define NC_MAX_STATIC_ALIGN_BYTES NC_IDEAL_MAX_ALIGN_BYTES
#else
#define NC_MAX_STATIC_ALIGN_BYTES 0
#endif

#endif

// If NC_MAX_ALIGN_BYTES is defined, then it is considered as an upper bound for NC_MAX_ALIGN_BYTES
#if defined(NC_MAX_ALIGN_BYTES) && NC_MAX_ALIGN_BYTES<NC_MAX_STATIC_ALIGN_BYTES
#undef NC_MAX_STATIC_ALIGN_BYTES
#define NC_MAX_STATIC_ALIGN_BYTES NC_MAX_ALIGN_BYTES
#endif

#if NC_MAX_STATIC_ALIGN_BYTES==0 && !defined(NC_DISABLE_UNALIGNED_ARRAY_ASSERT)
#define NC_DISABLE_UNALIGNED_ARRAY_ASSERT
#endif

// At this stage, NC_MAX_STATIC_ALIGN_BYTES>0 is the true test whether we want to align arrays on the stack or not.
// It takes into account both the user choice to explicitly enable/disable alignment (by setting NC_MAX_STATIC_ALIGN_BYTES)
// and the architecture config (NC_ARCH_WANTS_STACK_ALIGNMENT).
// Henceforth, only NC_MAX_STATIC_ALIGN_BYTES should be used.


// Shortcuts to NC_ALIGN_TO_BOUNDARY
#define NC_ALIGN8  NC_ALIGN_TO_BOUNDARY(8)
#define NC_ALIGN16 NC_ALIGN_TO_BOUNDARY(16)
#define NC_ALIGN32 NC_ALIGN_TO_BOUNDARY(32)
#define NC_ALIGN64 NC_ALIGN_TO_BOUNDARY(64)
#if NC_MAX_STATIC_ALIGN_BYTES>0
#define NC_ALIGN_MAX NC_ALIGN_TO_BOUNDARY(NC_MAX_STATIC_ALIGN_BYTES)
#else
#define NC_ALIGN_MAX
#endif


// Dynamic alignment control

#if defined(NC_DONT_ALIGN) && defined(NC_MAX_ALIGN_BYTES) && NC_MAX_ALIGN_BYTES>0
#error NC_MAX_ALIGN_BYTES and NC_DONT_ALIGN are both defined with NC_MAX_ALIGN_BYTES!=0. Use NC_MAX_ALIGN_BYTES=0 as a synonym of NC_DONT_ALIGN.
#endif

#ifdef NC_DONT_ALIGN
#ifdef NC_MAX_ALIGN_BYTES
    #undef NC_MAX_ALIGN_BYTES
  #endif
  #define NC_MAX_ALIGN_BYTES 0
#elif !defined(NC_MAX_ALIGN_BYTES)
#define NC_MAX_ALIGN_BYTES NC_IDEAL_MAX_ALIGN_BYTES
#endif

#if NC_IDEAL_MAX_ALIGN_BYTES > NC_MAX_ALIGN_BYTES
#define NC_DEFAULT_ALIGN_BYTES NC_IDEAL_MAX_ALIGN_BYTES
#else
#define NC_DEFAULT_ALIGN_BYTES NC_MAX_ALIGN_BYTES
#endif


#ifndef NC_UNALIGNED_VECTORIZE
#define NC_UNALIGNED_VECTORIZE 1
#endif

#endif

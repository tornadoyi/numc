// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_COMPILER_H__
#define __NC_MACROS_COMPILER_H__


// Compiler identification, NC_COMP_*

/// \internal NC_COMP_GNUC set to 1 for all compilers compatible with GCC
#ifdef __GNUC__
#define NC_COMP_GNUC (__GNUC__*10+__GNUC_MINOR__)
#else
#define NC_COMP_GNUC 0
#endif

/// \internal NC_COMP_CLANG set to major+minor version (e.g., 307 for clang 3.7) if the compiler is clang
#if defined(__clang__)
#define NC_COMP_CLANG (__clang_major__*100+__clang_minor__)
#else
#define NC_COMP_CLANG 0
#endif


/// \internal NC_COMP_LLVM set to 1 if the compiler backend is llvm
#if defined(__llvm__)
#define NC_COMP_LLVM 1
#else
#define NC_COMP_LLVM 0
#endif

/// \internal NC_COMP_ICC set to __INTEL_COMPILER if the compiler is Intel compiler, 0 otherwise
#if defined(__INTEL_COMPILER)
#define NC_COMP_ICC __INTEL_COMPILER
#else
#define NC_COMP_ICC 0
#endif

/// \internal NC_COMP_MINGW set to 1 if the compiler is mingw
#if defined(__MINGW32__)
#define NC_COMP_MINGW 1
#else
#define NC_COMP_MINGW 0
#endif

/// \internal NC_COMP_SUNCC set to 1 if the compiler is Solaris Studio
#if defined(__SUNPRO_CC)
#define NC_COMP_SUNCC 1
#else
#define NC_COMP_SUNCC 0
#endif

/// \internal NC_COMP_MSVC set to _MSC_VER if the compiler is Microsoft Visual C++, 0 otherwise.
#if defined(_MSC_VER)
#define NC_COMP_MSVC _MSC_VER
#else
#define NC_COMP_MSVC 0
#endif

// For the record, here is a table summarizing the possible values for NC_COMP_MSVC:
//  name  ver   MSC_VER
//  2008         9      1500
//  2010        10      1600
//  2012        11      1700
//  2013        12      1800
//  2015        14      1900
//  "15"        15      1900
//  2017-14.1   15.0    1910
//  2017-14.11  15.3    1911
//  2017-14.12  15.5    1912
//  2017-14.13  15.6    1913
//  2017-14.14  15.7    1914

/// \internal NC_COMP_MSVC_STRICT set to 1 if the compiler is really Microsoft Visual C++ and not ,e.g., ICC or clang-cl
#if NC_COMP_MSVC && !(NC_COMP_ICC || NC_COMP_LLVM || NC_COMP_CLANG)
#define NC_COMP_MSVC_STRICT _MSC_VER
#else
#define NC_COMP_MSVC_STRICT 0
#endif

/// \internal NC_COMP_IBM set to 1 if the compiler is IBM XL C++
#if defined(__IBMCPP__) || defined(__xlc__)
#define NC_COMP_IBM 1
#else
#define NC_COMP_IBM 0
#endif

/// \internal NC_COMP_PGI set to 1 if the compiler is Portland Group Compiler
#if defined(__PGI)
#define NC_COMP_PGI 1
#else
#define NC_COMP_PGI 0
#endif

/// \internal NC_COMP_ARM set to 1 if the compiler is ARM Compiler
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define NC_COMP_ARM 1
#else
#define NC_COMP_ARM 0
#endif

/// \internal NC_COMP_ARM set to 1 if the compiler is ARM Compiler
#if defined(__EMSCRIPTEN__)
#define NC_COMP_EMSCRIPTEN 1
#else
#define NC_COMP_EMSCRIPTEN 0
#endif


/// \internal NC_GNUC_STRICT set to 1 if the compiler is really GCC and not a compatible compiler (e.g., ICC, clang, mingw, etc.)
#if NC_COMP_GNUC && !(NC_COMP_CLANG || NC_COMP_ICC || NC_COMP_MINGW || NC_COMP_PGI || NC_COMP_IBM || NC_COMP_ARM || NC_COMP_EMSCRIPTEN)
#define NC_COMP_GNUC_STRICT 1
#else
#define NC_COMP_GNUC_STRICT 0
#endif


#if NC_COMP_GNUC
#define NC_GNUC_AT_LEAST(x,y) ((__GNUC__==x && __GNUC_MINOR__>=y) || __GNUC__>x)
#define NC_GNUC_AT_MOST(x,y)  ((__GNUC__==x && __GNUC_MINOR__<=y) || __GNUC__<x)
#define NC_GNUC_AT(x,y)       ( __GNUC__==x && __GNUC_MINOR__==y )
#else
#define NC_GNUC_AT_LEAST(x,y) 0
  #define NC_GNUC_AT_MOST(x,y)  0
  #define NC_GNUC_AT(x,y)       0
#endif

// FIXME: could probably be removed as we do not support gcc 3.x anymore
#if NC_COMP_GNUC && (__GNUC__ <= 3)
#define NC_GCC3_OR_OLDER 1
#else
#define NC_GCC3_OR_OLDER 0
#endif

#endif
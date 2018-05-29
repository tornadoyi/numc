// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_CUDA_H__
#define __NC_MACROS_CUDA_H__

#if defined(__CUDACC__) && !defined(NC_NO_CUDA)
#define NC_CUDACC __CUDACC__
#endif

#if defined(__CUDA_ARCH__) && !defined(NC_NO_CUDA)
#define NC_CUDA_ARCH __CUDA_ARCH__
#endif

// Starting with CUDA 9 the composite __CUDACC_VER__ is not available.
#if defined(__CUDACC_VER_MAJOR__) && (__CUDACC_VER_MAJOR__ >= 9)
#define NC_CUDACC_VER  ((__CUDACC_VER_MAJOR__ * 10000) + (__CUDACC_VER_MINOR__ * 100))
#elif defined(__CUDACC_VER__)
#define NC_CUDACC_VER __CUDACC_VER__
#else
#define NC_CUDACC_VER 0
#endif

// Handle NVCC/CUDA/SYCL
#if defined(NC_CUDACC) || defined(__SYCL_DEVICE_ONLY__)
// Do not try asserts on CUDA and SYCL!
  #ifndef NC_NO_DEBUG
  #define NC_NO_DEBUG
  #endif

  #ifdef NC_INTERNAL_DEBUGGING
  #undef NC_INTERNAL_DEBUGGING
  #endif

  #ifdef NC_EXCEPTIONS
  #undef NC_EXCEPTIONS
  #endif

  // All functions callable from CUDA code must be qualified with __device__
  #ifdef NC_CUDACC
    // Do not try to vectorize on CUDA and SYCL!
    #ifndef NC_DONT_VECTORIZE
    #define NC_DONT_VECTORIZE
    #endif

    #define NC_DEVICE_FUNC __host__ __device__
    // We need cuda_runtime.h to ensure that that NC_USING_STD_MATH macro
    // works properly on the device side
    #include <cuda_runtime.h>
  #else
    #define NC_DEVICE_FUNC
  #endif
#else
#define NC_DEVICE_FUNC
#endif

#ifdef __NVCC__
#define NC_DONT_VECTORIZE
#endif

// When compiling CUDA device code with NVCC, pull in math functions from the
// global namespace.  In host mode, and when device doee with clang, use the
// std versions.
#if defined(NC_CUDA_ARCH) && defined(__NVCC__)
#define NC_USING_STD_MATH(FUNC) using ::FUNC;
#else
#define NC_USING_STD_MATH(FUNC) using std::FUNC;
#endif

#if (defined(_CPPUNWIND) || defined(__EXCEPTIONS)) && !defined(NC_CUDA_ARCH) && !defined(NC_EXCEPTIONS) && !defined(NC_USE_SYCL)
#define NC_EXCEPTIONS
#endif

#ifdef NC_EXCEPTIONS
#include <new>
#endif


#endif
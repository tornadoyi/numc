// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_ARCH_H__
#define __NC_MACROS_ARCH_H__


#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64)
#define NC_ARCH_x86_64 1
#else
#define NC_ARCH_x86_64 0
#endif

#if defined(__i386__) || defined(_M_IX86) || defined(_X86_) || defined(__i386)
#define NC_ARCH_i386 1
#else
#define NC_ARCH_i386 0
#endif

#if NC_ARCH_x86_64 || NC_ARCH_i386
#define NC_ARCH_i386_OR_x86_64 1
#else
#define NC_ARCH_i386_OR_x86_64 0
#endif

/// \internal NC_ARCH_ARM set to 1 if the architecture is ARM
#if defined(__arm__)
#define NC_ARCH_ARM 1
#else
#define NC_ARCH_ARM 0
#endif

/// \internal NC_ARCH_ARM64 set to 1 if the architecture is ARM64
#if defined(__aarch64__)
#define NC_ARCH_ARM64 1
#else
#define NC_ARCH_ARM64 0
#endif

#if NC_ARCH_ARM || NC_ARCH_ARM64
#define NC_ARCH_ARM_OR_ARM64 1
#else
#define NC_ARCH_ARM_OR_ARM64 0
#endif

/// \internal NC_ARCH_MIPS set to 1 if the architecture is MIPS
#if defined(__mips__) || defined(__mips)
#define NC_ARCH_MIPS 1
#else
#define NC_ARCH_MIPS 0
#endif

/// \internal NC_ARCH_SPARC set to 1 if the architecture is SPARC
#if defined(__sparc__) || defined(__sparc)
#define NC_ARCH_SPARC 1
#else
#define NC_ARCH_SPARC 0
#endif

/// \internal NC_ARCH_IA64 set to 1 if the architecture is Intel Itanium
#if defined(__ia64__)
#define NC_ARCH_IA64 1
#else
#define NC_ARCH_IA64 0
#endif

/// \internal NC_ARCH_PPC set to 1 if the architecture is PowerPC
#if defined(__powerpc__) || defined(__ppc__) || defined(_M_PPC)
#define NC_ARCH_PPC 1
#else
#define NC_ARCH_PPC 0
#endif

#endif
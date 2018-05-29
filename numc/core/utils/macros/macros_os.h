// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __NC_MACROS_OS_H__
#define __NC_MACROS_OS_H__


// Operating system identification, NC_OS_*

/// \internal NC_OS_UNIX set to 1 if the OS is a unix variant
#if defined(__unix__) || defined(__unix)
#define NC_OS_UNIX 1
#else
#define NC_OS_UNIX 0
#endif

/// \internal NC_OS_LINUX set to 1 if the OS is based on Linux kernel
#if defined(__linux__)
#define NC_OS_LINUX 1
#else
#define NC_OS_LINUX 0
#endif

/// \internal NC_OS_ANDROID set to 1 if the OS is Android
// note: ANDROID is defined when using ndk_build, __ANDROID__ is defined when using a standalone toolchain.
#if defined(__ANDROID__) || defined(ANDROID)
#define NC_OS_ANDROID 1
#else
#define NC_OS_ANDROID 0
#endif

/// \internal NC_OS_GNULINUX set to 1 if the OS is GNU Linux and not Linux-based OS (e.g., not android)
#if defined(__gnu_linux__) && !(NC_OS_ANDROID)
#define NC_OS_GNULINUX 1
#else
#define NC_OS_GNULINUX 0
#endif

/// \internal NC_OS_BSD set to 1 if the OS is a BSD variant
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#define NC_OS_BSD 1
#else
#define NC_OS_BSD 0
#endif

/// \internal NC_OS_MAC set to 1 if the OS is MacOS
#if defined(__APPLE__)
#define NC_OS_MAC 1
#else
#define NC_OS_MAC 0
#endif

/// \internal NC_OS_QNX set to 1 if the OS is QNX
#if defined(__QNX__)
#define NC_OS_QNX 1
#else
#define NC_OS_QNX 0
#endif

/// \internal NC_OS_WIN set to 1 if the OS is Windows based
#if defined(_WIN32)
#define NC_OS_WIN 1
#else
#define NC_OS_WIN 0
#endif

/// \internal NC_OS_WIN64 set to 1 if the OS is Windows 64bits
#if defined(_WIN64)
#define NC_OS_WIN64 1
#else
#define NC_OS_WIN64 0
#endif

/// \internal NC_OS_WINCE set to 1 if the OS is Windows CE
#if defined(_WIN32_WCE)
#define NC_OS_WINCE 1
#else
#define NC_OS_WINCE 0
#endif

/// \internal NC_OS_CYGWIN set to 1 if the OS is Windows/Cygwin
#if defined(__CYGWIN__)
#define NC_OS_CYGWIN 1
#else
#define NC_OS_CYGWIN 0
#endif

/// \internal NC_OS_WIN_STRICT set to 1 if the OS is really Windows and not some variants
#if NC_OS_WIN && !( NC_OS_WINCE || NC_OS_CYGWIN )
#define NC_OS_WIN_STRICT 1
#else
#define NC_OS_WIN_STRICT 0
#endif

/// \internal NC_OS_SUN set to 1 if the OS is SUN
#if (defined(sun) || defined(__sun)) && !(defined(__SVR4) || defined(__svr4__))
#define NC_OS_SUN 1
#else
#define NC_OS_SUN 0
#endif

/// \internal NC_OS_SOLARIS set to 1 if the OS is Solaris
#if (defined(sun) || defined(__sun)) && (defined(__SVR4) || defined(__svr4__))
#define NC_OS_SOLARIS 1
#else
#define NC_OS_SOLARIS 0
#endif


#endif
// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_FORWARD_DECLARATIONS_H__
#define __NC_FORWARD_DECLARATIONS_H__


NS_INTERNAL_BEGIN

template<typename T> struct traits;

// here we say once and for all that traits<const T> == traits<T>
// When constness must affect traits, it has to be constness on template parameters on which T itself depends.
// For example, traits<Map<const T> > != traits<Map<T> >, but
//              traits<const Map<T> > == traits<Map<T> >
template<typename T> struct traits<const T> : traits<T> {};

NS_INTERNAL_END




NS_BEGIN

template<typename T> struct NumTraits;


template<typename BinaryOp, typename LhsType, typename RhsType> class CwiseBinaryOp;

template<typename Scalar> class Array;


NS_END


#endif
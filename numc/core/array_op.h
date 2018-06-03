// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_ARRAY_OP_H__
#define __NC_ARRAY_OP_H__

NS_BEGIN

template<typename Derived>
class ArrayOp
{
public:
    typedef typename internal::traits<Derived>::Scalar Scalar;
public:
    inline Derived& derived() { return *static_cast<Derived*>(this); }

    template<typename DerivedOther>
    CwiseBinaryOp<internal::scalar_sum_op<Scalar, Scalar>, Derived, DerivedOther>
    operator+( DerivedOther& other )
    {
        return CwiseBinaryOp<internal::scalar_sum_op<Scalar, Scalar>, Derived, DerivedOther>(derived(), other.derived());
    }
};

NS_END

#endif
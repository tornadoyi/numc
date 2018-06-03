// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_ARRAY_H__
#define __NC_ARRAY_H__



NS_INTERNAL_BEGIN

template<typename _Scalar>
struct traits< Array<_Scalar> >
{
    typedef _Scalar Scalar;
};

NS_INTERNAL_END


NS_BEGIN

template<typename Scalar>
class Array : public ArrayOp< Array<Scalar> >
{

public:
    NC_STRONG_INLINE Array(const Shape& shape) : _shape(shape) {}

    NC_STRONG_INLINE Array(std::initializer_list<Index>& shape) : _shape(shape) {}

    template <typename... T>
    NC_STRONG_INLINE Array(T... shape) : _shape(shape...) {}

protected:
    Shape _shape;
};


NS_END

#endif
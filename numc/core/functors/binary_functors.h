// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_BINARY_FUNCTORS_H__
#define __NC_BINARY_FUNCTORS_H__

NS_INTERNAL_BEGIN


//---------- associative binary functors ----------

template<typename Arg1, typename Arg2>
struct binary_op_base
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
};

/** \internal
  * \brief Template functor to compute the sum of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::operator+, class VectorwiseOp, DenseBase::sum()
  */
template<typename LhsScalar,typename RhsScalar>
struct scalar_sum_op : binary_op_base<LhsScalar,RhsScalar>
{
    typedef typename ScalarBinaryOpTraits<LhsScalar,RhsScalar,scalar_sum_op>::ReturnType result_type;
#ifndef NC_SCALAR_BINARY_OP_PLUGIN
    NC_EMPTY_STRUCT_CTOR(scalar_sum_op)
#else
    scalar_sum_op() {
    NC_SCALAR_BINARY_OP_PLUGIN
  }
#endif
    NC_DEVICE_FUNC NC_STRONG_INLINE const result_type operator() (const LhsScalar& a, const RhsScalar& b) const { return a + b; }
    /*
    template<typename Packet>
    NC_DEVICE_FUNC NC_STRONG_INLINE const Packet packetOp(const Packet& a, const Packet& b) const
    { return internal::padd(a,b); }
    template<typename Packet>
    NC_DEVICE_FUNC NC_STRONG_INLINE const result_type predux(const Packet& a) const
    { return internal::predux(a); }
     */

};



NS_INTERNAL_END

#endif
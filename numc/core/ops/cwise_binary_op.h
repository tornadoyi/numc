// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_CWISE_BINARY_OP_H__
#define __NC_CWISE_BINARY_OP_H__

NS_INTERNAL_BEGIN

template<typename BinaryOp, typename Lhs, typename Rhs>
struct traits<CwiseBinaryOp<BinaryOp, Lhs, Rhs> >
{
    typedef typename result_of<
            BinaryOp(
                    const typename Lhs::Scalar&,
                    const typename Rhs::Scalar&
            )
    >::type Scalar;
};


NS_INTERNAL_END


NS_BEGIN

template<typename BinaryOp, typename Lhs, typename Rhs>
class CwiseBinaryOpImpl;



/** \class CwiseBinaryOp
  * \ingroup Core_Module
  *
  * \brief Generic expression where a coefficient-wise binary operator is applied to two expressions
  *
  * \tparam BinaryOp template functor implementing the operator
  * \tparam LhsType the type of the left-hand side
  * \tparam RhsType the type of the right-hand side
  *
  * This class represents an expression  where a coefficient-wise binary operator is applied to two expressions.
  * It is the return type of binary operators, by which we mean only those binary operators where
  * both the left-hand side and the right-hand side are Eigen expressions.
  * For example, the return type of matrix1+matrix2 is a CwiseBinaryOp.
  *
  * Most of the time, this is the only way that it is used, so you typically don't have to name
  * CwiseBinaryOp types explicitly.
  *
  * \sa MatrixBase::binaryExpr(const MatrixBase<OtherDerived> &,const CustomBinaryOp &) const, class CwiseUnaryOp, class CwiseNullaryOp
  */
template<typename BinaryOp, typename LhsType, typename RhsType>
class CwiseBinaryOp : public CwiseBinaryOpImpl<BinaryOp, LhsType, RhsType>
{
    typedef typename internal::remove_all<BinaryOp>::type Functor;
    typedef typename internal::remove_all<LhsType>::type Lhs;
    typedef typename internal::remove_all<RhsType>::type Rhs;

public:
    NC_DEVICE_FUNC
    NC_STRONG_INLINE CwiseBinaryOp(const Lhs& lhs, const Rhs& rhs, const BinaryOp& func = BinaryOp())
    : _lhs(lhs), _rhs(rhs), _functor(func)
    {
        //nc_assert(lhs.size() == rhs.size());
    }

protected:
    LhsType const& _lhs;
    RhsType const& _rhs;
    const BinaryOp _functor;
};



template<typename BinaryOp, typename Lhs, typename Rhs>
class CwiseBinaryOpImpl : public ArrayOp< CwiseBinaryOp<BinaryOp, Lhs, Rhs> >
{
public:

};



NS_END

#endif
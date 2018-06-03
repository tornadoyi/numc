// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_XPR_HELPER_H__
#define __NC_XPR_HELPER_H__


// just a workaround because GCC seems to not really like empty structs
// FIXME: gcc 4.3 generates bad code when strict-aliasing is enabled
// so currently we simply disable this optimization for gcc 4.3
#if NC_COMP_GNUC && !NC_GNUC_AT(4,3)
#define NC_EMPTY_STRUCT_CTOR(X) \
    NC_DEVICE_FUNC NC_STRONG_INLINE X() {} \
    NC_DEVICE_FUNC NC_STRONG_INLINE X(const X& ) {}
#else
#define NC_EMPTY_STRUCT_CTOR(X)
#endif


NS_BEGIN

/** \class ScalarBinaryOpTraits
  * \ingroup Core_Module
  *
  * \brief Determines whether the given binary operation of two numeric types is allowed and what the scalar return type is.
  *
  * This class permits to control the scalar return type of any binary operation performed on two different scalar types through (partial) template specializations.
  *
  * For instance, let \c U1, \c U2 and \c U3 be three user defined scalar types for which most operations between instances of \c U1 and \c U2 returns an \c U3.
  * You can let %numc knows that by defining:
    \code
    template<typename BinaryOp>
    struct ScalarBinaryOpTraits<U1,U2,BinaryOp> { typedef U3 ReturnType;  };
    template<typename BinaryOp>
    struct ScalarBinaryOpTraits<U2,U1,BinaryOp> { typedef U3 ReturnType;  };
    \endcode
  * You can then explicitly disable some particular operations to get more explicit error messages:
    \code
    template<>
    struct ScalarBinaryOpTraits<U1,U2,internal::scalar_max_op<U1,U2> > {};
    \endcode
  * Or customize the return type for individual operation:
    \code
    template<>
    struct ScalarBinaryOpTraits<U1,U2,internal::scalar_sum_op<U1,U2> > { typedef U1 ReturnType; };
    \endcode
  *
  * By default, the following generic combinations are supported:
  <table class="manual">
  <tr><th>ScalarA</th><th>ScalarB</th><th>BinaryOp</th><th>ReturnType</th><th>Note</th></tr>
  <tr            ><td>\c T </td><td>\c T </td><td>\c * </td><td>\c T </td><td></td></tr>
  <tr class="alt"><td>\c NumTraits<T>::Real </td><td>\c T </td><td>\c * </td><td>\c T </td><td>Only if \c NumTraits<T>::IsComplex </td></tr>
  <tr            ><td>\c T </td><td>\c NumTraits<T>::Real </td><td>\c * </td><td>\c T </td><td>Only if \c NumTraits<T>::IsComplex </td></tr>
  </table>
  *
  * \sa CwiseBinaryOp
  */


//template<typename ScalarA, typename ScalarB, typename BinaryOp=internal::scalar_product_op<ScalarA,ScalarB> >
template<typename ScalarA, typename ScalarB, typename BinaryOp >
struct ScalarBinaryOpTraits
#ifndef NC_PARSED_BY_DOXYGEN
    // for backward compatibility, use the hints given by the (deprecated) internal::scalar_product_traits class.
        : internal::scalar_product_traits<ScalarA,ScalarB>
#endif // NC_PARSED_BY_DOXYGEN
{};


template<typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<T,T,BinaryOp>
{
    typedef T ReturnType;
};

template <typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<T, typename NumTraits<typename internal::enable_if<NumTraits<T>::IsComplex,T>::type>::Real, BinaryOp>
{
    typedef T ReturnType;
};
template <typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<typename NumTraits<typename internal::enable_if<NumTraits<T>::IsComplex,T>::type>::Real, T, BinaryOp>
{
    typedef T ReturnType;
};

// For Matrix * Permutation
template<typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<T,void,BinaryOp>
{
    typedef T ReturnType;
};

// For Permutation * Matrix
template<typename T, typename BinaryOp>
struct ScalarBinaryOpTraits<void,T,BinaryOp>
{
    typedef T ReturnType;
};

// for Permutation*Permutation
template<typename BinaryOp>
struct ScalarBinaryOpTraits<void,void,BinaryOp>
{
    typedef void ReturnType;
};


NS_END

#endif
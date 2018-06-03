// This file is part of numc, a lightweight C++ n-dimension array library
// for linear algebra.
//
// Copyright (C) 2018 <Yi Gu 390512308@qq.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef __NC_SHAPE_H__
#define __NC_SHAPE_H__

NS_BEGIN

class Shape
{
public:
    Shape(std::initializer_list<Index> ds) : _dims(ds.size())
    {
        Index i=0;
        auto it = ds.begin();
        _size = 1;
        for (; it != ds.end(); ++it, ++i)
        {
            _data[i] = *it;
            _size *= *it;
        }
    }


    template <typename... T>
    Shape(T... ds)
    {
        _dims = sizeof...(ds);
        _size = 1;
        _shape_ctor(ds...);
    }


    inline Index size() const { return _size; }

    inline Index dims() const { return _dims; }

    inline Index operator[](Index i) const
    {
        nc_assert(i < MAX_ARRAY_DIMENSIONS);
        return _data[i];
    }

    friend std::ostream &operator << (std::ostream &s, const Shape& shape)
    {
        s << "(";
        for(Index i=0; i<shape.dims(); ++i)
        {
            s << shape[i];
            if(i != shape.dims()-1) s << ", ";
        }
        s << ")";
        return s;
    }


private:

    template <typename T0, typename... T1>
    inline typename internal::enable_if< internal::is_same<int, T0>::value, void >::type
    _shape_ctor(T0 d0, T1... ds)
    {
        _data[_dims - sizeof...(ds) - 1] = d0;
        _size *= d0;
        _shape_ctor(ds...);
    }

    template <typename... T>
    inline void _shape_ctor(){}


private:
    Index _data[MAX_ARRAY_DIMENSIONS];
    Index _dims;
    Index _size;
};


NS_END

#endif
//
// Created by jim on 14.02.18.
//

#pragma once

#include <orbital/common/common.h>
#include <orbital/common/range.h>

template<class T, std::size_t N>
class Vector
        : public std::array<T, N>
{

    using ArrayType = std::array<T, N>;
    using SizeType = decltype(N);
    using VectorType = Vector<T, N>;

public:

    constexpr Vector()
    {
        ArrayType::fill(T{});
    }

    constexpr Vector(
            std::initializer_list<T> const &il
    )
    {
        std::copy(il.begin(), il.begin() + N, ArrayType::begin());
        if (il.size() < N)
        {
            std::fill(ArrayType::begin() + il.size(), ArrayType::end(), T{});
        }
    }

    constexpr explicit Vector(
            ArrayType const &array
    )
    {
        std::copy(array.begin(), array.begin() + N, ArrayType::begin());
        if (array.size() < N)
        {
            std::fill(ArrayType::begin() + array.size(), ArrayType::end(), T{});
        }
    }

    constexpr VectorType
    operator+(
            VectorType const &rhs
    ) const
    {
        VectorType result{};
        for(SizeType i{}; i < N; i++)
        {
            result[i] = (*this)[i] + rhs[i];
        }
        return result;
    }

    constexpr VectorType
    operator-(
            VectorType const &rhs
    ) const
    {
        VectorType result{};
        for(SizeType i{}; i < N; i++)
        {
            result[i] = (*this)[i] - rhs[i];
        }
        return result;
    }

    constexpr bool
    operator==(
            VectorType const &rhs
    ) const
    {
        return reduce_range(SizeType{}, N, true, [&](
                bool const &b,
                SizeType const &index
        ) {
            return ((*this)[index] == rhs[index]) && b;
        });
    }

    friend std::ostream &
    operator<<(
            std::ostream &os,
            Vector<T, N> const &vector
    )
    {
        os << '(';
        for(SizeType i{}; i < N; i++)
        {
            os << vector[i];
            if(i < N - SizeType{1})
            {
                os << ", ";
            }
        }
        os << ')';
        return os;
    }

};

template<class T>
class Vector2d
        : public Vector<T, 2>
{

public:

    using Vector<T, 2>::Vector;

    constexpr T &
    x()
    {
        return (*this)[0];
    }

    constexpr T &
    y()
    {
        return (*this)[1];
    }

    constexpr T const &
    x() const
    {
        return (*this)[0];
    }

    constexpr T const &
    y() const
    {
        return (*this)[1];
    }

};

template<class T>
class Vector3d
        : public Vector<T, 3>
{

public:

    using Vector<T, 3>::Vector;

    constexpr T &
    x()
    {
        return (*this)[0];
    }

    constexpr T &
    y()
    {
        return (*this)[1];
    }

    constexpr T &
    z()
    {
        return (*this)[2];
    }

    constexpr T const &
    x() const
    {
        return (*this)[0];
    }

    constexpr T const &
    y() const
    {
        return (*this)[1];
    }

    constexpr T const &
    z() const
    {
        return (*this)[2];
    }

};

//
// Created by jim on 05.02.18.
//

#pragma once

#include <array>
#include <stdexcept>
#include <ostream>

/**
 * A fixed-maximum sized array, with a dynamic count of actual values.
 * Efficient when maximum number of elements is known at compile-time, such a quadratic formula solutions.
 *
 * Elements must be default constructable and assignable.
 *
 * Therefore, this class is only efficient for lightweight structures, but it optimizes the heap away, since everything
 * is stored directly on the stack.
 */

template<class T, std::size_t N>
class DynamicArray
{

public:

    constexpr DynamicArray()
    {
        static_assert(N > 0, "Dynamic array must have at least one value");
    }

    constexpr DynamicArray(
            const std::initializer_list<T> &il
    )
        : DynamicArray{}
    {
        if(il.size() > N)
        {
            throw std::runtime_error{"Initializer list is too long for dynamic array"};
        }
        for(const auto e : il)
        {
            mArray[mLength] = std::move(e);
            ++mLength;
        }
    }

    template<class TObj>
    constexpr T &push_back(
            TObj &&obj
    )
    {
        if(mLength >= N)
        {
            throw std::runtime_error{"Exceeding maximum dynamic array size"};
        }

        mArray[mLength] = static_cast<T>(std::forward<TObj>(obj));
        ++mLength;
        return mArray[mLength - 1];
    }

    constexpr T &front()
    {
        return mArray.front();
    }

    constexpr const T &front() const
    {
        return mArray.front();
    }

    constexpr T &back()
    {
        return mArray[mLength - 1];
    }

    constexpr const T &back() const
    {
        return mArray[mLength - 1];
    }

    constexpr std::size_t size() const
    {
        return mLength;
    }

    constexpr std::size_t capacity() const
    {
        return N;
    }

    constexpr T &operator[](std::size_t index)
    {
        return mArray[index];
    }

    constexpr const T &operator[](std::size_t index) const
    {
        return mArray[index];
    }

    constexpr auto begin() {
        return mArray.begin();
    }

    constexpr auto end() {
        return mArray.begin() + mLength;
    }

    constexpr auto cbegin() const {
        return mArray.cbegin();
    }

    constexpr auto cend() const {
        return mArray.cbegin() + mLength;
    }

    friend std::ostream &
    operator<<(
            std::ostream &os,
            const DynamicArray &array
    )
    {
        os << "[ ";
        for(auto iter = array.cbegin(); iter != array.cend(); iter++)
        {
            os << *iter;
            if(iter + 1 != array.cend())
            {
                os << ", ";
            }
        }
        os << " ]";
        return os;
    }

private:

    std::size_t mLength = 0;
    std::array<T, N> mArray;

};


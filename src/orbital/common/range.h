//
// Created by jim on 13.02.18.
//

#pragma once

#include <functional>

/**
 * Executes a function over a given range. The current index is passed as a parameter.
 * @param min Lower range bound, inclusive.
 * @param max Upper range bound, exclusive.
 * @param fun Function to call.
 * @param args Arguments to pass, see std::apply().
 */
template<class TMin, class TMax, class... TArgs, class TFun>
constexpr void
range(
        TMin const min,
        TMax const max,
        TFun &&fun,
        TArgs &&...args
)
{
    if (!(min < max))
    {
        return;
    }

    std::apply(std::forward<TFun>(fun), std::tuple{std::forward<TFun>(args)..., min});
    range(min + TMin(1), max, std::forward<TFun>(fun), std::forward<TFun>(args)...);
}

/**
 * Executes a function over a given range. The current index, as well a the return value from the previous
 * invocation are passed as parameters.
 * @param min Lower range bound, inclusive.
 * @param max Upper range bound, exclusive.
 * @param init Initializer value, value passed to first invocation of fun.
 * @param fun Function to call.
 * @param args Arguments to pass, see std::apply().
 * @return Return value from last invocation.
 */
template<class TMin, class TMax, class T, class... TArgs, class TFun>
constexpr T
reduce_range(
        TMin const min,
        TMax const max,
        T const init,
        TFun &&fun,
        TArgs &&...args
)
{
    if (!(min < max))
    {
        return init;
    }

    auto result = std::apply(std::forward<TFun>(fun), std::tuple{std::forward<TFun>(args)..., init, min});
    return reduce_range(min + TMin(1), max, result, std::forward<TFun>(fun), std::forward<TFun>(args)...);
}

#pragma once

#include <iterator>

namespace qtl { namespace
{
        template<class T>
    struct reversed
    {
        T& container;

        size_t size() const { return container.size(); }

        auto operator[](size_t index) const -> decltype(auto)
        {
            return container[size() - index - 1];
        }

        auto operator[](size_t index) -> decltype(auto)
        {
            return container[size() - index - 1];
        }

        auto begin()  const { return container.rbegin(); }
        auto end()    const { return container.rend(); }

        auto rbegin() const { return container.begin(); }
        auto rend()   const { return container.end(); }
    };

        template<class T>
    reversed(T& container) -> reversed<T>;
}}
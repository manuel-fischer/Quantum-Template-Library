#pragma once

#include <iterator>
#include <type_traits>

namespace qtl { namespace
{

    #define QTL_DECLARE_CONTAINER_TYPES(T) \
        \
        using value_type = typename T::value_type; \
        \
        using size_type = typename T::size_type; \
        using difference_type = typename T::difference_type; \
        \
        using reference = std::conditional_t<std::is_const_v<T>, typename T::reference, typename T::const_reference>; \
        using const_reference = typename T::const_reference; \
        \
        using pointer = std::conditional_t<std::is_const_v<T>, typename T::pointer, typename T::const_reference>; \
        using const_pointer = typename T::const_pointer; \
        \
        using iterator = std::conditional_t<std::is_const_v<T>, typename T::const_reverse_iterator, typename T::reverse_iterator>; \
        using reverse_iterator = std::conditional_t<std::is_const_v<T>, typename T::const_iterator, typename T::iterator>; \
        \
        using const_iterator = typename T::const_reverse_iterator; \
        using const_reverse_iterator = typename T::const_iterator

        template<class T>
    struct reversed
    {
        QTL_DECLARE_CONTAINER_TYPES(T);

        T& container;

        size_type size() const { return container.size(); }

        reference operator[](size_type index) const
        {
            //return container[size() - index - size_type(1)];
            return container[size() - ++index];
        }

        const_reference operator[](size_type index)
        {
            return container[size() - ++index];
        }

        iterator begin()  { return container.rbegin(); }
        iterator end()    { return container.rend(); }

        reverse_iterator rbegin() { return container.begin(); }
        reverse_iterator rend()   { return container.end(); }

        const_iterator begin()  const { return container.rbegin(); }
        const_iterator end()    const { return container.rend(); }

        const_reverse_iterator rbegin() const { return container.begin(); }
        const_reverse_iterator rend()   const { return container.end(); }

        const_iterator cbegin()  const { return container.crbegin(); }
        const_iterator cend()    const { return container.crend(); }

        const_reverse_iterator crbegin() const { return container.cbegin(); }
        const_reverse_iterator crend()   const { return container.cend(); }
    };

        template<class T>
    reversed(T& container) -> reversed<T>;
}}
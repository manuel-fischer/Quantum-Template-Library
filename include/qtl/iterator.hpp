#pragma once

namespace qtl { namespace
{
    // indirect_iterator: stable iterator, that is valid after elements were added or removed from
    // the container. But it is only dereferencable, if the index points into the container.
    // it is undefined to use iterators in an operator, that point into different containers

        template<class Container>
    struct indirect_iterator
    {
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename Container::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = std::conditional_t<std::is_const_v<Container>, typename Container::const_pointer, typename Container::pointer>;
        using reference         = std::conditional_t<std::is_const_v<Container>, typename Container::const_reference, typename Container::reference>;



        Container* container;
        typename Container::size_type index;


        constexpr reference operator*() const { return (*container)[index]; }
        constexpr pointer operator->() const { return &(*container)[index]; } // TODO disable for containers like vector<bool>?

        constexpr reference operator[](difference_type n) const { (*container)[index + n]; }

        constexpr indirect_iterator& operator++() { index++; return *this; }
        constexpr indirect_iterator& operator--() { index--; return *this; }

        constexpr indirect_iterator operator++(int) { indirect_iterator i = *this; ++*this; return i; }
        constexpr indirect_iterator operator--(int) { indirect_iterator i = *this; --*this; return i; }

        constexpr indirect_iterator operator+(difference_type n) const { return { container, index + n }; }
        constexpr indirect_iterator operator-(difference_type n) const { return { container, index - n }; }

        constexpr indirect_iterator& operator+=(difference_type n) { index += n; return *this; }
        constexpr indirect_iterator& operator-=(difference_type n) { index -= n; return *this; }
    };


    #define QTL_INDIRECT_DEF_COMP(op) \
            template<class Container1, class Container2> \
        constexpr auto operator op(const indirect_iterator<Container1>& lhs, \
                                   const indirect_iterator<Container2>& rhs) \
        { \
            return lhs.index op rhs.index; \
        }
    
    QTL_INDIRECT_DEF_COMP(==)
    QTL_INDIRECT_DEF_COMP(!=)
    QTL_INDIRECT_DEF_COMP(<)
    QTL_INDIRECT_DEF_COMP(<=)
    QTL_INDIRECT_DEF_COMP(>)
    QTL_INDIRECT_DEF_COMP(>=)
    QTL_INDIRECT_DEF_COMP(<=>)
    



        template<class Container>
    constexpr indirect_iterator<Container>
        operator+(typename indirect_iterator<Container>::difference_type n,
                  const indirect_iterator<Container>& it )
    {
        return it + n;
    }



        template<class Container1, class Container2>
    constexpr auto operator-(const indirect_iterator<Container1>& lhs,
                             const indirect_iterator<Container2>& rhs)
    {
        return lhs.index - rhs.index;
    }




        template<class Container>
    indirect_iterator<Container> ibegin(Container& c)
    {
        return { &c, 0u };
    }

        template<class Container>
    indirect_iterator<Container> iend(Container& c)
    {
        return { &c, c.size() };
    }
}}
#pragma once

#include <type_traits>

// decl_field -> Named Field composition
// decl_member -> Get field pointer
// decl_isin -> Check if type has the field named like the symbol

#define qtl_def_symbol(decl, symbol) \
        template<class T> \
    struct decl##_field { T symbol; }; \
        template<class T> \
    struct decl##_member { static inline constexpr auto value = &T::symbol; }; \
        template<class T, typename = int> \
    struct decl##_isin : std::false_type {}; \
        template<class T> \
    struct decl##_isin<T, decltype((void)&T::symbol, 0)> : std::true_type {};




namespace qtl { namespace
{
        template<class T>
    struct atype { using type = T; };

        template<class FField, class FMember, class FIsin>
    struct symbol
    {
        //    template<class T>
        //using field = decltype(FField{}.template operator()<T>())::field; // <-- crashes Clang

        //    template<class T>
        //static inline constexpr auto member = FMember{}.template operator()<T>();

        /*    template<class T>
        static inline constexpr auto member = FMember{}(atype<T>{});*/ // crashes Clang again

            template<class T>
        using field = typename decltype(FField{}(atype<T>{}))::field;

//            template<class T>
//        static inline constexpr auto T::* member = FMember{}(atype<T>{}).member;

            template<class T>
        using member_type = typename decltype(FMember{}(atype<T>{}))::member_type;

            template<class T>
        static inline constexpr member_type<T> T::* member = FMember{}(atype<T>{}).member;

            /*template<class T>
        using isin = decltype(FMember{}.operator()<T>())::member;*/


            template<class T, typename = int>
        struct isin_impl : std::false_type {};
        //    template<class T>
        //struct isin_impl<T, decltype((void)&FMember{}(atype<T>{}).member, 0)> : std::true_type {};



            template<class T>
        static inline constexpr bool isin = isin_impl<T>::value;



            template<class T>
        static inline constexpr auto& of(T& obj) { return obj.*member<T>; }
    };

        template<class FField, class FMember, class FIsin>
    constexpr auto make_symbol(FField, FMember, FIsin) { return symbol<FField, FMember, FIsin>{}; }
}}

#define qtl_symbol(symbol) \
    qtl::make_symbol( \
        /*[]<class T>()*/ \
        [](auto t) \
        { \
            using T = typename decltype(t)::type; \
            struct s_field { T symbol; }; \
            struct info { using field = s_field; }; \
            return info{}; \
        }, \
        /*[]<class T>()*/ \
        [](auto t) \
        { \
            using T = typename decltype(t)::type; \
            struct s_member { \
                using member_type = decltype(std::declval<T>().symbol); \
                decltype(&T::symbol) member; \
            }; \
            return s_member { &T::symbol }; \
        }, \
        nullptr \
    )








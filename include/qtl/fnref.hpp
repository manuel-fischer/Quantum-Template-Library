#pragma once

namespace qtl { namespace
{
    // TODO inferface...

        template<class FN>
    struct fnref;

    
        template<class Ret, class... Args>
    struct fnref<Ret(Args...)>
    {
        using function_pointer = Ret(*)(void* user, Args...);
        void*            user;
        function_pointer fptr;


        auto operator()(Args... args) const
        {
            return fptr(user, std::forward<Args>(args)...);
        }
    };


    namespace fnref_func_object_impl
    {
            template<class CallOpMember>
        struct func_sig_impl;
        
            template<class Obj, class Ret, class... Args>
        struct func_sig_impl<Ret(Obj::*)(Args...) const>
        {
            using type = Ret(Args...);
        };

            template<class FObj, class T = decltype(&FObj::operator())>
        struct func_sig
        {
            using type = typename func_sig_impl<T>::type;
        };

            template<class FObj, class FN>
        struct fnref_invoker;

            template<class FObj, class Ret, class... Args>
        struct fnref_invoker<FObj, Ret(Args...)>
        {
            static Ret call(void* user, Args... args)
            {
                return (*static_cast<FObj*>(user))(std::forward<Args>(args)...);
            }
        };
    }

        template<class FObj, class FN = typename fnref_func_object_impl::func_sig<FObj>::type>
    constexpr auto make_fnref(FObj& fn) -> fnref<FN>
    {
        using namespace fnref_func_object_impl;
        return {
            static_cast<void*>(&fn),
            &fnref_invoker<FObj, FN>::call
        };
    }
}}
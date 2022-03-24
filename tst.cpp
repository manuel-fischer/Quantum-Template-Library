#include <iostream>
#include <array>
#include <algorithm>
#include "qtl.hpp"


qtl_def_symbol(sym_size, size);


int main()
{
    using namespace qtl;
    using namespace std;
    
    {
        auto add = [](int a, int b) { return a + b; };
        fnref<int(int, int)> f = make_fnref(add);
        cout << f(40, 2) << '\n';
    }

    {
        cout << sym_size_isin<string>::value << ' ' << sym_size_isin<int>::value << '\n';
    }

    auto SIZE_v = qtl_symbol(size);
        /*make_symbol(
            []<class T>() { struct s_field { T size; }; struct info { using field = s_field; }; return info{}; },
            []<class T>() { return &T::size; },
            nullptr
        );*/

    using SIZE = decltype(SIZE_v);

    auto sized = SIZE::field<size_t>{};
    //struct { size_t size; } sized;
    
    //auto member = &decltype(sized)::size;//info::member<decltype(sized)>; // &decltype(sized)::size;
    //sized.*member = 421;
    //cout << sized.*member << '\n';
    
    SIZE::of(sized) = 12345;
    cout << SIZE::of(sized) << '\n';

    cout << SIZE::isin<less<>> << '\n';



    array<int, 5> fibs = {{ 1, 1, 2, 3, 5 }};
    for(int fib : fibs) cout << fib << ' ';
    cout << "- ";

    auto r = reversed {fibs};
    for(int fib : r) cout << fib << ' ';
    cout << "- ";

    std::sort(std::begin(r), std::end(r));
    for(int fib : r) cout << fib << ' ';
    cout << "- ";

    std::sort(std::begin(fibs), std::end(fibs));
    for(int fib : r) cout << fib << '~';
    cout << "- ";

    std::sort(qtl::ibegin(fibs), qtl::iend(fibs));
    for(int fib : fibs) cout << fib << '~';
    cout << '\n';

    //std::for_each(qtl::ibegin(fibs), qtl::iend(fibs), [](int i) { cout << i << ','; });
    //cout << '\n';
}
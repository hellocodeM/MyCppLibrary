#ifndef MING_IO_PRINT_HPP
#define MING_IO_PRINT_HPP

#include <string>
#include <cstring>
#include <iostream>

#include "has_iterator.hpp"

namespace ming {
namespace IO {

namespace detail {
/**
 * @desc: Print arbitrary object to stdout, including integral, C-string, object(with overloaded operator <<), C++ container.
 * @para: The object to print.
 * @exam: ming::print(1024); 
 *        ming::print("hello");
 *        ming::print(std::string("hello"));
 *        ming::print(Dog("Scooby Doo"));
 *        ming::print(std::vector<int>{ 1, 0, 2, 4 });
 */
template <class T> void print(const T&);

void print() {};

/**
 * @desc: Print arbitrary object to stdout, with a line break. 
 */
template <class T> void println(const T&);

void println() { std::cout << std::endl; };
                                                            
template <class T>                    
void print_impl(const T& item, std::false_type) {           
    std::cout << item;
}

void print_impl(const std::string& str, std::true_type) {
    std::cout << str;
}

template <class T>
void print_impl(const T& cont, std::true_type) {
    for (auto i : cont)
        print(i), std::cout << " ";
}

template <class T>
void print(const T& item) {
    print_impl(item, typename std::has_iterator<T>::type());
}

template <class T>
void println(const T& item) {
    print(item);
    std::cout << std::endl;
}

} /* end of namespace ming::IO::detail */
} /* end of namespace ming::IO */

using IO::detail::print;
using IO::detail::println;
} /* end of namespace ming */
#endif

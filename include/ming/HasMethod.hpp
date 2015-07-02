#ifndef STD_HASMETHOD_HPP
#define STD_HASMETHOD_HPP


#include <type_traits>
#include <vector>

#define HAS_METHOD(M) \
    template <class T> \
    struct has_##M { \
        private: \
            template <class U> static std::true_type check(decltype(&U::M)); \
            template <class U> static std::false_type check(...); \
        public: \
            const static bool value = decltype(check<T>(nullptr))::value; \
            using type = std::integral_constant<bool, value>; \
    }

#endif 

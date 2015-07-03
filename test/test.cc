#include <vector>
#include <cassert>
#include <algorithm>

#include <ming/all.hpp>

class Dog {
    public:
        Dog (const char* name): name_(name) {}

        const std::string& name() const {
            return name_;
        }

        friend std::ostream& operator << (std::ostream& out,  const Dog& dog) {
            out << dog.name();
            return out;
        }

    private:
        std::string name_;
};

struct Functor {
    int operator() () {
        return 1;
    }
};

void TestExecTime() {
    Test {
        std::vector<int> vec(200000);
        ming::println(ExecTime(std::random_shuffle(vec.begin(), vec.end())));
    }
}

void TestPrint() {
    Test {
        ming::println("scooby doo");
        ming::println(1024);
        ming::println(std::vector<int> {1, 2, 3});
    }
}

void TestPrintf() {
    Test {
        ming::printf("object: %\n", Dog("schooby doo"));
        ming::printf("name: %\n", "schooby doo");
        ming::printf("age: %\n", 2);
        ming::printf("friends: %\n", std::vector<const char*>{ "tom", "kitty", "lilly"});
    }
}

void TestHasIterator() {
    Test {
        assert((std::has_iterator<std::vector<int>>::value == true));
        assert((std::has_iterator<int>::value == false));
    } 
}

void TestIsFunctor() {
    Test {
        assert((std::is_functor<Functor>::value));
        assert((std::is_functor<Dog>::value == false));
    } 
}

HAS_INNERTYPE(value_type);
HAS_INNERTYPE(const_iterator);

void TestHasInnerType() {
    Test {
        assert(has_value_type<std::vector<int>>::value);
        assert(has_value_type<int>::value == false);
        assert(has_const_iterator<std::vector<int>>::value);
    } 
}

HAS_METHOD(size);
HAS_METHOD(name);

void TestHasMethod() {
    Test {
        assert(has_size<std::vector<int>>::value);
        assert(has_name<Dog>::value);
        assert(has_name<std::vector<int>>::value == false);
    } 
}

void TestLambda() {
    Test {
        using namespace ming::placeholders;

        /* type test */
        TestBlock {
            int x = 1;
            const int y = 1;
            
            auto add1 = _1 + 1;
            auto addx = _1 + x;
            auto addy = _1 + y;
            auto add = _1 + _2;
            
            assert((add1(1) == 2));
            assert((add1(x) == 2));
            assert((add1(y) == 2));
            assert((addx(1) == 2));
            assert((addx(x) == 2));
            assert((addx(y) == 2));
            assert((addy(1) == 2));
            assert((addy(x) == 2));
            assert((addy(y) == 2));

            assert((add(1, 1) == 2));
            assert((add(x, 1) == 2));
            assert((add(y, 1) == 2));
            assert((add(x, y) == 2));
        }

        /* functionality test  */
        TestBlock {
            std::vector<int> vec = { 1, 2, 3 };
            const std::vector<int> ans = { 2, 3, 4 };

            std::for_each(vec.begin(), vec.end(), _1 += 1);
            assert(vec == ans);

            std::for_each(vec.begin(), vec.end(), _1 * 1);
            assert(vec == ans);

            std::for_each(vec.begin(), vec.end(), _1 *= 1);
            assert(vec == ans);

            std::for_each(vec.begin(), vec.end(), _1 -= 1);
            assert((vec == std::vector<int>{ 1, 2, 3} ));
            
            std::for_each(vec.begin(), vec.end(), std::cout << _1);
            std::for_each(vec.begin(), vec.end(), _1 %= 4);
            assert((vec == std::vector<int>{ 1, 2, 3 } ));

            std::for_each(vec.begin(), vec.end(), _1 <<= 1);
            assert((vec == std::vector<int>{ 2, 4, 6 } ));

            std::for_each(vec.begin(), vec.end(), _1 &= 1);
            assert((vec == std::vector<int>{ 0, 0, 0 }));

            std::for_each(ans.begin(), ans.end(), std::cout << _1);
        }

        /* another kind of lambda */
        TestBlock {
            int x = 1;
            const int y = 1;
            
            auto add1 = lambda(_ + 1);
            auto addx = lambda(_ + x);
            auto addy = lambda(_ + y);
            
            assert((add1(1) == 2));
            assert((add1(x) == 2));
            assert((add1(y) == 2));
            assert((addx(1) == 2));
            assert((addx(x) == 2));
            assert((addx(y) == 2));
            assert((addy(1) == 2));
            assert((addy(x) == 2));
            assert((addy(y) == 2));

            auto print = lambda(ming::print(_));
            print("wow");
        }

        TestBlock {
            std::vector<int> vec = { 1, 2, 3 };

            std::for_each(vec.begin(), vec.end(), lambda(_ + 1));
            std::for_each(vec.begin(), vec.end(), lambda(_ += 1));
            assert((vec == std::vector<int>{ 2, 3, 4 }));

            std::for_each(vec.begin(), vec.end(), lambda(_ * 1));
            std::for_each(vec.begin(), vec.end(), lambda(_ *= 1));
            assert((vec == std::vector<int>{ 2, 3, 4 }));

            std::sort(vec.begin(), vec.end(), lambda2(_1 > _2));
            assert((vec == std::vector<int>{ 4, 3, 2}));
        }
        
    }
    
}

int main()
{
    TestExecTime();
    TestPrint();
    TestPrintf();
    TestHasIterator();
    TestIsFunctor();
    TestHasInnerType();
    TestHasMethod();
    TestLambda();
    
    return 0;
}

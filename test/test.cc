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

            std::for_each(vec.begin(), vec.end(), lambda(ming::println(_)));
            std::for_each(vec.begin(), vec.end(), lambda(printf("%d\n", _)));
        }
        
    }
    
}

void TestCascadeFunction() {
    Test {
        /* test for operator + */
        TestBlock {
            ming::vector<int> vec1 = { 1, 2, 3 };
            const ming::vector<int> vec2 = { 1, 2, 3 };
            int x1 = 4;
            int& x2 = x1;
            const int& x3 = 4;
            int&& x4 = 4;
            
            /* rhs is int */
            assert((vec1 + x1 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec2 + x1 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((std::move(vec1) + x1 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec1 == ming::vector<int>{ 1, 2, 3 }));

            /* rhs is int& */
            assert((vec1 + x2 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec2 + x2 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((std::move(vec1) + x2 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec1 == ming::vector<int>{ 1, 2, 3 }));
            
            /* rhs is const int& */
            assert((vec1 + x3 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec2 + x3 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((std::move(vec1) + x3 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec1 == ming::vector<int>{ 1, 2, 3 }));

            /* rhs is int&& */
            assert((vec1 + x4 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec2 + x4 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((std::move(vec1) + std::move(x4) == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec1 == ming::vector<int>()));
            
            vec1 = { 1, 2, 3 }; /* restore vec1 */
            /* rhs is literal */
            assert((vec1 + 4 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec2 + 4 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((std::move(vec1) + 4 == ming::vector<int>{ 1, 2, 3, 4 }));
            assert((vec1 == ming::vector<int>()));
            
        }

        TestBlock {
            ming::vector<int> vec = { 1, 2, 3};

            vec.foreach(_1 += 1);
            assert((vec == ming::vector<int>{ 2, 3, 4 }));
            
            assert((vec.map(_1 - 1) == ming::vector<int>{ 1, 2, 3 }));
            
            assert((vec.fold(0, _1 + _2) == 9));

            assert((vec.filter(_1 < 4) == ming::vector<int>{ 2, 3 }));

            assert((vec.take(2) == ming::vector<int>{ 2, 3 }));
            assert((vec.take(100) == ming::vector<int>{ 2, 3, 4 }));
        }
        /* performance test */
        TestBlock {
            ming::vector<int> vec(2000000, 1);
            std::iota(vec.begin(), vec.end(), 1);

            ming::printf("map 2000000 elements time: %\n", ExecTime(vec.map(_1 - 1)));
            ming::printf("filter 20000000 elements time: %\n", ExecTime(vec.filter(_1 <= 10000)));
            ming::printf("foreach 20000000 elements time: %\n", ExecTime(vec.foreach(_1 + 1)));
            ming::printf("fold 20000000 elements time: %\n", ExecTime(vec.fold(0, _1 + _2)));
        }
    }
}

void TestContainers() {
    Test { 
        constexpr size_t cont_size = 100;
        /* test for ming::vector */
        TestBlock {
            ming::vector<int> vec(cont_size);
            vec.fold(0, lambda2((_2 = _1) + 1));

            /* single mode */
            assert(vec == ming::range(0, cont_size));
            assert((vec.map(_ * 2) == ming::range(0, cont_size*2, 2)));
            assert((vec.filter(_ < 50) == ming::range(0, 50)));
            assert((vec.take(10) == ming::range(0, 10)));
            /* cascade map */
            assert((ming::range(0, 10).map(_ * 2).map(_ * 2).map(_ * 2) == ming::range(0, 80, 8)));
            /* cascade fold */
            assert((ming::range(0, 10).fold(ming::vector<int>(), lambda2((_1.push_back(_2 * 2), _1))).fold(0, _ + _) == 90));
            /* cascade filter */
            assert((ming::range(0, 100).filter(lambda(_ % 2 == 0)).filter(lambda(_ % 3 == 0)) == ming::range(0, 100, 6)));
            /* cascade take */
            assert((ming::range(0, 100).take(50).take(20).take(10) == ming::range(0, 10)));
            /* compound */
            assert((ming::range(0, 100).filter(lambda(_ % 2 == 0)).map(_ / 2).fold(0, _ + _) == 1225));
        }

        /* test for ming::list */
        TestBlock {
        }
        /* test for ming::map */
        TestBlock {

        }
        /* test for ming::set */
        TestBlock {

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
    TestCascadeFunction();
    TestContainers();
    return 0;
}

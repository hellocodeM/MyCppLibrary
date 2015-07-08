#include <vector>
#include <cassert>
#include <algorithm>
#include <list>

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

void TestExecutionTime() {
    Test {
        std::vector<int> vec(200000);
        ming::println(ExecutionTime(std::random_shuffle(vec.begin(), vec.end())));
    }
}

void TestPrint() {
    Test {
        const std::vector<int> vec{1, 2, 3};
        ming::println("scooby doo");
        ming::println(1024);
        ming::println(std::vector<int> {1, 2, 3});
        ming::println(vec);
        ming::println(std::make_pair(1, 2));
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
        assert((ming::has_iterator<std::vector<int>>::value == true));
        assert((ming::has_iterator<int>::value == false));
    } 
}

void TestIsFunctor() {
    Test {
        assert((ming::is_functor<Functor>::value));
        assert((ming::is_functor<Dog>::value == false));
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
HAS_METHOD(push_back);

void TestHasMethod() {
    Test {
        /* normal member function */
        static_assert(has_size<std::vector<int>>::value, "vector<int>::size");
        static_assert(has_name<Dog>::value, "Dog::name");
        static_assert(has_name<std::vector<int>>::value == false, "vector<int>::size");
        /* overloaded member function */
        static_assert(has_push_back<std::vector<int>, int>::value, "vector<int>::push_back(int)");
        static_assert(has_push_back<std::vector<int>, const int&>::value, "vector<int>::push_back(const int&)");
        static_assert(has_push_back<std::vector<int>, int&&>::value, "vector<int>::push_back(int&&)");
        static_assert(has_push_back<std::vector<int>, double>::value, "vector<int>::push_back(double)");
        static_assert(has_push_back<std::vector<int>, short>::value, "vector<int>::push_back(short)");
        static_assert(has_push_back<std::vector<int>, Dog>::value == false, "vector<int>::push_back(Dog)");
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
        using namespace ming::placeholders;
        TestBlock {
            ming::Vector<int> vec = { 1, 2, 3};

            vec.foreach(_1 += 1);
            assert((vec == ming::Vector<int>{ 2, 3, 4 }));
            
            assert((vec.map(_1 - 1) == ming::Vector<int>{ 1, 2, 3 }));

            assert((vec.fold(0, _1 + _2) == 9));

            assert((vec.filter(_1 < 4) == ming::Vector<int>{ 2, 3 }));

            assert((vec.take(2) == ming::Vector<int>{ 2, 3 }));
            assert((vec.take(100) == ming::Vector<int>{ 2, 3, 4 }));
        }
        /* performance test */
        TestBlock {
            ming::Vector<int> vec(2000000, 1);
            std::iota(vec.begin(), vec.end(), 1);

            ming::printf("map 2000000 elements time: %\n", ExecutionTime(vec.map(_1 - 1)));
            ming::printf("filter 20000000 elements time: %\n", ExecutionTime(vec.filter(_1 <= 10000)));
            ming::printf("foreach 20000000 elements time: %\n", ExecutionTime(vec.foreach(_1 + 1)));
            ming::printf("fold 20000000 elements time: %\n", ExecutionTime(vec.fold(0, _1 + _2)));
        }
    }
}

void TestIsPair() {
    Test {
        assert((ming::is_pair<int>::value == false));
        assert((ming::is_pair<std::pair<int, int>>::value == true));
    }
}

void TestContainers() {
    Test { 
        using namespace ming::placeholders;
        constexpr size_t cont_size = 100;
        /* test for ming::vector */
        TestBlock {
            ming::Vector<int> vec(cont_size);
            vec.fold(0, lambda2((_2 = _1) + 1));

            /* single mode */
            assert(vec == ming::range(0, cont_size));
            assert((vec.map(_ * 2) == ming::range(0, cont_size*2, 2)));
            assert((vec.filter(_ < 50) == ming::range(0, 50)));
            assert((vec.take(10) == ming::range(0, 10)));
            /* cascade map */
            assert((ming::range(0, 10).map(_ * 2).map(_ * 2).map(_ * 2) == ming::range(0, 80, 8)));
            /* cascade fold */
            assert((ming::range(0, 10).fold(ming::Vector<int>(), lambda2((_1.push_back(_2 * 2), _1))).fold(0, _ + _) == 90));
            /* cascade filter */
            assert((ming::range(0, 100).filter(lambda(_ % 2 == 0)).filter(lambda(_ % 3 == 0)) == ming::range(0, 100, 6)));
            /* cascade take */
            assert((ming::range(0, 100).take(50).take(20).take(10) == ming::range(0, 10)));
            /* compound */
            assert((ming::range(0, 100).filter(lambda(_ % 2 == 0)).map(_ / 2).fold(0, _ + _) == 1225));
            /* head, tail */
            assert((ming::range(0, 100).tail().head() == 1));
            
        }

        /* test for ming::list */
        TestBlock {
            using cont = ming::List<int>;
            auto range = [](int from, int to, int step = 1) { 
                return ming::range<cont>(from, to, step);
            };

            cont con(cont_size);
            con.fold(0, lambda2((_2 = _1) + 1));
            /* single mode */
            assert(con == range(0, cont_size, 1));
            assert((con.map(_ * 2) == range(0, cont_size*2, 2)));
            assert((con.filter(_ < 50) == range(0, 50, 1)));
            assert((con.take(10) == range(0, 10, 1)));
            /* cascade map */
            assert((range(0, 10).map(_ * 2).map(_ * 2).map(_ * 2) == range(0, 80, 8)));
            /* cascade fold */
            assert((range(0, 10).fold(ming::List<int>(), lambda2((_1.push_back(_2 * 2), _1))).fold(0, _ + _) == 90));
            /* cascade filter */
            assert((range(0, 100).filter(lambda(_ % 2 == 0)).filter(lambda(_ % 3 == 0)) == range(0, 100, 6)));
            /* cascade take */
            assert((range(0, 100).take(50).take(20).take(10) == range(0, 10)));
            /* compound */
            assert((range(0, 100).filter(lambda(_ % 2 == 0)).map(_ / 2).fold(0, _ + _) == 1225));
            /* head, tail */
            assert((range(0, 100).tail().head() == 1));
        }
        /* test for ming::set */
        TestBlock {
            using container = ming::Set<int>;
            auto range = [](int from, int to, int step = 1) {
                return ming::range<container>(from, to, step);
            };

            container con;
            for (int i = 0; i < 100; i++)
                con.insert(i);
            /* single mode */
            assert(con == range(0, cont_size, 1));
            assert((con.map(_ * 2) == range(0, cont_size*2, 2)));
            assert((con.filter(_ < 50) == range(0, 50, 1)));
            assert((con.take(10) == range(0, 10, 1)));
            /* cascade map */
            assert((range(0, 10).map(_ * 2).map(_ * 2).map(_ * 2) == range(0, 80, 8)));
            /* cascade fold */
            assert((range(0, 10).fold(ming::Set<int>(), lambda2((_1.add(_2 * 2), _1))).fold(0, _ + _) == 90));
            /* cascade filter */
            assert((range(0, 100).filter(lambda(_ % 2 == 0)).filter(lambda(_ % 3 == 0)) == range(0, 100, 6)));
            /* cascade take */
            assert((range(0, 100).take(50).take(20).take(10) == range(0, 10)));
            /* compound */
            assert((range(0, 100).filter(lambda(_ % 2 == 0)).map(_ / 2).fold(0, _ + _) == 1225));
            /* head, tail */
            assert((range(0, 100).tail().head() == 1));
        }
        /* test for ming::map */
        TestBlock {
            using pair_type = std::pair<int, int>;
            using container = ming::Map<pair_type>;

            container con = { { 1, 2}, { 3, 4}, { 5, 6 } };
            container ans = { {1, 4}, {3, 8}, {5, 12} };
            
            /* map to another map */
            assert((con.map(lambda(std::make_pair(_.first, _.second * 2))) == ans));
            /* map to a vector */
            assert((con.map(lambda(_.second * 2)) == ming::Vector<int>{4, 8, 12}));
            /* cascade map */
            auto convert1 = [](auto&& pair) { return std::make_pair(pair.first, pair.second * 2); };
            auto convert2 = [](auto&& pair) { return std::make_pair(pair.first, pair.second / 2); };
            assert((con.map(convert1).map(convert2) == con));
            /* cascade filter */
            assert((con.filter(lambda(_.first != 1)).filter(lambda(_.first != 3)) == ming::Map<pair_type>{{5, 6}}));
            /* cascade take */
            assert((con.take(3).take(2).take(1) == ming::Map<pair_type>{{1, 2}}));
            /* head tail */
            assert((con.tail().head() == std::pair<const int, int>(3, 4)));
            
        }
    }
}

void TestOverloadedOperator() {
    Test {
        using namespace ming::operators;
        TestBlock {
            assert((std::move(ming::Vector<int>()) + 1 == ming::Vector<int>{1}));
        }
    }
}

int main()
{
    TestExecutionTime();
    TestPrint();
    TestPrintf();
    TestHasIterator();
    TestIsFunctor();
    TestHasInnerType();
    TestHasMethod();
    TestLambda();
    TestCascadeFunction();
    TestIsPair();
    TestContainers();
    TestOverloadedOperator();
    return 0;
}

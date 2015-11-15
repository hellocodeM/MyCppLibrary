#include <vector>
#include <cassert>
#include <algorithm>
#include <list>

#include <ming/all.hpp>

class Dog {
public:
    Dog(const char* name) : name_(name) {}

    const std::string& name() const { return name_; }

    friend std::ostream& operator<<(std::ostream& out, const Dog& dog) {
        out << dog.name();
        return out;
    }

private:
    std::string name_;
};

struct Functor {
    int operator()() { return 1; }
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
        ming::println(std::vector<int>{1, 2, 3});
        ming::println(vec);
        ming::println(std::make_pair(1, 2));
    }
}

void TestPrintf() {
    Test {
        ming::printf("object: %\n", Dog("schooby doo"));
        ming::printf("name: %\n", "schooby doo");
        ming::printf("age: %\n", 2);
        ming::printf("friends: %\n", std::vector<const char*>{"tom", "kitty", "lilly"});
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
        static_assert(has_push_back<std::vector<int>, const int&>::value,
                      "vector<int>::push_back(const int&)");
        static_assert(has_push_back<std::vector<int>, int&&>::value,
                      "vector<int>::push_back(int&&)");
        static_assert(has_push_back<std::vector<int>, double>::value,
                      "vector<int>::push_back(double)");
        static_assert(has_push_back<std::vector<int>, short>::value,
                      "vector<int>::push_back(short)");
        static_assert(has_push_back<std::vector<int>, Dog>::value == false,
                      "vector<int>::push_back(Dog)");
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
            std::vector<int> vec = {1, 2, 3};
            const std::vector<int> ans = {2, 3, 4};

            std::for_each(vec.begin(), vec.end(), _1 += 1);
            assert(vec == ans);

            std::for_each(vec.begin(), vec.end(), _1 * 1);
            assert(vec == ans);

            std::for_each(vec.begin(), vec.end(), _1 *= 1);
            assert(vec == ans);

            std::for_each(vec.begin(), vec.end(), _1 -= 1);
            assert((vec == std::vector<int>{1, 2, 3}));

            std::for_each(vec.begin(), vec.end(), std::cout << _1);
            std::for_each(vec.begin(), vec.end(), _1 %= 4);
            assert((vec == std::vector<int>{1, 2, 3}));

            std::for_each(vec.begin(), vec.end(), _1 <<= 1);
            assert((vec == std::vector<int>{2, 4, 6}));

            std::for_each(vec.begin(), vec.end(), _1 &= 1);
            assert((vec == std::vector<int>{0, 0, 0}));

            std::for_each(ans.begin(), ans.end(), std::cout << _1);
        }

        /* another kind of lambda */
        TestBlock {
            int x = 1;
            const int y = 1;

            auto add1 = Lambda(_ + 1);
            auto addx = Lambda(_ + x);
            auto addy = Lambda(_ + y);

            assert((add1(1) == 2));
            assert((add1(x) == 2));
            assert((add1(y) == 2));
            assert((addx(1) == 2));
            assert((addx(x) == 2));
            assert((addx(y) == 2));
            assert((addy(1) == 2));
            assert((addy(x) == 2));
            assert((addy(y) == 2));

            auto print = Lambda(ming::print(_));
            print("wow");
        }

        TestBlock {
            std::vector<int> vec = {1, 2, 3};

            std::for_each(vec.begin(), vec.end(), Lambda(_ + 1));
            std::for_each(vec.begin(), vec.end(), Lambda(_ += 1));
            assert((vec == std::vector<int>{2, 3, 4}));

            std::for_each(vec.begin(), vec.end(), Lambda(_ * 1));
            std::for_each(vec.begin(), vec.end(), Lambda(_ *= 1));
            assert((vec == std::vector<int>{2, 3, 4}));

            std::sort(vec.begin(), vec.end(), Lambda2(_1 > _2));
            assert((vec == std::vector<int>{4, 3, 2}));

            std::for_each(vec.begin(), vec.end(), Lambda(ming::println(_)));
            std::for_each(vec.begin(), vec.end(), Lambda(printf("%d\n", _)));
        }
    }
}

void TestCascadeFunction() {
    Test {
        using namespace ming::placeholders;
        constexpr size_t size = 12345678;
        TestBlock {
            ming::Vector<int> vec = {1, 2, 3};

            vec.foreach (_1 += 1);
            assert((vec == ming::Vector<int>{2, 3, 4}));

            assert((vec.map(_1 - 1) == ming::Vector<int>{1, 2, 3}));

            assert((vec.fold(0, _1 + _2) == 9));

            assert((vec.filter(_1 < 4) == ming::Vector<int>{2, 3}));

            assert((vec.take(2) == ming::Vector<int>{2, 3}));
            assert((vec.take(100) == ming::Vector<int>{2, 3, 4}));
        }
        /* performance test */
    }
}

void TestIsPair() {
    Test {
        assert((ming::is_pair<int>::value == false));
        assert((ming::is_pair<std::pair<int, int>>::value == true));
    }
}

template <class Container>
void TestOverloadedOperatorCase() {
    Container con1{1, 2, 3};
    Container con2{4, 5, 6};

    /* operator += */
    /* container and element */
    con1 += 4;
    assert((con1 == Container{1, 2, 3, 4}));
    /* container and container */
    con1 = {1, 2, 3};
    con1 += con2;
    assert((con1 == Container{1, 2, 3, 4, 5, 6}));
    con1 = {1, 2, 3};
    con2 += con1;
    assert((con2 == Container{4, 5, 6, 1, 2, 3}));

    /* operator + */
    con1 = {1, 2, 3};
    con2 = {4, 5, 6};
    /* container and element */
    assert(((con1 + 4) == Container{1, 2, 3, 4}));
    assert(((4 + con1) == Container{1, 2, 3, 4}));
    /* container and container */
    assert((con1 + con2 == Container{1, 2, 3, 4, 5, 6}));
    assert((con2 + con1 == Container{4, 5, 6, 1, 2, 3}));
    assert((con1 == Container{1, 2, 3}));
    assert((con2 == Container{4, 5, 6}));
    /* rvalue */
    assert((Container{1} + 2 == Container{1, 2}));
    assert((Container{1} + Container{2} == Container{1, 2}));
}

void TestOverloadedOperator() {
    Test {
        /* ming::Vector */
        TestBlock {
            using Container = ming::Vector<int>;
            TestOverloadedOperatorCase<Container>();
        }
        /* ming::List */
        TestBlock {
            using Container = ming::List<int>;
            TestOverloadedOperatorCase<Container>();
        }
        TestBlock {
            using Container = ming::Set<int>;
            TestOverloadedOperatorCase<Container>();
        }
        TestBlock {
            using Container = ming::Map<std::pair<int, int>>;
            Container con1{{1, 2}, {3, 4}};
            Container con2{{5, 6}, {7, 8}};

            /* operator += */
            /* container and element */
            con1 += std::make_pair(5, 6);
            assert((con1 == Container{{1, 2}, {3, 4}, {5, 6}}));
            con1 = {{1, 2}, {3, 4}};
            /* contaienr and container */
            con1 += con2;
            assert((con1 == Container{{1, 2}, {3, 4}, {5, 6}, {7, 8}}));

            /* oeprator + */
            con1 = {{1, 2}, {3, 4}};
            /* container and element */
            assert((con1 + std::make_pair(5, 6) == Container{{1, 2}, {3, 4}, {5, 6}}));
            assert((std::make_pair(5, 6) + con1 == Container{{1, 2}, {3, 4}, {5, 6}}));
            /* container and contaienr */
            assert((con1 + con2 == Container{{1, 2}, {3, 4}, {5, 6}, {7, 8}}));
            assert((con2 + con1 == Container{{1, 2}, {3, 4}, {5, 6}, {7, 8}}));
            /* rvalue */
            assert((Container{{1, 2}} + std::make_pair(3, 4) == Container{{1, 2}, {3, 4}}));
            assert((Container{{1, 2}} + Container{{3, 4}} == Container{{1, 2}, {3, 4}}));
        }
    }
}

template <class Cont>
void TestContainerCase() {
    using namespace ming::placeholders;
    /* map, filter, take, fold */
    assert((ming::range<Cont>(0, 100).map(_ * 2) == ming::range<Cont>(0, 200, 2)));
    assert((ming::range<Cont>(0, 100).filter(_ < 50) == ming::range<Cont>(0, 50)));
    assert((ming::range<Cont>(0, 100).take(50) == ming::range<Cont>(0, 50)));
    assert((ming::range<Cont>(0, 100).fold(0, _ + _) == 4950));
    /* cascade map */
    assert((ming::range<Cont>(0, 100).map(_ * 2).map(_ * 2).map(_ * 2) ==
            ming::range<Cont>(0, 800, 8)));
    /* cascade filter */
    assert((ming::range<Cont>(0, 100).filter(Lambda(_ % 2 == 0)).filter(Lambda(_ % 3 == 0)) ==
            ming::range<Cont>(0, 100, 6)));
    /* cascade take */
    assert((ming::range<Cont>(0, 100).take(50).take(20).take(10) == ming::range<Cont>(0, 10)));
    /* compound */
    assert(
        (ming::range<Cont>(0, 100).filter(Lambda(_ % 2 == 0)).map(_ / 2).fold(0, _ + _) == 1225));
    /* head tail */
    assert((ming::range<Cont>(0, 100).tail().head() == 1));
}

template <class Cont>
void TestContainerCaseMap() {
    Cont con = {{1, 2}, {3, 4}, {5, 6}};
    Cont ans = {{1, 4}, {3, 8}, {5, 12}};

    /* map to another map */
    assert((con.map(Lambda(std::make_pair(_.first, _.second * 2))) == ans));
    /* map to a vector */
    assert((con.map(Lambda(_.second * 2)) == ming::Vector<int>{4, 8, 12}));
    /* cascade map */
    auto convert1 = [](auto&& pair) { return std::make_pair(pair.first, pair.second * 2); };
    auto convert2 = [](auto&& pair) { return std::make_pair(pair.first, pair.second / 2); };
    assert((con.map(convert1).map(convert2) == con));
    /* cascade filter */
    assert((con.filter(Lambda(_.first != 1)).filter(Lambda(_.first != 3)) == Cont{{5, 6}}));
    /* cascade take */
    assert((con.take(3).take(2).take(1) == Cont{{1, 2}}));
    /* head tail */
    assert((con.tail().head() == std::pair<const int, int>(3, 4)));
}

void TestContainers() {
    Test {
        using namespace ming::placeholders;
        constexpr size_t cont_size = 100;
        /* test for ming::Vector */
        TestBlock {
            using container = ming::Vector<int>;
            TestContainerCase<container>();
        }
        /* test for ming::List */
        TestBlock {
            using container = ming::List<int>;
            TestContainerCase<container>();
        }
        /* test for ming::Set */
        TestBlock {
            using container = ming::Set<int>;
            TestContainerCase<container>();
        }
        /* test for ming::Map */
        TestBlock {
            using container = ming::Map<std::pair<int, int>>;
            TestContainerCaseMap<container>();
        }
    }
}

void TestParallelContainers() {
    Test {
        using namespace ming::placeholders;

        /* correctness */

        TestBlock {
            /* ming::ParallelVector */
            using container = ming::ParallelVector<int>;
            TestContainerCase<container>();
        }
        TestBlock {
            /* ming::ParallelList */
            using container = ming::ParallelList<int>;
            TestContainerCase<container>();
        }
        TestBlock {
            /* ming::ParallelSet */
            using container = ming::ParallelSet<int>;
            TestContainerCase<container>();
        }
        TestBlock {
            /* ming::ParallelMap */
            using container = ming::ParallelMap<std::pair<int, int>>;
            TestContainerCaseMap<container>();
        }
        TestBlock {
            /* par memeber function */
            assert((ming::Vector<int>{1, 2, 3}.par() == ming::ParallelVector<int>{1, 2, 3}));
            assert((ming::List<int>{1, 2, 3}.par() == ming::ParallelList<int>{1, 2, 3}));
            assert((ming::Set<int>{1, 2, 3}.par() == ming::ParallelSet<int>{1, 2, 3}));
            assert((ming::Map<std::pair<int, int>>{{1, 2}, {2, 3}}.par() ==
                    ming::ParallelMap<std::pair<int, int>>{{1, 2}, {2, 3}}));
        }
    }
}

void TestThreadPool() {
    Test {
        ming::ThreadPool pool;
        for (int i = 0; i < 1000; i++) {
            pool.Submit([] {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(10ms);
            });
        }
        pool.Wait();
    }
}

int main() {
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
    TestOverloadedOperator();
    TestContainers();
    TestParallelContainers();
    TestThreadPool();
    return 0;
}

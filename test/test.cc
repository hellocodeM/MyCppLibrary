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
    TestCase(
        std::vector<int> vec(200000);
        ming::println(ExecTime(std::random_shuffle(vec.begin(), vec.end())));
    );
}
void TestPrint() {
    TestCase(
        ming::println("scooby doo");
        ming::println(1024);
        ming::println(std::vector<int> {1, 2, 3});
    );
}

void TestPrintf() {
    TestCase(
        ming::printf("object: %\n", Dog("schooby doo"));
        ming::printf("name: %\n", "schooby doo");
        ming::printf("age: %\n", 2);
        ming::printf("friends: %\n", std::vector<const char*>{ "tom", "kitty", "lilly"});
    );
}

void TestHasIterator() {
    TestCase(
        assert((std::has_iterator<std::vector<int>>::value == true));
        assert((std::has_iterator<int>::value == false));
    );
}

void TestIsFunctor() {
    TestCase(
        assert((std::is_functor<Functor>::value));
        assert((std::is_functor<Dog>::value == false));
    );
}

HAS_INNERTYPE(value_type);
HAS_INNERTYPE(const_iterator);

void TestHasInnerType() {
    TestCase(
        assert(has_value_type<std::vector<int>>::value);
        assert(has_value_type<int>::value == false);
        assert(has_const_iterator<std::vector<int>>::value);
    );
}

HAS_METHOD(size);
HAS_METHOD(name);

void TestHasMethod() {
    TestCase(
        assert(has_size<std::vector<int>>::value);
        assert(has_name<Dog>::value);
        assert(has_name<std::vector<int>>::value == false);
    );
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
    return 0;
}

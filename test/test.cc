#include <vector>
#include <cassert>

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

int main()
{
    TestPrint();
    TestPrintf();
    TestHasIterator();
    TestIsFunctor();
    return 0;
}

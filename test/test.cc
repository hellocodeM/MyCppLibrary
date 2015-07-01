#include <vector>

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

void TestPrint() {
    ming::println("TestPrint");
    ming::print("scooby doo");
    ming::print(1024);
    ming::print(std::vector<int> {1, 2, 3});
    ming::println("\nPass TestPrint\n");
}

void TestPrintf() {
    ming::println("TestPrintf");
    ming::printf("object: %\n", Dog("schooby doo"));
    ming::printf("name: %\n", "schooby doo");
    ming::printf("age: %\n", 2);
    ming::printf("friends: %\n", std::vector<const char*>{ "tom", "kitty", "lilly"});
    ming::println("Pass TestPrintf\n");
}

int main()
{
    TestPrint();
    TestPrintf();
    return 0;
}

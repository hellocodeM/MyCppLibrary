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
    ming::printf("object: %,\nname: %,\nage: %,\nnum: %\n", Dog("schooby"), "scooby doo", 2, std::vector<int>{1, 0, 2, 4});
    ming::println("Pass TestPrintf\n");
}

int main()
{
    TestPrint();
    TestPrintf();
    return 0;
}

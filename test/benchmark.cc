#include <algorithm>

#include <ming/all.hpp>

void TestContainers() {
    Test {
        using namespace ming::placeholders;
        constexpr size_t size = 12345678;
        TestBlock {
            ming::Vector<int> vec(size, 1);
            std::iota(vec.begin(), vec.end(), 1);

            ming::printf("map % elements time: %ms\n", size, ExecutionTime(vec.map(_1 - 1)));
            ming::printf("filter % elements time: %ms\n", size, ExecutionTime(vec.filter(_1 <= 10000)));
            ming::printf("foreach % elements time: %ms\n", size, ExecutionTime(vec.foreach(_1 + 1)));
            ming::printf("fold % elements time: %ms\n", size, ExecutionTime(vec.fold(0, _1 + _2)));
        }
    }
}
void TestParallelContainers() {
    Test {
        constexpr size_t size = 87654321;
        using namespace ming::placeholders;
        using container = ming::ParallelVector<int>;

        ming::Vector<int> vec(size);
        container con1(size);

        std::iota(con1.begin(), con1.end(), 1);
        std::iota(vec.begin(), vec.end(), 1);
        ming::printf("map % elements parallel duration: %ms\n", size, DurationTime(con1.map(_ * 2)));
        ming::printf("map % elements sequential duration: %ms\n", size, DurationTime(vec.map(_ * 2)));
        ming::printf("filter % elements parallel duration: %ms\n", size, DurationTime(con1.filter(_ < 2)));
        ming::printf("filter % elements sequential duration: %ms\n", size, DurationTime(vec.filter(_ < 2)));
        ming::printf("foreach % elements parallel duration: %ms\n", size, DurationTime(con1.foreach(_ * 2)));
        ming::printf("foreach % elements sequential duration: %ms\n", size, DurationTime(vec.foreach(_ * 2)));

    }

}

int main()
{
    TestContainers();
    TestParallelContainers();
    return 0;
}

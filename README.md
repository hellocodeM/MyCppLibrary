# MyCppLibrary
Some useful tools I wrote and used in everyday life.

# example 
## print
You want a generic print function?
```c++
ming::println(1024);
ming::println("scooby doo");
ming::println(std::string("scooby doo"));
ming::println(std::vector<int>{1, 2, 3});
ming::println(std::make_pair(1, 2));
```

## operators
You want to add an element to a container? Why not use operator +?
```c++
std::vector<int> vec{1, 2, 3};
vec += 4;                       // {1, 2, 3, 4}
auto vec1 = vec + 4;            // vec: {1, 2, 3}; vec1: {1, 2, 3, 4}
std::set<int> set{1, 2, 3};     
set += 4;                       // {1, 2, 3, 4}
auto set1 = set + 4;            // set: {1, 2, 3}; set1: {1, 2, 3, 4}
```

## placeholders
You want to execute an STL algorithm? Why not use placeholders to simply the code?
```c++
std::vector<int> vec{1, 2, 3};
std::sort(vec.begin(), vec.end(), _1 > _2); // {3, 2, 1}
std::for_each(vec.begin(), vec.end(), _ += 1); // {4, 3, 2}
```

## stream-style container
You want to use stream-style container like functional language?
```c++
ming::Vector<int>{1, 2, 3}.map(_ * 2).filter(lambda(_ % 2 == 0)).take(2)  // {2, 4 }
ming::range(0, 101).fold(0, _ + _)          // 5050
```

# List
- ming::type_traits
  - has_iterator
  - is_functor
  - is_pair
  - underlying
  
- ming::IO
  - print
  - printf
  - println
  
- ming::placeholders
  - placeholders 
  - lambda

- ming::PP
  - Test
  - TestBlock
  - HasMethod
  - HasInnerType
  - ExecTime

- ming::container
  - Iterable
  - List
  - Vector
  - Map
  - Set
  - ParallelIterable
  - ParallelList
  - ParallelVector
  - ParallelMap
  - ParallelSet
  - range
  

- ming::operators
  - +
  - +=

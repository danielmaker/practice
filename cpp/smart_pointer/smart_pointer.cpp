#include <iostream>
#include <memory>

int main(int argc, char const *argv[])
{
    // unique_ptr with the deleter
    auto theArray = std::unique_ptr<int [], void(*)(int*)>(new int[10], [](int *ptr) {
        std::cout << "delete array" << std::endl;
        delete ptr;
    });

    return 0;
}

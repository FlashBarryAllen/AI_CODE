#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <algorithm>
#include <map>
#include <set>

// Test various C++ features through examples

// Lambda expressions example
auto multiply = [](int a, int b) { return a * b; };

class RAIIExample {
private:
    int* data;
public:
    explicit RAIIExample(int size) : data(new int[size]) {
        std::cout << "RAIIExample constructed with size " << size << std::endl;
    }
    
    ~RAIIExample() {
        delete[] data;
        std::cout << "RAIIExample destructed" << std::endl;
    }
    
    // Move constructor
    RAIIExample(RAIIExample&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "RAIIExample moved" << std::endl;
    }
    
    // Move assignment operator
    RAIIExample& operator=(RAIIExample&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
            std::cout << "RAIIExample move assigned" << std::endl;
        }
        return *this;
    }
    
    // Delete copy constructor and copy assignment to prevent copying
    RAIIExample(const RAIIExample&) = delete;
    RAIIExample& operator=(const RAIIExample&) = delete;
};

void testBasicFeatures() {
    std::cout << "\n=== Testing Basic C++11/14/17 Features ===" << std::endl;
    
    // Auto keyword
    auto num = 42;
    auto pi = 3.14159;
    std::cout << "Auto detected types: " << num << ", " << pi << std::endl;
    
    // Range-based for loop
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Range-based for loop: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // Smart pointers
    std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(100);
    std::shared_ptr<int> sharedPtr2 = sharedPtr1;  // Shared ownership
    
    std::cout << "Unique ptr value: " << *uniquePtr << std::endl;
    std::cout << "Shared ptr value: " << *sharedPtr1 << std::endl;
    std::cout << "Shared ptr count: " << sharedPtr1.use_count() << std::endl;
    
    // Lambda expressions
    auto square = [](int x) { return x * x; };
    std::cout << "Lambda result: " << square(5) << std::endl;
    std::cout << "Predefined lambda result: " << multiply(6, 7) << std::endl;
}

void testSTLContainers() {
    std::cout << "\n=== Testing STL Containers ===" << std::endl;
    
    // Vector
    std::vector<int> numbers = {5, 2, 8, 1, 9};
    std::sort(numbers.begin(), numbers.end());
    std::cout << "Sorted vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Map
    std::map<std::string, int> ages = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    std::cout << "Map contents:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Set
    std::set<int> uniqueNumbers = {5, 2, 8, 1, 9, 2, 5};  // Duplicates removed
    std::cout << "Set (unique values): ";
    for (const auto& num : uniqueNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void testRAIIAndMoveSemantics() {
    std::cout << "\n=== Testing RAII and Move Semantics ===" << std::endl;
    
    // RAII
    {
        RAIIExample raii(100);
        // Destructor called automatically when going out of scope
    }
    
    // Move semantics
    RAIIExample obj1(50);
    RAIIExample obj2(std::move(obj1));  // Move constructor called
}

void testThreading() {
    std::cout << "\n=== Testing Threading ===" << std::endl;
    
    std::mutex mtx;
    int counter = 0;
    
    auto increment = [&mtx, &counter]() {
        for (int i = 0; i < 1000; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            counter++;
        }
    };
    
    std::thread t1(increment);
    std::thread t2(increment);
    
    t1.join();
    t2.join();
    
    std::cout << "Counter value after threads: " << counter << std::endl;
}

void testAsyncProgramming() {
    std::cout << "\n=== Testing Async Programming ===" << std::endl;
    
    auto asyncFunc = [](int x) -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x * x;
    };
    
    auto future = std::async(std::launch::async, asyncFunc, 10);
    
    std::cout << "Async result: " << future.get() << std::endl;
}

int main() {
    std::cout << "C++ Features Learning Project" << std::endl;
    
    testBasicFeatures();
    testSTLContainers();
    testRAIIAndMoveSemantics();
    testThreading();
    testAsyncProgramming();
    
    std::cout << "\nAll tests completed!" << std::endl;
    
    return 0;
}
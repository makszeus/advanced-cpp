#include <iostream>
#include <utility>

// Function template using perfect forwarding
template<typename T>
void process(T&& arg) {
    // Perform some processing on the argument
    std::cout << "Processing: " << std::forward<T>(arg) << std::endl;
}

// Function template with multiple arguments using perfect forwarding
template<typename T1, typename T2>
void combineAndProcess(T1&& arg1, T2&& arg2) {
    // Combine the arguments and perform some processing
    std::cout << "Combining and Processing: " << std::forward<T1>(arg1) << " " << std::forward<T2>(arg2) << std::endl;
}

int main() {
    
    int x = 7;
    const std::string str = "Hallo zusammen!";

    // Example 1: Perfect forwarding with an lvalue
    process(x); // lvalue

    // Example 2: Perfect forwarding with an rvalue
    process(96); // rvalue

    // Example 3: Perfect forwarding with a const lvalue
    process(str); // const lvalue

    // Example 4: Perfect forwarding with multiple arguments
    combineAndProcess(x, str); // lvalue and const lvalue

    return 0;
}

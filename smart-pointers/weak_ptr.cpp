#include <iostream>
#include <memory>
#include <vector>

class MyClass {
public:
    explicit MyClass(int val) : value(val) {
        std::cout << "Constructor called. Value: " << value << std::endl;
    }

    void printValue() const {
        std::cout << "Value: " << value << std::endl;
    }

    [[nodiscard]] int getValue() const {
        return value;
    }

    ~MyClass() {
        std::cout << "Destructor called. Value: " << value << std::endl;
    }

private:
    int value;
};

int main() {
    // 1. Creating a weak_ptr from shared_ptr
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(10);
    std::weak_ptr<MyClass> weakPtr1 = sharedPtr;

    // 2. Converting weak_ptr to shared_ptr (lock)
    std::shared_ptr<MyClass> sharedPtr2 = weakPtr1.lock();

    if (sharedPtr2) {
        sharedPtr2->printValue();
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    // 3. Checking if weak_ptr is expired
    if (!weakPtr1.expired()) {
        std::cout << "Weak pointer is still valid." << std::endl;
    } else {
        std::cout << "Weak pointer expired." << std::endl;
    }

    // 4. Creating weak_ptr for objects with circular references
    struct CircularRefExample {
        std::weak_ptr<CircularRefExample> selfWeakPtr;
        int value{};
    };
    auto circularPtr1 = std::make_shared<CircularRefExample>();
    auto circularPtr2 = std::make_shared<CircularRefExample>();
    circularPtr1->selfWeakPtr = circularPtr1;
    circularPtr2->selfWeakPtr = circularPtr2;

    // 5. Using weak_ptr for shared ownership in a container (e.g., vector)
    std::vector<std::shared_ptr<MyClass>> ptrVector;
    ptrVector.push_back(sharedPtr);
    ptrVector.push_back(sharedPtr2);

    // The weak_ptr does not contribute to the reference count, and the objects will be automatically deleted
    // when the last shared_ptr goes out of scope.

    return 0;
}

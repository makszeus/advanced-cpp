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

    ~MyClass() {
        std::cout << "Destructor called. Value: " << value << std::endl;
    }

    [[nodiscard]] int getValue() const {
        return value;
    }

private:
    int value;
};

int main() {
    // 1. Creating a shared_ptr using `new`
    std::shared_ptr<MyClass> ptr1(new MyClass(10));

    // 2. Creating a shared_ptr using `make_shared` (C++11 and above)
    auto ptr2 = std::make_shared<MyClass>(20);

    // 3. Copying a shared_ptr (increases reference count)
    std::shared_ptr<MyClass> ptr3 = ptr1;

    // 4. Move a shared_ptr (increases reference count)
    std::shared_ptr<MyClass> ptr4 = std::move(ptr2);

    // 5. Get the reference count of a shared_ptr
    std::cout << "Reference count of ptr1: " << ptr1.use_count() << std::endl;

    // 6. Accessing the object through shared_ptr
    ptr3->printValue();

    // 7. Resetting a shared_ptr to nullptr (decreases reference count)
    ptr3.reset();

    // 8. Custom deleter: using a lambda function as a custom deleter
    std::shared_ptr<MyClass> customPtr(new MyClass(30),
                                       [](MyClass* obj) {
                                           std::cout << "Custom deleter called. Value: " << obj->getValue() << std::endl;
                                           delete obj;
                                       });

    // 9. Using shared_ptr for shared ownership in a container (vector)
    std::vector<std::shared_ptr<MyClass>> ptrVector;
    ptrVector.push_back(ptr1);
    ptrVector.push_back(ptr4);
    ptrVector.push_back(customPtr);

    // 10. Using shared_ptr to manage objects with circular references
    struct CircularRefExample {
        std::shared_ptr<CircularRefExample> selfPtr;
        int value{};
    };
    auto circularPtr1 = std::make_shared<CircularRefExample>();
    auto circularPtr2 = std::make_shared<CircularRefExample>();
    circularPtr1->selfPtr = circularPtr1;
    circularPtr2->selfPtr = circularPtr2;

    // The shared_ptr objects will be automatically deleted when their reference count reaches zero.

    return 0;
}

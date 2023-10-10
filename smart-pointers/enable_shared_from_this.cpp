#include <iostream>
#include <memory>

class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    explicit MyClass(int value) : data(value) {}

    void printValue() const {
        std::cout << "Value: " << data << std::endl;
    }

    std::shared_ptr<MyClass> getShared() {
        return shared_from_this();
    }

private:
    int data;
};

int main() {
    // Creating a shared_ptr instance
    std::shared_ptr<MyClass> sharedPtr1 = std::make_shared<MyClass>(42);

    // Accessing member function via shared_ptr
    sharedPtr1->printValue();

    // Creating another shared_ptr using member function getShared()
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1->getShared();

    // Accessing member function via shared_ptr
    sharedPtr2->printValue();

    // Checking if both shared pointers point to the same object
    if (sharedPtr1 == sharedPtr2) {
        std::cout << "sharedPtr1 and sharedPtr2 point to the same object" << std::endl;
    } else {
        std::cout << "sharedPtr1 and sharedPtr2 point to different objects" << std::endl;
    }

    // Resetting sharedPtr1 to null
    sharedPtr1.reset();

    // Checking if sharedPtr2 is now the only owner of the object
    if (sharedPtr2.unique()) {
        std::cout << "sharedPtr2 is the only owner of the object" << std::endl;
    }

    // Resetting sharedPtr2 to null
    sharedPtr2.reset();

    // Checking if the object has been deleted
    if (sharedPtr1 == nullptr && sharedPtr2 == nullptr) {
        std::cout << "The object has been deleted" << std::endl;
    }

    return 0;
}

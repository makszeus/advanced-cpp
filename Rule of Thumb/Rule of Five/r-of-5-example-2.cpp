#include <iostream>

class MyClass {
private:
    int* data;

public:
    // Default constructor
    MyClass() : data(nullptr) {
        std::cout << "Default constructor called." << std::endl;
    }

    // Parameterized constructor
    explicit MyClass(int value) : data(new int(value)) {
        std::cout << "Parameterized constructor called." << std::endl;
    }

    // Destructor
    ~MyClass() {
        delete data;
        std::cout << "Destructor called." << std::endl;
    }

    // Copy constructor
    MyClass(const MyClass& other) : data(new int(*other.data)) {
        std::cout << "Copy constructor called." << std::endl;
    }

    // Copy assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        std::cout << "Copy assignment operator called." << std::endl;
        return *this;
    }

    // Move constructor
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Move constructor called." << std::endl;
    }

    // Other member functions and class implementation...

};

int main() {
    // Creating an instance of MyClass using the default constructor
    MyClass obj1;

    // Creating another instance using the parameterized constructor
    MyClass obj2(9);

    // Copying obj2 to obj3 using the copy constructor
    const MyClass& obj3(obj2);

    // Assigning obj3 to obj4 using the copy assignment operator
    MyClass obj4;
    obj4 = obj3;

    // Moving obj4 to obj5 using the move constructor
    MyClass obj5(std::move(obj4));

    return 0;
}

#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
};

int main() {
    Base* basePtr = new Derived();

    // Using typeid to check the dynamic type of the object
    if (typeid(*basePtr) == typeid(Derived)) {
        std::cout << "Object is of type Derived." << std::endl;
    } else if (typeid(*basePtr) == typeid(Base)) {
        std::cout << "Object is of type Base." << std::endl;
    } else {
        std::cout << "Object's dynamic type is neither Base nor Derived." << std::endl;
    }

    delete basePtr;

    return 0;
}

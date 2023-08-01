#include <iostream>
#include <memory>

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

void customDeleter(MyClass* obj) {
    std::cout << "Custom deleter called. Value: " << obj->getValue() << std::endl;
    delete obj;
}

int main() {
    // 1. Creating a unique_ptr using `new`
    std::unique_ptr<MyClass> ptr1(new MyClass(10));

    // 2. Creating a unique_ptr using `make_unique` (C++14 and above)
    auto ptr2 = std::make_unique<MyClass>(20);

    // 3. Move ownership from one unique_ptr to another
    std::unique_ptr<MyClass> ptr3 = std::move(ptr1);

    // 4. Release ownership from a unique_ptr (returns raw pointer, relinquishing ownership)
    MyClass* rawPtr = ptr2.release();
    if (rawPtr) {
        std::cout << "Raw pointer value: " << rawPtr->getValue() << std::endl;
        delete rawPtr; // Release the raw pointer's memory manually (not recommended in practice)
    }

    // 5. Accessing the object through unique_ptr
    ptr3->printValue();

    // 6. Resetting a unique_ptr with a new object (old object gets deleted)
    ptr3 = std::make_unique<MyClass>(30);

    // 7. Resetting a unique_ptr to nullptr (deletes the managed object)
    ptr3.reset();

    // 8. Custom deleter: using a lambda function as a custom deleter
    std::unique_ptr<MyClass, void(*)(MyClass*)> customPtr(new MyClass(40),
                                                          [](MyClass* obj) { delete obj; });

    // 9. Custom deleter with a function pointer (equivalent to the lambda above)


    std::unique_ptr<MyClass, void(*)(MyClass*)> customPtr2(new MyClass(50), customDeleter);

    // 10. Using a custom deleter for array deletion
    std::unique_ptr<MyClass[], void(*)(MyClass*)> arrayPtr(new MyClass[3]{
                                                                   MyClass(60), MyClass(61), MyClass(62)
                                                           },
                                                           [](MyClass* arr) { delete[] arr; }
    );

    // 11. Using a lambda function to customize array deletion
    auto arrayDeleter = [](MyClass* arr) {
        std::cout << "Custom array deleter called." << std::endl;
        delete[] arr;
    };
    std::unique_ptr<MyClass[], decltype(arrayDeleter)> arrayPtr2(new MyClass[2]{ MyClass(70), MyClass(71) },
                                                                 arrayDeleter);




    // The unique_ptr objects will automatically be deleted when they go out of scope.

    return 0;
}

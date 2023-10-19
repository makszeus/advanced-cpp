#include <iostream>

class Resource {
private:
    int* data;

public:
    // Default constructor
    Resource() : data(nullptr) {
        std::cout << "Default constructor called." << std::endl;
    }

    // Destructor
    ~Resource() {
        delete data;
        std::cout << "Destructor called." << std::endl;
    }

    // Copy constructor
    Resource(const Resource& other) : data(new int(*other.data)) {
        std::cout << "Copy constructor called." << std::endl;
    }

    // Copy assignment operator
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        std::cout << "Copy assignment operator called." << std::endl;
        return *this;
    }

    // Move constructor
    Resource(Resource&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Move constructor called." << std::endl;
    }

    // Move assignment operator
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        std::cout << "Move assignment operator called." << std::endl;
        return *this;
    }
};

int main() {
    Resource res1; // Default constructor called

    const Resource& res2 = res1; // Copy constructor called

    Resource res3;
    res3 = res2; // Copy assignment operator called

    Resource res4 = std::move(res3); // Move constructor called

    Resource res5;
    res5 = std::move(res4); // Move assignment operator called

    return 0;
}

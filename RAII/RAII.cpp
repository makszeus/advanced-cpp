#include <iostream>
#include <mutex>

class File {
public:
    explicit File(const char* filename) : file_(fopen(filename, "r")) {
        if (!file_) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~File() {
        if (file_) {
            fclose(file_);
        }
    }

    // Add more member functions for reading/writing data from the file

private:
    FILE* file_;
};

class MutexLock {
public:
    explicit MutexLock(std::mutex& mutex) : mutex_(mutex) {
        mutex_.lock();
    }

    ~MutexLock() {
        mutex_.unlock();
    }

private:
    std::mutex& mutex_;
};

int main() {
    try {
        File file("example.txt"); // Resource (file) acquired here

        std::mutex mtx;
        {
            MutexLock lock(mtx); // Resource (mutex) acquired here

            // Perform some operations with the file and mutex
            // ...

        } // Resource (mutex) released here

        // Perform more operations with the file
        // ...

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : data(value) {
        std::cout << "MyClass Constructor" << std::endl;
    }

    void Print() {
        std::cout << "Data: " << data << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass Destructor" << std::endl;
    }

private:
    int data;
};

int main() {
    // Creating a unique pointer
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(42);

    // Accessing the object through the unique pointer
    uniquePtr->Print();

    // Attempting to create another unique pointer, which is not allowed
    // std::unique_ptr<MyClass> anotherUniquePtr = uniquePtr; // This will not compile

    // Unique pointers can be moved to transfer ownership
    std::unique_ptr<MyClass> anotherUniquePtr = std::move(uniquePtr);
    if (!uniquePtr) {
        std::cout << "uniquePtr is now empty" << std::endl;
    }

    // The object is automatically destroyed when the unique pointer goes out of scope
    return 0;
}

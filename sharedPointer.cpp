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
    // Creating a shared pointer
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(42);

    // Accessing the object through the shared pointer
    sharedPtr->Print();

    // Creating another shared pointer that shares ownership
    std::shared_ptr<MyClass> anotherPtr = sharedPtr;

    // Both shared pointers are sharing ownership of the same object
    sharedPtr->Print();
    anotherPtr->Print();

    // The object is automatically destroyed when the last shared pointer goes out of scope
    return 0;
}

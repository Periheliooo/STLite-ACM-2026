// A standalone language demonstration, not the submitted vector implementation.
#include <iostream>
#include <new>

struct Student {
    int id;
    explicit Student(int x) : id(x) {
        std::cout << "Construct Student(" << id << ")\n";
    }
    ~Student() {
        std::cout << "Destroy Student(" << id << ")\n";
    }
};

int main() {
    // Correct size and alignment; no Student has been constructed yet.
    alignas(Student) unsigned char storage[sizeof(Student)];
    std::cout << "Storage ready; no Student exists yet\n";
    Student *p = new (storage) Student(42);
    std::cout << "Read id: " << p->id << '\n';
    p->~Student();
    std::cout << "Student destroyed; storage still exists\n";
    // storage is a local array; its storage ends automatically at scope exit.
}

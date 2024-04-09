#include <iostream>
#include <string>

class AgeException {
private:
    std::string message;

public:
    AgeException(std::string _message) : message{ _message } {}
    virtual std::string getMessage() const { // виртуальная функция
        return message;
    }
};

class MaxAgeException : public AgeException {
public:
    MaxAgeException(std::string _message, int _maxAge) : AgeException{ _message }, maxAge{ _maxAge } {}
    std::string getMessage() const override { // переопределяем виртуальную функцию
        return AgeException::getMessage() + " Max age should be " + std::to_string(maxAge);
    }
private:
    int maxAge;
};

class Person {
public:
    Person(std::string name, int age) {
        if (age <= 0) { // если возраст равен 0
            throw AgeException{ "Invalid age" };
        }
        if (age > 110) { // если возраст больше 110
            throw MaxAgeException{ "Invalid age.", 110 };
        }
        this->name = name;
        this->age = age;
    }
    void print() const {
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
private:
    std::string name;
    int age;
};

int main() {
    try {
        Person bob{ "Bob", 152 };
        bob.print();

        Person tom{ "Tom", -15 };
        tom.print();
    }
    catch (const AgeException& ex) {
        std::cout << ex.getMessage() << std::endl;
    }
}

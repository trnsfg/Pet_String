#include <iostream>
#include <string>

class Pet {
protected:
    std::string name;
    int age;

public:
    Pet(const std::string& name, int age) : name(name), age(age) {}

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << " years\n";
    }

    virtual ~Pet() {}
};

class Dog : public Pet {
private:
    std::string breed;

public:
    Dog(const std::string& name, int age, const std::string& breed)
        : Pet(name, age), breed(breed) {}

    void displayInfo() const override {
        std::cout << "Dog-";
        Pet::displayInfo();
        std::cout << "Breed: " << breed << "\n";
    }
};

class Cat : public Pet {
private:
    std::string color;

public:
    Cat(const std::string& name, int age, const std::string& color)
        : Pet(name, age), color(color) {}

    void displayInfo() const override {
        std::cout << "Cat-";
        Pet::displayInfo();
        std::cout << "Color: " << color << "\n";
    }
};

class Parrot : public Pet {
private:
    std::string pattern;

public:
    Parrot(const std::string& name, int age, const std::string& pattern)
        : Pet(name, age), pattern(pattern) {}

    void displayInfo() const override {
        std::cout << "Parrot-";
        Pet::displayInfo();
        std::cout << "Pattern: " << pattern << "\n";
    }
};

int main() {
    Dog dog("Rex", 4, "Husky");
    Cat cat("Pushok", 5, "White");
    Parrot parrot("Polly", 1, "Green and Yellow");

    dog.displayInfo();
    cat.displayInfo();
    parrot.displayInfo();

    return 0;
}

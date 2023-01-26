//
//  main.cpp
//  Week 1 Command Line
//
//  Created by Jacob Penn on 1/23/23.
//

// These are include statements, they pull in existing code for us to use
#include <iostream>
#include <string>
#include <vector>

// this is the delcaration of a namespace, this is so we don't need to type: std::vector
// we can simply type vector
using namespace std;

// Your goals for week 1:

// Step 1 - Understanding Types
// Step 2 - Understanding how to make types, AKA classes
// Step 3 - Understanding Inheritance
// Step 4 - Understanding Memory (Pointers)


// this is an example of a class that can make a sound
class Animal {
public:
    void makeSound() {
        cout << "Make Sound" << endl;
    }
};

// this is an example of a virtual base class which can be inherited from
class AnimalBase {
public:
    virtual void makeSound() = 0;
};

// this is a derived class which can be used during runtime (while the application is running)
class Cat : public AnimalBase {
public:
    void makeSound() override {
        cout << cat_sound << endl;
    }
    
    void setSound(string in_sound) {
        cat_sound = in_sound;
    }
    
    string cat_sound = "Meow";
};

class Dog : public AnimalBase {
public:
    void makeSound() override {
        cout << "Bark" << endl;
    }
};

int main(int argc, const char * argv[]) {
    //
    // STEP 1 TYPES
    //
    
    // <- this is a comment block
    
    // this is variable
    // int mean integer, meaning a whole number
    int x = 5;
    
    // single precision floating point number
    float y = 0.5f;
    
    // double (more decimal precision)
    double y_d = 0.5;
    
    // standard library string class
    string name = "Name";
    
    //
    // STEP 2 CLASSES
    //
    Animal animal;
    animal.makeSound();
    
    //
    // STEP 3 INHERITANCE
    //
    Cat cat;
    Dog dog;
    
    vector<AnimalBase*> all_animals;
    all_animals.push_back(&cat);
    all_animals.push_back(&dog);
    
    for (auto* animal : all_animals) {
        animal->makeSound();
    }
    
    // how a DAW might use a base class.
    
//    for (auto* plugin : channel_plugins) {
//        plugin->processAudio(float* in_audio);
//    }
    
    //
    // STEP 4 MEMORY
    //

    // 4 cats
    Cat cat1;
    Cat cat2;
    Cat cat3;
    Cat cat4;

    // a container to the hold pointers to the cats above
    vector<Cat*> all_cats;
    
    // the address of a cat in memory
    cout << std::addressof(cat1) << endl;
    
    // put pointers to the cats into the vector (array) by obtaining their address via the & operator
    all_cats.push_back(&cat1);
    all_cats.push_back(&cat2);
    all_cats.push_back(&cat3);
    all_cats.push_back(&cat4);
    
    // loop through the pointers to the cats
    for (auto* cat : all_cats) {
        cat->makeSound();

        // we can change the cat's sound
        cat->setSound("purrrr");
    }
    
    // proof they changed
    for (auto* cat : all_cats) {
        cat->makeSound();
    }
    
    // proof that the cat in the vector, as the same cat 1
    cat1.makeSound();

    return 0;
}

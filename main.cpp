#include <iostream>
#include <random>
#include <assert.h>
#include <string.h>

#include "list.h"

using namespace std;

#define MIN 100
#define MAX 500

#define PUSH_FRONT 0
#define PUSH_BACK 1

#define POP_FRONT 2
#define POP_BACK 3

int generateRandomInt(int min, int max);
void insertIntoList(List<int> &numbers);
void removeFromList(List<int> &numbers);

mt19937 rng;

int main(int argc, char *argv[]) {
    rng.seed(random_device()());
    cout << "===========================================================" << endl;
    cout << "\tDouble Linked Circular List Practice" << endl;
    cout << "===========================================================" << endl << endl;

    List<int> test;

    const int numberOfElements = generateRandomInt(MIN, MAX);
    for (int i = 0; i < numberOfElements; i++) {
        insertIntoList(test);
    }

    assert(test.size() == numberOfElements && "Something is wrong with the push methods");

    const int elementsToRemove = generateRandomInt(0, MIN - 1);
    for (int i = 0; i < elementsToRemove; i++) {
        removeFromList(test);
    }

    const int newNumbersSize = numberOfElements - elementsToRemove;
    assert(test.size() == newNumbersSize && "Something is wrong with the pop functions");

    test.clear();
    assert(test.empty() && "Something is wrong with the clear or empty methods");
    assert(test.size() == 0 && "Something is wrong with the clear method");
    
    for (int i = 0; i < numberOfElements; i++) {
        insertIntoList(test);
    }

    Iterator<int> ite = test.begin();
    assert(test.front() == *ite && "Something is wrong with the front method or the iterator");

    const int position = generateRandomInt(0, numberOfElements - 1);
    for (int i = 0; i < position; i++) {
        ++ite;
    }
    assert(test.get(position) == *ite && "Something is wrong with the get method or the iterator");

    ite = test.begin();
    for (int i = 0; i < numberOfElements - 1; i++) {
        ++ite;
    }
    assert(test.back() == *ite && "Something is wrong with the back method or the iterator");

    --ite;
    assert(test.get(numberOfElements - 2) == *ite && "Something is wrong with the iterator (-- operator)");

    for (ite = test.begin(); ite != test.end(); ++ite) {
        cout << *ite << " ";
    }
    cout << endl;

    system("read");
    return EXIT_SUCCESS;
}

int generateRandomInt(int min, int max) {
    uniform_int_distribution<mt19937::result_type> distribution(min, max);
    return distribution(rng);
}

void insertIntoList(List<int> &numbers) {
    const int numberToInsert = generateRandomInt(0, 100);
    const int action = generateRandomInt(0, 1);
    switch (action) {
        case PUSH_FRONT: numbers.push_front(numberToInsert); break;
        case PUSH_BACK: numbers.push_back(numberToInsert); break;
    }
}

void removeFromList(List<int> &numbers) {
    const int action = generateRandomInt(2, 3);
    switch (action) {
        case POP_FRONT: numbers.pop_front(); break;
        case POP_BACK: numbers.pop_back(); break;
    }
}
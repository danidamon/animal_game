#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Animal {
    string question;
    string yes_guess, no_guess;
    Animal *no, *yes;
};

bool MakeGuess(string guess) {
    char c;
    cout << "Is it a " << guess << "?" << endl;
    cin >> c;
    cin.ignore();

    if (c == 'y'){
        cout << "I win!" << endl;
        return true;
    } else {
        cout << "You win!" << endl;
        return false;
    }
}

// Add a new node to the tree on specified side
void NewNode(Animal *node, char side) {
    string animal; // for the inputted correct answer
    char c; 
    Animal *new_animal;
    new_animal = new Animal; // make sure new_animal persists ouside NewNode

    new_animal->yes = NULL;
    new_animal->no = NULL;
    
    if (side == 'y') {
        node->yes = new_animal;
    }
    else {
        node->no = new_animal;
    }

    new_animal->no_guess = node->no_guess;
    new_animal->yes_guess = node->yes_guess;
    
    cout << "What's the right answer?" << endl;
    getline(cin, animal);

    cout << "What's a question to identify your animal?" << endl;
    getline(cin, new_animal->question);

    cout << "Is the answer 'y' or 'n'?" << endl;
    cin >> c;
    cin.ignore();

    if (c == 'y') {
        new_animal->yes_guess = animal;
    }
    else {
        new_animal->no_guess = animal;
    }
    return;
}

void DestroyTree(Animal *root) {
    if (root==NULL) return;
    DestroyTree(root->no);
    DestroyTree(root->yes);
    delete root;
}

int main() {
    Animal *root=NULL, *current=NULL;
    char c;
    bool play = true, guessed = false;
    root = new Animal;
    root->no = NULL; root->yes=NULL;
    root->question = "Can it fly?";
    root->yes_guess = "eagle";
    root->no_guess = "bear";

    cout << " --------------------" << endl;
    cout << " ANIMAL GUESSING GAME" << endl;
    cout << "  Use y/n to respond " << endl;
    cout << " --------------------" << endl;

    current = root;
    while (play) {
        // Travel down tree until we get to a guess
        guessed = false;
        while (guessed == false) {
            cout << current->question << endl;
            cin >> c;
            cin.ignore();

            if (c == 'y') {
                if (current->yes == NULL) { // at a leaf node
                    if (MakeGuess(current->yes_guess) == false) {
                        // add the correct answer to the tree
                        NewNode(current, 'y');
                    }
                    guessed = true;
                }
                else current = current->yes;
            }
            else {
                if (current->no == NULL) { // at a leaf node
                    if (MakeGuess(current->no_guess) == false) {
                        // add the correct answer to the tree
                        NewNode(current, 'n');
                    }
                    guessed = true;
                }
                else current = current->no;
            }
        }

        cout << "Play again? Press y/n, or press r to reset." << endl;
        cin >> c;
        cin.ignore();
        if (c == 'n') play = false;
        if (c == 'r') { // destroy the tree and reset root
            DestroyTree(root);
            Animal *root = NULL;
            root = new Animal;
            root->no = NULL; root->yes=NULL;
            root->question = "Can it fly?";
            root->yes_guess = "eagle";
            root->no_guess = "bear";
        }
        current = root; // reset current to root node
    }

    DestroyTree(root); // destroy the tree
    return 0;
}
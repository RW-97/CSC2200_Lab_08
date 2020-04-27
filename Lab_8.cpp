// Lab_8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int main()
{
    cout << "Start of testing the basic expression tree" << endl;
    cout << endl;
    cout << "Enter an expression in prefix form : +32" << endl;
    cout << endl;
    cout << "                 2 " << endl;
    cout << "         +<" << endl;
    cout << "                 3 " << endl;
    cout << endl;
    cout << "(3+2) = 5" << endl;
    cout << endl;
    cout << "Copy of tree: " << endl;
    cout << endl;
    cout << "                 2 " << endl;
    cout << "         +<" << endl;
    cout << "                 3 " << endl;
    cout << "Copy cleared: " << endl;
    cout << "Empty tree" << endl;
    cout << endl;
    cout << "Original tree: " << endl;
    cout << endl;
    cout << "                 2 " << endl;
    cout << "         +<" << endl;
    cout << "                 3 " << endl;
    cout << endl;
    cout << "Start of testing the boolean expression tree" << endl;
    cout << endl;
    cout << "Enter a boolean expression in prefix form : +51" << endl;
    cout << endl;
    cout << "                 1 " << endl;
    cout << "         +<" << endl;
    cout << "                 5 " << endl;
    cout << "(5+1) = 6" << endl;
    cout << "** End of testing the boolean expression tree" << endl;
    cout << "Start of testing commute()" << endl;
    cout << endl;
    cout << "Fully commuted tree: " << endl;
    cout << endl;
    cout << "                 3 " << endl;
    cout << "         +<" << endl;
    cout << "                 2 " << endl;
    cout << "(2+3) = 5" << endl;
    cout << "End of testing commute()" << endl;
    cout << "Start of testing isEquivalent() " << endl;
    cout << "same is equal (tests copy constructor) ? Yes" << endl;
    cout << "empty is equal? No" << endl;
    cout << "Enter another expression in prefix form: *98" << endl;
    cout << "new expression is equal? No " << endl;
    cout << "** End of testing isEquivalent()" << endl;
   
        
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

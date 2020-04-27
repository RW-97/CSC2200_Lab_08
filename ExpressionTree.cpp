
//--------------------------------------------------------------------
//
//  Laboratory 8                                  exprtree.cpp
//
//  ** SOLUTION: Linked implementation of the Expression Tree ADT **
//
//--------------------------------------------------------------------

#ifndef EXPRESSIONTREE_CPP
#define EXPRESSIONTREE_CPP

#include <stdexcept>
#include <iostream>
#include <cctype>

#include "ExpressionTree.h"

//--------------------------------------------------------------------

template <typename DataType>
ExprTree<DataType>::ExprTreeNode:: ExprTreeNode ( char nodeDataItem,
                              ExprTreeNode *leftPtr,
                              ExprTreeNode *rightPtr )

// Creates an expreesion tree node containing data item nodeDataItem,
// left child pointer leftPtr, and right child pointer rightPtr.
            //Nothing needed here

  : dataItem(nodeDataItem),
    left(leftPtr),
    right(rightPtr)

{}

//--------------------------------------------------------------------

template <typename DataType>
ExprTree<DataType>:: ExprTree ()

// Creates an empty expression tree.

  : root(0) // root set to 0

{}

//--------------------------------------------------------------------

template <typename DataType>
ExprTree<DataType>:: ~ExprTree ()

// Frees the memory used by an expression tree.

{
    clear();
}

//--------------------------------------------------------------------

template <typename DataType>
void ExprTree<DataType>::build() 

// Builds a new expression tree from standard input (cin)

{
    clear();
    buildHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& p)  // creating a float tree

// Specialized function to help build trees of floats.
// Input is single digit ints or operators.

{
    char ch;   // Input operator or number

    cin >> ch;
    p = new ExprTreeNode(ch,0,0);   // Link in node

    if ( !isdigit(ch) )             // Operator -- construct subtrees
    {
       buildHelper(p->left);
       buildHelper(p->right);
    }
}

template <>
void ExprTree<bool>::buildHelper(ExprTreeNode*& p) 

// Specialized function to help build boolean trees.
// Input is 0, 1, or operators.

{
    char ch;   // Input operator or number

    cin >> ch;
    p = new ExprTreeNode(ch,0,0);   // Link in node

    if ( !isdigit(ch) )             // Operator -- construct subtrees
    {
        if (ch != '-') {    //Special case - naught case
           buildHelper(p->left);
	}
        buildHelper(p->right);
    }
}

//--------------------------------------------------------------------

template <typename DataType>
void ExprTree<DataType>::expression() const 
            //Prints out entire expression
// Public function to print out fully parenthesized expression tree.

{
    exprHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>::exprHelper(ExprTreeNode* p) const 

// Private helper function to print out fully parenthesized expression tree.
//What kind of order do these 3 statements give us (132-134)
    // IN order, as opposed to out - of - order
{
    if ( p != 0 ) {
       if ( !isdigit(p->dataItem) ) cout << '(';
       exprHelper(p->left);
       cout << p->dataItem;
       exprHelper(p->right);
       if ( !isdigit(p->dataItem) ) cout << ')';
    }
}

//--------------------------------------------------------------------

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error) 

// Public function to evaluate an expression tree.

{
    if (!root) {
        throw logic_error("tree is empty");
    }

    return evalHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <>
float ExprTree<float>::evalHelper(ExprTreeNode* p) const  // float

// Private helper function to evaluate an expression tree with a float
// result.

{
    float l, r,     // Intermediate results
          result;   // Result returned

    if ( isdigit(p->dataItem) )
       result = p->dataItem - '0';      // Convert from char to number
    else
    {
       l = evalHelper(p->left);       // Evaluate subtrees
       r = evalHelper(p->right);
       switch ( p->dataItem )           // Combine results
       {
         case '+' :  result = l + r;  break;
         case '-' :  result = l - r;  break;
         case '*' :  result = l * r;  break;
         case '/' :  result = l / r;
       }
    }
    return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <>
bool ExprTree<bool>::evalHelper(ExprTreeNode* p) const 

// Private helper function to evaluate an boolean expression tree with a 
// bool result.

{
    if (isdigit(p->dataItem)) {
        return p->dataItem == '1';
    } else {
        bool l = true;
	if (p->dataItem != '-') {
	    l = evalHelper(p->left);
	}
	bool r = evalHelper(p->right);
	
	switch (p->dataItem) {
	  case '+': return l || r;
	  case '*': return l && r;
	  case '-': return !r;
	}
    }
}

//--------------------------------------------------------------------

template <typename DataType>
void ExprTree<DataType>:: clear ()

// Removes all the nodes from an expression tree.

{
    clearHelper(root);
    root = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>:: clearHelper ( ExprTreeNode *p )

// Recursive helper for the clear() function. Clears the subtree
// pointed to by p.
            //Deletes all the children of the tree 
{
    if ( p != 0 )
    {
       clearHelper(p->left);
       clearHelper(p->right);
       delete p;
    }
}

//--------------------------------------------------------------------

template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    // No isEmpty function in this class. Add a private one if you wish.
    if ( root == 0 )		
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}

//--------------------------------------------------------------------

template <typename DataType>
ExprTree<DataType>:: ExprTree ( const ExprTree &source )

// Copy constructor. Creates a copy of valueTree.

{
   root = source.root;
   copyHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source) 

// Overloads the assignment operator for any data type.

{
    if (this != &source)
    {
        clear();
        root = source.root;
        copyHelper(root);
    }
    return source;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>:: copyHelper ( ExprTreeNode *&p )

// Recursive private helper for the copy constructor and overloaded
// assignment operator. Creates a copy of the subtree pointed to by p, 
// p points to the new subtree.

{
    if (p != NULL)
    {
        p = new ExprTreeNode(p->dataitem, p->left, p->right)
          
        this->root = p;
        copyHelper(p->right);
        copyHelper(p->left);
    }
}

//--------------------------------------------------------------------

template <typename DataType>
void ExprTree<DataType>::commute() 
//
// Public operator to commute the tree.

{
    commuteHelper(root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* p) 

// Private recursive helper function to commute the tree.

{
    if (isdigit(p->dataItem))
    {
        return;
    }
    else
    {
        ExprTreeNode* tempNode = p->left;
        p->left = p->right;
        p->right = tempNode; 

        commuteHelper(p->right);
        commuteHelper(p->left);

    }
}

//--------------------------------------------------------------------

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree<DataType>& source) const 
//checking if each node is the same or not
// Public operator to determine whether two expression trees are equivalent.

{
    return isEquivalentHelper(root, source.root);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x,
    const ExprTreeNode* y) const

    // Private recursive assistant function to determine whether two expression 
    // trees are equivalent.
    
{
    bool equivelanceCheck = false;
    bool temp = false;
    
    if (x->dataItem == y->dataItem)
    {
        if (isdigit(x->dataItem) || isdigit(y->dataItem))
        {
            equivelanceCheck = (x->dataItem == y->dataItem);
        }
        else
        {
            if (isEquivalentHelper(x->left, y->left) && isEquivalentHelper(x->right, y->left))
            {
                equivelanceCheck = true;
            }
          
            else if (isEquivalentHelper(x->left, y->left) && isEquivalentHelper(x->right, y->left))
            {
                    equivelanceCheck = true;
            }
            else
            {
                equivelanceCheck = false;
            }
            equivelanceCheck = temp;
        }
    }
    return temp;
}

#endif		// #ifndef EXPRESSIONTREE_CPP

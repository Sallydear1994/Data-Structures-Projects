// AVLSet.hpp
//
// ICS 46 Spring 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"

template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    ~AVLSet() noexcept override;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const noexcept;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    struct Node
    {
        ElementType value;
        Node* left;
        Node* right;
        int height;
    };
    AVLSet* backup;
    Node* root;
    bool avlTree;
    bool duplicate;
    int treePathHeight;
    unsigned int treeSize;
    void deleteNodes(Node* node);
    void checkTree(Node*& node, const ElementType& element);
    void checkBalance(Node*& node, const ElementType& element);
    void preorderTraverse(VisitFunction visit, Node* node) const;
    void inorderTraverse(VisitFunction visit, Node* node) const;
    void postorderTraverse(VisitFunction visit, Node* node) const;
    void RRRotation(Node*& node);
    void RLRotation(Node*& node);
    void LLRotation(Node*& node);
    void LRRotation(Node*& node);
    void copyTree(Node* node);
    int getSubtreeHeight(Node* node) const;
};


template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    root = nullptr;
    avlTree = shouldBalance;
    treePathHeight = -1;
    treeSize = 0;
    duplicate = false;
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    deleteNodes(root);
}


template <typename ElementType>
void AVLSet<ElementType>::deleteNodes(Node* node)
{
    if (node != nullptr)
    {
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    }
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    root = nullptr;
    avlTree = s.avlTree;
    treePathHeight = -1;
    treeSize = 0;   
    duplicate = false;
    try
    {
        copyTree(s.root);
        avlTree = s.avlTree;
        duplicate = s.duplicate;
        treeSize = s.treeSize;
    }
    catch(...)
    {
        deleteNodes(root);
        root = nullptr;
        avlTree = s.avlTree;
        treePathHeight = -1;
        treeSize = 0;
        duplicate = false;
    }
}


template <typename ElementType>
void AVLSet<ElementType>::copyTree(Node* node)
{
    if (node != nullptr)
    {
        add(node->value);
        copyTree(node->left);
        copyTree(node->right);
    }
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    root = nullptr;
    avlTree = s.avlTree;
    treePathHeight = -1;
    treeSize = 0;   
    duplicate = false;
    try
    {
        std::swap(root, s.root);
        std::swap(avlTree, s.avlTree);
        std::swap(duplicate, s.duplicate);
        std::swap(treeSize, s.treeSize);
    }
    catch(...)
    {
        deleteNodes(root);
        root = nullptr;
        avlTree = s.avlTree;
        treePathHeight = -1;
        treeSize = 0;   
        duplicate = false;
    }
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    backup = new AVLSet(*this);
    try
    {
        copyTree(s.root);
        avlTree = s.avlTree;
        treeSize = s.treeSize;
        duplicate = s.duplicate;
        delete backup;
    }
    catch(...)
    {
        deleteNodes(root);
        return *backup;
    }
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    std::swap(root, s.root);
    std::swap(avlTree, s.avlTree);
    std::swap(duplicate, s.duplicate);
    std::swap(treeSize, s.treeSize);
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    //return false;
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
    treePathHeight = 0;
    treeSize += 1;
    if (root == nullptr)
    {
        root = new Node;
        root->value = element;
        root->left = nullptr;
        root->right = nullptr;
        root->height = 0;
    }
    else
    {
        if (!contains(element))
        {
            checkTree(root, element);
        }
        duplicate = false;
    }
}


template <typename ElementType>
void AVLSet<ElementType>::checkTree(Node*& node, const ElementType& element)
{
    if (node == nullptr)
    {
        node = new Node;
        node->value = element;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 0;
    }
    else if (element < node->value)
    {
        checkTree(node->left, element);
        treePathHeight += 1;
    }
    else if (element > node->value)
    {
        checkTree(node->right, element);
        treePathHeight += 1;
    }
    else // value is a duplicate
    {
        duplicate = true;
        treeSize -= 1;
        node->value = element;   
    }
    if (!duplicate)
    {
        if (treePathHeight > node->height)
        {
            node->height += 1;
        }
        if (avlTree)
        {
            checkBalance(node, element);
        }
    }
}


template <typename ElementType>
void AVLSet<ElementType>::checkBalance(Node*& node, const ElementType& element)
{
    if (getSubtreeHeight(node->left) - getSubtreeHeight(node->right) <= -2)
    {
        if (element > node->right->value)
        {
            treePathHeight -= 1;
            RRRotation(node);
        }
        else if (element < node->right->value)
        {
            treePathHeight -= 1;
            RLRotation(node);
        }
    }
    else if (getSubtreeHeight(node->right) - getSubtreeHeight(node->left) <= -2)
    {
        if (element < node->left->value)
        {
            treePathHeight -= 1;
            LLRotation(node);
        }
        else if (element > node->left->value)
        {
            treePathHeight -= 1;
            LRRotation(node);
        }
    }
}


template <typename ElementType>
void AVLSet<ElementType>::RRRotation(Node*& node)
{
    Node* A = node;
    Node* B = A->right;
    Node* T1 = A->left;
    Node* T2 = B->left;
    Node* T3 = B->right;
    
    node = B;
    node->left = A;
    node->right = T3;
    node->height = A->height - 1;

    A->left = T1;
    A->right = T2;
    A->height = node->height - 1;
}


template <typename ElementType>
void AVLSet<ElementType>::RLRotation(Node*& node)
{
    Node* A = node;
    Node* C = node->right;
    Node* B = C->left;
    Node* T1 = node->left;
    Node* T2 = B->left;
    Node* T3 = B->right;
    Node* T4 = C->right;
    
    node = B;
    node->left = A;
    node->right = C;
    node->height = B->height + 1;

    A->left = T1;
    A->right = T2;
    A->height = C->height - 1;

    C->left = T3;
    C->right = T4;
    C->height = C->height - 1;
}


template <typename ElementType>
void AVLSet<ElementType>::LLRotation(Node*& node)
{
    Node* B = node;
    Node* A = node->left;
    Node* T1 = A->left;
    Node* T2 = A->right;
    Node* T3 = node->right;

    node = A;
    node->left = T1;
    node->right = B;
    node->height = B->height - 1;

    B->left = T2;
    B->right = T3;
    B->height = A->height - 1;
}


template <typename ElementType>
void AVLSet<ElementType>::LRRotation(Node*& node)
{
    Node* C = node;
    Node* A = C->left;
    Node* B = A->right;
    Node* T1 = A->left;
    Node* T2 = B->left;
    Node* T3 = B->right;
    Node* T4 = C->right;
    
    node = B;
    node->left = A;
    node->right = C;
    node->height = B->height + 1;

    C->left = T3;
    C->right = T4;
    C->height = A->height - 1;
    
    A->left = T1;
    A->right = T2;
    A->height = A->height - 1;
}


template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    Node* currentNode = root;
    while (currentNode != nullptr)
    {
        if (element == currentNode->value)
        {
            return true;
        }
        else if (element < currentNode->value)
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
    }
    return false;
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return treeSize;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const noexcept
{
    return getSubtreeHeight(root);
}


template <typename ElementType>
int AVLSet<ElementType>::getSubtreeHeight(Node* node) const
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->height;
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    preorderTraverse(visit, root);
}


template <typename ElementType>
void AVLSet<ElementType>::preorderTraverse(VisitFunction visit, Node* node) const
{
    if (node != nullptr)
    {
        visit(node->value);
        preorderTraverse(visit, node->left);
        preorderTraverse(visit, node->right);
    }
}


template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    inorderTraverse(visit, root);
}


template <typename ElementType>
void AVLSet<ElementType>::inorderTraverse(VisitFunction visit, Node* node) const
{
    if (node != nullptr)
    {
        inorderTraverse(visit, node->left);
        visit(node->value);
        inorderTraverse(visit, node->right);
    }
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    postorderTraverse(visit, root);
}


template <typename ElementType>
void AVLSet<ElementType>::postorderTraverse(VisitFunction visit, Node* node) const
{
    if (node != nullptr)
    {
        postorderTraverse(visit, node->left);
        postorderTraverse(visit, node->right);
        visit(node->value);
    }
}


#endif


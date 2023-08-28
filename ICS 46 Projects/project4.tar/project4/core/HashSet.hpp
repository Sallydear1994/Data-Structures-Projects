// HashSet.hpp
//
// ICS 46 Spring 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    ~HashSet() noexcept override;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8, in which case
    // the new capacity should be determined by this formula:
    //
    //     capacity * 2 + 1
    //
    // In the case where the array is resized, this function runs in linear
    // time (with respect to the number of elements, assuming a good hash
    // function); otherwise, it runs in constant time (again, assuming a good
    // hash function).  The amortized running time is also constant.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns false.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;

    // User defined
    struct Node
    {
        ElementType value;
        Node* next = nullptr;
        Node* head = nullptr;
        unsigned int listSize = 0;
    };
    unsigned int numberOfElements;
    unsigned int tableSize;
    Node* hashTable;
    HashSet* backup;
    void deleteElements(Node* node);
    void copyTable(const HashSet& s); // For copy constructor and operator
    void resizeHashTable();
};



namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    numberOfElements = 0;
    tableSize = DEFAULT_CAPACITY;
    hashTable = new Node[tableSize];
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    for (int i = 0; i < tableSize; i++)
    {
        if (hashTable[i].head != nullptr)
        {
            deleteElements(hashTable[i].head);
        }
    }
    delete [] hashTable;
}


template <typename ElementType>
void HashSet<ElementType>::deleteElements(Node* node)
{
    if (node != nullptr)
    {
        deleteElements(node->next);
        delete node;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    try
    {
        copyTable(s);
    }
    catch(...)
    {
        for (int i = 0; i < tableSize; i++)
        {
            if (hashTable[i].head != nullptr)
            {
                deleteElements(hashTable[i].head);
            }
        }
        delete [] hashTable;
        numberOfElements = 0;
        tableSize = DEFAULT_CAPACITY;
        hashTable = new Node[tableSize];
    }
}


template <typename ElementType>
void HashSet<ElementType>::copyTable(const HashSet& s)
{
    numberOfElements = s.numberOfElements;
    tableSize = s.tableSize;
    hashTable = new Node[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        Node* bucket = s.hashTable[i].head;
        while (bucket != nullptr)
        {
            Node* newNode = new Node;
            newNode->value = bucket->value;
            newNode->next = nullptr;
            if (hashTable[i].head == nullptr)
            {
                hashTable[i].head = newNode;
                hashTable[i].head->next = nullptr;
                hashTable[i].listSize += 1;
            }
            else
            {
                Node* nextNode = hashTable[i].head;
                hashTable[i].head = newNode;
                hashTable[i].head->next = nextNode;
                hashTable[i].listSize += 1;
            }
            bucket = bucket->next;
        }
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    numberOfElements = 0;
    tableSize = DEFAULT_CAPACITY;
    hashTable = new Node[tableSize];
    std::swap(numberOfElements, s.numberOfElements);
    std::swap(tableSize, s.tableSize);
    std::swap(hashTable, s.hashTable);
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    backup = new HashSet(*this);
    try
    {
        for (int i = 0; i < tableSize; i++)
        {
            if (hashTable[i].head != nullptr)
            {
                deleteElements(hashTable[i].head);
            }
        }
        delete [] hashTable;
        copyTable(s);
        delete backup;
    }
    catch(...)
    {
        for (int i = 0; i < tableSize; i++)
        {
            if (hashTable[i].head != nullptr)
            {
                deleteElements(hashTable[i].head);
            }
        }
        delete [] hashTable;
        numberOfElements = 0;
        tableSize = DEFAULT_CAPACITY;
        hashTable = new Node[tableSize];
        return *backup;
    }
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    std::swap(numberOfElements, s.numberOfElements);
    std::swap(tableSize, s.tableSize);
    std::swap(hashTable, s.hashTable);
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    //return false;
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    numberOfElements += 1;
    Node* newNode = new Node;
    newNode->value = element;
    newNode->next = nullptr;
    unsigned int index = hashFunction(element) % tableSize;
    if (hashTable[index].head == nullptr)
    {
        hashTable[index].head = newNode;
        hashTable[index].head->next = nullptr;
        hashTable[index].listSize += 1;
    }
    else
    {
        // Check for duplicates
        if (!contains(element))
        {
            Node* nextNode = hashTable[index].head;
            hashTable[index].head = newNode;
            hashTable[index].head->next = nextNode;
            hashTable[index].listSize += 1;
        }
    }
    float ratio = float(numberOfElements) / float(tableSize);
    if (ratio >= 0.8)
    {
        resizeHashTable();
    }
}


template <typename ElementType>
void HashSet<ElementType>::resizeHashTable()
{
    unsigned int newTableSize = tableSize * 2 + 1;
    unsigned int oldTableSize = tableSize;
    tableSize = newTableSize;
    Node* newHashTable = new Node[newTableSize];
    for (int i = 0; i < oldTableSize; i++)
    {
        Node* bucket = hashTable[i].head;
        while (bucket != nullptr)
        {
            Node* newNode = new Node;
            newNode->value = bucket->value;
            newNode->next = nullptr;
            unsigned int index = hashFunction(bucket->value) % tableSize;
            if (newHashTable[index].head == nullptr)
            {
                newHashTable[index].head = newNode;
                newHashTable[index].head->next = nullptr;
                newHashTable[index].listSize += 1;
            }
            else
            {
                Node* nextNode = newHashTable[index].head;
                newHashTable[index].head = newNode;
                newHashTable[index].head->next = nextNode;
                newHashTable[index].listSize += 1;
            }
            bucket = bucket->next;
        }
    }
    for (int i = 0; i < oldTableSize; i++)
    {
        if (hashTable[i].head != nullptr)
        {
            deleteElements(hashTable[i].head);
        }
    }
    delete [] hashTable;
    hashTable = newHashTable;
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    unsigned int index = hashFunction(element) % tableSize;
    Node* bucket = hashTable[index].head;
    if (bucket != nullptr)
    {
        if (bucket->value == element)
        {
            return true;
        }
        else
        {
            bucket = bucket->next;
            while (bucket != nullptr)
            {
                if (bucket->value == element)
                {
                    return true;
                }
                bucket = bucket->next;
            }
        }   
    }
    return false;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return numberOfElements;
    //return 0;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    return hashTable[index].listSize;
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if (index < tableSize)
    {
        Node* bucket = hashTable[index].head;
        while (bucket != nullptr)
        {
            if (bucket->value == element)
            {
                return true;
            }
            bucket = bucket->next;
        }
    }
    return false;
}



#endif


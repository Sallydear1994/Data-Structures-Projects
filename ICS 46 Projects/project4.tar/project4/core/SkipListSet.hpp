// SkipListSet.hpp
//
// ICS 46 Spring 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// A SkipListSet is an implementation of a Set that is a skip list, implemented
// as we discussed in lecture.  A skip list is a sequence of levels
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the keys and their
// values.  Instead, you'll need to implement your own dynamically-allocated
// nodes, with pointers connecting them.  You can, however, use other parts of
// the C++ Standard Library -- including <random>, notably.
//
// Each node should contain only two pointers: one to the node that follows it
// on the same level and another to the equivalent node on the level below it.
// Additional pointers use more memory but don't enable any techniques not
// enabled by the other two.
//
// A couple of utilities are included here: SkipListKind and SkipListKey.
// You can feel free to use these as-is and probably will not need to
// modify them, though you can make changes to them, if you'd like.

#ifndef SKIPLISTSET_HPP
#define SKIPLISTSET_HPP

#include <memory>
#include <optional>
#include <random>
#include "Set.hpp"




// SkipListKind indicates a kind of key: a normal one, the special key
// -INF, or the special key +INF.  It's necessary for us to implement
// the notion of -INF and +INF separately, since we're building a class
// template and not all types of keys would have a reasonable notion of
// -INF and +INF.

enum class SkipListKind
{
    Normal,
    NegInf,
    PosInf
};




// A SkipListKey represents a single key in a skip list.  It is possible
// to compare these keys using < or == operators (which are overloaded here)
// and those comparisons respect the notion of whether each key is normal,
// -INF, or +INF.

template <typename ElementType>
class SkipListKey
{
public:
    static SkipListKey normal(const ElementType& element);
    static SkipListKey negInf();
    static SkipListKey posInf();

    bool operator==(const SkipListKey& other) const;
    bool operator==(const ElementType& other) const;

    bool operator<(const SkipListKey& other) const;
    bool operator<(const ElementType& other) const;

private:
    SkipListKey(SkipListKind kind, std::optional<ElementType> element);

private:
    SkipListKind kind;
    std::optional<ElementType> element;
};


template <typename ElementType>
SkipListKey<ElementType> SkipListKey<ElementType>::normal(const ElementType& element)
{
    return SkipListKey{SkipListKind::Normal, std::make_optional(element)};
}


template <typename ElementType>
SkipListKey<ElementType> SkipListKey<ElementType>::negInf()
{
    return SkipListKey{SkipListKind::NegInf, std::nullopt};
}


template <typename ElementType>
SkipListKey<ElementType> SkipListKey<ElementType>::posInf()
{
    return SkipListKey{SkipListKind::PosInf, std::nullopt};
}


template <typename ElementType>
SkipListKey<ElementType>::SkipListKey(SkipListKind kind, std::optional<ElementType> element)
    : kind{kind}, element{element}
{
}


template <typename ElementType>
bool SkipListKey<ElementType>::operator==(const SkipListKey& other) const
{
    return kind == other.kind
        && (kind != SkipListKind::Normal || *element == *other.element);
}


template <typename ElementType>
bool SkipListKey<ElementType>::operator==(const ElementType& other) const
{
    return kind == SkipListKind::Normal && *element == other;
}


template <typename ElementType>
bool SkipListKey<ElementType>::operator<(const SkipListKey& other) const
{
    switch (kind)
    {
    case SkipListKind::NegInf:
        return other.kind != SkipListKind::NegInf;

    case SkipListKind::PosInf:
        return false;

    default: // SkipListKind::Normal
        return other.kind == SkipListKind::PosInf
            || (other.kind == SkipListKind::Normal && *element < *other.element);
    }
}


template <typename ElementType>
bool SkipListKey<ElementType>::operator<(const ElementType& other) const
{
    return kind == SkipListKind::NegInf
        || (kind == SkipListKind::Normal && *element < other);
}



// The SkipListLevelTester class represents the ability to decide whether
// a key placed on one level of the skip list should also occupy the next
// level.  This is the "coin flip," so to speak.  Note that this is an
// abstract base class with one implementation, RandomSkipListLevelTester,
// just below it.  RandomSkipListLevelTester is what it sounds like: It
// makes the decision at random (with a 50/50 chance of deciding whether
// a key should occupy the next level).  However, by setting things up
// this way, we have a way to control things more carefully in our
// testing (as you can, as well).
//
// DO NOT MAKE CHANGES TO THE SIGNATURES OF THE MEMBER FUNCTIONS OF
// THE "level tester" CLASSES.  You can add new member functions or even
// whole new level tester classes, but the ones declared below are part
// of how we test your implementation, so they need to maintain the
// parts of the interface that are declared already.

template <typename ElementType>
class SkipListLevelTester
{
public:
    virtual ~SkipListLevelTester() = default;

    virtual bool shouldOccupyNextLevel(const ElementType& element) = 0;
    virtual std::unique_ptr<SkipListLevelTester<ElementType>> clone() = 0;
};


template <typename ElementType>
class RandomSkipListLevelTester : public SkipListLevelTester<ElementType>
{
public:
    RandomSkipListLevelTester();

    bool shouldOccupyNextLevel(const ElementType& element) override;
    std::unique_ptr<SkipListLevelTester<ElementType>> clone() override;

private:
    std::default_random_engine engine;
    std::bernoulli_distribution distribution;
};


template <typename ElementType>
RandomSkipListLevelTester<ElementType>::RandomSkipListLevelTester()
    : engine{std::random_device{}()}, distribution{0.5}
{
}


template <typename ElementType>
bool RandomSkipListLevelTester<ElementType>::shouldOccupyNextLevel(const ElementType& element)
{
    return distribution(engine);
}


template <typename ElementType>
std::unique_ptr<SkipListLevelTester<ElementType>> RandomSkipListLevelTester<ElementType>::clone()
{
    return std::unique_ptr<SkipListLevelTester<ElementType>>{
        new RandomSkipListLevelTester<ElementType>};
}




template <typename ElementType>
class SkipListSet : public Set<ElementType>
{
public:
    // Initializes an SkipListSet to be empty, with or without a
    // "level tester" object that will decide, whenever a "coin flip"
    // is needed, whether a key should occupy the next level above.
    SkipListSet();
    explicit SkipListSet(std::unique_ptr<SkipListLevelTester<ElementType>> levelTester);

    // Cleans up the SkipListSet so that it leaks no memory.
    ~SkipListSet() noexcept override;

    // Initializes a new SkipListSet to be a copy of an existing one.
    SkipListSet(const SkipListSet& s);

    // Initializes a new SkipListSet whose contents are moved from an
    // expiring one.
    SkipListSet(SkipListSet&& s) noexcept;

    // Assigns an existing SkipListSet into another.
    SkipListSet& operator=(const SkipListSet& s);

    // Assigns an expiring SkipListSet into another.
    SkipListSet& operator=(SkipListSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a SkipListSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in an expected time
    // of O(log n) (i.e., over the long run, we expect the average to be
    // O(log n)) with very high probability.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in an expected time of O(log n)
    // (i.e., over the long run, we expect the average to be O(log n))
    // with very high probability.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // levelCount() returns the number of levels in the skip list.
    unsigned int levelCount() const noexcept;


    // elementsOnLevel() returns the number of elements that are stored
    // on the given level of the skip list.  Level 0 is the bottom level;
    // level 1 is the one above level 0; and so on.  If the given level
    // doesn't exist, this function returns 0.  (Note that the -INF
    // and +INF shouldn't be counted.)
    unsigned int elementsOnLevel(unsigned int level) const noexcept;


    // isElementOnLevel() returns true if the given element is on the
    // given level, false otherwise.  Level 0 is the bottom level; level 1
    // is the one above level 0; and so on.  If the given level doesn't
    // exist, this function returns false.
    bool isElementOnLevel(const ElementType& element, unsigned int level) const;


private:
    std::unique_ptr<SkipListLevelTester<ElementType>> levelTester;

    // User added
    struct Node
    {
        SkipListKey<ElementType> key;
        ElementType value;
        Node* next;
        Node* down;
        Node(SkipListKey<ElementType> key) : key(key) {}
    };
    SkipListSet* backup;
    unsigned int listSize;
    int maxLevel;
    int currentLevel;
    Node* start;
    Node* end;
    bool duplicateError;
    void deleteElements(Node* node);
    void copyList(const SkipListSet& s);
    void flipCoin(Node* node, const ElementType& element, int level);
    void addNodeToLevel(Node* node, const ElementType& element, int level);
    bool checkLevel(Node* node, const ElementType& element);
};


template <typename ElementType>
SkipListSet<ElementType>::SkipListSet()
    : SkipListSet{std::make_unique<RandomSkipListLevelTester<ElementType>>()}
{
}


template <typename ElementType>
SkipListSet<ElementType>::SkipListSet(std::unique_ptr<SkipListLevelTester<ElementType>> levelTester)
    : levelTester{std::move(levelTester)}
{
    listSize = 0;
    maxLevel = 0;
    start = new Node(SkipListKey<ElementType>::negInf());
    end = new Node(SkipListKey<ElementType>::posInf());
    start->value = -97;
    end->value = 97;
    start->next = end;
    start->down = nullptr;
    end->next = nullptr;
    end->down = nullptr;
    duplicateError = false;
}


template <typename ElementType>
SkipListSet<ElementType>::~SkipListSet() noexcept
{
    Node* current = start;
    Node* downNode = start->down;
    while (current != nullptr)
    {
        deleteElements(current);
        current = downNode;
        if (downNode != nullptr)
        {
            downNode = downNode->down;
        }
    }
}


template <typename ElementType>
void SkipListSet<ElementType>::deleteElements(Node* node)
{
    if (node != nullptr)
    {
        deleteElements(node->next);
        delete node;
    }
}


template <typename ElementType>
SkipListSet<ElementType>::SkipListSet(const SkipListSet& s)
{
    try
    {
        copyList(s);
    }
    catch(...)
    {
        Node* current = start;
        Node* downNode = start->down;
        while (current != nullptr)
        {
            deleteElements(current);
            current = downNode;
            if (downNode != nullptr)
            {
                downNode = downNode->down;
            }
        }
        listSize = 0;
        maxLevel = 0;
        start = new Node(SkipListKey<ElementType>::negInf());
        end = new Node(SkipListKey<ElementType>::posInf());
        start->value = -97;
        end->value = 97;
        start->next = end;
        start->down = nullptr;
        end->next = nullptr;
        end->down = nullptr;
        duplicateError = false;
    }
}


template <typename ElementType>
void SkipListSet<ElementType>::copyList(const SkipListSet& s)
{
    listSize = s.listSize;
    maxLevel = s.maxLevel;
    currentLevel = s.currentLevel;
    start = nullptr;
    duplicateError = false;
    Node* otherCurrentNode = s.start;
    Node* currentNode = start;
    Node* currentLevel = start;
    Node* prevLevel = start;
    Node* otherCurrentLevel = s.start;
    for (int i = 0; i < maxLevel + 1; i++)
    {
        Node* levelStart = new Node(SkipListKey<ElementType>::negInf());
        levelStart->value = -97;
        levelStart->next = nullptr;
        levelStart->down = nullptr;
        if (i == 0)
        {
            currentLevel = levelStart;
            currentLevel->down = nullptr;
        }
        else
        {
            prevLevel = currentLevel;
            currentLevel = levelStart;
            currentLevel->down = prevLevel;
        }
    }
    start = currentLevel;
    prevLevel = start;
    currentNode = start;
    otherCurrentNode = s.start->next;
    for (int i = maxLevel + 1; i >= 0; i--)
    {
        int level = i - 1;
        while (otherCurrentNode != nullptr)
        {
            Node* copyNode = new Node(otherCurrentNode->key);
            copyNode->next = nullptr;
            copyNode->down = nullptr;
            copyNode->value = otherCurrentNode->value;
            currentNode->next = copyNode;
            if (level < maxLevel && (s.isElementOnLevel(otherCurrentNode->value, level + 1) || otherCurrentNode->key == s.end->key))
            {
                Node* node = prevLevel;
                while (node->key < otherCurrentNode->key)
                {
                    node = node->next;
                }
                node->down = copyNode;
            }
            currentNode = currentNode->next;
            otherCurrentNode = otherCurrentNode->next;
        }
        prevLevel = currentLevel;
        if (currentLevel->down != nullptr)
        {
            currentLevel = currentLevel->down;
            currentNode = currentLevel;
            otherCurrentLevel = otherCurrentLevel->down;
            otherCurrentNode = otherCurrentLevel->next;
        }
    }
    end = currentNode;
}


template <typename ElementType>
SkipListSet<ElementType>::SkipListSet(SkipListSet&& s) noexcept
{
    listSize = 0;
    maxLevel = 0;
    start = new Node(SkipListKey<ElementType>::negInf());
    end = new Node(SkipListKey<ElementType>::posInf());
    start->value = -97;
    end->value = 97;
    start->next = end;
    start->down = nullptr;
    end->next = nullptr;
    end->down = nullptr;
    duplicateError = false;
    std::swap(listSize, s.listSize);
    std::swap(maxLevel, s.maxLevel);
    std::swap(currentLevel, s.currentLevel);
    std::swap(start, s.start);
    std::swap(end, s.end);
    std::swap(duplicateError, s.duplicateError);
}


template <typename ElementType>
SkipListSet<ElementType>& SkipListSet<ElementType>::operator=(const SkipListSet& s)
{
    backup = new SkipListSet(*this);
    try
    {
        Node* current = start;
        Node* downNode = start->down;
        while (current != nullptr)
        {
            deleteElements(current);
            current = downNode;
            if (downNode != nullptr)
            {
                downNode = downNode->down;
            }
        }
        copyList(s);
        delete backup;
    }
    catch(...)
    {
        Node* current = start;
        Node* downNode = start->down;
        while (current != nullptr)
        {
            deleteElements(current);
            current = downNode;
            if (downNode != nullptr)
            {
                downNode = downNode->down;
            }
        }
        return *backup;
    }
    return *this;
}


template <typename ElementType>
SkipListSet<ElementType>& SkipListSet<ElementType>::operator=(SkipListSet&& s) noexcept
{
    std::swap(listSize, s.listSize);
    std::swap(maxLevel, s.maxLevel);
    std::swap(currentLevel, s.currentLevel);
    std::swap(start, s.start);
    std::swap(end, s.end);
    std::swap(duplicateError, s.duplicateError);
    return *this;
}


template <typename ElementType>
bool SkipListSet<ElementType>::isImplemented() const noexcept
{
    return true;
    //return false;
}


template <typename ElementType>
void SkipListSet<ElementType>::add(const ElementType& element)
{
    if (!contains(element))
    {
        int level = maxLevel;
        if (listSize == 0) // Creating new skiplist
        {
            Node* newNode = new Node(SkipListKey<ElementType>::normal(element));
            newNode->next = end;
            newNode->down = nullptr;
            newNode->value = element;
            start->next = newNode;
            listSize += 1;
            flipCoin(newNode, element, level);
        }
        else
        {
            int level = maxLevel;
            Node* node = start;
            Node* current = start;
            while (level != 0 || current->key < element)
            {
                if (current->key < element && current->next->key < element && current->next->key < end->key)
                {
                    current = current->next;
                }
                else if (level != 0 || (current->key < element && current->key < current->next->key && level != 0))
                {
                    level -= 1;
                    current = current->down;
                }
                else if (level == 0)
                {
                    if (current->key < element && current->next->key < element)
                    {
                        current = current->next;
                    }
                    else if (current->key < element && (current->next->key < end->key || current->next->key == end->key))
                    {
                        Node* newNode = new Node(SkipListKey<ElementType>::normal(element));
                        newNode->next = current->next;
                        newNode->down = nullptr;
                        newNode->value = element;
                        current->next = newNode;
                        current = newNode;
                        node = newNode;
                        listSize += 1;
                        break;
                    }
                }
            }
            flipCoin(node, element, 0);
        }
    }
}


template <typename ElementType>
void SkipListSet<ElementType>::addNodeToLevel(Node* node, const ElementType& element, int level)
{
    Node* current = start;
    while (current->key < element)
    {
        if (current->key < element && current->next->key < element)
        {
            current = current->next;
        }
        else if (current->key < element && current->key < current->next->key && (current->next->key == end->key || current->next->key < end->key)) // can go no further
        {
            if (current->key == element || current->next->key == element)
            {
                duplicateError = true;
                break;
            }
            Node *temp = current;
            current = current->down;
            if (checkLevel(current, element))
            {
                Node* newNode = new Node(SkipListKey<ElementType>::normal(element));
                newNode->value = element;
                newNode->next = temp->next;
                newNode->down = node;
                temp->next = newNode;
                current = newNode;
                node = newNode;
                break;
            }
            else
            {
                level -= 1;
            }
        }
    }
    flipCoin(node, element, level);
}


template <typename ElementType>
void SkipListSet<ElementType>::flipCoin(Node* node, const ElementType& element, int level)
{
    if (levelTester->shouldOccupyNextLevel(element) || duplicateError)
    {
        if (duplicateError)
        {
            duplicateError = false;
        }
        currentLevel = level + 1;
        if (currentLevel > maxLevel)
        {
            maxLevel += 1;
            Node* levelHead = new Node(SkipListKey<ElementType>::negInf());
            Node* current = new Node(SkipListKey<ElementType>::normal(element));
            Node* levelTail = new Node(SkipListKey<ElementType>::posInf());
            levelHead->down = start;
            levelHead->value = -97;
            levelHead->next = current;
            current->down = node;
            current->value = element;
            current->next = levelTail;
            levelTail->down = end;
            levelTail->value = 97;
            levelTail->next = nullptr;
            start = levelHead;
            end = levelTail;
            flipCoin(current, element, currentLevel);
        }
        else // find spot
        {
            addNodeToLevel(node, element, currentLevel);
        }
    }
}


template <typename ElementType>
bool SkipListSet<ElementType>::checkLevel(Node* node, const ElementType& element)
{
    while (node->key < end->key && node != nullptr)
    {
        if (node->key == element)
        {
            return true;
        }
        else if (node->key == end->key)
        {
            return false;
        }
        node = node->next;
    }
    return false;
}


template <typename ElementType>
bool SkipListSet<ElementType>::contains(const ElementType& element) const
{
    Node* current = start;
    while (current->key < element)
    {
        if (current->key == element || current->next->key == element)
        {
            return true;
        }
        else if (current->key < element && current->next->key < element)
        {
            current = current->next;
        }
        else
        {
            if (current->down == nullptr)
            {
                current = current->next;
            }
            else
            {
                current = current->down;
            }
        }
    }
    return false;
}


template <typename ElementType>
unsigned int SkipListSet<ElementType>::size() const noexcept
{
    //return 0;
    return listSize;
}


template <typename ElementType>
unsigned int SkipListSet<ElementType>::levelCount() const noexcept
{
    return maxLevel + 1;
    //return 0;
}


template <typename ElementType>
unsigned int SkipListSet<ElementType>::elementsOnLevel(unsigned int level) const noexcept
{
    unsigned int elementNum = 0;
    if (level <= maxLevel)
    {
        Node* current = start;
        for (int i = 0; i < maxLevel - level; i++)
        {
            current = current->down;
        }
        current = current->next;
        while (current->key < end->key)
        {
            elementNum += 1;
            current = current->next;
        }
    }
    return elementNum;
}


template <typename ElementType>
bool SkipListSet<ElementType>::isElementOnLevel(const ElementType& element, unsigned int level) const
{
    if (level <= maxLevel)
    {
        Node* current = start;
        for (int i = 0; i < maxLevel - level; i++)
        {
            current = current->down;
        }
        while (current->key < element && current->key < end->key)
        {
            current = current->next;
        }
        if (current->key == element)
        {
            return true;
        }
    }
    return false;
}



#endif


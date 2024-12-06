#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <stdexcept>

template <class Key, class Value>
class HashMap
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *next;
        Node(const Key &k, const Value &v) : key(k), value(v), next(nullptr) {}
    };

    size_t bucketCount;
    size_t amountOfElements;
    Node **buckets;

    size_t hash(const Key &key) const
    {
        std::hash<Key> hasher;
        return hasher(key) % bucketCount;
    }

    void copyFrom(const HashMap &other)
    {
        bucketCount = other.bucketCount;
        amountOfElements = other.amountOfElements;
        buckets = new Node *[bucketCount]();
        for (size_t i = 0; i < bucketCount; ++i)
        {
            Node *current = other.buckets[i];
            while (current)
            {
                Node *newNode = new Node(current->key, current->value);
                newNode->next = buckets[i];
                buckets[i] = newNode;
                current = current->next;
            }
        }
    }

    void rehash()
    {
        size_t oldBucketCount = bucketCount;
        bucketCount *= 2;
        Node **newBuckets = new Node *[bucketCount]();
        for (size_t i = 0; i < oldBucketCount; ++i)
        {
            Node *current = buckets[i];
            while (current)
            {
                Node *next = current->next;
                size_t index = hash(current->key);
                current->next = newBuckets[index];
                newBuckets[index] = current;
                current = next;
            }
        }
        delete[] buckets;
        buckets = newBuckets;
    }

public:
    class iterator
    {
    private:
        Node **bucketPtr;
        Node **bucketEnd;
        Node *currentNode;

    public:
        iterator(Node **bucketPtr, Node **bucketEnd, Node *currentNode)
            : bucketPtr(bucketPtr), bucketEnd(bucketEnd), currentNode(currentNode) {}

        iterator &operator++()
        {
            if (currentNode)
            {
                currentNode = currentNode->next;
            }
            while (!currentNode && bucketPtr != bucketEnd)
            {
                ++bucketPtr;
                if (bucketPtr != bucketEnd)
                {
                    currentNode = *bucketPtr;
                }
            }
            return *this;
        }

        bool operator!=(const iterator &other) const
        {
            return bucketPtr != other.bucketPtr || currentNode != other.currentNode;
        }

        std::pair<const Key &, Value &> operator*() const
        {
            return {currentNode->key, currentNode->value};
        }

        Node *operator->() const
        {
            return currentNode;
        }
    };

    HashMap() : bucketCount(10), amountOfElements(0)
    {
        buckets = new Node *[bucketCount]();
    }

    HashMap(const HashMap &other)
    {
        copyFrom(other);
    }

    HashMap(HashMap &&other) noexcept : bucketCount(0), amountOfElements(0), buckets(nullptr)
    {
        *this = std::move(other);
    }

    ~HashMap()
    {
        clear();
        delete[] buckets;
    }

    HashMap &operator=(const HashMap &other)
    {
        if (this != &other)
        {
            clear();
            delete[] buckets;
            copyFrom(other);
        }
        return *this;
    }

    HashMap &operator=(HashMap &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            delete[] buckets;
            bucketCount = other.bucketCount;
            amountOfElements = other.amountOfElements;
            buckets = other.buckets;
            other.buckets = nullptr;
            other.bucketCount = 0;
            other.amountOfElements = 0;
        }
        return *this;
    }

    iterator begin()
    {
        for (size_t i = 0; i < bucketCount; ++i)
        {
            if (buckets[i])
            {
                return iterator(buckets + i, buckets + bucketCount, buckets[i]);
            }
        }
        return end();
    }

    iterator end()
    {
        return iterator(buckets + bucketCount, buckets + bucketCount, nullptr);
    }

    iterator find(const Key &key)
    {
        size_t index = hash(key);
        Node *current = buckets[index];
        while (current)
        {
            if (current->key == key)
            {
                return iterator(buckets + index, buckets + bucketCount, current);
            }
            current = current->next;
        }
        return end();
    }

    Value &operator[](const Key &key)
    {
        size_t index = hash(key);
        Node *current = buckets[index];
        while (current)
        {
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }
        Node *newNode = new Node(key, Value());
        newNode->next = buckets[index];
        buckets[index] = newNode;
        amountOfElements++;
        if (amountOfElements / bucketCount > 0.7)
        {
            rehash();
        }
        return newNode->value;
    }

    bool contains(const Key &key) const
    {
        size_t index = hash(key);
        Node *current = buckets[index];
        while (current)
        {
            if (current->key == key)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    size_t erase(const Key &key)
    {
        size_t index = hash(key);
        Node *current = buckets[index];
        Node *prev = nullptr;
        while (current)
        {
            if (current->key == key)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    buckets[index] = current->next;
                }
                delete current;
                amountOfElements--;
                return 1;
            }
            prev = current;
            current = current->next;
        }
        return 0;
    }

    size_t size() const
    {
        return amountOfElements;
    }

    void clear()
    {
        for (size_t i = 0; i < bucketCount; ++i)
        {
            Node *current = buckets[i];
            while (current)
            {
                Node *next = current->next;
                delete current;
                current = next;
            }
            buckets[i] = nullptr;
        }
        amountOfElements = 0;
    }
};

#include "hashMap.hpp"
#include <string>
#include <cmath>

HashMap::HashMap() : bucketCount(10), amountOfElements(0)
{
    buckets = new Node *[bucketCount]();
}


HashMap::HashMap(const HashMap &other)
{
    copyFrom(other);
}

HashMap::~HashMap() {
    clear();
    delete[] buckets;
}

void HashMap::copyFrom(const HashMap & other){
    bucketCount = other.bucketCount;
    amountOfElements = other.amountOfElements;
    buckets = new Node *[bucketCount]();
    for (size_t i = 0; i < bucketCount; i++)
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

size_t HashMap::hash(const std::string &key) const
{
    size_t len = key.length();
    size_t hash = 0;
    size_t exp = 1;
    for (size_t i = 0; i < len; i++)
    {
        hash += key[i] % 3 * exp;
        exp *= 3;
    }
    return hash % bucketCount;
}

HashMap &HashMap::operator=(const HashMap &other){
    if (this != &other) {
        clear();
        delete[] buckets;
        copyFrom(other);
    }
    return *this;
}

std::size_t HashMap::erase(const std::string &key){
    size_t i = hash(key);
    Node *current = buckets[i];
    Node *prev = nullptr;
    while (current)
    {
        if (current->key == key){
            if(prev){
                prev->next = current->next;
            }
            else {
                buckets[i] = current -> next;
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

void HashMap::rehash()
{
    size_t oldBucketCount = bucketCount;
    bucketCount *= 2;
    Node **newBuckets = new Node *[bucketCount]();
    for (size_t i = 0; i < oldBucketCount; i++)
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

std::string &HashMap::operator[](const std::string &key)
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
    Node *newNode = new Node(key, "");
    newNode->next = buckets[index];
    buckets[index] = newNode;
    amountOfElements++;
    if(amountOfElements/bucketCount > 0.7){
        rehash();
    }
    return newNode->value;
}

size_t HashMap::size() const
{
    return amountOfElements;
}

void HashMap::clear(){
    for (size_t i = 0; i < bucketCount; i++)
    {
        Node *current = buckets[i];
        while(current){
            Node *next = current->next;
            delete current;
            current = next;
        }
        buckets[i] = nullptr;
    }
    amountOfElements = 0;
}

bool HashMap::contains(const std::string &key)
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

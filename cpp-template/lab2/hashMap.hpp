// #include <stdio.h>
#include <string>

class HashMap
{
private:
    struct Node
    {
        std::string key;
        std::string value;
        Node *next;

        Node(const std::string &k, const std::string &v) : key(k), value(v), next(nullptr){}
    };
    Node **buckets;
    size_t bucketCount;
    size_t amountOfElements;
    size_t hash(const std::string& key) const;
    void rehash();
    void copyFrom(const HashMap &other);

public:
    // стандартный конструктор
    HashMap();

    // конструктор копирования
    HashMap(const HashMap &otherMap);

    // деструктор
    ~HashMap();

    // оператор присваивания
    HashMap &operator=(const HashMap &other_map);

    // получить количество элементов
    std::size_t size() const;

    // доступ / вставка элемента по ключу
    std::string &operator[](const std::string &key);

    // возвращает true, если запись с таким ключом присутствует
    bool contains(const std::string &key);

    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const std::string &key);

    // очистка мэпы, удаление всех элементов
    void clear();
};

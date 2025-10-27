#pragma once

#include <iostream>
#include <string>
#include <utility>

template <typename K, typename V>
struct Node
{
    K key;
    V value;
    Node *next;
    Node(K k, V v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashMap
{
private:
    Node<K, V> **table;
    int cap;
    int size;

    unsigned long hashFunc(const std::string &key) const
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash = (hash * 131 + c) % cap;
        }
        return hash;
    }
    unsigned long hashFunc(unsigned long long key) const
    {
        return key % cap;
    }

    unsigned long hashFunc(int key) const
    {
        return static_cast<unsigned long>(key) % cap;
    }

public:
    class Iterator
    {
    private:
        Node<K, V> **table;
        int cap;
        int index;
        Node<K, V> *current;

    public:
        Iterator(Node<K, V> **t, int c, int i, Node<K, V> *curr)
            : table(t), cap(c), index(i), current(curr) {}

        bool operator!=(const Iterator &other) const { return current != other.current || index != other.index; }
        bool operator==(const Iterator &other) const { return current == other.current && index == other.index; }

        Iterator &operator++()
        {
            if (current && current->next)
            {
                current = current->next;
            }
            else
            {
                index++;
                while (index < cap && table[index] == nullptr)
                {
                    index++;
                }
                current = (index < cap) ? table[index] : nullptr;
            }
            return *this;
        }

        std::pair<const K, V> operator*() const
        {
            return {current->key, current->value};
        }
    };

    HashMap(int c = 20) : cap(c), size(0)
    {
        table = new Node<K, V> *[cap];
        for (int i = 0; i < cap; i++)
        {
            table[i] = nullptr;
        }
    }

    ~HashMap()
    {
        clear();
        delete[] table;
    }

    void insert(const K &key, const V &val)
    {
        unsigned long index = hashFunc(key);
        Node<K, V> *head = table[index];

        while (head != nullptr)
        {
            if (head->key == key)
            {
                head->value = val;
                return;
            }
            head = head->next;
        }

        Node<K, V> *newNode = new Node<K, V>(key, val);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    bool get(const K &key, V &val)
    {
        unsigned long index = hashFunc(key);
        Node<K, V> *head = table[index];

        while (head != nullptr)
        {
            if (head->key == key)
            {
                val = head->value;
                return true;
            }
            head = head->next;
        }
        return false;
    }

    void remove(const K &key)
    {
        unsigned long index = hashFunc(key);
        Node<K, V> *head = table[index];
        Node<K, V> *prev = nullptr;

        while (head != nullptr)
        {
            if (head->key == key)
            {
                if (prev == nullptr)
                {
                    table[index] = head->next;
                }
                else
                {
                    prev->next = head->next;
                }
                delete head;
                size--;
                return;
            }
            prev = head;
            head = head->next;
        }
    }

    Iterator find(const K &key) const
    {
        unsigned long index = hashFunc(key);
        Node<K, V> *curr = table[index];

        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                return Iterator(table, cap, index, curr);
            }
            curr = curr->next;
        }
        return end();
    }

    void clear()
    {

        for (int i = 0; i < cap; i++)
        {
            Node<K, V> *head = table[i];
            while (head)
            {
                Node<K, V> *temp = head;
                head = head->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }

    Iterator begin() const
    {
        for (int i = 0; i < cap; i++)
        {
            if (table[i])
            {
                return Iterator(table, cap, i, table[i]);
            }
        }
        return end();
    }
    Iterator end() const
    {
        return Iterator(table, cap, cap, nullptr);
    }

    V &operator[](const K &key)
    {
        unsigned long index = hashFunc(key);
        Node<K, V> *head = table[index];

        while (head != nullptr)
        {
            if (head->key == key)
            {
                return head->value;
            }
            head = head->next;
        }

        Node<K, V> *newNode = new Node<K, V>(key, V{});
        newNode->next = table[index];
        table[index] = newNode;
        size++;

        return newNode->value;
    }

    int getSize() { return size; }
    int getCapacity() { return cap; }
};

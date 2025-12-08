#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void append(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }


    bool search(T val) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == val) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void remove(T val) {
        if (head == nullptr) return;


        if (head->data == val) {
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != val) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            Node<T>* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }


    int getSize() {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    Node<T>* getHead() {
        return head;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void display() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

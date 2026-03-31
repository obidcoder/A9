#pragma once

#include <utility>     // provides std::swap
#include <stdexcept>
#include <iostream>

namespace dsac::list {

/// circularly linked list
template <typename T>
class CircularlyLinkedList {
    private:
        class Node {
            public:
                T elem;
                Node* next;
                // ToDo
                Node(const T& element, Node* nxt = nullptr)
                    : elem{element}, next{nxt} {}
        };
    private:
        int sz{0};
        Node* tail{nullptr};
    public:
        // ToDo
        /*CircularlyLinkedList();
        int size() const;
        bool empty() const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        void push_front(const T& elem);
        void push_back(const T& elem);
        void pop_front();
        void rotate();
        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B);
        */
       CircularlyLinkedList() = default;

        int size() const {
            return sz;
        }

        bool empty() const {
            return sz == 0;
        }

        T& front() {
            return tail->next->elem;
        }

        const T& front() const {
            return tail->next->elem;
        }

        T& back() {
            return tail->elem;
        }

        const T& back() const {
            return tail->elem;
        }

        void push_front(const T& elem) {
            Node* newest = new Node(elem);

            if (empty()) {
                newest->next = newest;
                tail = newest;
            } else {
                newest->next = tail->next;
                tail->next = newest;
            }
            sz++;
        }

        void push_back(const T& elem) {
            push_front(elem);
            tail = tail->next;
        }

        void pop_front() {
            if (empty()) return;

            Node* head = tail->next;

            if (sz == 1) {
                delete head;
                tail = nullptr;
            } else {
                tail->next = head->next;
                delete head;
            }
            sz--;
        }

        void rotate() {
            if (tail != nullptr) {
                tail = tail->next;
            }
        }

        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
            // If the list is empty, both result lists should also be empty
            A.clear();
            B.clear();

            if (empty()) return;

            // splitEven is only valid for even-sized lists else throw exception
            if (sz % 2 != 0) {
                throw std::out_of_range("List size must be even");
            }

            // head is the first node in the circular list
            Node* head = tail->next;

            int half = sz / 2;

            // Find the last node of the first half
            Node* firstTail = head;
            for (int i = 1; i < half; i++) {
                firstTail = firstTail->next;
            }

            // The node after firstTail is the head of the second half
            Node* secondHead = firstTail->next;

            // The original tail becomes the tail of the second half
            Node* secondTail = tail;

            // Rewire pointers to form two separate circular lists
            firstTail->next = head;
            secondTail->next = secondHead;

            // Assign the two halves
            A.tail = firstTail;
            A.sz = half;

            B.tail = secondTail;
            B.sz = half;

            // Original list becomes empty
            tail = nullptr;
            sz = 0;
        }
    private:
         void clone(const CircularlyLinkedList& other) {
            if (other.empty()) return;

            Node* walk = other.tail->next;
            for (int i = 0; i < other.sz; i++) {
                push_back(walk->elem);
                walk = walk->next;
            }
        }
    public:
        friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b) {
            std::swap(a.sz, b.sz);
            std::swap(a.tail, b.tail);
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        CircularlyLinkedList(const CircularlyLinkedList& other) {
            clone(other);
        }

        CircularlyLinkedList& operator=(const CircularlyLinkedList& other) {
            if (this != &other) {
                clear();
                clone(other);
            }
            return *this;
        }

        CircularlyLinkedList(CircularlyLinkedList&& other) {
            sz = other.sz;
            tail = other.tail;
            other.sz = 0;
            other.tail = nullptr;
        }

        CircularlyLinkedList& operator=(CircularlyLinkedList&& other) {
            if (this != &other) {
                clear();
                sz = other.sz;
                tail = other.tail;
                other.sz = 0;
                other.tail = nullptr;
            }
            return *this;
        }

        ~CircularlyLinkedList() {
            clear();
        }

        void print() {
            if (empty()) return;

            Node* walk = tail->next;
            for (int i = 0; i < sz; i++) {
                std::cout << walk->elem << " ";
                walk = walk->next;
            }
            std::cout << "\n";
        }
};

}  // namespace dsac::list


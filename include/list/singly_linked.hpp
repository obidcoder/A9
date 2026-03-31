#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

// similar to std::forward_list
template <typename T>
class SinglyLinkedList {
    private:
        class Node {
            public:
                T elem;
                Node* next;
                // ToDo
                //Node(const T& element, Node* nxt = nullptr);
                Node(const T& element, Node* nxt = nullptr) : elem(element), next(nxt) {}
        };
        int sz{0};
        Node* head{nullptr};
        Node* tail{nullptr};
    public:
        // ToDo
        //SinglyLinkedList();
        SinglyLinkedList() : sz(0), head(nullptr), tail(nullptr) {}

        int size() const { return sz; }

        bool empty() const {return sz == 0; }

        T& front() {
            return head->elem;
        }

        const T& front() const {
            return head->elem;
        }

        T& back() {
            return tail->elem;
        }

        const T& back() const {
            return tail->elem;
        }

        void push_front(const T& elem) {
            Node* newest = new Node(elem, head);
            head = newest;
            if (sz == 0) tail = head;
            ++sz;
        }

        void pop_front() {
            if (empty()) return;

            Node* old = head;
            head = head->next;
            delete old;
            --sz;

            if (sz == 0) tail = nullptr;
        }

        void push_back(const T& elem) {
            Node* newest = new Node(elem);

            if (empty()) {
                head = tail = newest;
            } else {
                tail->next = newest;
                tail = newest;
            }
            ++sz;
        }

        void concatenate(SinglyLinkedList& M) {
            if (this == &M) return;
            if (M.empty()) return;

            if (empty()) {
                head = M.head;
                tail = M.tail;
                sz = M.sz;
            } else {
                tail->next = M.head;
                tail = M.tail;
                sz += M.sz;
            }

            M.head = nullptr;
            M.tail = nullptr;
            M.sz = 0;
        }

        void reverse() {
            if (head == nullptr || head->next == nullptr) return;

            Node* prev = nullptr;
            Node* curr = head;
            tail = head;

            while (curr != nullptr) {
                Node* nxt = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nxt;
            }

            head = prev;
        }

    public:
        class iterator {
            friend class SinglyLinkedList;
            private:
                Node* node_ptr;  // pointer to a node
            public:
                // ToDo
                iterator(Node* ptr = nullptr) : node_ptr(ptr) {}

                T& operator*() const {
                    return node_ptr->elem;
                }

                T* operator->() const {
                    return &(node_ptr->elem);
                }

                iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }

                iterator operator++(int) {
                    iterator temp = *this;
                    node_ptr = node_ptr->next;
                    return temp;
                }

                bool operator==(iterator rhs) const {
                    return node_ptr == rhs.node_ptr;
                }

                bool operator!=(iterator rhs) const {
                    return node_ptr != rhs.node_ptr;
                }
        };
    public:
        class const_iterator {
            private:
                Node* node_ptr;
            public:
                const_iterator(Node* ptr = nullptr) : node_ptr(ptr) {}

                const T& operator*() const {
                    return node_ptr->elem;
                }

                const T* operator->() const {
                    return &(node_ptr->elem);
                }

                const_iterator& operator++() {
                    node_ptr = node_ptr->next;
                    return *this;
                }

                const_iterator operator++(int) {
                    const_iterator temp = *this;
                    node_ptr = node_ptr->next;
                    return temp;
                }

                bool operator==(const_iterator rhs) const {
                    return node_ptr == rhs.node_ptr;
                }

                bool operator!=(const_iterator rhs) const {
                    return node_ptr != rhs.node_ptr;
                }
        };
    public:
        iterator begin() { return iterator(head); }

        const_iterator begin() const { return const_iterator(head); }

        iterator end() { return iterator(nullptr); }

        const_iterator end() const { return const_iterator(nullptr); }

         iterator insert_after(iterator it, const T& elem) {
            if (it.node_ptr == nullptr) return end();

            Node* newest = new Node(elem, it.node_ptr->next);
            it.node_ptr->next = newest;

            if (tail == it.node_ptr) tail = newest;

            ++sz;
            return iterator(newest);
        }

        iterator erase_after(iterator it) {
            if (it.node_ptr == nullptr || it.node_ptr->next == nullptr) return end();

            Node* target = it.node_ptr->next;
            it.node_ptr->next = target->next;

            if (target == tail) tail = it.node_ptr;

            iterator result(it.node_ptr->next);
            delete target;
            --sz;

            return result;
        }

    private:
        void clone(const SinglyLinkedList& other) {
            for (Node* walk = other.head; walk != nullptr; walk = walk->next) {
                push_back(walk->elem);
            }
        }
    public:
        friend void swap(SinglyLinkedList& a, SinglyLinkedList& b) {
            std::swap(a.sz, b.sz);
            std::swap(a.head, b.head);
            std::swap(a.tail, b.tail);
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        SinglyLinkedList(const SinglyLinkedList& other) : sz(0), head(nullptr), tail(nullptr) {
            clone(other);
        }

        SinglyLinkedList& operator=(const SinglyLinkedList& other) {
            if (this != &other) {
                SinglyLinkedList temp(other);
                swap(*this, temp);
            }
            return *this;
        }

        SinglyLinkedList(SinglyLinkedList&& other)
            : sz(other.sz), head(other.head), tail(other.tail) {
            other.sz = 0;
            other.head = nullptr;
            other.tail = nullptr;
        }

        SinglyLinkedList& operator=(SinglyLinkedList&& other) {
            if (this != &other) {
                clear();
                sz = other.sz;
                head = other.head;
                tail = other.tail;

                other.sz = 0;
                other.head = nullptr;
                other.tail = nullptr;
            }
            return *this;
        }

        ~SinglyLinkedList() {
            clear();
        }
};

} // namespace dsac::list

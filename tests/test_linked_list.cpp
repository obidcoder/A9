#define CATCH_CONFIG_MAIN
#include <vector>
#include <algorithm>
#include "catch2/catch.hpp"

#include "list/singly_linked.hpp"
#include "list/circularly_linked.hpp"
#include "list/doubly_linked.hpp"

using dsac::list::SinglyLinkedList;
using dsac::list::CircularlyLinkedList;
using dsac::list::DoublyLinkedList;

TEST_CASE("SinglyLinkedList concatenate joins two non-empty lists") {
    SinglyLinkedList<int> a;
    SinglyLinkedList<int> b;

    a.push_back(1);
    a.push_back(2);

    b.push_back(3);
    b.push_back(4);

    a.concatenate(b);

    REQUIRE(a.size() == 4);
    REQUIRE(b.size() == 0);
    REQUIRE(b.empty());

    auto it = a.begin();
    REQUIRE(*it == 1); ++it;
    REQUIRE(*it == 2); ++it;
    REQUIRE(*it == 3); ++it;
    REQUIRE(*it == 4); ++it;
    REQUIRE(it == a.end());

    REQUIRE(a.front() == 1);
    REQUIRE(a.back() == 4);
}

TEST_CASE("SinglyLinkedList reverse reverses a longer list") {
    SinglyLinkedList<int> s;
    s.push_back(10);
    s.push_back(20);
    s.push_back(30);
    s.push_back(40);

    s.reverse();

    REQUIRE(s.size() == 4);
    REQUIRE(s.front() == 40);
    REQUIRE(s.back() == 10);

    auto it = s.begin();
    REQUIRE(*it == 40); ++it;
    REQUIRE(*it == 30); ++it;
    REQUIRE(*it == 20); ++it;
    REQUIRE(*it == 10); ++it;
    REQUIRE(it == s.end());
}

TEST_CASE("SinglyLinkedList reverse on single-node list does nothing") {
    SinglyLinkedList<int> s;
    s.push_back(99);

    s.reverse();

    REQUIRE(s.size() == 1);
    REQUIRE(s.front() == 99);
    REQUIRE(s.back() == 99);
}

TEST_CASE("CircularlyLinkedList splitEven splits 4 nodes into two halves") {
    CircularlyLinkedList<int> c;
    CircularlyLinkedList<int> a;
    CircularlyLinkedList<int> b;

    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);

    c.splitEven(a, b);

    REQUIRE(c.empty());

    REQUIRE(a.size() == 2);
    REQUIRE(a.front() == 1);
    REQUIRE(a.back() == 2);

    REQUIRE(b.size() == 2);
    REQUIRE(b.front() == 3);
    REQUIRE(b.back() == 4);
}

TEST_CASE("CircularlyLinkedList splitEven throws on odd-sized list") {
    CircularlyLinkedList<int> c;
    CircularlyLinkedList<int> a;
    CircularlyLinkedList<int> b;

    c.push_back(5);
    c.push_back(6);
    c.push_back(7);

    REQUIRE_THROWS_AS(c.splitEven(a, b), std::out_of_range);
}

TEST_CASE("CircularlyLinkedList rotate moves front to back") {
    CircularlyLinkedList<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);

    c.rotate();

    REQUIRE(c.front() == 2);
    REQUIRE(c.back() == 1);

    c.rotate();
    REQUIRE(c.front() == 3);
    REQUIRE(c.back() == 2);
}

TEST_CASE("DoublyLinkedList concatenate joins two non-empty lists") {
    DoublyLinkedList<int> a;
    DoublyLinkedList<int> b;

    a.push_back(1);
    a.push_back(2);

    b.push_back(3);
    b.push_back(4);

    a.concatenate(b);

    REQUIRE(a.size() == 4);
    REQUIRE(b.size() == 0);
    REQUIRE(b.empty());

    auto it = a.begin();
    REQUIRE(*it == 1); ++it;
    REQUIRE(*it == 2); ++it;
    REQUIRE(*it == 3); ++it;
    REQUIRE(*it == 4); ++it;
    REQUIRE(it == a.end());

    REQUIRE(a.front() == 1);
    REQUIRE(a.back() == 4);
}

TEST_CASE("DoublyLinkedList concatenate when first list is empty") {
    DoublyLinkedList<int> a;
    DoublyLinkedList<int> b;

    b.push_back(8);
    b.push_back(9);

    a.concatenate(b);

    REQUIRE(a.size() == 2);
    REQUIRE(a.front() == 8);
    REQUIRE(a.back() == 9);

    REQUIRE(b.empty());
    REQUIRE(b.size() == 0);
}

TEST_CASE("DoublyLinkedList push and pop preserve order") {
    DoublyLinkedList<int> d;
    d.push_back(11);
    d.push_back(22);
    d.push_back(33);

    REQUIRE(d.front() == 11);
    REQUIRE(d.back() == 33);

    d.pop_front();
    REQUIRE(d.front() == 22);

    d.pop_back();
    REQUIRE(d.back() == 22);
    REQUIRE(d.size() == 1);
}
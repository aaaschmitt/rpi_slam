//
//  ConcurrentQueue.cpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 9/29/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#include <memory>
#include "ConcurrentQueue.hpp"

typedef std::mutex lock;
typedef std::lock_guard<lock> guard;

template <class T>
typename ConcurrentQueue<T>::Node& ConcurrentQueue<T>::createEmptyNode() {
    Node& n = new Node();
    n.val = 0;
    n.lock = new std::mutex();
    n.next = 0;
    n.prev = 0;
    return n;
}

template <class T>
typename ConcurrentQueue<T>::Node& ConcurrentQueue<T>::createNode(const T& val, Node& prev, Node& next) {
    Node& n = createEmptyNode();
    n.val = val;
    n.prev = prev;
    prev.next = n;
    n.next = next;
    next.prev = n;
    return n;
}

template <class T>
void ConcurrentQueue<T>::deleteNode(Node& n) {
    delete n.lock;
    delete n;
}

template <class T>
void ConcurrentQueue<T>::create() {
    head = createEmptyNode();
    tail = createEmptyNode();
    head.next = tail;
    tail.prev = head;
}

template <class T>
void ConcurrentQueue<T>::enque(const T& val) {
    Node& addTo = tail.prev;
    guard prev(addTo.lock);
    guard next(tail.lock);
    createNode(val, addTo, tail);
}

template <class T>
T& ConcurrentQueue<T>::deque() {
    guard headGuard(head.lock);
    guard removeGuard(head.next);
    Node& toRemove = head.next;
    if (toRemove == tail) {
        return 0;
    }
    
    guard nextGuard(toRemove.next.lock);
    head.next = toRemove.next;
    head.next.prev = head;
    T val = toRemove.val;
    deleteNode(toRemove);
    return val;
}

template <class T>
bool ConcurrentQueue<T>::isEmpty() {
    guard headGuard(head.lock);
    guard nextGuard(head.next);
    return head.next == tail;
}

template <class T>
void ConcurrentQueue<T>::destroy() {
    Node& cur = tail;
    Node& prev = tail.prev;
    while (prev != head) {
        deleteNode(cur);
        cur = prev;
        prev = prev.prev;
    }
    deleteNode(cur);
    deleteNode(prev);
}

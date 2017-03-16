//
//  ConcurrentQueue.hpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 9/29/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#ifndef ConcurrentQueue_h
#define ConcurrentQueue_h
#include <cstddef>
#include <mutex>

#endif /* ConcurrentQueue_h */


/**
 * This is similar in concept to a ring buffer.
 * Values are enqued at one end and dequed at the other.
 * This allows two threads to effectively communicate, while doing work
 * independently.  This is particularly useful if the dequeing thread must perform
 * more computation than the enqueing thread.
 * As such this can be thought of as a buffer between threads.
 */
template <class T>
class ConcurrentQueue {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    
    /* Default initializer */
    ConcurrentQueue() { create(); };
    /* Default assignment */
    ConcurrentQueue& operator=(const ConcurrentQueue&);
    
    /* Destructor */
    ~ConcurrentQueue() { destroy(); };
    
    /* Add a copy of an item to this queue */
    void enque(const T& val);
    /* Remove an item from this queue in the order it was added */
    T& deque();
    /* True if this queue contains no items */
    bool isEmpty();
    
private:
    struct Node {
        T val;
        Node& next;
        Node& prev;
        std::mutex lock;
    };
    Node& head;
    Node& tail;
    Node& createEmptyNode();
    Node& createNode(const T& val, Node& prev, Node& next);
    void deleteNode(Node& n);
    
    void create();
    void create(const ConcurrentQueue& q);
    void destroy();

    /* Copy consturctor
     * This disallows copying because it would be 
     * a very strange operation for a concurrent Q to have.
     */
    ConcurrentQueue(const ConcurrentQueue& q);
};

#include "ConcurrentQueue.tpp" // inlcude the template implementation here so the linker can find it

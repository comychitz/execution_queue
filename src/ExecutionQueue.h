#ifndef _EXECUTION_QUEUE_H_
#define _EXECUTION_QUEUE_H_

#include "ExecutionQueueMsg.h"

class ExecutionQueue {
  public:
    ExecutionQueue();

    virtual ~ExecutionQueue();

    template <typename T>
    void enqueue(void (T::*method)(), T &obj);

    template <typename T, typename P1>
    void enqueue(void (T::*method)(P1), T &obj, P1 p1);

    template <typename T, typename P1, typename P2>
    void enqueue(void (T::*method)(P1, P2), T &obj, P1 p1, P2 p2);

    template <typename T, typename P1, typename P2, typename P3>
    void enqueue(void (T::*method)(P1, P2, P3), T &obj, P1 p1, P2 p2, P3 p3);

    template <typename T, typename P1, typename P2, typename P3, typename P4>
    void enqueue(void (T::*method)(P1, P2, P3, P4), T &obj, P1 p1, P2 p2, P3 p3, P4 p4);

    template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
    void enqueue(void (T::*method)(P1, P2, P3, P4, P5), T &obj, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5);
};

ExecutionQueue::ExecutionQueue() {
}

ExecutionQueue::~ExecutionQueue() {
}

template <typename T>
void ExecutionQueue::enqueue(void (T::*method)(), T &obj) {
  ExecutionQueueMsg<T> msg = ExecutionQueueMsg<T>(obj, method);
  msg.call();
}

template <typename T, typename P1>
void ExecutionQueue::enqueue(void (T::*method)(P1), T &obj, P1 p1) {
  ExecutionQueueMsg<T, P1> msg = ExecutionQueueMsg<T, P1>(obj, method, p1);
  msg.call();
}

template <typename T, typename P1, typename P2>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2), T &obj, P1 p1, P2 p2) {
  ExecutionQueueMsg<T, P1, P2> msg = ExecutionQueueMsg<T, P1, P2>(obj, method, p1, p2);
  msg.call();
}


template <typename T, typename P1, typename P2, typename P3>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2, P3), T &obj, P1 p1, P2 p2, P3 p3) {
  ExecutionQueueMsg<T, P1, P2, P3> msg = ExecutionQueueMsg<T, P1, P2, P3>(obj, method, p1, p2, p3);
  msg.call();
}

template <typename T, typename P1, typename P2, typename P3, typename P4>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2, P3, P4), T &obj, P1 p1, P2 p2, P3 p3, P4 p4) {
  ExecutionQueueMsg<T, P1, P2, P3, P4> msg = ExecutionQueueMsg<T, P1, P2, P3, P4>(obj, method, p1, p2, p3, p4);
  msg.call();
}

template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2, P3, P4, P5), T &obj, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
  ExecutionQueueMsg<T, P1, P2, P3, P4, P5> msg = ExecutionQueueMsg<T, P1, P2, P3, P4, P5>(obj, method, p1, p2, p3, p4, p5);
  msg.call();
}

#endif

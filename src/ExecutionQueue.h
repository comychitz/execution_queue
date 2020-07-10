#ifndef _EXECUTION_QUEUE_H_
#define _EXECUTION_QUEUE_H_

#include "ExecutionQueueMsg.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class ExecutionQueue {
  public:
    ExecutionQueue();

    ~ExecutionQueue();

    /**
     * process one message on the execution queue. if queue is empty, block
     * until interrupted or a message arrives.
     * @returns 0 on success, 1 if interrupted, -1 on error
     */
    int process();

    /**
     * interrupt the execution queue if it's blocked waiting for messages.
     */
    void interrupt();

    /**
     * clear the queue
     */
    void clear();

    /**
     * check if the queue is empty
     * @returns true if empty, false otherwise
     */
    bool empty();

    /**
     * enqueue an object's method (with params) onto the execution queue.
     */
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

  private:
    ExecutionQueue(const ExecutionQueue&);
    void enqueue_(ExecutionQueueMsgBase *msg);

  private:
    std::mutex lock_;
    std::condition_variable cond_;
    std::queue<ExecutionQueueMsgBase*>  q_;
};

ExecutionQueue::ExecutionQueue() {
}

ExecutionQueue::~ExecutionQueue() {
}

int ExecutionQueue::process() {
  std::unique_lock<std::mutex> lock(lock_);
  if (q_.empty()) {
    cond_.wait(lock);
    if (q_.empty()) {
      return 1;
    }
  }

  if (!q_.empty()) {
    ExecutionQueueMsgBase *msg = q_.front();
    msg->call();
    q_.pop();
    delete msg;
  }
  return 0;
}

void ExecutionQueue::interrupt() {
  std::unique_lock<std::mutex> lock(lock_);
  cond_.notify_one();
}

void ExecutionQueue::clear() {
  std::unique_lock<std::mutex> lock(lock_);
  while (!q_.empty()) {
    q_.pop();
  }
}

bool ExecutionQueue::empty() {
  return q_.empty();
}

void ExecutionQueue::enqueue_(ExecutionQueueMsgBase *msg) {
  std::unique_lock<std::mutex> lock(lock_);
  q_.push(msg);
  cond_.notify_one();
}

template <typename T>
void ExecutionQueue::enqueue(void (T::*method)(), T &obj) {
  ExecutionQueueMsgBase *msg = new ExecutionQueueMsg<T>(obj, method);
  enqueue_(msg);
}

template <typename T, typename P1>
void ExecutionQueue::enqueue(void (T::*method)(P1), T &obj, P1 p1) {
  ExecutionQueueMsgBase *msg = new ExecutionQueueMsg<T, P1>(obj, method, p1);
  enqueue_(msg);
}

template <typename T, typename P1, typename P2>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2), T &obj, P1 p1, P2 p2) {
  ExecutionQueueMsgBase *msg = new ExecutionQueueMsg<T, P1, P2>(obj, method, p1, p2);
  enqueue_(msg);
}

template <typename T, typename P1, typename P2, typename P3>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2, P3), T &obj, P1 p1, P2 p2, P3 p3) {
  ExecutionQueueMsgBase *msg = new ExecutionQueueMsg<T, P1, P2, P3>(obj, method, p1, p2, p3);
  enqueue_(msg);
}

template <typename T, typename P1, typename P2, typename P3, typename P4>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2, P3, P4), T &obj, P1 p1, P2 p2, P3 p3, P4 p4) {
  ExecutionQueueMsgBase *msg = new ExecutionQueueMsg<T, P1, P2, P3, P4>(obj, method, p1, p2, p3, p4);
  enqueue_(msg);
}

template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
void ExecutionQueue::enqueue(void (T::*method)(P1, P2, P3, P4, P5), T &obj, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
  ExecutionQueueMsgBase *msg = new ExecutionQueueMsg<T, P1, P2, P3, P4, P5>(obj, method, p1, p2, p3, p4, p5);
  enqueue_(msg);
}

#endif

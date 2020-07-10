#ifndef _EXECUTION_QUEUE_MSG_H_
#define _EXECUTION_QUEUE_MSG_H_

class ExecutionQueueMsgBase {
  public:
    virtual ~ExecutionQueueMsgBase() { }

    virtual void call() = 0; 
};

template <typename...>
class ExecutionQueueMsg;

template <typename T>
class ExecutionQueueMsg<T> : public ExecutionQueueMsgBase {
  T &obj_;
  void (T::*method_)();

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)()) : obj_(obj), method_(method) { }

    ~ExecutionQueueMsg() { }

    void call() override {
      (obj_.*method_)();
    }
};

template <typename T, typename P1>
class ExecutionQueueMsg<T, P1> : public ExecutionQueueMsgBase {
  T &obj_;
  void (T::*method_)(P1);
  P1 p1_;

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(P1), P1 p1) 
      : obj_(obj), method_(method), p1_(p1) { }

    ~ExecutionQueueMsg() { }

    void call() {
      (obj_.*method_)(p1_);
    }
};

template <typename T, typename P1, typename P2>
class ExecutionQueueMsg<T, P1, P2> : public ExecutionQueueMsgBase {
  T &obj_;
  void (T::*method_)(P1, P2);
  P1 p1_;
  P2 p2_;

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(P1, P2), P1 p1, P2 p2) 
      : obj_(obj), method_(method), p1_(p1), p2_(p2) { }

    ~ExecutionQueueMsg() { }

    void call() {
      (obj_.*method_)(p1_, p2_);
    }
};

template <typename T, typename P1, typename P2, typename P3>
class ExecutionQueueMsg<T, P1, P2, P3> : public ExecutionQueueMsgBase {
  T &obj_;
  void (T::*method_)(P1, P2, P3);
  P1 p1_;
  P2 p2_;
  P3 p3_;

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(P1, P2, P3), P1 p1, P2 p2, P3 p3) 
      : obj_(obj), method_(method), p1_(p1), p2_(p2), p3_(p3) { }

    ~ExecutionQueueMsg() { }

    void call() {
      (obj_.*method_)(p1_, p2_, p3_);
    }
};

template <typename T, typename P1, typename P2, typename P3, typename P4>
class ExecutionQueueMsg<T, P1, P2, P3, P4> : public ExecutionQueueMsgBase {
  T &obj_;
  void (T::*method_)(P1, P2, P3, P4);
  P1 p1_;
  P2 p2_;
  P3 p3_;
  P4 p4_;

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(P1, P2, P3, P4), P1 p1, P2 p2, P3 p3, P4 p4) 
      : obj_(obj), method_(method), p1_(p1), p2_(p2), p3_(p3), p4_(p4) { }

    ~ExecutionQueueMsg() { }

    void call() {
      (obj_.*method_)(p1_, p2_, p3_, p4_);
    }
};

template <typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
class ExecutionQueueMsg<T, P1, P2, P3, P4, P5> : public ExecutionQueueMsgBase {

  T &obj_;
  void (T::*method_)(P1, P2, P3, P4, P5);
  P1 p1_;
  P2 p2_;
  P3 p3_;
  P4 p4_;
  P5 p5_;

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(P1, P2, P3, P4, P5), P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) 
      : obj_(obj), method_(method), p1_(p1), p2_(p2), p3_(p3), p4_(p4), p5_(p5) { }

    ~ExecutionQueueMsg() { }

    void call() {
      (obj_.*method_)(p1_, p2_, p3_, p4_, p5_);
    }
};

#endif

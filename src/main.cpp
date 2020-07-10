#include <iostream>

class Printer {

  public:
    Printer() {  
    }

    ~Printer() {  
    }

    void print() {
      std::cout << "print" << std::endl;
    }

    void printString(std::string str) {
      std::cout << str << std::endl;
    }
};

class ExecutionQueueMsgBase {
  public:
    ~ExecutionQueueMsgBase() { }
    virtual void call() = 0;
};

template <typename...>
class ExecutionQueueMsg;

template <typename T>
class ExecutionQueueMsg<T> : public ExecutionQueueMsgBase {

  T &obj_;
  void (T::*method_)();

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)()) : obj_(obj), method_(method) {
    }

    ~ExecutionQueueMsg() {
    }

    void call() {
      (obj_.*method_)();
    }
};

template <typename T, typename Param1>
class ExecutionQueueMsg<T, Param1> : public ExecutionQueueMsgBase {

  T &obj_;
  void (T::*method_)(Param1);
  Param1 p1_;

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(Param1), Param1 p1) : obj_(obj), method_(method), p1_(p1) {
    }

    ~ExecutionQueueMsg() {
    }

    void call() {
      (obj_.*method_)(p1_);
    }
};

class ExecutionQueue {

  // queue member

  public:
    ExecutionQueue() { }

    ~ExecutionQueue() { }

    template <typename T>
    void emit(T &obj, void (T::*method)());

    template <typename T, typename Param1>
    void emit(T &obj, void (T::*method)(Param1), Param1);
};

template <typename T>
void ExecutionQueue::emit(T &obj, void (T::*method)()) {
  ExecutionQueueMsg<T> msg = ExecutionQueueMsg<T>(obj, method);
  msg.call();
}

template <typename T, typename Param1>
void ExecutionQueue::emit(T &obj, void (T::*method)(Param1), Param1 p1) {
  ExecutionQueueMsg<T, Param1> msg = ExecutionQueueMsg<T, Param1>(obj, method, p1);
  msg.call();
}

int main(int argc, const char *argv[])
{
  Printer printer = Printer();
  ExecutionQueueMsg<Printer> msg = ExecutionQueueMsg<Printer>(printer, &Printer::print);
  msg.call();

  std::string str = "hi";
  ExecutionQueueMsg<Printer, std::string> msgWithArg = ExecutionQueueMsg<Printer, std::string>(printer, &Printer::printString, str);
  msgWithArg.call();

  ExecutionQueue q = ExecutionQueue();

  q.emit(printer, &Printer::print);
  q.emit(printer, &Printer::printString, str);
  
  return 0;
}

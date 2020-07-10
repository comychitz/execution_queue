#include <iostream>

class ExecutionQueueMsgBase {
  public:
    ~ExecutionQueueMsgBase() { }
    virtual void call() = 0;
};

template <typename>
class ExecutionQueueMsg;

template <typename T>
class ExecutionQueueMsg : public ExecutionQueueMsgBase {
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

class Printer {

  public:
    Printer() {  
    }

    ~Printer() {  
    }

    void print() {
      std::cout << "print" << std::endl;
    }

    void printString(std::string &str) {
      std::cout << str << std::endl;
    }
};

int main(int argc, const char *argv[])
{
  Printer printer = Printer();
  ExecutionQueueMsg<Printer> msg = ExecutionQueueMsg<Printer>(printer, &Printer::print);
  msg.call();

  
  return 0;
}

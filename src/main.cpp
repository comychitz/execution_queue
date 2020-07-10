#include <iostream>

class ExecutionQueueMsgBase {
  public:
    ~ExecutionQueueMsgBase() { }
    virtual void call() = 0;
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

    void printString(std::string str) {
      std::cout << str << std::endl;
    }
};

template <typename T, class ...Args>
class ExecutionQueueMsg : public ExecutionQueueMsgBase {

  public:
    ExecutionQueueMsg(T &obj, void (T::*method)(Args ...), Args ...args) {
        (obj.*method)(args...);
    }

    ~ExecutionQueueMsg() {
    }

    void call() {
    }
};

int main(int argc, const char *argv[])
{
  Printer printer = Printer();
  ExecutionQueueMsg<Printer> msg = ExecutionQueueMsg<Printer>(printer, &Printer::print);
  msg.call();

  std::string str = "hi";
  ExecutionQueueMsg<Printer, std::string> msgWithArg = ExecutionQueueMsg<Printer, std::string>(printer, &Printer::printString, str);
  msgWithArg.call();
  
  return 0;
}

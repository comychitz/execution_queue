#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "ExecutionQueue.h"

class Printer {

  public:
    Printer() {  }
    ~Printer() {  }
    void print() { std::cout << "print" << std::endl; }
    void print(std::string s1) { std::cout << s1 << std::endl; }
    void print(std::string s1, std::string s2) { std::cout << s1 << s2 << std::endl; }
    void print(std::string s1, std::string s2, std::string s3) { std::cout << s1 << s2 << s3 << std::endl; }
    void print(std::string s1, std::string s2, std::string s3, std::string s4) { std::cout << s1 << s2 << s3 << s4 << std::endl; }
    void print(std::string s1, std::string s2, std::string s3, std::string s4, std::string s5) { std::cout << s1 << s2 << s3 << s4 << s5 << std::endl; }
};

TEST_CASE("enqueue method with diff num of params", "[exec queue]") {
  Printer printer = Printer();
  ExecutionQueue q = ExecutionQueue();
  q.enqueue(&Printer::print, printer);
  std::string s1 = "h", s2 = "e", s3 = "l", s4 = "l", s5 = "o";
  q.enqueue(&Printer::print, printer, s1);
  q.enqueue(&Printer::print, printer, s1, s2);
  q.enqueue(&Printer::print, printer, s1, s2, s3);
  q.enqueue(&Printer::print, printer, s1, s2, s3, s4);
  q.enqueue(&Printer::print, printer, s1, s2, s3, s4, s5);
}


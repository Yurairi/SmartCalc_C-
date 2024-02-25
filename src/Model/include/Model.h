#ifndef CPP3_SMARTCALC_V2_SRC_MATHMODEL_H
#define CPP3_SMARTCALC_V2_SRC_MATHMODEL_H

#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>

namespace s21 {

class MathModel {
 public:
  // constructor
  MathModel();
  // get set
  void SetString(std::string str);
  void SetX(std::string x_num);
  bool GetError();
  std::string GetResult();

 private:
  using op_func = std::function<double(double, double)>;
  using math_func = std::function<double(double)>;

  inline bool IsPlusMinus(char c) { return (c == '+' || c == '-'); };
  bool err_ = true;
  int brackets_;
  int iter_;
  std::string str_, x_num_;
  std::deque<std::string> q_oper_;
  std::deque<std::string> q_rpn_;
  std::deque<std::string> q_temp_;

  const std::string mathematical_sign_ = "+-*/^%()";

  std::unordered_map<std::string, int> operations_ = {
      {"sin", 3},  {"cos", 3},  {"tan", 3}, {"acos", 3}, {"asin", 3},
      {"atan", 3}, {"sqrt", 3}, {"ln", 3},  {"log", 3},  {"^", 3},
      {"*", 2},    {"/", 2},    {"%", 2},   {"+", 1},    {"-", 1},
      {")", 0},    {"(", 0}};

  const std::map<int, op_func> op_func_map_{
      {'+', std::plus<double>()},
      {'-', std::minus<double>()},
      {'*', std::multiplies<double>()},
      {'/', std::divides<double>()},
      {'%', fmodl},
      {'^', powl},
  };

  const std::map<std::string, math_func> math_func_map_{
      {"cos", cosl},   {"sin", sinl},   {"tan", tanl},
      {"acos", acosl}, {"asin", asinl}, {"atan", atanl},
      {"log", log10l}, {"ln", logl},    {"sqrt", sqrtl},
  };
  // Parcer
  void DigitParse();
  void AlphaParse();
  void XParse();
  void OperationParse();
  // RPN
  void ToRPNOpen();
  void ToRPN(int priority);
  // Extra functions
  void PrintRPNDeque();
  void PrintParseDeque();
  // Calculation
  void CalculateAlpha(std::stack<double>& values);
  void CalculateOperation(std::stack<double>& values);
  // clear deques
  void ClearAll();
  // Result func
  void Parcer();
  void RPN();
  double Calculation();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MATHMODEL_H

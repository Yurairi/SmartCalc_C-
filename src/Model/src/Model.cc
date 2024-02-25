#include "Model.h"

#include <iomanip>
#include <sstream>

namespace s21 {
// Constructors
MathModel::MathModel() : err_(true), brackets_(0), iter_(0) {}

// Setters
void MathModel::SetString(std::string str) { str_ = str; }

void MathModel::SetX(std::string x_num) { x_num_ = x_num; }

// Getters
bool MathModel::GetError() { return err_; }

std::string MathModel::GetResult() {
  Parcer();
  if (!err_) {
    ClearAll();
    return "ERROR";
  }
  RPN();
  auto value = Calculation();
  if (err_) {
    ClearAll();
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(7) << value;
    return ss.str();
  } else {
    ClearAll();
    return "ERROR";
  }
}

// Parser

void MathModel::Parcer() {
  while (iter_ < str_.length() && err_) {
    auto c = str_[iter_];
    if (isdigit(c)) {
      DigitParse();
    } else if (c == 'x') {
      XParse();
    } else if (mathematical_sign_.find_first_of(c) != std::string::npos) {
      OperationParse();
    } else if (isalpha(c)) {
      AlphaParse();
    } else {
      err_ = false;
    }
  }
  if (brackets_ != 0) {
    err_ = false;
  }
  if (str_.length() == 0) {
    err_ = false;
  }
}

void MathModel::AlphaParse() {
  std::string char_oper;
  while (isalpha(str_[iter_])) {
    char_oper += str_[iter_];
    iter_++;
  }
  if (operations_.find(char_oper) != operations_.end()) {
    q_temp_.push_back(char_oper);
  } else {
    err_ = false;
  }
}

void MathModel::XParse() {
  if (stod(x_num_) >= 0) {
    q_temp_.push_back(x_num_);
  } else {
    q_temp_.push_back("(");
    q_temp_.push_back("0");
    q_temp_.push_back("-");
    q_temp_.push_back(x_num_.erase(x_num_.find('-'), 1));
    q_temp_.push_back(")");
  }
  iter_++;
}

void MathModel::DigitParse() {
  std::string num;
  int dot_count = 0;
  int e_count = 0;
  auto c = str_[iter_];
  auto str_size = str_.length();
  while (iter_ < str_size && (isdigit(c) || c == '.' || c == 'e')) {
    if (c == '.')
      dot_count++;
    else if (c == 'e')
      e_count++;
    num += c;
    iter_++;
    c = str_[iter_];
  }
  if (e_count != 0) {
    OperationParse();
    if (IsPlusMinus(q_temp_.back()[0])) {
      num += q_temp_.back();
      q_temp_.pop_back();
      DigitParse();
      num += q_temp_.back();
      q_temp_.pop_back();
    } else {
      err_ = false;
    }
  }
  if (dot_count > 1 || e_count > 1) {
    err_ = false;
  } else {
    q_temp_.push_back(num);
  }
}

void MathModel::OperationParse() {
  auto c = str_[iter_];
  if (IsPlusMinus(c) && (iter_ == 0 || str_[iter_ - 1] == '(')) {
    q_temp_.push_back("0");
  }
  if (c == '(') {
    brackets_++;
  } else if (c == ')') {
    brackets_--;
  }
  if (brackets_ < 0) {
    err_ = false;
  }
  q_temp_.push_back(std::string{str_[iter_]});
  iter_++;
}

// RPN

void MathModel::RPN() {
  for (int i = 0; i < q_temp_.size(); ++i) {
    std::string temp = q_temp_[i];
    if (isdigit(temp[0])) {
      q_rpn_.push_back(temp);
    } else if (temp == "(") {
      q_oper_.push_back(temp);
    } else if (temp == ")") {
      ToRPNOpen();
    } else {
      int cur_priority = operations_[temp];
      ToRPN(cur_priority);
      q_oper_.push_back(temp);
    }
  }
  ToRPNOpen();
  q_temp_.clear();
}

void MathModel::ToRPN(int priority) {
  while (!q_oper_.empty() &&
         (operations_[q_oper_.back()] > priority ||
          (operations_[q_oper_.back()] == priority && q_oper_.back() != "^"))) {
    q_rpn_.push_back(q_oper_.back());
    q_oper_.pop_back();
  }
}

void MathModel::ToRPNOpen() {
  while (!q_oper_.empty() && q_oper_.back() != "(") {
    q_rpn_.push_back(q_oper_.back());
    q_oper_.pop_back();
  }
  if (!q_oper_.empty()) {
    q_oper_.pop_back();
  }
}

// Check RPN

void MathModel::PrintRPNDeque() {
  for (auto& str : q_rpn_) {
    std::cout << str << " ";
  }
}

void MathModel::PrintParseDeque() {
  for (auto& str : q_temp_) {
    std::cout << str << " ";
  }
}

// Calculation

double MathModel::Calculation() {
  std::stack<double> values;
  while (!q_rpn_.empty() && err_) {
    if (isalpha(q_rpn_.front()[0])) {
      CalculateAlpha(values);
    } else if (mathematical_sign_.find_first_of(q_rpn_.front()[0]) !=
               std::string::npos) {
      CalculateOperation(values);
    } else {
      values.push(std::stod(q_rpn_.front()));
    }
    q_rpn_.pop_front();
  }
  if (values.size() > 1 || values.empty()) {
    err_ = false;
  } else {
    return values.top();
  }
  return 0;
}

void MathModel::CalculateAlpha(std::stack<double>& values) {
  double temp;
  std::string operation = q_rpn_.front();
  if (values.empty()) {
    err_ = false;
    return;
  }
  temp = math_func_map_.at(operation)(values.top());
  values.pop();
  values.push(temp);
}

void MathModel::CalculateOperation(std::stack<double>& values) {
  std::string operation = q_rpn_.front();
  if (values.size() < 2) {
    err_ = false;
    return;
  }
  double num_2 = values.top();
  values.pop();
  double num_1 = values.top();
  values.pop();
  values.push(op_func_map_.at(operation[0])(num_1, num_2));
}

// Clear all
void MathModel::ClearAll() {
  q_temp_.clear();
  q_oper_.clear();
  q_rpn_.clear();
  err_ = true;
  brackets_ = 0;
  iter_ = 0;
}
}  // namespace s21

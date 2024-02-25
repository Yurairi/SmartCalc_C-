#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_H_

#include "Model.h"

namespace s21 {

class Controller {
 public:
  Controller();
  explicit Controller(s21::MathModel* m);

  std::string CalculateResult(const std::string& str, const std::string& x_num);

 private:
  s21::MathModel* model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_H_

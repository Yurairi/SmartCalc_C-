#include "Controller.h"

namespace s21 {

Controller::Controller() {}

Controller::Controller(s21::MathModel* m) : model_(m) {}

std::string Controller::CalculateResult(const std::string& str,
                                        const std::string& x_num) {
  model_->SetString(str);
  model_->SetX(x_num);
  return model_->GetResult();
}

}  // namespace s21

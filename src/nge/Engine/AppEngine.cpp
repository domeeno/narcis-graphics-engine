#include "AppEngine.hpp"

namespace nge {
AppEngine *AppEngine::Instance = nullptr;

AppEngine::AppEngine() {
  this->WindowManager = new Window();
}

void AppEngine::SwitchView() {
  if (this->view == NORMAL) {
    this->ViewWireframe();
    this->view = LINE;
  } else if (this->view == LINE) {
    this->ViewPoints();
    this->view = POINT;
  } else {
    this->ViewNormal();
    this->view = NORMAL;
  }
}

AppEngine::~AppEngine() { 
  this->Instance = nullptr; 
  delete this->WindowManager;
}

} // namespace nge

#include "AppEngine.hpp"

namespace nge{
  AppEngine *AppEngine::Instance = nullptr;

  AppEngine::AppEngine() {
    this->WindowManager = new Window();
  }

  AppEngine::~AppEngine() {
    this->Instance = nullptr;
  }
}

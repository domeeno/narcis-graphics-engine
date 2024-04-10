#ifndef UTILS_NO_COPY_H_
#define UTILS_NO_COPY_H_

namespace nge {
class NonCopyable {
protected:
  NonCopyable() = default;
  virtual ~NonCopyable() = default;

public:
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable(NonCopyable &&) = default;
  NonCopyable &operator=(const NonCopyable &) = delete;
  NonCopyable &operator=(NonCopyable &&) = default;
};
} // namespace nge

#endif // UTILS_NO_COPY_H_

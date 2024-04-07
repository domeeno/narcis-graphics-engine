#ifndef UTILS_NO_COPY_H_
#define UTILS_NO_COPY_H_

namespace nge {
class NoCopy {
protected:
  NoCopy() = default;
  virtual ~NoCopy() = default;

public:
  NoCopy(const NoCopy &) = delete;
  NoCopy(NoCopy &&) = default;
  NoCopy &operator=(const NoCopy &) = delete;
  NoCopy &operator=(NoCopy &&) = default;
};
} // namespace nge

#endif // UTILS_NO_COPY_H_

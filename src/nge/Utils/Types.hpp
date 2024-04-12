#ifndef UTILS_TYPES_H_
#define UTILS_TYPES_H_

#include <cstdint>
#include <string>

typedef float f32;
typedef double f64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
#define PI 3.141592f;
typedef std::string GLSL;
typedef const char *GLSLC;

namespace nge {
typedef enum {
    XZ_PLANE,
    XY_PLANE,
    YZ_PLANE,
} Plane;

typedef enum {
  NORMAL,
  POINT,
  LINE,
} View;
} // namespace nge

#endif // UTILS_TYPES_H_

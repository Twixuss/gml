#pragma once
#include <corecrt_math.h> // sqrt
#include "Vector_Scalar.h"
#ifndef GML_NO_INTRIN
#include "Vector_SSE.h"
#endif
namespace gml {
   GML_CI float  Sqrt(float  x, float  curr, float  prev) noexcept { return curr == prev ? curr : Sqrt(x, 0.5f * (curr + x / curr), curr); }
   GML_CI double Sqrt(double x, double curr, double prev) noexcept { return curr == prev ? curr : Sqrt(x, 0.5 * (curr + x / curr), curr); }
   GML_CI Vec2<float> Sqrt(Vec2<float> x, Vec2<float> curr, Vec2<float> prev) noexcept { return curr == prev ? curr : Sqrt(x, (curr + x / curr) * 0.5f, curr); }
   GML_CI Vec3<float> Sqrt(Vec3<float> x, Vec3<float> curr, Vec3<float> prev) noexcept { return curr == prev ? curr : Sqrt(x, (curr + x / curr) * 0.5f, curr); }
#ifdef GML_NO_INTRIN
   GML_CI Vec4<float> Sqrt(Vec4<float> x, Vec4<float> curr, Vec4<float> prev) noexcept { return curr == prev ? curr : Sqrt(x, (curr + x / curr) * 0.5f, curr); }
#endif

   template<class T> GML_CI T Sqrt(T x) { return x >= 0 && x < std::numeric_limits<T>::infinity() ? Sqrt<T>(x, x, static_cast<T>(0)) : std::numeric_limits<T>::quiet_NaN(); }
   template<> GML_I float Sqrt<float>(float x) { return sqrtf(x); }
   template<> GML_I double Sqrt<double>(double x) { return sqrt(x); }
   template<class T> GML_CI T Dot(const Vec1<T>& a, const Vec1<T>& b) noexcept { return a[0] * b[0]; }
   template<class T> GML_CI T Dot(const Vec2<T>& a, const Vec2<T>& b) noexcept { return a[0] * b[0] + a[1] * b[1]; }
   template<class T> GML_CI T Dot(const Vec3<T>& a, const Vec3<T>& b) noexcept { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
   template<class T> GML_CI T Dot(const Vec4<T>& a, const Vec4<T>& b) noexcept { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]; }
   template<class T> GML_CI T LengthSqr(const Vec2<T>& v) noexcept { return Dot<T>(v, v); }
   template<class T> GML_CI T LengthSqr(const Vec3<T>& v) noexcept { return Dot<T>(v, v); }
   template<class T> GML_CI T LengthSqr(const Vec4<T>& v) noexcept { return Dot<T>(v, v); }
   template<class T> GML_I T Length(const Vec2<T>& v) noexcept { return Sqrt(LengthSqr(v)); }
   template<class T> GML_I T Length(const Vec3<T>& v) noexcept { return Sqrt(LengthSqr(v)); }
   template<class T> GML_I T Length(const Vec4<T>& v) noexcept { return Sqrt(LengthSqr(v)); }
   template<class T> GML_I Vec2<T> Normalize(const Vec2<T>& v) noexcept { return v / Length(v); }
   template<class T> GML_I Vec3<T> Normalize(const Vec3<T>& v) noexcept { return v / Length(v); }
   template<class T> GML_I Vec4<T> Normalize(const Vec4<T>& v) noexcept { return v / Length(v); }
   template<class T> GML_CI auto Distance(const Vec3<T>& a, const Vec3<T>& b) noexcept { return Length(a - b); }
   template<class T> GML_CI Vec3<T> Cross(const Vec3<T>& a, const Vec3<T>& b) noexcept {
      return {
         a.y * b.z - a.z * b.y,
         a.z * b.x - a.x * b.z,
         a.x * b.y - a.y * b.x
      };
   }
}

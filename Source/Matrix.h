#pragma once
#include "Matrix_Scalar.h"
#ifndef GML_NO_INTRIN
#include "Matrix_SSE.h"
#endif
namespace gml {
   template<class T>
   GML_CI Matrix4x4<T> Transpose(const Matrix4x4<T>& a) noexcept {
      return {
         a[0][0], a[1][0], a[2][0], a[3][0],
         a[0][1], a[1][1], a[2][1], a[3][1],
         a[0][2], a[1][2], a[2][2], a[3][2],
         a[0][3], a[1][3], a[2][3], a[3][3]
      };
   }
   template<class T>
   GML_CI Matrix4x4<T> Translation(T x, T y, T z) noexcept {
      return
      {
         1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         x, y, z, 1
      };
   }
   template<class T>
   GML_CI Matrix4x4<T> Translation(const Vec3<T>& v) noexcept { return Translation(v.x, v.y, v.z); }

   template<class T, int D = 4> GML_CI Matrix4x4<T> RotationX(T a) noexcept { static_assert(false, "Can't create matrix with this type or/and dimensions"); }
   template<class T, int D = 4> GML_CI Matrix4x4<T> RotationY(T a) noexcept { static_assert(false, "Can't create matrix with this type or/and dimensions"); }
   template<class T, int D = 4> GML_CI Matrix4x4<T> RotationZ(T a) noexcept { static_assert(false, "Can't create matrix with this type or/and dimensions"); }
   template<> GML_I Matrix4x4<float> RotationX<float, 4>(float a) noexcept {
      return {
         1, 0,       0,       0,
         0, cosf(a),-sinf(a), 0,
         0, sinf(a), cosf(a), 0,
         0, 0,       0,       1,
      };
   }
   template<> GML_I Matrix4x4<float> RotationY<float, 4>(float a) noexcept {
      return {
         cosf(a), 0,-sinf(a), 0,
         0,       1, 0,       0,
         sinf(a), 0, cosf(a), 0,
         0,       0, 0,       1,
      };
   }
   template<> GML_I Matrix4x4<float> RotationZ<float, 4>(float a) noexcept {
      return {
         cosf(a), sinf(a), 0, 0,
        -sinf(a), cosf(a), 0, 0,
         0,       0,       1, 0,
         0,       0,       0, 1
      };
   }
   template<> GML_CI Matrix4x4<double> RotationX<double, 4>(double a) noexcept {
      return {
         1, 0,      0,      0,
         0, cos(a), sin(a), 0,
         0,-sin(a), cos(a), 0,
         0, 0,      0,      1,
      };
   }
   template<> GML_CI Matrix4x4<double> RotationY<double, 4>(double a) noexcept {
      return {
         cos(a), 0,-sin(a), 0,
         0,      1, 0,      0,
         sin(a), 0, cos(a), 0,
         0,      0, 0,      1,
      };
   }
   template<> GML_CI Matrix4x4<double> RotationZ<double, 4>(double a) noexcept {
      return {
         cos(a),-sin(a), 0, 0,
         sin(a), cos(a), 0, 0,
         0,      0,      1, 0,
         0,      0,      0, 1
      };
   }
   template<class T, int D = 4, GML_ENABLE_IF_NUMBER(T)> GML_CI auto RotationZXY(T x, T y, T z) noexcept { return (RotationY<T, D>(y) * RotationX<T, D>(x)) * RotationZ<T, D>(z); }
   template<class T, int D = 4, GML_ENABLE_IF_NUMBER(T)> GML_CI auto RotationYXZ(T x, T y, T z) noexcept { return (RotationZ<T, D>(z) * RotationX<T, D>(x)) * RotationY<T, D>(y); }
   template<class T, int D = 4> GML_CI auto RotationZXY(const Vec3<T> & v) noexcept { return (RotationY<T, D>(v.y) * RotationX<T, D>(v.x)) * RotationZ<T, D>(v.z); }
   template<class T, int D = 4> GML_CI auto RotationYXZ(const Vec3<T> & v) noexcept { return (RotationZ<T, D>(v.z) * RotationX<T, D>(v.x)) * RotationY<T, D>(v.y); }
   template<class T, int D = 4> GML_CI static Matrix4x4<T> Scaling(T x, T y, T z) noexcept { static_assert(false, "Can't create matrix with this type or/and dimensions"); }
#ifdef GML_NO_INTRIN
   template<> GML_CI static Matrix4x4<float> Scaling<float, 4>(float x, float y, float z) noexcept {
      return {
         x, 0, 0, 0,
         0, y, 0, 0,
         0, 0, z, 0,
         0, 0, 0, 1
      };
   }
#else
   template<> GML_I static Matrix4x4<float> Scaling<float, 4>(float x, float y, float z) noexcept {
      return {
         _gml_set_ps(x, 0, 0, 0),
         _gml_set_ps(0, y, 0, 0),
         _gml_set_ps(0, 0, z, 0),
         _gml_set_ps(0, 0, 0, 1)
      };
   }
#endif
   template<class T, int D = 4> GML_CI static Matrix4x4<T> Scaling(const Vec3<T> & v) noexcept { return Scaling<T, 4>(v.x, v.y, v.z); }
}
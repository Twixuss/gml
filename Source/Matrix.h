#pragma once
#include "Array.h"
#include "Quaternion.h"
namespace gml {
   GML_CI Array<Vector4<float>, 4> _GetArrayFromQuaternion(const Quaternion<float> & q) noexcept {
      float sqx = q.x * q.x;
      float sqy = q.y * q.y;
      float sqz = q.z * q.z;
      return {
         Vector4<float>{ 1.0f - 2.0f * sqy - 2.0f * sqz,      2.0f * q.x * q.y - 2.0f * q.z * q.w, 2.0f * q.x * q.z + 2.0f * q.y * q.w, 0.0f },
         Vector4<float>{ 2.0f * q.x * q.y + 2.0f * q.z * q.w, 1.0f - 2.0f * sqx - 2.0f * sqz,      2.0f * q.y * q.z - 2.0f * q.x * q.w, 0.0f },
         Vector4<float>{ 2.0f * q.x * q.z - 2.0f * q.y * q.w, 2.0f * q.y * q.z + 2.0f * q.x * q.w, 1.0f - 2.0f * sqx - 2.0f * sqy,      0.0f },
         Vector4<float>{ 0.0f,                                0.0f,                                0.0f,                                1.0f }
      };
   }
   GML_CI Array<Vector4<double>, 4> _GetArrayFromQuaternion(const Quaternion<double>& q) noexcept {
      double sqx = q.x * q.x;
      double sqy = q.y * q.y;
      double sqz = q.z * q.z;
      return {
         Vector4<double>{ 1.0 - 2.0 * sqy - 2.0 * sqz,       2.0 * q.x * q.y - 2.0 * q.z * q.w, 2.0 * q.x * q.z + 2.0 * q.y * q.w, 0.0 },
         Vector4<double>{ 2.0 * q.x * q.y + 2.0 * q.z * q.w, 1.0 - 2.0 * sqx - 2.0 * sqz,       2.0 * q.y * q.z - 2.0 * q.x * q.w, 0.0 },
         Vector4<double>{ 2.0 * q.x * q.z - 2.0 * q.y * q.w, 2.0 * q.y * q.z + 2.0 * q.x * q.w, 1.0 - 2.0 * sqx - 2.0 * sqy,       0.0 },
         Vector4<double>{ 0.0,                               0.0,                               0.0,                               1.0 }
      };
   }
   template<class T>
   struct Matrix4x4 {
      GML_CI Matrix4x4() noexcept : array({ Vector4<T>{ (T)1,0,0,0 }, Vector4<T>{ 0,(T)1,0,0 }, Vector4<T>{ 0,0,(T)1,0 }, Vector4<T>{ 0,0,0,(T)1 } }) {}
      GML_CI Matrix4x4(
         T ix, T iy, T iz, T iw, 
         T jx, T jy, T jz, T jw,
         T kx, T ky, T kz, T kw,
         T lx, T ly, T lz, T lw) noexcept : array({
            Vector4<T>{ ix,iy,iz,iw },
            Vector4<T>{ jx,jy,jz,jw },
            Vector4<T>{ kx,ky,kz,kw },
            Vector4<T>{ kx,ky,kz,kw }
            }) {
      }
      GML_CI Matrix4x4(const Vector4<T>& i, const Vector4<T>& j, const Vector4<T>& k, const Vector4<T>& l) noexcept : array({i,j,k,l}) {}
      GML_CI Matrix4x4(const Quaternion<T>& q) noexcept : array(_GetArrayFromQuaternion(q)) {}
      Array<Vector4<T>, 4> array;
      GML_CI Vector4<T>& operator[](int i) noexcept { return array[i]; }
      GML_CI const Vector4<T>& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T>
   GML_CI Vector4<T> operator*(const Matrix4x4<T>& a, const Vector4<T>& b) noexcept {
      return
      {
         a[0][0] * b[0] + a[1][0] * b[1] + a[2][0] * b[2] + a[3][0] * b[3],
         a[0][1] * b[0] + a[1][1] * b[1] + a[2][1] * b[2] + a[3][1] * b[3],
         a[0][2] * b[0] + a[1][2] * b[1] + a[2][2] * b[2] + a[3][2] * b[3],
         a[0][3] * b[0] + a[1][3] * b[1] + a[2][3] * b[2] + a[3][3] * b[3]
      };
   }
   template<class T>
   GML_CI Matrix4x4<T> operator*(const Matrix4x4<T>& a, const Matrix4x4<T>& b) noexcept {
      return
      {
         a * b[0],
         a * b[1],
         a * b[2],
         a * b[3]
      };
   }
   template<class T>
   GML_CI Matrix4x4<T>& operator*=(Matrix4x4<T>& a, const Matrix4x4<T>& b) noexcept {
      a = a * b;
      return a;
   }
}
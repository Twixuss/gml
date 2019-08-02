#pragma once
#include "Array.h"
#include "Quaternion.h"
namespace gml {
   namespace internal {
      GML_CI Array<Array<float, 4>, 4> GetArrayFromQuaternion(const Quaternion<float> & q) {
         float sqx = q.x * q.x;
         float sqy = q.y * q.y;
         float sqz = q.z * q.z;
         return {
            { 1.0f - 2.0f * sqy - 2.0f * sqz,      2.0f * q.x * q.y - 2.0f * q.z * q.w, 2.0f * q.x * q.z + 2.0f * q.y * q.w, 0.0f },
            { 2.0f * q.x * q.y + 2.0f * q.z * q.w, 1.0f - 2.0f * sqx - 2.0f * sqz,      2.0f * q.y * q.z - 2.0f * q.x * q.w, 0.0f },
            { 2.0f * q.x * q.z - 2.0f * q.y * q.w, 2.0f * q.y * q.z + 2.0f * q.x * q.w, 1.0f - 2.0f * sqx - 2.0f * sqy,      0.0f },
            { 0.0f,                                0.0f,                                0.0f,                                1.0f }
         };
      }
      GML_CI Array<Array<double, 4>, 4> GetArrayFromQuaternion(const Quaternion<double>& q){
         double sqx = q.x * q.x;
         double sqy = q.y * q.y;
         double sqz = q.z * q.z;
         return {
            { 1.0 - 2.0 * sqy - 2.0 * sqz,       2.0 * q.x * q.y - 2.0 * q.z * q.w, 2.0 * q.x * q.z + 2.0 * q.y * q.w, 0.0 },
            { 2.0 * q.x * q.y + 2.0 * q.z * q.w, 1.0 - 2.0 * sqx - 2.0 * sqz,       2.0 * q.y * q.z - 2.0 * q.x * q.w, 0.0 },
            { 2.0 * q.x * q.z - 2.0 * q.y * q.w, 2.0 * q.y * q.z + 2.0 * q.x * q.w, 1.0 - 2.0 * sqx - 2.0 * sqy,       0.0 },
            { 0.0,                               0.0,                               0.0,                               1.0 }
         };
      }
   }
   template<class T>
   struct Matrix4x4 {
      GML_CI Matrix4x4() = default;
      GML_CI Matrix4x4(const Quaternion<T>& q) noexcept : array(GetArrayFromQuaternion(q)) {}
      Array<Array<T, 4>, 4> array;
   };
}
#pragma once
#include <corecrt_math.h> // trig
#include "Vector.h" // from euler
#include "Traits.h" // IsArithmetic
namespace gml {
   template<class T>
   struct Quaternion {
      static_assert(IsArithmetic<T>, "gml::Quaternion's template param must be arithmetic");
      T x, y, z, w;
   };
   template<class T> Quaternion<T> operator/(const Quaternion<T>& q, T v) {
      return { q.x / v, q.y / v, q.z / v, q.w / v };
   }
   Quaternion<float> Euler(const Vector3<float>& angles){
      float cy = cosf(angles[0] * 0.5f);
      float sy = sinf(angles[0] * 0.5f);
      float cp = cosf(angles[1] * 0.5f);
      float sp = sinf(angles[1] * 0.5f);
      float cr = cosf(angles[2] * 0.5f);
      float sr = sinf(angles[2] * 0.5f);
      return {
         cy * cp * sr - sy * sp * cr,
         sy * cp * sr + cy * sp * cr,
         sy * cp * cr - cy * sp * sr,
         cy * cp * cr + sy * sp * sr
      };
   }
   Quaternion<double> Euler(const Vector3<double>& angles) {
      double cy = cos(angles[0] * 0.5);
      double sy = sin(angles[0] * 0.5);
      double cp = cos(angles[1] * 0.5);
      double sp = sin(angles[1] * 0.5);
      double cr = cos(angles[2] * 0.5);
      double sr = sin(angles[2] * 0.5);
      return {
         cy * cp * sr - sy * sp * cr,
         sy * cp * sr + cy * sp * cr,
         sy * cp * cr - cy * sp * sr,
         cy * cp * cr + sy * sp * sr
      };
   }
   Quaternion<float> Normalize(const Quaternion<float>& q) {
      float n = sqrtf(q.x + q.y + q.z + q.w);
      return q / n;
   }
   Quaternion<double> Normalize(const Quaternion<double>& q) {
      double n = sqrt(q.x + q.y + q.z + q.w);
      return q / n;
   }
}
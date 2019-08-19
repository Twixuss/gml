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
   template<class T, GML_ENABLE_IF_NUMBER(T)>
   inline Quaternion<T> Euler(T yaw, T pitch, T roll){
      float cx = cosf(roll *  0.5f);
      float sx = sinf(roll *  0.5f);
      float cy = cosf(pitch * -0.5f);
      float sy = sinf(pitch * -0.5f);
      float cz = cosf(yaw *  0.5f);
      float sz = sinf(yaw *  0.5f);
      return {
         cx * cy * sz - sx * sy * cz,
         sx * cy * sz + cx * sy * cz,
         sx * cy * cz - cx * sy * sz,
         cx * cy * cz + sx * sy * sz
      };
   }
   template<class T>
   inline Quaternion<T> Euler(const Vec3<T>& a) { return Euler<T>(a.x, a.y, a.z); }
   inline Quaternion<float> Normalize(const Quaternion<float>& q) {
      float n = sqrtf(q.x + q.y + q.z + q.w);
      return q / n;
   }
   inline Quaternion<double> Normalize(const Quaternion<double>& q) {
      double n = sqrt(q.x + q.y + q.z + q.w);
      return q / n;
   }
}
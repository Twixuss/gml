#pragma once
#include "Vector.h"
namespace gml {
   template<class T>
   struct AABB3 {
      Vec3<T> a, b;
      AABB3(const Vec3<T>& min, const Vec3<T>& max) : a(min), b(max) {}
      bool Contains(const gml::Vec3<float>& p) {
         return
            a.x < p.x && p.x < b.x &&
            a.y < p.y && p.y < b.y &&
            a.z < p.z && p.z < b.z;
      }
      bool Intersects(const AABB3& o) {
         return !(
            b.x < o.a.x || o.b.x < a.x ||
            b.y < o.a.y || o.b.y < a.y ||
            b.z < o.a.z || o.b.z < a.z);
      }
   };
}

#pragma once
#include "Matrix_Scalar.h"
namespace gml {
   GML_I Array<Vec4<float>, 4> _GetArrayFromQuaternion(const Quaternion<float>& q) noexcept {
      float sqx = q.x * q.x;
      float sqy = q.y * q.y;
      float sqz = q.z * q.z;
      return {
         Vec4<float>{ 1.0f - 2.0f * (sqy + sqz),      2.0f * (q.x * q.y - q.z * q.w), 2.0f * (q.x * q.z + q.y * q.w), 0.0f },
         Vec4<float>{ 2.0f * (q.x * q.y + q.z * q.w), 1.0f - 2.0f * (sqx + sqz),      2.0f * (q.y * q.z - q.x * q.w), 0.0f },
         Vec4<float>{ 2.0f * (q.x * q.z - q.y * q.w), 2.0f * (q.y * q.z + q.x * q.w), 1.0f - 2.0f * (sqx + sqy),      0.0f },
         Vec4<float>{ 0.0f,                           0.0f,                           0.0f,                           1.0f }
      };
   }
   template<>
   struct Matrix4x4<float> {
      union {
         Array<Vec4<float>, 4> _arr;
         Vec4<float> _v[4];
         struct {
            __m128 _m0;
            __m128 _m1;
            __m128 _m2;
            __m128 _m3;
         };
      };
      GML_I Matrix4x4() noexcept :
         _m0(_gml_set_ps(1.f,0.f,0.f,0.f)),
         _m1(_gml_set_ps(0.f,1.f,0.f,0.f)),
         _m2(_gml_set_ps(0.f,0.f,1.f,0.f)),
         _m3(_gml_set_ps(0.f,0.f,0.f,1.f)) 
      {
      }
      GML_CI Matrix4x4(const Matrix4x4<float>& m) noexcept :
         _m0(m._m0),
         _m1(m._m1),
         _m2(m._m2),
         _m3(m._m3) {
      }
      GML_I Matrix4x4(
         float ix, float iy, float iz, float iw,
         float jx, float jy, float jz, float jw,
         float kx, float ky, float kz, float kw,
         float lx, float ly, float lz, float lw) noexcept : 
            _m0(_gml_set_ps(ix,iy,iz,iw)),
            _m1(_gml_set_ps(jx,jy,jz,jw)),
            _m2(_gml_set_ps(kx,ky,kz,kw)),
            _m3(_gml_set_ps(lx,ly,lz,lw))
      {
      }
      GML_CI Matrix4x4(
         const Vec4<float>& i, 
         const Vec4<float>& j,
         const Vec4<float>& k, 
         const Vec4<float>& l) noexcept : 
         _m0(i._m),
         _m1(j._m),
         _m2(k._m),
         _m3(l._m)
      {}
      GML_CI Matrix4x4(__m128 i, __m128 j, __m128 k, __m128 l) noexcept :
         _m0(i),
         _m1(j),
         _m2(k),
         _m3(l)
      {}
      GML_I Matrix4x4(const Quaternion<float>& q) noexcept : _arr(_GetArrayFromQuaternion(q)) {}
      GML_CI Vec4<float>& operator[](int i) noexcept { return _v[i]; }
      GML_CI const Vec4<float>& operator[](int i) const noexcept { return _v[i]; }
   };
   GML_I __m128 _gml_dot4_ps(__m128 x, __m128 y) {
      __m128 multi = _gml_mul_ps(x, y); 
      __m128 shuf = _gml_permute_ps(multi, GML_SHUFFLE(1,0,3,0));
      __m128 add = _gml_add_ps(shuf, multi);
      return _gml_add_ss(add, _gml_movehl_ps(shuf, add));
   }
   GML_I Vec4<float> operator*(const Matrix4x4<float>& a, const Vec4<float>& b) noexcept {
      __m128 dx = _gml_dot4_ps(a._m0, b._m);
      __m128 dy = _gml_dot4_ps(a._m1, b._m);
      __m128 dz = _gml_dot4_ps(a._m2, b._m);
      __m128 dw = _gml_dot4_ps(a._m3, b._m);
      return _gml_blend_ps(
         _gml_shuffle_ps(dx, dz, GML_SHUFFLE(0, 0, 0, 0)), 
         _gml_shuffle_ps(dy, dw, GML_SHUFFLE(0, 0, 0, 0)), 
         GML_BLEND(1, 0, 1, 0)
      );
   }
   GML_I Matrix4x4<float> operator*(const Matrix4x4<float>& a, const Matrix4x4<float>& b) noexcept {
      return {
         _gml_madd_ps(a._m3, _gml_permute_ps(b._m0, GML_SHUFFLE(3,3,3,3)), _gml_madd_ps(a._m2, _gml_permute_ps(b._m0, GML_SHUFFLE(2, 2, 2, 2)), _gml_madd_ps(a._m1, _gml_permute_ps(b._m0, GML_SHUFFLE(1, 1, 1, 1)), _gml_mul_ps (a._m0, _gml_permute_ps(b._m0, GML_SHUFFLE(0, 0, 0, 0)))))),
         _gml_madd_ps(a._m3, _gml_permute_ps(b._m1, GML_SHUFFLE(3,3,3,3)), _gml_madd_ps(a._m2, _gml_permute_ps(b._m1, GML_SHUFFLE(2, 2, 2, 2)), _gml_madd_ps(a._m1, _gml_permute_ps(b._m1, GML_SHUFFLE(1, 1, 1, 1)), _gml_mul_ps (a._m0, _gml_permute_ps(b._m1, GML_SHUFFLE(0, 0, 0, 0)))))),
         _gml_madd_ps(a._m3, _gml_permute_ps(b._m2, GML_SHUFFLE(3,3,3,3)), _gml_madd_ps(a._m2, _gml_permute_ps(b._m2, GML_SHUFFLE(2, 2, 2, 2)), _gml_madd_ps(a._m1, _gml_permute_ps(b._m2, GML_SHUFFLE(1, 1, 1, 1)), _gml_mul_ps (a._m0, _gml_permute_ps(b._m2, GML_SHUFFLE(0, 0, 0, 0)))))),
         _gml_madd_ps(a._m3, _gml_permute_ps(b._m3, GML_SHUFFLE(3,3,3,3)), _gml_madd_ps(a._m2, _gml_permute_ps(b._m3, GML_SHUFFLE(2, 2, 2, 2)), _gml_madd_ps(a._m1, _gml_permute_ps(b._m3, GML_SHUFFLE(1, 1, 1, 1)), _gml_mul_ps (a._m0, _gml_permute_ps(b._m3, GML_SHUFFLE(0, 0, 0, 0))))))
      };
   }

   GML_I Matrix4x4<float> Transpose(const Matrix4x4<float>& m) noexcept {
      __m128 t0 = _mm_shuffle_ps(m._m0, m._m1, 0x44);
      __m128 t2 = _mm_shuffle_ps(m._m0, m._m1, 0xEE);
      __m128 t1 = _mm_shuffle_ps(m._m2, m._m3, 0x44);
      __m128 t3 = _mm_shuffle_ps(m._m2, m._m3, 0xEE);
      return {
         _mm_shuffle_ps(t0, t1, 0x88),
         _mm_shuffle_ps(t0, t1, 0xDD),
         _mm_shuffle_ps(t2, t3, 0x88),
         _mm_shuffle_ps(t2, t3, 0xDD)
      };
   }
}
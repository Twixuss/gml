#pragma once
#include <intrin.h>
#include "Vector_Scalar.h"
#define GML_ALIGN(x) __declspec(align(x))
#define _gml_set_ps(x,y,z,w) _mm_set_ps(w,z,y,x)
#define _gml_madd_ps(x,y,z) _mm_add_ps(_mm_mul_ps(x,y), z)
#define _gml_add_ps(x,y) _mm_add_ps(x,y)
#define _gml_sub_ps(x,y) _mm_sub_ps(x,y)
#define _gml_mul_ps(x,y) _mm_mul_ps(x,y)
#define _gml_div_ps(x,y) _mm_div_ps(x,y)
#define _gml_add_ss(x,y) _mm_add_ss(x,y)
#define _gml_sub_ss(x,y) _mm_sub_ss(x,y)
#define _gml_mul_ss(x,y) _mm_mul_ss(x,y)
#define _gml_div_ss(x,y) _mm_div_ss(x,y)
#define _gml_movehl_ps(x,y) _mm_movehl_ps(x,y)
#define _gml_identity_mask 228
#define _gml_permute_ps(x,y) _mm_shuffle_ps(x,x,y)
#define _gml_shuffle_ps(x,y,z) _mm_shuffle_ps(x,y,z)
#define _gml_blend_ps(x,y,z) _mm_blend_ps(x,y,z)
#define GML_SHUFFLE(x,y,z,w) (((w) << 6) | ((z) << 4) | ((y) << 2) | (x))
#define GML_SHUFFLE2(x,y,z,w,a,b,c,d) ((((57 * a) & 3) << (x << 1)) |  \
                                       (((57 * b) & 3) << (y << 1)) |  \
                                       (((57 * c) & 3) << (z << 1)) |  \
                                       (((57 * d) & 3) << (w << 1)))
#define GML_BLEND(X, Y, Z, W)		(~((X) | ((Y) << 1) | ((Z) << 2) | ((W) << 3)) & 0xF)
namespace gml {
   template<int X, int Y, int Z, int W>
   struct GML_ALIGN(16) Swizzle4<float, 4, X, Y, Z, W> {
      union {
         __m128 _m;
         Array<float, 4> _arr;
         float _data[4];
      };
      GML_C Swizzle4& operator=(const Vec4<float>& v) noexcept { GML_CHECK4(X, Y, Z, W); _m = _gml_permute_ps(v._m, GML_SHUFFLE(X, Y, Z, W)); return *this; }
      template<int S, int A, int B, int C, int D> GML_C Swizzle4& operator=(const Swizzle4<float, S, A, B, C, D>& s) noexcept { GML_CHECK4(X, Y, Z, W); _m = _gml_set_ps(s._arr[A], s._arr[B], s._arr[C], s._arr[D]); return *this; }
      template<       int A, int B, int C, int D> GML_C Swizzle4& operator=(const Swizzle4<float, 4, A, B, C, D>& s) noexcept { GML_CHECK4(X, Y, Z, W); _m = _gml_permute_ps(s._m, GML_SHUFFLE2(X, Y, Z, W, A, B, C, D)); return *this; }
   };
   template<>
   struct GML_ALIGN(16) Vec4<float> {
      union {
         __m128 _m;
         Array<float, 4> _arr;
         float _data[4];
         GML_SWIZZLE_XYZW(float);
      };
      explicit operator float*() { return _data; }
      GML_I Vec4() : _m(_mm_setzero_ps()) {}
      GML_I Vec4(__m128 m) : _m(m) {}
      GML_I Vec4(const Vec4<float>& v) : _m(v._m) {}
      GML_I Vec4(const Vec1<float>& v) : _m(_mm_set_ps1(v[0])) {}
      GML_I Vec4(const Vec3<float>& xyz, const Vec1<float>& w) : _m(_gml_set_ps(xyz._data[0], xyz._data[1], xyz._data[2], w._data[0])) {}
      GML_I Vec4(const Vec1<float>& x, const Vec3<float>& yzw) : _m(_gml_set_ps(x._data[0], yzw._data[0], yzw._data[1], yzw._data[2])) {}
      GML_I Vec4(const Vec2<float>& xy, const Vec2<float>& zw) : _m(_gml_set_ps(xy._data[0], xy._data[1], zw._data[0], zw._data[1])) {}
      GML_I Vec4(const Vec2<float>& xy, const Vec1<float>& z, const Vec1<float>& w) : _m(_gml_set_ps(xy._data[0], xy._data[1], z._data[0], w._data[0])) {}
      GML_I Vec4(const Vec1<float>& x, const Vec2<float>& yz, const Vec1<float>& w) : _m(_gml_set_ps(x._data[0], yz._data[0], yz._data[1], w._data[0])) {}
      GML_I Vec4(const Vec1<float>& x, const Vec1<float>& y, const Vec2<float>& zw) : _m(_gml_set_ps(x._data[0], y._data[0], zw._data[0], zw._data[1])) {}
      GML_I Vec4(const Vec1<float>& x, const Vec1<float>& y, const Vec1<float>& z, const Vec1<float>& w) : _m(_gml_set_ps(x._data[0], y._data[0], z._data[0], w._data[0])) {}
      template<int S, int X, int Y, int Z, int W>                              GML_I Vec4(const Swizzle4<float, S, X, Y, Z, W>& v) noexcept : _m(_gml_set_ps(v._data[X], v._data[Y], v._data[Z], v._data[W])) {}
      template<int X, int Y, int Z, int W>                                     GML_I Vec4(const Swizzle4<float, 4, X, Y, Z, W>& v) noexcept : _m(_gml_permute_ps(v._m, GML_SHUFFLE(X, Y, Z, W))) {}
      template<int S1, int X1>                                                 GML_I Vec4(const Swizzle1<float, S1, X1>& v) noexcept : _m(_gml_set_ps(v._data[X1], v._data[X1], v._data[X1], v._data[X1])) {}
      template<int S1, int X1, int Y1, int Z1, int S2, int X2>                 GML_I Vec4(const Swizzle3<float, S1, X1, Y1, Z1>& xyz, const Swizzle1<float, S2, X2>& w) noexcept : _m(_gml_set_ps(xyz._data[X1], xyz._data[Y1], xyz._data[Z1], w._data[X2])) {}
      template<int S1, int X1, int S2, int X2, int Y2, int Z2>                 GML_I Vec4(const Swizzle1<float, S1, X1>& x, const Swizzle3<float, S2, X2, Y2, Z2>& yzw) noexcept : _m(_gml_set_ps(x._data[X1], yzw._data[X2], yzw._data[Y2], yzw._data[Z2])) {}
      template<int S1, int X1, int Y1, int S2, int X2, int Y2>                 GML_I Vec4(const Swizzle2<float, S1, X1, Y1>& xy, const Swizzle2<float, S2, X2, Y2>& zw) noexcept : _m(_gml_set_ps(xy._data[X1], xy._data[Y1], zw._data[X2], zw._data[Y2])) {}
      template<int S1, int X1, int Y1, int S2, int X2, int S3, int X3>         GML_I Vec4(const Swizzle2<float, S1, X1, Y1>& xy, const Swizzle1<float, S2, X2>& z, const Swizzle1<float, S3, X3>& w) noexcept : _m(_gml_set_ps(xy._data[X1], xy._data[Y1], z._data[X2], w._data[X3])) {}
      template<int S1, int X1, int S2, int X2, int Y2, int S3, int X3>         GML_I Vec4(const Swizzle1<float, S1, X1>& x, const Swizzle2<float, S2, X2, Y2>& yz, const Swizzle1<float, S3, X3>& w) noexcept : _m(_gml_set_ps(x._data[X1], yz._data[X2], yz._data[Y2], w._data[X3])) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3, int Y3>         GML_I Vec4(const Swizzle1<float, S1, X1>& x, const Swizzle1<float, S2, X2>& y, const Swizzle2<float, S3, X3, Y3>& zw) noexcept : _m(_gml_set_ps(x._data[X1], y._data[X2], zw._data[X3], zw._data[Y3])) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3, int S4, int X4> GML_I Vec4(const Swizzle1<float, S1, X1>& x, const Swizzle1<float, S2, X2>& y, const Swizzle1<float, S3, X3>& z, const Swizzle1<float, S4, X4>& w) noexcept : _m(_gml_set_ps(x._data[X1], y._data[X2], z._data[X3], w._data[X4])) {}
      template<class N1, GML_ENABLE_IF_NUMBER(N1)> GML_I Vec4(N1 v) noexcept : _m(_mm_set_ps1(float(v))) {}
      template<class N1, class N2, class N3, class N4, GML_ENABLE_IF_NUMBER4(N1, N2, N3, N4)> GML_I Vec4(N1 x, N2 y, N3 z, N4 w) noexcept : _m(_gml_set_ps(float(x), float(y), float(z), float(w))) {}
      GML_I float& operator[](int i) noexcept { GML_ASSERT(0 <= i && i < 4); return _data[i]; }
      GML_I const float& operator[](int i) const noexcept { GML_ASSERT(0 <= i && i < 4); return _data[i]; }
   };

   template<class T, class R> GML_I T _cast(R r) {
      static_assert(sizeof(T) == sizeof(R));
      union U {
         T t;
         R r;
         GML_I U(R r) : r(r) {}
      } u(r);
      return u.t;
   }

   const __m128 _m_0 = _mm_set_ps1(0.0f);
   const __m128 _m_minus1 = _mm_set_ps1(-1.0f);
   const __m128 _m_neg_mask = _mm_set_ps1(-0.0f);

   GML_I bool _equal(__m128 a, __m128 b) {
      __m128 r = _mm_cmpeq_ps(a, b);
      return r.m128_u64[0] & r.m128_u64[1];
   }
   GML_I Vec4<bool> _equalb(__m128 a, __m128 b) {
      __m128 r = _mm_cmpeq_ps(a, b);
      return { r.m128_u32[0], r.m128_u32[1], r.m128_u32[2], r.m128_u32[3] };
   }

   GML_I bool operator==(const Vec4<float>& a, const Vec4<float>& b) noexcept { return _equal(a._m, b._m);   }
   template<int S, int X, int Y, int Z, int W> GML_I bool operator==(const Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _equal(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<       int X, int Y, int Z, int W> GML_I bool operator==(const Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _equal(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I bool operator==(const Vec4<float>& a, U b) noexcept { return _equal(a._m, _mm_set_ps1((float)b)); }
   template<int S, int X, int Y, int Z, int W> GML_I bool operator==(const Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return b == a; }
   template<int S, int X, int Y, int Z, int W, int A, int B, int C, int D> GML_I bool operator==(const Swizzle4<float, S, X, Y, Z, W>& a, const Swizzle4<float, 4, A, B, C, D>& b) noexcept { return _equal(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), _gml_permute_ps(b._m, GML_SHUFFLE(A, B, C, D))); }
   template<int S, int X, int Y, int Z, int W, int A, int B, int C, int D> GML_I bool operator==(const Swizzle4<float, 4, X, Y, Z, W>& a, const Swizzle4<float, S, A, B, C, D>& b) noexcept { return _equal(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _gml_set_ps(b._data[A], b._data[B], b._data[C], b._data[D])); }
   template<int X, int Y, int Z, int W, int A, int B, int C, int D> GML_I bool operator==(const Swizzle4<float, 4, X, Y, Z, W>& a, const Swizzle4<float, 4, A, B, C, D>& b) noexcept { return _equal(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X, Y, Z, W, A, B, C, D))); }

   /* 1 gb of vec4. times (average ms) */
   /* sub: 90.42 */
   /* mul: 91.12 */
   /* xor: 92.44 */
#define _gml_neg_ps(x) _mm_xor_ps(_m_neg_mask, x)
   template<> GML_I Vec4<float> operator+<float>(const Vec4<float>& v) noexcept { return v._m; }
   template<> GML_I Vec4<float> operator-<float>(const Vec4<float>& v) noexcept { return _gml_neg_ps(v._m); }

   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Swizzle4<float, S, X, Y, Z, W>& v) noexcept { return _gml_set_ps(v._data[X], v._data[Y], v._data[Z], v._data[W]); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Swizzle4<float, S, X, Y, Z, W>& v) noexcept { return _gml_neg_ps(_gml_set_ps(v._data[X], v._data[Y], v._data[Z], v._data[W])); }
   template<int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X, Y, Z, W>& v) noexcept { return _gml_permute_ps(v._m, GML_SHUFFLE(X, Y, Z, W)); }
   template<int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X, Y, Z, W>& v) noexcept { return _gml_neg_ps(_gml_permute_ps(v._m, GML_SHUFFLE(X, Y, Z, W))); }
#pragma region .   Vector Vector
   template<> GML_I Vec4<float> operator+<float>(const Vec4<float>& a, const Vec1<float>& b) noexcept { return _mm_add_ps(a._m, _mm_set_ps1(b[0])); }
   template<> GML_I Vec4<float> operator-<float>(const Vec4<float>& a, const Vec1<float>& b) noexcept { return _mm_sub_ps(a._m, _mm_set_ps1(b[0])); }
   template<> GML_I Vec4<float> operator*<float>(const Vec4<float>& a, const Vec1<float>& b) noexcept { return _mm_mul_ps(a._m, _mm_set_ps1(b[0])); }
   template<> GML_I Vec4<float> operator/<float>(const Vec4<float>& a, const Vec1<float>& b) noexcept { return _mm_div_ps(a._m, _mm_set_ps1(b[0])); }
   template<> GML_I Vec4<float> operator+<float>(const Vec4<float>& a, const Vec4<float>& b) noexcept { return _mm_add_ps(a._m, b._m); }
   template<> GML_I Vec4<float> operator-<float>(const Vec4<float>& a, const Vec4<float>& b) noexcept { return _mm_sub_ps(a._m, b._m); }
   template<> GML_I Vec4<float> operator*<float>(const Vec4<float>& a, const Vec4<float>& b) noexcept { return _mm_mul_ps(a._m, b._m); }
   template<> GML_I Vec4<float> operator/<float>(const Vec4<float>& a, const Vec4<float>& b) noexcept { return _mm_div_ps(a._m, b._m); }
   template<> GML_I Vec4<float>& operator+=<float>(Vec4<float>& a, const Vec1<float>& b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<> GML_I Vec4<float>& operator-=<float>(Vec4<float>& a, const Vec1<float>& b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<> GML_I Vec4<float>& operator*=<float>(Vec4<float>& a, const Vec1<float>& b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<> GML_I Vec4<float>& operator/=<float>(Vec4<float>& a, const Vec1<float>& b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<> GML_I Vec4<float>& operator+=<float>(Vec4<float>& a, const Vec4<float>& b) noexcept { a._m = _mm_add_ps(a._m, b._m); return a; }
   template<> GML_I Vec4<float>& operator-=<float>(Vec4<float>& a, const Vec4<float>& b) noexcept { a._m = _mm_sub_ps(a._m, b._m); return a; }
   template<> GML_I Vec4<float>& operator*=<float>(Vec4<float>& a, const Vec4<float>& b) noexcept { a._m = _mm_mul_ps(a._m, b._m); return a; }
   template<> GML_I Vec4<float>& operator/=<float>(Vec4<float>& a, const Vec4<float>& b) noexcept { a._m = _mm_div_ps(a._m, b._m); return a; }
#pragma endregion
#pragma region .   Vector Swizzle
   template<int S, int X> GML_I Vec4<float> operator+(const Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { return _mm_add_ps(a._m, _mm_set_ps1(b._data[X])); }
   template<int S, int X> GML_I Vec4<float> operator-(const Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { return _mm_sub_ps(a._m, _mm_set_ps1(b._data[X])); }
   template<int S, int X> GML_I Vec4<float> operator*(const Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { return _mm_mul_ps(a._m, _mm_set_ps1(b._data[X])); }
   template<int S, int X> GML_I Vec4<float> operator/(const Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { return _mm_div_ps(a._m, _mm_set_ps1(b._data[X])); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_add_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_sub_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator*(const Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_mul_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator/(const Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_div_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_add_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_sub_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator*(const Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_mul_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator/(const Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_div_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<int S, int X> GML_I Vec4<float>& operator+=(Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1(b._data[X])); return a; }
   template<int S, int X> GML_I Vec4<float>& operator-=(Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1(b._data[X])); return a; }
   template<int S, int X> GML_I Vec4<float>& operator*=(Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1(b._data[X])); return a; }
   template<int S, int X> GML_I Vec4<float>& operator/=(Vec4<float>& a, const Swizzle1<float, S, X>& b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1(b._data[X])); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float>& operator+=(Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { a._m = _mm_add_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float>& operator-=(Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { a._m = _mm_sub_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float>& operator*=(Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { a._m = _mm_mul_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float>& operator/=(Vec4<float>& a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { a._m = _mm_div_ps(a._m, _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); return a; }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float>& operator+=(Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { a._m = _mm_add_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float>& operator-=(Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { a._m = _mm_sub_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float>& operator*=(Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { a._m = _mm_mul_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float>& operator/=(Vec4<float>& a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { a._m = _mm_div_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); return a; }
#pragma endregion
#pragma region .   Vector Scalar
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator+(const Vec4<float>& a, U b) noexcept { return _mm_add_ps(a._m, _mm_set_ps1((float)b)); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator-(const Vec4<float>& a, U b) noexcept { return _mm_sub_ps(a._m, _mm_set_ps1((float)b)); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator*(const Vec4<float>& a, U b) noexcept { return _mm_mul_ps(a._m, _mm_set_ps1((float)b)); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator/(const Vec4<float>& a, U b) noexcept { return _mm_div_ps(a._m, _mm_set_ps1((float)b)); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float>& operator+=(Vec4<float>& a, U b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1((float)b)); return a; }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float>& operator-=(Vec4<float>& a, U b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1((float)b)); return a; }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float>& operator*=(Vec4<float>& a, U b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1((float)b)); return a; }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float>& operator/=(Vec4<float>& a, U b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1((float)b)); return a; }
   GML_I Vec4<float> operator+(const Vec4<float>& a, float b) noexcept { return _mm_add_ps(a._m, _mm_set_ps1(b)); }
   GML_I Vec4<float> operator-(const Vec4<float>& a, float b) noexcept { return _mm_sub_ps(a._m, _mm_set_ps1(b)); }
   GML_I Vec4<float> operator*(const Vec4<float>& a, float b) noexcept { return _mm_mul_ps(a._m, _mm_set_ps1(b)); }
   GML_I Vec4<float> operator/(const Vec4<float>& a, float b) noexcept { return _mm_div_ps(a._m, _mm_set_ps1(b)); }
   GML_I Vec4<float>& operator+=(Vec4<float>& a, float b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1(b)); return a; }
   GML_I Vec4<float>& operator-=(Vec4<float>& a, float b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1(b)); return a; }
   GML_I Vec4<float>& operator*=(Vec4<float>& a, float b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1(b)); return a; }
   GML_I Vec4<float>& operator/=(Vec4<float>& a, float b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1(b)); return a; }
#pragma endregion
#pragma region .   Swizzle Vector
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_add_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_sub_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator*(const Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_mul_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); }
   template<int S, int X, int Y, int Z, int W> GML_I Vec4<float> operator/(const Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_div_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_add_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), b._m); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_sub_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), b._m); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator*(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_mul_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), b._m); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator/(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { return _mm_div_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), b._m); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { return _mm_add_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1(b[0])); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { return _mm_sub_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1(b[0])); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator*(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { return _mm_mul_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1(b[0])); }
   template<       int X, int Y, int Z, int W> GML_I Vec4<float> operator/(const Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { return _mm_div_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1(b[0])); }
   template<int S, int X, int Y, int Z, int W> GML_I Swizzle4<float, S, X, Y, Z, W>& operator+=(Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a = _mm_add_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Swizzle4<float, S, X, Y, Z, W>& operator-=(Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a = _mm_sub_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Swizzle4<float, S, X, Y, Z, W>& operator*=(Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a = _mm_mul_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); return a; }
   template<int S, int X, int Y, int Z, int W> GML_I Swizzle4<float, S, X, Y, Z, W>& operator/=(Swizzle4<float, S, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a = _mm_div_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), b._m); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator+=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a._m = _mm_add_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X, Y, Z, W, 0, 1, 2, 3))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator-=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a._m = _mm_sub_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X, Y, Z, W, 0, 1, 2, 3))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator*=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a._m = _mm_mul_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X, Y, Z, W, 0, 1, 2, 3))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator/=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec4<float>& b) noexcept { a._m = _mm_div_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X, Y, Z, W, 0, 1, 2, 3))); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator+=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator-=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator*=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1(b[0])); return a; }
   template<       int X, int Y, int Z, int W> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator/=(Swizzle4<float, 4, X, Y, Z, W>& a, const Vec1<float>& b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1(b[0])); return a; }
#pragma endregion
#pragma region .   Swizzle Swizzle
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { return _mm_add_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _mm_set_ps1(b._data[X2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { return _mm_sub_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _mm_set_ps1(b._data[X2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Vec4<float> operator*(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { return _mm_mul_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _mm_set_ps1(b._data[X2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Vec4<float> operator/(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { return _mm_div_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _mm_set_ps1(b._data[X2])); }
   template<int S, int X1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator+(const Swizzle1<float, S, X1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_add_ps(_mm_set_ps1(a._data[X1]), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int S, int X1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator-(const Swizzle1<float, S, X1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_sub_ps(_mm_set_ps1(a._data[X1]), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int S, int X1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator*(const Swizzle1<float, S, X1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_mul_ps(_mm_set_ps1(a._data[X1]), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int S, int X1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator/(const Swizzle1<float, S, X1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_div_ps(_mm_set_ps1(a._data[X1]), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, S, X2, Y2, Z2, W2>& b) noexcept { return _mm_add_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_set_ps(b._data[X2], b._data[Y2], b._data[Z2], b._data[W2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, S, X2, Y2, Z2, W2>& b) noexcept { return _mm_sub_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_set_ps(b._data[X2], b._data[Y2], b._data[Z2], b._data[W2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator*(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, S, X2, Y2, Z2, W2>& b) noexcept { return _mm_mul_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_set_ps(b._data[X2], b._data[Y2], b._data[Z2], b._data[W2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator/(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, S, X2, Y2, Z2, W2>& b) noexcept { return _mm_div_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_set_ps(b._data[X2], b._data[Y2], b._data[Z2], b._data[W2])); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator+(const Swizzle4<float, S, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_add_ps(_gml_set_ps(a._data[X1], a._data[Y1], a._data[Z1], a._data[W1]), _gml_permute_ps(b._m, GML_SHUFFLE(X1, Y1, Z1, W1))); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator-(const Swizzle4<float, S, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_sub_ps(_gml_set_ps(a._data[X1], a._data[Y1], a._data[Z1], a._data[W1]), _gml_permute_ps(b._m, GML_SHUFFLE(X1, Y1, Z1, W1))); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator*(const Swizzle4<float, S, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_mul_ps(_gml_set_ps(a._data[X1], a._data[Y1], a._data[Z1], a._data[W1]), _gml_permute_ps(b._m, GML_SHUFFLE(X1, Y1, Z1, W1))); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator/(const Swizzle4<float, S, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_div_ps(_gml_set_ps(a._data[X1], a._data[Y1], a._data[Z1], a._data[W1]), _gml_permute_ps(b._m, GML_SHUFFLE(X1, Y1, Z1, W1))); }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_add_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_sub_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator*(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_mul_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Vec4<float> operator/(const Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { return _mm_div_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X1, Y1, Z1, W1)), _gml_permute_ps(b._m, GML_SHUFFLE(X2, Y2, Z2, W2))); }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator+=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1(b._data[X2])); return a; }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator-=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1(b._data[X2])); return a; }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator*=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1(b._data[X2])); return a; }
   template<int S, int X1, int Y1, int Z1, int W1, int X2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator/=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle1<float, S, X2>& b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1(b._data[X2])); return a; }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator+=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { a._m = _mm_add_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X1,Y1,Z1,W1,X2,Y2,Z2,W2))); return a; }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator-=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { a._m = _mm_sub_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X1,Y1,Z1,W1,X2,Y2,Z2,W2))); return a; }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator*=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { a._m = _mm_mul_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X1,Y1,Z1,W1,X2,Y2,Z2,W2))); return a; }
   template<int X1, int Y1, int Z1, int W1, int X2, int Y2, int Z2, int W2> GML_I Swizzle4<float, 4, X1, Y1, Z1, W1>& operator/=(Swizzle4<float, 4, X1, Y1, Z1, W1>& a, const Swizzle4<float, 4, X2, Y2, Z2, W2>& b) noexcept { a._m = _mm_div_ps(a._m, _gml_permute_ps(b._m, GML_SHUFFLE2(X1,Y1,Z1,W1,X2,Y2,Z2,W2))); return a; }
#pragma endregion
#pragma region .   Swizzle Scalar
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator+(const Swizzle4<float, S, X, Y, Z, W>& a, U b) noexcept { return _mm_add_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), _mm_set_ps1((float)b)); }
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator-(const Swizzle4<float, S, X, Y, Z, W>& a, U b) noexcept { return _mm_sub_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), _mm_set_ps1((float)b)); }
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator*(const Swizzle4<float, S, X, Y, Z, W>& a, U b) noexcept { return _mm_mul_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), _mm_set_ps1((float)b)); }
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator/(const Swizzle4<float, S, X, Y, Z, W>& a, U b) noexcept { return _mm_div_ps(_gml_set_ps(a._data[X], a._data[Y], a._data[Z], a._data[W]), _mm_set_ps1((float)b)); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator+(const Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { return _mm_add_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1((float)b)); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator-(const Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { return _mm_sub_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1((float)b)); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator*(const Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { return _mm_mul_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1((float)b)); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator/(const Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { return _mm_div_ps(_gml_permute_ps(a._m, GML_SHUFFLE(X, Y, Z, W)), _mm_set_ps1((float)b)); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator+=(Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { a._m = _mm_add_ps(a._m, _mm_set_ps1((float)b)); return a; }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator-=(Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { a._m = _mm_sub_ps(a._m, _mm_set_ps1((float)b)); return a; }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator*=(Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { a._m = _mm_mul_ps(a._m, _mm_set_ps1((float)b)); return a; }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Swizzle4<float, 4, X, Y, Z, W>& operator/=(Swizzle4<float, 4, X, Y, Z, W>& a, U b) noexcept { a._m = _mm_div_ps(a._m, _mm_set_ps1((float)b)); return a; }
#pragma endregion
#pragma region .   Scalar Vector
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator+(U a, const Vec4<float>& b) noexcept { return _mm_add_ps(_mm_set_ps1((float)a), b._m); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator-(U a, const Vec4<float>& b) noexcept { return _mm_sub_ps(_mm_set_ps1((float)a), b._m); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator*(U a, const Vec4<float>& b) noexcept { return _mm_mul_ps(_mm_set_ps1((float)a), b._m); }
   template<class U, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator/(U a, const Vec4<float>& b) noexcept { return _mm_div_ps(_mm_set_ps1((float)a), b._m); }
#pragma endregion
#pragma region .   Scalar Swizzle
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator+(U a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_add_ps(_mm_set_ps1((float)a), _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator-(U a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_sub_ps(_mm_set_ps1((float)a), _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator*(U a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_mul_ps(_mm_set_ps1((float)a), _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator/(U a, const Swizzle4<float, S, X, Y, Z, W>& b) noexcept { return _mm_div_ps(_mm_set_ps1((float)a), _gml_set_ps(b._data[X], b._data[Y], b._data[Z], b._data[W])); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator+(U a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_add_ps(_mm_set_ps1((float)a), _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator-(U a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_sub_ps(_mm_set_ps1((float)a), _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator*(U a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_mul_ps(_mm_set_ps1((float)a), _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
   template<class U, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_I Vec4<float> operator/(U a, const Swizzle4<float, 4, X, Y, Z, W>& b) noexcept { return _mm_div_ps(_mm_set_ps1((float)a), _gml_permute_ps(b._m, GML_SHUFFLE(X, Y, Z, W))); }
#pragma endregion
}

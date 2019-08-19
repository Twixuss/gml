#pragma once
#include "Traits.h"
#include "Common.h"
#include "Array.h"
#include "Swizzle.h"
#define GML_CHECK2(x, y)       static_assert(x != y, "Assign on repeating swizzle is not allowed.")
#define GML_CHECK3(x, y, z)    static_assert(x != y && x != z && y != z, "Assign on repeating swizzle is not allowed.")
#define GML_CHECK4(x, y, z, w) static_assert(x != y && x != z && x != w && y != z && y != w && z != w, "Assign on repeating swizzle is not allowed.")
#define GML_ENABLE_IF_NUMBER(A)        class = EnableIf<IsArithmetic<A>>
#define GML_ENABLE_IF_NUMBER2(A,B)     class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>>
#define GML_ENABLE_IF_NUMBER3(A,B,C)   class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>&&IsArithmetic<C>>
#define GML_ENABLE_IF_NUMBER4(A,B,C,D) class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>&&IsArithmetic<C>&&IsArithmetic<D>>
#define GML_ASSERT(x) if(!(x))__debugbreak()
namespace gml {
   template<class A, class B>
   using _mp = MostPrecision<A, B>;
   template<class, int, int>                struct Swizzle1;
   template<class, int, int, int>           struct Swizzle2;
   template<class, int, int, int, int>      struct Swizzle3;
   template<class, int, int, int, int, int> struct Swizzle4;
   template<class> struct Vec1;
   template<class> struct Vec2;
   template<class> struct Vec3;
   template<class> struct Vec4;

   template<class T, int S, int X>
   struct Swizzle1 {
      union {
         Array<T, S> _arr;
         T _data[S];
      };
      GML_CI operator T() const noexcept { return _data[X]; }
      GML_CI Swizzle1& operator=(const Vec1<T>& v) noexcept {
         _data[X] = v[0];
         return *this;
      }
      template<int S2, int A>
      GML_CI Swizzle1& operator=(const Swizzle1<T, S2, A>& v) noexcept {
         _data[X] = v._data[A];
         return *this;
      }
      template<class N, GML_ENABLE_IF_NUMBER(N)> GML_CI Swizzle1& operator=(N n) noexcept {
         _data[X] = (T)n;
         return *this;
      }
   };
   template<class T, int S, int X, int Y>
   struct Swizzle2 {
      union {
         Array<T, S> _arr;
         T _data[S];
      };
      GML_CI Swizzle2& operator=(const Vec2<T>& v) noexcept {
         GML_CHECK2(X, Y);
         _data[X] = v._data[0];
         _data[Y] = v._data[1];
         return *this;
      }
      template<int S2, int A, int B>
      GML_CI Swizzle2& operator=(const Swizzle2<T, S2, A, B>& v) noexcept {
         GML_CHECK2(X, Y);
         _data[X] = v._data[A];
         _data[Y] = v._data[B];
         return *this;
      }
      template<class N, GML_ENABLE_IF_NUMBER(N)> GML_CI Swizzle2& operator=(N n) noexcept {
         _data[X] = (T)n;
         _data[Y] = (T)n;
         return *this;
      }
   };
   template<class T, int S, int X, int Y, int Z>
   struct Swizzle3 {
      union {
         Array<T, S> _arr;
         T _data[S];
      };
      GML_CI Swizzle3& operator=(const Vec3<T>& v) noexcept {
         GML_CHECK3(X, Y, Z);
         _data[X] = v._data[0];
         _data[Y] = v._data[1];
         _data[Z] = v._data[2];
         return *this;
      }
      template<int S2, int A, int B, int C>
      GML_CI Swizzle3& operator=(const Swizzle3<T, S2, A, B, C>& v) noexcept {
         GML_CHECK3(X, Y, Z);
         _data[X] = v._data[A];
         _data[Y] = v._data[B];
         _data[Z] = v._data[C];
         return *this;
      }
      template<class N, GML_ENABLE_IF_NUMBER(N)> GML_CI Swizzle3& operator=(N n) noexcept {
         _data[X] = (T)n;
         _data[Y] = (T)n;
         _data[Z] = (T)n;
         return *this;
      }
   };
   template<class T, int S, int X, int Y, int Z, int W>
   struct Swizzle4 {
      union {
         Array<T, S> _arr;
         T _data[S];
      };
      GML_C Swizzle4& operator=(const Vec4<T>& v) noexcept {
         GML_CHECK4(X, Y, Z, W);
         _data[X] = v._data[0];
         _data[Y] = v._data[1];
         _data[Z] = v._data[2];
         _data[W] = v._data[3];
         return *this;
      }
      template<int S2, int A, int B, int C, int D>
      GML_C Swizzle4& operator=(const Swizzle4<T, S2, A, B, C, D>& v) noexcept {
         GML_CHECK4(X, Y, Z, W);
         _data[X] = v._data[A];
         _data[Y] = v._data[B];
         _data[Z] = v._data[C];
         _data[W] = v._data[D];
         return *this;
      }
      template<class N, GML_ENABLE_IF_NUMBER(N)> GML_CI Swizzle4& operator=(N n) noexcept {
         _data[X] = (T)n;
         _data[Y] = (T)n;
         _data[Z] = (T)n;
         _data[W] = (T)n;
         return *this;
      }
   };
   template<class T>
   struct Vec1 {
      static_assert(IsArithmetic<T>, "gml::Vec1's template param must be arithmetic");
      union {
         Array<T, 1> _arr;
         T _data[1];
         GML_SWIZZLE_X(T);
      };
      explicit operator T* () { return _data; }
      GML_CI Vec1() {};
      GML_CI Vec1(const Vec1& v) : _arr(v._arr) {};
      template<int S, int X> GML_CI Vec1(const Swizzle1<T, S, X>& s) : _arr({ s._data[X] }) {}
      template<class U> GML_CI explicit Vec1(const Vec1<U>& v) : _arr({(T)v._data[0]}) {};
      template<class U, int S, int X> explicit GML_CI Vec1(const Swizzle1<U, S, X>& s) : _arr({ (T)s._data[X] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER(N1)> GML_CI Vec1(N1 v) : _arr({ (T)v }) {}
      GML_CI Vec1(T v) noexcept : _arr({ v }) {}
      GML_CI operator T() const { return _data[0]; }
      GML_CI T& operator[](int i) noexcept { GML_ASSERT(i == 0); return _data[i]; }
      GML_CI const T& operator[](int i) const noexcept { GML_ASSERT(i == 0); return _data[i]; }
   };
   template<class T>
   struct Vec2 {
      static_assert(IsArithmetic<T>, "gml::Vec2's template param must be arithmetic");
      union {
         Array<T, 2> _arr;
         T _data[2];
         GML_SWIZZLE_XY(T);
      };
      explicit operator T* () { return _data; }
      GML_CI Vec2() {};
      GML_CI Vec2(const Vec2<T>& v) : _arr(v._arr) {}
      GML_CI Vec2(const Vec1<T>& a) : _arr({ a._data[0], a._data[0] }) {}
      GML_CI Vec2(const Vec1<T>& a, const Vec1<T>& b) : _arr({ a._data[0], b._data[0] }) {}
      template<int S, int X>                   GML_CI Vec2(const Swizzle1<T, S, X   >& v) noexcept : _arr({ v._data[X], v._data[X] }) {}
      template<int S, int X, int Y>            GML_CI Vec2(const Swizzle2<T, S, X, Y>& v) noexcept : _arr({ v._data[X], v._data[Y] }) {}
      template<int S1, int S2, int X1, int X2> GML_CI Vec2(const Swizzle1<T, S1, X1>& v1, const Swizzle1<T, S2, X2>& v2) noexcept : _arr({ v1._data[X1], v2._data[X2] }) {}
      template<class U> GML_CI Vec2(const Vec2<U>& v) : _arr({ (T)v._data[0], (T)v._data[1] }) {}
      template<class U> GML_CI Vec2(const Vec1<U>& v) : _arr({ (T)v._data[0], (T)v._data[0] }) {}
      template<class U> GML_CI Vec2(const Vec1<U>& x, const Vec1<T>& y) : _arr({ (T)x._data[0], (T)y._data[0] }) {}
      template<class U, int S, int X>                   GML_CI Vec2(const Swizzle1<U, S, X   >& v) noexcept : _arr({ (T)v._data[X], (T)v._data[X] }) {}
      template<class U, int S, int X, int Y>            GML_CI Vec2(const Swizzle2<U, S, X, Y>& v) noexcept : _arr({ (T)v._data[X], (T)v._data[Y] }) {}
      template<class U, int S1, int S2, int X1, int X2> GML_CI Vec2(const Swizzle1<U, S1, X1>& v1, const Swizzle1<T, S2, X2>& v2) noexcept : _arr({ (T)v1._data[X1], (T)v2._data[X2] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER(N1)    > GML_CI Vec2(N1 v) noexcept : _arr({ T(v),T(v) }) {}
      template<class N1, class N2, GML_ENABLE_IF_NUMBER2(N1, N2)> GML_CI Vec2(N1 x, N2 y) noexcept : _arr({ T(x),T(y) }) {}
      GML_CI Vec2(T v) noexcept : _arr({ v,v }) {}
      GML_CI Vec2(T x, T y) noexcept : _arr({ x,y }) {}
      GML_CI T& operator[](int i) noexcept { GML_ASSERT(0 <= i && i < 2); return _data[i]; }
      GML_CI const T& operator[](int i) const noexcept { GML_ASSERT(0 <= i && i < 2); return _data[i]; }
   };
   template<class T>
   struct Vec3 {
      static_assert(IsArithmetic<T>, "gml::Vec3's template param must be arithmetic");
      union {
         Array<T, 3> _arr;
         T _data[3];
         GML_SWIZZLE_XYZ(T);
      };
      explicit operator T* () { return _data; }
      GML_CI Vec3() {}
      GML_CI Vec3(const Vec3<T>& v) : _arr(v._arr) {}
      GML_CI Vec3(const Vec2<T>& xy, const Vec1<T>& z) : _arr({ xy[0], xy[1], z[0] }) {}
      GML_CI Vec3(const Vec1<T>& x, const Vec2<T>& yz) : _arr({ x[0], yz[0], yz[1] }) {}
      GML_CI Vec3(const Vec1<T>& x, const Vec1<T>& y, const Vec1<T>& z) : _arr({ x[0], y[0], z[0] }) {}
      GML_CI Vec3(const Vec1<T>& v) : _arr({ v[0], v[0], v[0] }) {}
      template<int S, int X>                                   GML_CI Vec3(const Swizzle1<T, S, X>& v) : _arr({ v._data[X], v._data[X], v._data[X] }) {}
      template<int S, int X, int Y, int Z>                     GML_CI Vec3(const Swizzle3<T, S, X, Y, Z>& v) : _arr({ v._data[X], v._data[Y], v._data[Z] }) {}
      template<int S1, int X1, int Y1, int S2, int X2>         GML_CI Vec3(const Swizzle2<T, S1, X1, Y1>& xy, const Swizzle1<T, S2, X2>& z) : _arr({ xy._data[X1], xy._data[Y1], z._data[X2] }) {}
      template<int S1, int X1, int S2, int X2, int Y2>         GML_CI Vec3(const Swizzle1<T, S1, X1>& x, const Swizzle2<T, S2, X2, Y2>& yz) : _arr({ x._data[X1], yz._data[X2], yz._data[Y2] }) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3> GML_CI Vec3(const Swizzle1<T, S1, X1>& x, const Swizzle1<T, S2, X2>& y, const Swizzle1<T, S3, X3>& z) : _arr({ x._data[X1], y._data[X2], z._data[X3] }) {}
      template<class U> GML_CI Vec3(const Vec3<U>& v) : _arr(v._arr) {}
      template<class U> GML_CI Vec3(const Vec2<U>& xy, const Vec1<U>& z) : _arr({ xy[0], xy[1], z[0] }) {}
      template<class U> GML_CI Vec3(const Vec1<U>& x, const Vec2<U>& yz) : _arr({ x[0], yz[0], yz[1] }) {}
      template<class U> GML_CI Vec3(const Vec1<U>& x, const Vec1<U>& y, const Vec1<U>& z) : _arr({ x[0], y[0], z[0] }) {}
      template<class U> GML_CI Vec3(const Vec1<U>& v) : _arr({ v[0], v[0], v[0] }) {}
      template<class U, int S, int X>                                   GML_CI Vec3(const Swizzle1<U, S, X>& v) : _arr({ (T)v._data[X], (T)v._data[X], (T)v._data[X] }) {}
      template<class U, int S, int X, int Y, int Z>                     GML_CI Vec3(const Swizzle3<U, S, X, Y, Z>& v) : _arr({ (T)v._data[X], (T)v._data[Y], (T)v._data[Z] }) {}
      template<class U, int S1, int X1, int Y1, int S2, int X2>         GML_CI Vec3(const Swizzle2<U, S1, X1, Y1>& xy, const Swizzle1<U, S2, X2>& z) : _arr({ (T)xy._data[X1], (T)xy._data[Y1], (T)z._data[X2] }) {}
      template<class U, int S1, int X1, int S2, int X2, int Y2>         GML_CI Vec3(const Swizzle1<U, S1, X1>& x, const Swizzle2<U, S2, X2, Y2>& yz) : _arr({ (T)x._data[X1], (T)yz._data[X2], (T)yz._data[Y2] }) {}
      template<class U, int S1, int X1, int S2, int X2, int S3, int X3> GML_CI Vec3(const Swizzle1<U, S1, X1>& x, const Swizzle1<U, S2, X2>& y, const Swizzle1<U, S3, X3>& z) : _arr({ (T)x._data[X1], (T)y._data[X2], (T)z._data[X3] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER(N1)> GML_CI Vec3(N1 v) noexcept : _arr({ T(v),T(v),T(v) }) {}
      template<class N1, class N2, class N3, GML_ENABLE_IF_NUMBER3(N1, N2, N3)> GML_CI Vec3(N1 x, N2 y, N3 z) noexcept : _arr({ T(x),T(y),T(z) }) {}
      GML_CI Vec3(T v) noexcept : _arr({ v,v,v }) {}
      GML_CI Vec3(T x, T y, T z) noexcept : _arr({ x,y,z }) {}
      GML_CI T& operator[](int i) noexcept { GML_ASSERT(0 <= i && i < 3); return _data[i]; }
      GML_CI const T& operator[](int i) const noexcept { GML_ASSERT(0 <= i && i < 3); return _data[i]; }
   };
   template<class T>
   struct Vec4 {
      static_assert(IsArithmetic<T>, "gml::Vec4's template param must be arithmetic");
      union {
         Array<T, 4> _arr;
         T _data[4];
         GML_SWIZZLE_XYZW(T);
      };
      explicit operator T*() { return _data; }
      GML_CI Vec4() {}
      GML_CI Vec4(const Vec4<T>& v) : _arr(v._arr) {}
      GML_CI Vec4(const Vec3<T>& xyz, const Vec1<T>& w) : _arr({ xyz[0], xyz[1], xyz[2],   w[0] }) {}
      GML_CI Vec4(const Vec1<T>& x, const Vec3<T>& yzw) : _arr({ x[0], yzw[0], yzw[1], yzw[2] }) {}
      GML_CI Vec4(const Vec2<T>& xy, const Vec2<T>& zw) : _arr({ xy[0],  xy[1],  zw[0],  zw[1] }) {}
      GML_CI Vec4(const Vec2<T>& xy, const Vec1<T>& z, const Vec1<T>& w) : _arr({ xy[0], xy[1], z[0], w[0] }) {}
      GML_CI Vec4(const Vec1<T>& x, const Vec2<T>& yz, const Vec1<T>& w) : _arr({ x[0], yz[0], yz[1], w[0] }) {}
      GML_CI Vec4(const Vec1<T>& x, const Vec1<T>& y, const Vec2<T>& zw) : _arr({ x[0], y[0], zw[0], zw[1] }) {}
      GML_CI Vec4(const Vec1<T>& x, const Vec1<T>& y, const Vec1<T>& z, const Vec1<T>& w) : _arr({ x[0], y[0], z[0], w[0] }) {}
      GML_CI Vec4(const Vec1<T>& v) : _arr({ v[0], v[0], v[0], v[0] }) {}
      template<int S, int X>                                                   GML_CI Vec4(const Swizzle1<T, S, X>& v) noexcept : _arr({ v._data[X], v._data[X], v._data[X], v._data[X] }) {}
      template<int S, int X, int Y, int Z, int W>                              GML_CI Vec4(const Swizzle4<T, S, X, Y, Z, W>& v) noexcept : _arr({ v._data[X], v._data[Y], v._data[Z], v._data[W] }) {}
      template<int S1, int X1, int Y1, int Z1, int S2, int X2>                 GML_CI Vec4(const Swizzle3<T, S1, X1, Y1, Z1>& xyz, const Swizzle1<T, S2, X2>& w) noexcept : _arr({ xyz._data[X1], xyz._data[Y1], xyz._data[Z1], w._data[X2] }) {}
      template<int S1, int X1, int S2, int X2, int Y2, int Z2>                 GML_CI Vec4(const Swizzle1<T, S1, X1>& x, const Swizzle3<T, S2, X2, Y2, Z2>& yzw) noexcept : _arr({ x._data[X1], yzw._data[X2], yzw._data[Y2], yzw._data[Z2] }) {}
      template<int S1, int X1, int Y1, int S2, int X2, int Y2>                 GML_CI Vec4(const Swizzle2<T, S1, X1, Y1>& xy, const Swizzle2<T, S2, X2, Y2>& zw) noexcept : _arr({ xy._data[X1], xy._data[Y1], zw._data[X2], zw._data[Y2] }) {}
      template<int S1, int X1, int Y1, int S2, int X2, int S3, int X3>         GML_CI Vec4(const Swizzle2<T, S1, X1, Y1>& xy, const Swizzle1<T, S2, X2>& z, const Swizzle1<T, S3, X3>& w) noexcept : _arr({ xy._data[X1], xy._data[Y1], z._data[X2], w._data[X3] }) {}
      template<int S1, int X1, int S2, int X2, int Y2, int S3, int X3>         GML_CI Vec4(const Swizzle1<T, S1, X1>& x, const Swizzle2<T, S2, X2, Y2>& yz, const Swizzle1<T, S3, X3>& w) noexcept : _arr({ x._data[X1], yz._data[X2], yz._data[Y2], w._data[X3] }) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3, int Y3>         GML_CI Vec4(const Swizzle1<T, S1, X1>& x, const Swizzle1<T, S2, X2>& y, const Swizzle2<T, S3, X3, Y3>& zw) noexcept : _arr({ x._data[X1], y._data[X2], zw._data[X3], zw._data[Y3] }) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3, int S4, int X4> GML_CI Vec4(const Swizzle1<T, S1, X1>& x, const Swizzle1<T, S2, X2>& y, const Swizzle1<T, S3, X3>& z, const Swizzle1<T, S4, X4>& w) noexcept : _arr({ x._data[X1], y._data[X2], z._data[X3], w._data[X4] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER(N1)> GML_CI Vec4(N1 v) noexcept : _arr({ T(v),T(v),T(v),T(v) }) {}
      template<class N1, class N2, class N3, class N4, GML_ENABLE_IF_NUMBER4(N1, N2, N3, N4)> GML_CI Vec4(N1 x, N2 y, N3 z, N4 w) noexcept : _arr({ T(x),T(y),T(z),T(w) }) {}
      GML_CI Vec4(T v) noexcept : _arr({ v,v,v,v }) {}
      GML_CI Vec4(T x, T y, T z, T w) noexcept : _arr({ x,y,z,w }) {}
      GML_CI T& operator[](int i) noexcept { GML_ASSERT(0 <= i && i < 4); return _data[i]; }
      GML_CI const T& operator[](int i) const noexcept { GML_ASSERT(0 <= i && i < 4); return _data[i]; }
   };
   
#pragma region .   Unary
#pragma region .   Vector
   template<class T> GML_CI Vec1<T> operator+(const Vec1<T>& v) noexcept { return v; }
   template<class T> GML_CI Vec2<T> operator+(const Vec2<T>& v) noexcept { return v; }
   template<class T> GML_CI Vec3<T> operator+(const Vec3<T>& v) noexcept { return v; }
   template<class T> GML_CI Vec4<T> operator+(const Vec4<T>& v) noexcept { return v; }
   template<class T> GML_CI Vec1<T> operator-(const Vec1<T>& v) noexcept { return { -v[0] }; }
   template<class T> GML_CI Vec2<T> operator-(const Vec2<T>& v) noexcept { return { -v[0], -v[1] }; }
   template<class T> GML_CI Vec3<T> operator-(const Vec3<T>& v) noexcept { return { -v[0], -v[1], -v[2] }; }
   template<class T> GML_CI Vec4<T> operator-(const Vec4<T>& v) noexcept { return { -v[0], -v[1], -v[2], -v[3] }; }
#pragma endregion
#pragma region .   Swizzle
   template<class T, int S, int X                     > GML_CI Vec1<T> operator+(const Swizzle1<T, S, X         >& v) noexcept { return Vec1<T>(v); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator+(const Swizzle2<T, S, X, Y      >& v) noexcept { return Vec2<T>(v); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator+(const Swizzle3<T, S, X, Y, Z   >& v) noexcept { return Vec3<T>(v); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(const Swizzle4<T, S, X, Y, Z, W>& v) noexcept { return Vec4<T>(v); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator-(const Swizzle1<T, S, X         >& v) noexcept { return -Vec1<T>(v); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator-(const Swizzle2<T, S, X, Y      >& v) noexcept { return -Vec2<T>(v); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator-(const Swizzle3<T, S, X, Y, Z   >& v) noexcept { return -Vec3<T>(v); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(const Swizzle4<T, S, X, Y, Z, W>& v) noexcept { return -Vec4<T>(v); }
#pragma endregion
#pragma endregion
#pragma region .   Binary
#pragma region .   Comparison
#pragma region .   Vector Vector
   template<class T> GML_CI bool operator==(const Vec1<T>& a, const Vec1<T>& b) noexcept { return a[0] == b[0]; }
   template<class T> GML_CI bool operator==(const Vec2<T>& a, const Vec1<T>& b) noexcept { return a[0] == b[0] && a[1] == b[0]; }
   template<class T> GML_CI bool operator==(const Vec3<T>& a, const Vec1<T>& b) noexcept { return a[0] == b[0] && a[1] == b[0] && a[2] == b[0]; }
   template<class T> GML_CI bool operator==(const Vec4<T>& a, const Vec1<T>& b) noexcept { return a[0] == b[0] && a[1] == b[0] && a[2] == b[0] && a[3] == b[0]; }

   template<class T> GML_CI bool operator==(const Vec1<T>& a, const Vec2<T>& b) noexcept { return b == a; }
   template<class T> GML_CI bool operator==(const Vec1<T>& a, const Vec3<T>& b) noexcept { return b == a; }
   template<class T> GML_CI bool operator==(const Vec1<T>& a, const Vec4<T>& b) noexcept { return b == a; }

   template<class T> GML_CI bool operator==(const Vec2<T>& a, const Vec2<T>& b) noexcept { return a[0] == b[0] && a[1] == b[1]; }
   template<class T> GML_CI bool operator==(const Vec3<T>& a, const Vec3<T>& b) noexcept { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2]; }
   template<class T> GML_CI bool operator==(const Vec4<T>& a, const Vec4<T>& b) noexcept { return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]; }
#pragma endregion
#pragma region .   Vector Swizzle
   template<class T, int S, int X> GML_CI bool operator==(const Vec1<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a[0] == b._data[X]; }
   template<class T, int S, int X> GML_CI bool operator==(const Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a[0] == b._data[X] && a[1] == b._data[X]; }
   template<class T, int S, int X> GML_CI bool operator==(const Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a[0] == b._data[X] && a[1] == b._data[X] && a[2] == b._data[X]; }
   template<class T, int S, int X> GML_CI bool operator==(const Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a[0] == b._data[X] && a[1] == b._data[X] && a[2] == b._data[X] && a[3] == b._data[X]; }
   template<class T, int S, int X, int Y              > GML_CI bool operator==(const Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return a[0] == b._data[X] && a[1] == b._data[Y]; }
   template<class T, int S, int X, int Y, int Z       > GML_CI bool operator==(const Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return a[0] == b._data[X] && a[1] == b._data[Y] && a[2] == b._data[Z]; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI bool operator==(const Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return a[0] == b._data[X] && a[1] == b._data[Y] && a[2] == b._data[Z] && a[3] == b._data[W]; }
#pragma endregion
#pragma region .   Vector Scalar
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Vec1<T>& a, U b) noexcept { return a[0] == (T)b; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Vec2<T>& a, U b) noexcept { return a[0] == (T)b && a[1] == (T)b; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Vec3<T>& a, U b) noexcept { return a[0] == (T)b && a[1] == (T)b && a[2] == (T)b; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Vec4<T>& a, U b) noexcept { return a[0] == (T)b && a[1] == (T)b && a[2] == (T)b && a[3] == (T)b; }
#pragma endregion
#pragma region .   Swizzle Vector
   template<class T, int S, int X> GML_CI bool operator==(const Swizzle1<T, S, X>& a, const Vec1<T>& b) noexcept { return b == a; }
   template<class T, int S, int X> GML_CI bool operator==(const Swizzle1<T, S, X>& a, const Vec2<T>& b) noexcept { return b == a; }
   template<class T, int S, int X> GML_CI bool operator==(const Swizzle1<T, S, X>& a, const Vec3<T>& b) noexcept { return b == a; }
   template<class T, int S, int X> GML_CI bool operator==(const Swizzle1<T, S, X>& a, const Vec4<T>& b) noexcept { return b == a; }
   template<class T, int S, int X, int Y              > GML_CI bool operator==(const Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { return b == a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI bool operator==(const Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { return b == a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI bool operator==(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { return b == a; }
   template<class T, int S, int X, int Y              > GML_CI bool operator==(const Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { return b == a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI bool operator==(const Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { return b == a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI bool operator==(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { return b == a; }
#pragma endregion
#pragma region .   Swizzle Swizzle
   template<class T, int S1, int X1, int S2, int X2                        > GML_CI bool operator==(const Swizzle1<T, S1, X1>& a, const Swizzle1<T, S2, X2            >& b) noexcept { return a._data[X1] == b._data[X2]; }
   template<class T, int S1, int X1, int S2, int X2, int Y2                > GML_CI bool operator==(const Swizzle1<T, S1, X1>& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return a._data[X1] == b._data[X2] && a._data[X1] == b._data[Y2]; }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2        > GML_CI bool operator==(const Swizzle1<T, S1, X1>& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return a._data[X1] == b._data[X2] && a._data[X1] == b._data[Y2] && a._data[X1] == b._data[Z2]; }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2, int W2> GML_CI bool operator==(const Swizzle1<T, S1, X1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return a._data[X1] == b._data[X2] && a._data[X1] == b._data[Y2] && a._data[X1] == b._data[Z2] && a._data[X1] == b._data[W2]; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2> GML_CI bool operator==(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { return a._data[X1] == b._data[X2] && a._data[Y1] == b._data[X2]; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2> GML_CI bool operator==(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { return a._data[X1] == b._data[X2] && a._data[Y1] == b._data[X2] && a._data[Z1] == b._data[X2]; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI bool operator==(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { return a._data[X1] == b._data[X2] && a._data[Y1] == b._data[X2] && a._data[Z1] == b._data[X2] && a._data[W1] == b._data[X2]; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2, int Y2                > GML_CI bool operator==(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return a._data[X1] == b._data[X2] && a._data[Y1] == b._data[Y2]; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2, int Y2, int Z2        > GML_CI bool operator==(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return a._data[X1] == b._data[X2] && a._data[Y1] == b._data[Y2] && a._data[Z1] == b._data[Z2]; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI bool operator==(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return a._data[X1] == b._data[X2] && a._data[Y1] == b._data[Y2] && a._data[Z1] == b._data[Z2] && a._data[W1] == b._data[W2]; }
#pragma endregion
#pragma region .   Swizzle Scalar
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Swizzle1<T, S, X         >& a, U b) noexcept { return a._data[X] == b; }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Swizzle2<T, S, X, Y      >& a, U b) noexcept { return a._data[X] == b && a._data[Y] == b; }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { return a._data[X] == b && a._data[Y] == b && a._data[Z] == b; }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI bool operator==(const Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { return a._data[X] == b && a._data[Y] == b && a._data[Z] == b && a._data[W] == b; }
#pragma endregion
#pragma endregion
#pragma region .   Arithmetic
#pragma region .   Vector Vector
   template<class T> GML_CI Vec1<T> operator+(const Vec1<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] + b._data[0] }; }
   template<class T> GML_CI Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) noexcept { return { a._data[0] + b._data[0], a._data[1] + b._data[1] }; }
   template<class T> GML_CI Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) noexcept { return { a._data[0] + b._data[0], a._data[1] + b._data[1], a._data[2] + b._data[2] }; }
   template<class T> GML_CI Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b) noexcept { return { a._data[0] + b._data[0], a._data[1] + b._data[1], a._data[2] + b._data[2], a._data[3] + b._data[3] }; }
   template<class T> GML_CI Vec2<T> operator+(const Vec2<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] + b._data[0], a._data[1] + b._data[0] }; }
   template<class T> GML_CI Vec3<T> operator+(const Vec3<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] + b._data[0], a._data[1] + b._data[0], a._data[2] + b[0] }; }
   template<class T> GML_CI Vec4<T> operator+(const Vec4<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] + b._data[0], a._data[1] + b._data[0], a._data[2] + b[0], a._data[3] + b._data[0] }; }
   template<class T> GML_CI Vec1<T> operator-(const Vec1<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] - b._data[0] }; }
   template<class T> GML_CI Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) noexcept { return { a._data[0] - b._data[0], a._data[1] - b._data[1] }; }
   template<class T> GML_CI Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) noexcept { return { a._data[0] - b._data[0], a._data[1] - b._data[1], a._data[2] - b._data[2] }; }
   template<class T> GML_CI Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b) noexcept { return { a._data[0] - b._data[0], a._data[1] - b._data[1], a._data[2] - b._data[2], a._data[3] - b._data[3] }; }
   template<class T> GML_CI Vec2<T> operator-(const Vec2<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] - b._data[0], a._data[1] - b._data[0] }; }
   template<class T> GML_CI Vec3<T> operator-(const Vec3<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] - b._data[0], a._data[1] - b._data[0], a._data[2] - b._data[0] }; }
   template<class T> GML_CI Vec4<T> operator-(const Vec4<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] - b._data[0], a._data[1] - b._data[0], a._data[2] - b._data[0], a._data[3] - b._data[0] }; }
   template<class T> GML_CI Vec1<T> operator*(const Vec1<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] * b._data[0] }; }
   template<class T> GML_CI Vec2<T> operator*(const Vec2<T>& a, const Vec2<T>& b) noexcept { return { a._data[0] * b._data[0], a._data[1] * b._data[1] }; }
   template<class T> GML_CI Vec3<T> operator*(const Vec3<T>& a, const Vec3<T>& b) noexcept { return { a._data[0] * b._data[0], a._data[1] * b._data[1], a._data[2] * b._data[2] }; }
   template<class T> GML_CI Vec4<T> operator*(const Vec4<T>& a, const Vec4<T>& b) noexcept { return { a._data[0] * b._data[0], a._data[1] * b._data[1], a._data[2] * b._data[2], a._data[3] * b._data[3] }; }
   template<class T> GML_CI Vec2<T> operator*(const Vec2<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] * b._data[0], a._data[1] * b._data[0] }; }
   template<class T> GML_CI Vec3<T> operator*(const Vec3<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] * b._data[0], a._data[1] * b._data[0], a._data[2] * b._data[0] }; }
   template<class T> GML_CI Vec4<T> operator*(const Vec4<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] * b._data[0], a._data[1] * b._data[0], a._data[2] * b._data[0], a._data[3] * b._data[0] }; }
   template<class T> GML_CI Vec1<T> operator/(const Vec1<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] / b._data[0] }; }
   template<class T> GML_CI Vec2<T> operator/(const Vec2<T>& a, const Vec2<T>& b) noexcept { return { a._data[0] / b._data[0], a._data[1] / b._data[1] }; }
   template<class T> GML_CI Vec3<T> operator/(const Vec3<T>& a, const Vec3<T>& b) noexcept { return { a._data[0] / b._data[0], a._data[1] / b._data[1], a._data[2] / b._data[2] }; }
   template<class T> GML_CI Vec4<T> operator/(const Vec4<T>& a, const Vec4<T>& b) noexcept { return { a._data[0] / b._data[0], a._data[1] / b._data[1], a._data[2] / b._data[2], a._data[3] / b._data[3] }; }
   template<class T> GML_CI Vec2<T> operator/(const Vec2<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] / b._data[0], a._data[1] / b._data[0] }; }
   template<class T> GML_CI Vec3<T> operator/(const Vec3<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] / b._data[0], a._data[1] / b._data[0], a._data[2] / b._data[0] }; }
   template<class T> GML_CI Vec4<T> operator/(const Vec4<T>& a, const Vec1<T>& b) noexcept { return { a._data[0] / b._data[0], a._data[1] / b._data[0], a._data[2] / b._data[0], a._data[3] / b._data[0] }; }
   template<class T> GML_CI Vec1<T>& operator+=(Vec1<T>& a, const Vec1<T>& b) noexcept { a = a + b; return a; }
   template<class T> GML_CI Vec2<T>& operator+=(Vec2<T>& a, const Vec2<T>& b) noexcept { a = a + b; return a; }
   template<class T> GML_CI Vec3<T>& operator+=(Vec3<T>& a, const Vec3<T>& b) noexcept { a = a + b; return a; }
   template<class T> GML_CI Vec4<T>& operator+=(Vec4<T>& a, const Vec4<T>& b) noexcept { a = a + b; return a; }
   template<class T> GML_CI Vec1<T>& operator-=(Vec1<T>& a, const Vec1<T>& b) noexcept { a = a - b; return a; }
   template<class T> GML_CI Vec2<T>& operator-=(Vec2<T>& a, const Vec2<T>& b) noexcept { a = a - b; return a; }
   template<class T> GML_CI Vec3<T>& operator-=(Vec3<T>& a, const Vec3<T>& b) noexcept { a = a - b; return a; }
   template<class T> GML_CI Vec4<T>& operator-=(Vec4<T>& a, const Vec4<T>& b) noexcept { a = a - b; return a; }
   template<class T> GML_CI Vec1<T>& operator*=(Vec1<T>& a, const Vec1<T>& b) noexcept { a = a * b; return a; }
   template<class T> GML_CI Vec2<T>& operator*=(Vec2<T>& a, const Vec2<T>& b) noexcept { a = a * b; return a; }
   template<class T> GML_CI Vec3<T>& operator*=(Vec3<T>& a, const Vec3<T>& b) noexcept { a = a * b; return a; }
   template<class T> GML_CI Vec4<T>& operator*=(Vec4<T>& a, const Vec4<T>& b) noexcept { a = a * b; return a; }
   template<class T> GML_CI Vec1<T>& operator/=(Vec1<T>& a, const Vec1<T>& b) noexcept { a = a / b; return a; }
   template<class T> GML_CI Vec2<T>& operator/=(Vec2<T>& a, const Vec2<T>& b) noexcept { a = a / b; return a; }
   template<class T> GML_CI Vec3<T>& operator/=(Vec3<T>& a, const Vec3<T>& b) noexcept { a = a / b; return a; }
   template<class T> GML_CI Vec4<T>& operator/=(Vec4<T>& a, const Vec4<T>& b) noexcept { a = a / b; return a; }
   template<class T> GML_CI Vec2<T>& operator+=(Vec2<T>& a, const Vec1<T>& b) noexcept { a = a + Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator+=(Vec3<T>& a, const Vec1<T>& b) noexcept { a = a + Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator+=(Vec4<T>& a, const Vec1<T>& b) noexcept { a = a + Vec4<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator-=(Vec2<T>& a, const Vec1<T>& b) noexcept { a = a - Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator-=(Vec3<T>& a, const Vec1<T>& b) noexcept { a = a - Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator-=(Vec4<T>& a, const Vec1<T>& b) noexcept { a = a - Vec4<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator*=(Vec2<T>& a, const Vec1<T>& b) noexcept { a = a * Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator*=(Vec3<T>& a, const Vec1<T>& b) noexcept { a = a * Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator*=(Vec4<T>& a, const Vec1<T>& b) noexcept { a = a * Vec4<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator/=(Vec2<T>& a, const Vec1<T>& b) noexcept { a = a / Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator/=(Vec3<T>& a, const Vec1<T>& b) noexcept { a = a / Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator/=(Vec4<T>& a, const Vec1<T>& b) noexcept { a = a / Vec4<T>(b); return a; }
#pragma endregion
#pragma region .   Vector Swizzle
   template<class T, int S, int X> GML_CI Vec2<T> operator+(const Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a + Vec2<T>(b); }
   template<class T, int S, int X> GML_CI Vec2<T> operator-(const Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a - Vec2<T>(b); }
   template<class T, int S, int X> GML_CI Vec2<T> operator*(const Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a * Vec2<T>(b); }
   template<class T, int S, int X> GML_CI Vec2<T> operator/(const Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a / Vec2<T>(b); }
   template<class T, int S, int X> GML_CI Vec3<T> operator+(const Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a + Vec3<T>(b); }
   template<class T, int S, int X> GML_CI Vec3<T> operator-(const Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a - Vec3<T>(b); }
   template<class T, int S, int X> GML_CI Vec3<T> operator*(const Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a * Vec3<T>(b); }
   template<class T, int S, int X> GML_CI Vec3<T> operator/(const Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a / Vec3<T>(b); }
   template<class T, int S, int X> GML_CI Vec4<T> operator+(const Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a + Vec4<T>(b); }
   template<class T, int S, int X> GML_CI Vec4<T> operator-(const Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a - Vec4<T>(b); }
   template<class T, int S, int X> GML_CI Vec4<T> operator*(const Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a * Vec4<T>(b); }
   template<class T, int S, int X> GML_CI Vec4<T> operator/(const Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { return a / Vec4<T>(b); }

   template<class T, int S, int X>                      GML_CI Vec1<T> operator+(const Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { return a + Vec1<T>(b); }
   template<class T, int S, int X>                      GML_CI Vec1<T> operator-(const Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { return a - Vec1<T>(b); }
   template<class T, int S, int X>                      GML_CI Vec1<T> operator*(const Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { return a * Vec1<T>(b); }
   template<class T, int S, int X>                      GML_CI Vec1<T> operator/(const Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { return a / Vec1<T>(b); }

   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator+(const Vec1<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator-(const Vec1<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator*(const Vec1<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator/(const Vec1<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator+(const Vec1<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator-(const Vec1<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator*(const Vec1<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator/(const Vec1<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(const Vec1<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(const Vec1<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator*(const Vec1<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator/(const Vec1<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }

   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator+(const Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return a + Vec2<T>(b); }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator-(const Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return a - Vec2<T>(b); }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator*(const Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return a * Vec2<T>(b); }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T> operator/(const Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { return a / Vec2<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator+(const Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return a + Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator-(const Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return a - Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator*(const Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return a * Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T> operator/(const Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return a / Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(const Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return a + Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(const Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return a - Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator*(const Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return a * Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator/(const Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return a / Vec4<T>(b); }

   template<class T, int S, int X> GML_CI Vec2<T>& operator+=(Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { a += Vec2<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec2<T>& operator-=(Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { a -= Vec2<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec2<T>& operator*=(Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { a *= Vec2<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec2<T>& operator/=(Vec2<T>& a, const Swizzle1<T, S, X>& b) noexcept { a /= Vec2<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec3<T>& operator+=(Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { a += Vec3<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec3<T>& operator-=(Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { a -= Vec3<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec3<T>& operator*=(Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { a *= Vec3<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec3<T>& operator/=(Vec3<T>& a, const Swizzle1<T, S, X>& b) noexcept { a /= Vec3<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec4<T>& operator+=(Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { a += Vec4<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec4<T>& operator-=(Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { a -= Vec4<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec4<T>& operator*=(Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { a *= Vec4<T>(b); return a; }
   template<class T, int S, int X> GML_CI Vec4<T>& operator/=(Vec4<T>& a, const Swizzle1<T, S, X>& b) noexcept { a /= Vec4<T>(b); return a; }

   template<class T, int S, int X>                      GML_CI Vec1<T>& operator+=(Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { a += Vec1<T>(b); return a; }
   template<class T, int S, int X>                      GML_CI Vec1<T>& operator-=(Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { a -= Vec1<T>(b); return a; }
   template<class T, int S, int X>                      GML_CI Vec1<T>& operator*=(Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { a *= Vec1<T>(b); return a; }
   template<class T, int S, int X>                      GML_CI Vec1<T>& operator/=(Vec1<T>& a, const Swizzle1<T, S, X         >& b) noexcept { a /= Vec1<T>(b); return a; }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T>& operator+=(Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { a += Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T>& operator-=(Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { a -= Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T>& operator*=(Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { a *= Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y>               GML_CI Vec2<T>& operator/=(Vec2<T>& a, const Swizzle2<T, S, X, Y      >& b) noexcept { a /= Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T>& operator+=(Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { a += Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T>& operator-=(Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { a -= Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T>& operator*=(Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { a *= Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z>        GML_CI Vec3<T>& operator/=(Vec3<T>& a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { a /= Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T>& operator+=(Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { a += Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T>& operator-=(Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { a -= Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T>& operator*=(Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { a *= Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T>& operator/=(Vec4<T>& a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { a /= Vec4<T>(b); return a; }
#pragma endregion
#pragma region .   Vector Scalar
   template<class T> GML_CI Vec1<T> operator+(const Vec1<T>& a, T b) noexcept { return a + Vec1<T>(b); }
   template<class T> GML_CI Vec2<T> operator+(const Vec2<T>& a, T b) noexcept { return a + Vec2<T>(b); }
   template<class T> GML_CI Vec3<T> operator+(const Vec3<T>& a, T b) noexcept { return a + Vec3<T>(b); }
   template<class T> GML_CI Vec4<T> operator+(const Vec4<T>& a, T b) noexcept { return a + Vec4<T>(b); }
   template<class T> GML_CI Vec1<T> operator-(const Vec1<T>& a, T b) noexcept { return a - Vec1<T>(b); }
   template<class T> GML_CI Vec2<T> operator-(const Vec2<T>& a, T b) noexcept { return a - Vec2<T>(b); }
   template<class T> GML_CI Vec3<T> operator-(const Vec3<T>& a, T b) noexcept { return a - Vec3<T>(b); }
   template<class T> GML_CI Vec4<T> operator-(const Vec4<T>& a, T b) noexcept { return a - Vec4<T>(b); }
   template<class T> GML_CI Vec1<T> operator*(const Vec1<T>& a, T b) noexcept { return a * Vec1<T>(b); }
   template<class T> GML_CI Vec2<T> operator*(const Vec2<T>& a, T b) noexcept { return a * Vec2<T>(b); }
   template<class T> GML_CI Vec3<T> operator*(const Vec3<T>& a, T b) noexcept { return a * Vec3<T>(b); }
   template<class T> GML_CI Vec4<T> operator*(const Vec4<T>& a, T b) noexcept { return a * Vec4<T>(b); }
   template<class T> GML_CI Vec1<T> operator/(const Vec1<T>& a, T b) noexcept { return a / Vec1<T>(b); }
   template<class T> GML_CI Vec2<T> operator/(const Vec2<T>& a, T b) noexcept { return a / Vec2<T>(b); }
   template<class T> GML_CI Vec3<T> operator/(const Vec3<T>& a, T b) noexcept { return a / Vec3<T>(b); }
   template<class T> GML_CI Vec4<T> operator/(const Vec4<T>& a, T b) noexcept { return a / Vec4<T>(b); }
   template<class T> GML_CI Vec1<T>& operator+=(Vec1<T>& a, T b) noexcept { a += Vec1<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator+=(Vec2<T>& a, T b) noexcept { a += Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator+=(Vec3<T>& a, T b) noexcept { a += Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator+=(Vec4<T>& a, T b) noexcept { a += Vec4<T>(b); return a; }
   template<class T> GML_CI Vec1<T>& operator-=(Vec1<T>& a, T b) noexcept { a -= Vec1<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator-=(Vec2<T>& a, T b) noexcept { a -= Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator-=(Vec3<T>& a, T b) noexcept { a -= Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator-=(Vec4<T>& a, T b) noexcept { a -= Vec4<T>(b); return a; }
   template<class T> GML_CI Vec1<T>& operator*=(Vec1<T>& a, T b) noexcept { a *= Vec1<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator*=(Vec2<T>& a, T b) noexcept { a *= Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator*=(Vec3<T>& a, T b) noexcept { a *= Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator*=(Vec4<T>& a, T b) noexcept { a *= Vec4<T>(b); return a; }
   template<class T> GML_CI Vec1<T>& operator/=(Vec1<T>& a, T b) noexcept { a /= Vec1<T>(b); return a; }
   template<class T> GML_CI Vec2<T>& operator/=(Vec2<T>& a, T b) noexcept { a /= Vec2<T>(b); return a; }
   template<class T> GML_CI Vec3<T>& operator/=(Vec3<T>& a, T b) noexcept { a /= Vec3<T>(b); return a; }
   template<class T> GML_CI Vec4<T>& operator/=(Vec4<T>& a, T b) noexcept { a /= Vec4<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator+(const Vec1<T>& a, U b) noexcept { return a + Vec1<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator+(const Vec2<T>& a, U b) noexcept { return a + Vec2<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator+(const Vec3<T>& a, U b) noexcept { return a + Vec3<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator+(const Vec4<T>& a, U b) noexcept { return a + Vec4<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator-(const Vec1<T>& a, U b) noexcept { return a - Vec1<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator-(const Vec2<T>& a, U b) noexcept { return a - Vec2<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator-(const Vec3<T>& a, U b) noexcept { return a - Vec3<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator-(const Vec4<T>& a, U b) noexcept { return a - Vec4<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator*(const Vec1<T>& a, U b) noexcept { return a * Vec1<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator*(const Vec2<T>& a, U b) noexcept { return a * Vec2<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator*(const Vec3<T>& a, U b) noexcept { return a * Vec3<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator*(const Vec4<T>& a, U b) noexcept { return a * Vec4<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator/(const Vec1<T>& a, U b) noexcept { return a / Vec1<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator/(const Vec2<T>& a, U b) noexcept { return a / Vec2<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator/(const Vec3<T>& a, U b) noexcept { return a / Vec3<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator/(const Vec4<T>& a, U b) noexcept { return a / Vec4<T>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T>& operator+=(Vec1<T>& a, U b) noexcept { a += Vec1<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T>& operator+=(Vec2<T>& a, U b) noexcept { a += Vec2<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T>& operator+=(Vec3<T>& a, U b) noexcept { a += Vec3<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T>& operator+=(Vec4<T>& a, U b) noexcept { a += Vec4<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T>& operator-=(Vec1<T>& a, U b) noexcept { a -= Vec1<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T>& operator-=(Vec2<T>& a, U b) noexcept { a -= Vec2<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T>& operator-=(Vec3<T>& a, U b) noexcept { a -= Vec3<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T>& operator-=(Vec4<T>& a, U b) noexcept { a -= Vec4<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T>& operator*=(Vec1<T>& a, U b) noexcept { a *= Vec1<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T>& operator*=(Vec2<T>& a, U b) noexcept { a *= Vec2<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T>& operator*=(Vec3<T>& a, U b) noexcept { a *= Vec3<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T>& operator*=(Vec4<T>& a, U b) noexcept { a *= Vec4<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T>& operator/=(Vec1<T>& a, U b) noexcept { a /= Vec1<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T>& operator/=(Vec2<T>& a, U b) noexcept { a /= Vec2<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T>& operator/=(Vec3<T>& a, U b) noexcept { a /= Vec3<T>(b); return a; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T>& operator/=(Vec4<T>& a, U b) noexcept { a /= Vec4<T>(b); return a; }
#pragma endregion
#pragma region .   Swizzle Vector
   template<class T, int S, int X> GML_CI Vec1<T> operator+(const Swizzle1<T, S, X>& a, const Vec1<T>& b) noexcept { return Vec1<T>(a) + b; }
   template<class T, int S, int X> GML_CI Vec1<T> operator-(const Swizzle1<T, S, X>& a, const Vec1<T>& b) noexcept { return Vec1<T>(a) - b; }
   template<class T, int S, int X> GML_CI Vec1<T> operator*(const Swizzle1<T, S, X>& a, const Vec1<T>& b) noexcept { return Vec1<T>(a) * b; }
   template<class T, int S, int X> GML_CI Vec1<T> operator/(const Swizzle1<T, S, X>& a, const Vec1<T>& b) noexcept { return Vec1<T>(a) / b; }

   template<class T, int S, int X> GML_CI Vec2<T> operator+(const Swizzle1<T, S, X>& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) + b; }
   template<class T, int S, int X> GML_CI Vec2<T> operator-(const Swizzle1<T, S, X>& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) - b; }
   template<class T, int S, int X> GML_CI Vec2<T> operator*(const Swizzle1<T, S, X>& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) * b; }
   template<class T, int S, int X> GML_CI Vec2<T> operator/(const Swizzle1<T, S, X>& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) / b; }
   template<class T, int S, int X> GML_CI Vec3<T> operator+(const Swizzle1<T, S, X>& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) + b; }
   template<class T, int S, int X> GML_CI Vec3<T> operator-(const Swizzle1<T, S, X>& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) - b; }
   template<class T, int S, int X> GML_CI Vec3<T> operator*(const Swizzle1<T, S, X>& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) * b; }
   template<class T, int S, int X> GML_CI Vec3<T> operator/(const Swizzle1<T, S, X>& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) / b; }
   template<class T, int S, int X> GML_CI Vec4<T> operator+(const Swizzle1<T, S, X>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) + b; }
   template<class T, int S, int X> GML_CI Vec4<T> operator-(const Swizzle1<T, S, X>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) - b; }
   template<class T, int S, int X> GML_CI Vec4<T> operator*(const Swizzle1<T, S, X>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) * b; }
   template<class T, int S, int X> GML_CI Vec4<T> operator/(const Swizzle1<T, S, X>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) / b; }

   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator+(const Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator-(const Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator*(const Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator/(const Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator+(const Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator-(const Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator*(const Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator/(const Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator*(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator/(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }

   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator+(const Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator-(const Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator*(const Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator/(const Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator+(const Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator-(const Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator*(const Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator/(const Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator*(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator/(const Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }

   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator+=(Swizzle1<T, S, X         >& a, const Vec1<T>& b) noexcept { a = Vec1<T>(a) + b; return a; }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator-=(Swizzle1<T, S, X         >& a, const Vec1<T>& b) noexcept { a = Vec1<T>(a) - b; return a; }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator*=(Swizzle1<T, S, X         >& a, const Vec1<T>& b) noexcept { a = Vec1<T>(a) * b; return a; }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator/=(Swizzle1<T, S, X         >& a, const Vec1<T>& b) noexcept { a = Vec1<T>(a) / b; return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator+=(Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { a = Vec2<T>(a) + b; return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator-=(Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { a = Vec2<T>(a) - b; return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator*=(Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { a = Vec2<T>(a) * b; return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator/=(Swizzle2<T, S, X, Y      >& a, const Vec2<T>& b) noexcept { a = Vec2<T>(a) / b; return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator+=(Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { a = Vec3<T>(a) + b; return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator-=(Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { a = Vec3<T>(a) - b; return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator*=(Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { a = Vec3<T>(a) * b; return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator/=(Swizzle3<T, S, X, Y, Z   >& a, const Vec3<T>& b) noexcept { a = Vec3<T>(a) / b; return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator+=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { a = Vec4<T>(a) + b; return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator-=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { a = Vec4<T>(a) - b; return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator*=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { a = Vec4<T>(a) * b; return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator/=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec4<T>& b) noexcept { a = Vec4<T>(a) / b; return a; }

   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator+=(Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { a = Vec2<T>(a) + Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator-=(Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { a = Vec2<T>(a) - Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator*=(Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { a = Vec2<T>(a) * Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator/=(Swizzle2<T, S, X, Y      >& a, const Vec1<T>& b) noexcept { a = Vec2<T>(a) / Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator+=(Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { a = Vec3<T>(a) + Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator-=(Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { a = Vec3<T>(a) - Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator*=(Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { a = Vec3<T>(a) * Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator/=(Swizzle3<T, S, X, Y, Z   >& a, const Vec1<T>& b) noexcept { a = Vec3<T>(a) / Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator+=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { a = Vec4<T>(a) + Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator-=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { a = Vec4<T>(a) - Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator*=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { a = Vec4<T>(a) * Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator/=(Swizzle4<T, S, X, Y, Z, W>& a, const Vec1<T>& b) noexcept { a = Vec4<T>(a) / Vec4<T>(b); return a; }
#pragma endregion
#pragma region .   Swizzle Swizzle
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Vec1<T> operator+(const Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { return Vec1<T>(a) + Vec1<T>(b); }
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Vec1<T> operator-(const Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { return Vec1<T>(a) - Vec1<T>(b); }
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Vec1<T> operator*(const Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { return Vec1<T>(a) * Vec1<T>(b); }
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Vec1<T> operator/(const Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { return Vec1<T>(a) / Vec1<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Vec2<T> operator+(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Vec2<T> operator-(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Vec2<T> operator*(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Vec2<T> operator/(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Vec3<T> operator+(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Vec3<T> operator-(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Vec3<T> operator*(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Vec3<T> operator/(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator+(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator-(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator*(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator/(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }

   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Vec2<T> operator+(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Vec2<T> operator-(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Vec2<T> operator*(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Vec2<T> operator/(const Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Vec3<T> operator+(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Vec3<T> operator-(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Vec3<T> operator*(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Vec3<T> operator/(const Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Vec4<T> operator+(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Vec4<T> operator-(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Vec4<T> operator*(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Vec4<T> operator/(const Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2>                 GML_CI Vec2<T> operator+(const Swizzle1<T, S1, X1>& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2>                 GML_CI Vec2<T> operator-(const Swizzle1<T, S1, X1>& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2>                 GML_CI Vec2<T> operator*(const Swizzle1<T, S1, X1>& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2>                 GML_CI Vec2<T> operator/(const Swizzle1<T, S1, X1>& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2>         GML_CI Vec3<T> operator+(const Swizzle1<T, S1, X1>& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2>         GML_CI Vec3<T> operator-(const Swizzle1<T, S1, X1>& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2>         GML_CI Vec3<T> operator*(const Swizzle1<T, S1, X1>& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2>         GML_CI Vec3<T> operator/(const Swizzle1<T, S1, X1>& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator+(const Swizzle1<T, S1, X1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator-(const Swizzle1<T, S1, X1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator*(const Swizzle1<T, S1, X1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S1, int X1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Vec4<T> operator/(const Swizzle1<T, S1, X1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }

   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Swizzle1<T, S1, X1            >& operator+=(Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { a = Vec1<T>(a) + Vec1<T>(b); return a; }
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Swizzle1<T, S1, X1            >& operator-=(Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { a = Vec1<T>(a) - Vec1<T>(b); return a; }
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Swizzle1<T, S1, X1            >& operator*=(Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { a = Vec1<T>(a) * Vec1<T>(b); return a; }
   template<class T, int S1, int X1, int S2, int X2>                                                 GML_CI Swizzle1<T, S1, X1            >& operator/=(Swizzle1<T, S1, X1            >& a, const Swizzle1<T, S2, X2            >& b) noexcept { a = Vec1<T>(a) / Vec1<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator+=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { a = Vec2<T>(a) + Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator-=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { a = Vec2<T>(a) - Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator*=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { a = Vec2<T>(a) * Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2, int Y2>                                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator/=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle2<T, S2, X2, Y2        >& b) noexcept { a = Vec2<T>(a) / Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator+=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { a = Vec3<T>(a) + Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator-=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { a = Vec3<T>(a) - Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator*=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { a = Vec3<T>(a) * Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2, int Y2, int Z2>                 GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator/=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle3<T, S2, X2, Y2, Z2    >& b) noexcept { a = Vec3<T>(a) / Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator+=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { a = Vec4<T>(a) + Vec4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator-=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { a = Vec4<T>(a) - Vec4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator*=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { a = Vec4<T>(a) * Vec4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator/=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>& b) noexcept { a = Vec4<T>(a) / Vec4<T>(b); return a; }

   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator+=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec2<T>(a) + Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator-=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec2<T>(a) - Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator*=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec2<T>(a) * Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int S2, int X2>                 GML_CI Swizzle2<T, S1, X1, Y1        >& operator/=(Swizzle2<T, S1, X1, Y1        >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec2<T>(a) / Vec2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator+=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec3<T>(a) + Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator-=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec3<T>(a) - Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator*=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec3<T>(a) * Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int S2, int X2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1    >& operator/=(Swizzle3<T, S1, X1, Y1, Z1    >& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec3<T>(a) / Vec3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator+=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec4<T>(a) + Vec4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator-=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec4<T>(a) - Vec4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator*=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec4<T>(a) * Vec4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator/=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) noexcept { a = Vec4<T>(a) / Vec4<T>(b); return a; }
#pragma endregion
#pragma region .   Swizzle Scalar
   template<class T, int S, int X                     > GML_CI Vec1<T> operator+(const Swizzle1<T, S, X         >& a, T b) noexcept { return Vec1<T>(a) + Vec1<T>(b); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator-(const Swizzle1<T, S, X         >& a, T b) noexcept { return Vec1<T>(a) - Vec1<T>(b); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator*(const Swizzle1<T, S, X         >& a, T b) noexcept { return Vec1<T>(a) * Vec1<T>(b); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator/(const Swizzle1<T, S, X         >& a, T b) noexcept { return Vec1<T>(a) / Vec1<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator+(const Swizzle2<T, S, X, Y      >& a, T b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator-(const Swizzle2<T, S, X, Y      >& a, T b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator*(const Swizzle2<T, S, X, Y      >& a, T b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator/(const Swizzle2<T, S, X, Y      >& a, T b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator+(const Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator-(const Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator*(const Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator/(const Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(const Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(const Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator*(const Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator/(const Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator+=(Swizzle1<T, S, X         >& a, T b) noexcept { a += Vec1<T>(b); return a; }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator-=(Swizzle1<T, S, X         >& a, T b) noexcept { a -= Vec1<T>(b); return a; }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator*=(Swizzle1<T, S, X         >& a, T b) noexcept { a *= Vec1<T>(b); return a; }
   template<class T, int S, int X                     > GML_CI Swizzle1<T, S, X         >& operator/=(Swizzle1<T, S, X         >& a, T b) noexcept { a /= Vec1<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator+=(Swizzle2<T, S, X, Y      >& a, T b) noexcept { a += Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator-=(Swizzle2<T, S, X, Y      >& a, T b) noexcept { a -= Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator*=(Swizzle2<T, S, X, Y      >& a, T b) noexcept { a *= Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y              > GML_CI Swizzle2<T, S, X, Y      >& operator/=(Swizzle2<T, S, X, Y      >& a, T b) noexcept { a /= Vec2<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator+=(Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { a += Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator-=(Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { a -= Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator*=(Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { a *= Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z       > GML_CI Swizzle3<T, S, X, Y, Z   >& operator/=(Swizzle3<T, S, X, Y, Z   >& a, T b) noexcept { a /= Vec3<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator+=(Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { a += Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator-=(Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { a -= Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator*=(Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { a *= Vec4<T>(b); return a; }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator/=(Swizzle4<T, S, X, Y, Z, W>& a, T b) noexcept { a /= Vec4<T>(b); return a; }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator+(const Swizzle1<T, S, X         >& a, U b) noexcept { return Vec1<T>(a) + Vec1<T>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator-(const Swizzle1<T, S, X         >& a, U b) noexcept { return Vec1<T>(a) - Vec1<T>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator*(const Swizzle1<T, S, X         >& a, U b) noexcept { return Vec1<T>(a) * Vec1<T>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<T> operator/(const Swizzle1<T, S, X         >& a, U b) noexcept { return Vec1<T>(a) / Vec1<T>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator+(const Swizzle2<T, S, X, Y      >& a, U b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator-(const Swizzle2<T, S, X, Y      >& a, U b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator*(const Swizzle2<T, S, X, Y      >& a, U b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<T> operator/(const Swizzle2<T, S, X, Y      >& a, U b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator+(const Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator-(const Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator*(const Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<T> operator/(const Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator+(const Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator-(const Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator*(const Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<T> operator/(const Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle1<T, S, X         >& operator+=(Swizzle1<T, S, X         >& a, U b) noexcept { a += Vec1<T>(b); return a; }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle1<T, S, X         >& operator-=(Swizzle1<T, S, X         >& a, U b) noexcept { a -= Vec1<T>(b); return a; }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle1<T, S, X         >& operator*=(Swizzle1<T, S, X         >& a, U b) noexcept { a *= Vec1<T>(b); return a; }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle1<T, S, X         >& operator/=(Swizzle1<T, S, X         >& a, U b) noexcept { a /= Vec1<T>(b); return a; }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle2<T, S, X, Y      >& operator+=(Swizzle2<T, S, X, Y      >& a, U b) noexcept { a += Vec2<T>(b); return a; }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle2<T, S, X, Y      >& operator-=(Swizzle2<T, S, X, Y      >& a, U b) noexcept { a -= Vec2<T>(b); return a; }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle2<T, S, X, Y      >& operator*=(Swizzle2<T, S, X, Y      >& a, U b) noexcept { a *= Vec2<T>(b); return a; }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle2<T, S, X, Y      >& operator/=(Swizzle2<T, S, X, Y      >& a, U b) noexcept { a /= Vec2<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle3<T, S, X, Y, Z   >& operator+=(Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { a += Vec3<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle3<T, S, X, Y, Z   >& operator-=(Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { a -= Vec3<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle3<T, S, X, Y, Z   >& operator*=(Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { a *= Vec3<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle3<T, S, X, Y, Z   >& operator/=(Swizzle3<T, S, X, Y, Z   >& a, U b) noexcept { a /= Vec3<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator+=(Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { a += Vec4<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator-=(Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { a -= Vec4<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator*=(Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { a *= Vec4<T>(b); return a; }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Swizzle4<T, S, X, Y, Z, W>& operator/=(Swizzle4<T, S, X, Y, Z, W>& a, U b) noexcept { a /= Vec4<T>(b); return a; }
#pragma endregion
#pragma region .   Scalar Vector
   template<class T> GML_CI Vec1<T> operator+(T a, const Vec1<T>& b) noexcept { return Vec1<T>(a) + b; }
   template<class T> GML_CI Vec2<T> operator+(T a, const Vec2<T>& b) noexcept { return Vec2<T>(a) + b; }
   template<class T> GML_CI Vec3<T> operator+(T a, const Vec3<T>& b) noexcept { return Vec3<T>(a) + b; }
   template<class T> GML_CI Vec4<T> operator+(T a, const Vec4<T>& b) noexcept { return Vec4<T>(a) + b; }
   template<class T> GML_CI Vec1<T> operator-(T a, const Vec1<T>& b) noexcept { return Vec1<T>(a) - b; }
   template<class T> GML_CI Vec2<T> operator-(T a, const Vec2<T>& b) noexcept { return Vec2<T>(a) - b; }
   template<class T> GML_CI Vec3<T> operator-(T a, const Vec3<T>& b) noexcept { return Vec3<T>(a) - b; }
   template<class T> GML_CI Vec4<T> operator-(T a, const Vec4<T>& b) noexcept { return Vec4<T>(a) - b; }
   template<class T> GML_CI Vec1<T> operator*(T a, const Vec1<T>& b) noexcept { return Vec1<T>(a) * b; }
   template<class T> GML_CI Vec2<T> operator*(T a, const Vec2<T>& b) noexcept { return Vec2<T>(a) * b; }
   template<class T> GML_CI Vec3<T> operator*(T a, const Vec3<T>& b) noexcept { return Vec3<T>(a) * b; }
   template<class T> GML_CI Vec4<T> operator*(T a, const Vec4<T>& b) noexcept { return Vec4<T>(a) * b; }
   template<class T> GML_CI Vec1<T> operator/(T a, const Vec1<T>& b) noexcept { return Vec1<T>(a) / b; }
   template<class T> GML_CI Vec2<T> operator/(T a, const Vec2<T>& b) noexcept { return Vec2<T>(a) / b; }
   template<class T> GML_CI Vec3<T> operator/(T a, const Vec3<T>& b) noexcept { return Vec3<T>(a) / b; }
   template<class T> GML_CI Vec4<T> operator/(T a, const Vec4<T>& b) noexcept { return Vec4<T>(a) / b; }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator+(U a, const Vec1<T>& b) noexcept { return Vec1<_mp<T, U>>(a) + Vec1<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator+(U a, const Vec2<T>& b) noexcept { return Vec2<_mp<T, U>>(a) + Vec2<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator+(U a, const Vec3<T>& b) noexcept { return Vec3<_mp<T, U>>(a) + Vec3<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator+(U a, const Vec4<T>& b) noexcept { return Vec4<_mp<T, U>>(a) + Vec4<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator-(U a, const Vec1<T>& b) noexcept { return Vec1<_mp<T, U>>(a) - Vec1<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator-(U a, const Vec2<T>& b) noexcept { return Vec2<_mp<T, U>>(a) - Vec2<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator-(U a, const Vec3<T>& b) noexcept { return Vec3<_mp<T, U>>(a) - Vec3<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator-(U a, const Vec4<T>& b) noexcept { return Vec4<_mp<T, U>>(a) - Vec4<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator*(U a, const Vec1<T>& b) noexcept { return Vec1<_mp<T, U>>(a) * Vec1<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator*(U a, const Vec2<T>& b) noexcept { return Vec2<_mp<T, U>>(a) * Vec2<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator*(U a, const Vec3<T>& b) noexcept { return Vec3<_mp<T, U>>(a) * Vec3<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator*(U a, const Vec4<T>& b) noexcept { return Vec4<_mp<T, U>>(a) * Vec4<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator/(U a, const Vec1<T>& b) noexcept { return Vec1<_mp<T, U>>(a) / Vec1<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator/(U a, const Vec2<T>& b) noexcept { return Vec2<_mp<T, U>>(a) / Vec2<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator/(U a, const Vec3<T>& b) noexcept { return Vec3<_mp<T, U>>(a) / Vec3<_mp<T, U>>(b); }
   template<class T, class U, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator/(U a, const Vec4<T>& b) noexcept { return Vec4<_mp<T, U>>(a) / Vec4<_mp<T, U>>(b); }
#pragma endregion
#pragma region .   Scalar Swizzle
   template<class T, int S, int X                     > GML_CI Vec1<T> operator+(T a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<T>(a) + Vec1<T>(b); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator-(T a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<T>(a) - Vec1<T>(b); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator*(T a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<T>(a) * Vec1<T>(b); }
   template<class T, int S, int X                     > GML_CI Vec1<T> operator/(T a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<T>(a) / Vec1<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator+(T a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) + Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator-(T a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) - Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator*(T a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) * Vec2<T>(b); }
   template<class T, int S, int X, int Y              > GML_CI Vec2<T> operator/(T a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<T>(a) / Vec2<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator+(T a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) + Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator-(T a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) - Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator*(T a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) * Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z       > GML_CI Vec3<T> operator/(T a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<T>(a) / Vec3<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator+(T a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) + Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator-(T a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) - Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator*(T a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) * Vec4<T>(b); }
   template<class T, int S, int X, int Y, int Z, int W> GML_CI Vec4<T> operator/(T a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<T>(a) / Vec4<T>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator+(U a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<_mp<T, U>>(a) + Vec1<_mp<T, U>>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator-(U a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<_mp<T, U>>(a) - Vec1<_mp<T, U>>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator*(U a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<_mp<T, U>>(a) * Vec1<_mp<T, U>>(b); }
   template<class T, class U, int S, int X                     , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec1<_mp<T, U>> operator/(U a, const Swizzle1<T, S, X         >& b) noexcept { return Vec1<_mp<T, U>>(a) / Vec1<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator+(U a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<_mp<T, U>>(a) + Vec2<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator-(U a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<_mp<T, U>>(a) - Vec2<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator*(U a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<_mp<T, U>>(a) * Vec2<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y              , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec2<_mp<T, U>> operator/(U a, const Swizzle2<T, S, X, Y      >& b) noexcept { return Vec2<_mp<T, U>>(a) / Vec2<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator+(U a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<_mp<T, U>>(a) + Vec3<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator-(U a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<_mp<T, U>>(a) - Vec3<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator*(U a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<_mp<T, U>>(a) * Vec3<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z       , GML_ENABLE_IF_NUMBER(U)> GML_CI Vec3<_mp<T, U>> operator/(U a, const Swizzle3<T, S, X, Y, Z   >& b) noexcept { return Vec3<_mp<T, U>>(a) / Vec3<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator+(U a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<_mp<T, U>>(a) + Vec4<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator-(U a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<_mp<T, U>>(a) - Vec4<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator*(U a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<_mp<T, U>>(a) * Vec4<_mp<T, U>>(b); }
   template<class T, class U, int S, int X, int Y, int Z, int W, GML_ENABLE_IF_NUMBER(U)> GML_CI Vec4<_mp<T, U>> operator/(U a, const Swizzle4<T, S, X, Y, Z, W>& b) noexcept { return Vec4<_mp<T, U>>(a) / Vec4<_mp<T, U>>(b); }
#pragma endregion
#pragma endregion
#pragma endregion
}
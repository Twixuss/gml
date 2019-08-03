#pragma once
#include <corecrt_math.h> // sqrt
#include "Traits.h"
#include "Common.h"
#include "Array.h"
#define GML_ENABLE_IF_NUMBER1(A)       class = EnableIf<IsArithmetic<A>>
#define GML_ENABLE_IF_NUMBER2(A,B)     class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>>
#define GML_ENABLE_IF_NUMBER3(A,B,C)   class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>&&IsArithmetic<C>>
#define GML_ENABLE_IF_NUMBER4(A,B,C,D) class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>&&IsArithmetic<C>&&IsArithmetic<D>>
#define GML_ENABLE_IF_NUMBER_R(A,R)    EnableIf<IsArithmetic<A>, R>
namespace gml {
   template<class T, int S, int A>                      struct Swizzle1;
   template<class T, int S, int A, int B>               struct Swizzle2;
   template<class T, int S, int A, int B, int C>        struct Swizzle3;
   template<class T, int S, int A, int B, int C, int D> struct Swizzle4;
   template<class T> struct Vector1;
   template<class T> struct Vector2;
   template<class T> struct Vector3;
   template<class T> struct Vector4;

   template<class T, int S, int A>
   struct Swizzle1 {
      Array<T, S> array;
      GML_CI operator T() const noexcept { return array[A]; }
      GML_CI Swizzle1& operator=(T v) noexcept {
         array[A] = v;
         return *this;
      }
      template<int S2, int X>
      GML_CI Swizzle1& operator=(const Swizzle1<T, S2, X>& v) noexcept {
         array[A] = v.array[X];
         return *this;
      }
      template<int S2>
      GML_CI Swizzle1& operator=(const Vector1<T>& v) noexcept {
         array[A] = v[0];
         return *this;
      }
      T& operator[](int i) { return array[i]; }
      const T& operator[](int i) const { return array[i]; }
   };
   template<class T, int S, int A, int B>
   struct Swizzle2 {
      Array<T, S> array;
      GML_CI Swizzle2& operator=(const Vector2<T>& v) noexcept {
         check();
         array[A] = v.array[0];
         array[B] = v.array[1];
         return *this;
      }
      template<int S2, int X, int Y>
      GML_CI Swizzle2& operator=(const Swizzle2<T, S2, X, Y>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[Y];
         return *this;
      }
      T& operator[](int i) { return array[i]; }
      const T& operator[](int i) const { return array[i]; }
   private:
      static GML_CI void check() noexcept {
         static_assert(A != B, "assign on repeating swizzle is not allowed");
      }
   };
   template<class T, int S, int A, int B, int C>
   struct Swizzle3 {
      Array<T, S> array;
      GML_CI Swizzle3& operator=(const Vector3<T>& v) noexcept {
         check();
         array[A] = v.array[0];
         array[B] = v.array[1];
         array[C] = v.array[2];
         return *this;
      }
      template<int S2, int X, int Y, int Z>
      GML_CI Swizzle3& operator=(const Swizzle3<T, S2, X, Y, Z>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[Y];
         array[C] = v.array[Z];
         return *this;
      }
      T& operator[](int i) { return array[i]; }
      const T& operator[](int i) const { return array[i]; }
   private:
      static GML_CI void check() noexcept {
         static_assert(A != B && A != C && B != C, "assign on repeating swizzle is not allowed");
      }
   };
   template<class T, int S, int A, int B, int C, int D>
   struct Swizzle4 {
      Array<T, S> array;
      GML_C Swizzle4& operator=(const Vector4<T>& v) noexcept {
         check();
         array[A] = v.array[0];
         array[B] = v.array[1];
         array[C] = v.array[2];
         array[D] = v.array[3];
         return *this;
      }
      template<int S2, int X, int Y, int Z, int W>
      GML_C Swizzle4& operator=(const Swizzle4<T, S2, X, Y, Z, W>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[Y];
         array[C] = v.array[Z];
         array[D] = v.array[W];
         return *this;
      }
      T& operator[](int i) { return array[i]; }
      const T& operator[](int i) const { return array[i]; }
   private:
      static GML_CI void check() noexcept {
         static_assert(A != B && A != C && A != D && B != C && B != D && C != D, "assign on repeating swizzle is not allowed");
      }
   };
   template<class T>
   struct Vector1 {
      static_assert(IsArithmetic<T>, "gml::Vector2's template param must be arithmetic");
      union {
         Array<T, 1> array;
         Swizzle1<T, 1, 0> x;
         Swizzle2<T, 1, 0, 0> xx;
         Swizzle3<T, 1, 0, 0, 0> xxx;
         Swizzle4<T, 1, 0, 0, 0, 0> xxxx;
      };
      GML_CI Vector1() {};
      GML_CI Vector1(const Vector1& v) : array(v.array) {};
      template<int S, int A> GML_CI Vector1(const Swizzle1<T, S, A>& s) : array({ s.array[A] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)> GML_CI Vector1(N1 v) : array({ (T)v }) {}
      GML_CI operator T() const { return array[0]; }
      GML_CI T& operator[](int i) noexcept { return array[i]; }
      GML_CI const T& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T>
   struct Vector2 {
      static_assert(IsArithmetic<T>, "gml::Vector2's template param must be arithmetic");
      union {
         Array<T, 2> array;
         Swizzle1<T, 2, 0> x;
         Swizzle1<T, 2, 1> y;
         Swizzle2<T, 2, 0, 0> xx;
         Swizzle2<T, 2, 0, 1> xy;
         Swizzle2<T, 2, 1, 0> yx;
         Swizzle2<T, 2, 1, 1> yy;
         Swizzle3<T, 2, 0, 0, 0> xxx;
         Swizzle3<T, 2, 0, 0, 1> xxy;
         Swizzle3<T, 2, 0, 1, 0> xyx;
         Swizzle3<T, 2, 0, 1, 1> xyy;
         Swizzle3<T, 2, 1, 0, 0> yxx;
         Swizzle3<T, 2, 1, 0, 1> yxy;
         Swizzle3<T, 2, 1, 1, 0> yyx;
         Swizzle3<T, 2, 1, 1, 1> yyy;
         Swizzle4<T, 2, 0, 0, 0, 0> xxxx;
         Swizzle4<T, 2, 0, 0, 0, 1> xxxy;
         Swizzle4<T, 2, 0, 0, 1, 0> xxyx;
         Swizzle4<T, 2, 0, 0, 1, 1> xxyy;
         Swizzle4<T, 2, 0, 1, 0, 0> xyxx;
         Swizzle4<T, 2, 0, 1, 0, 1> xyxy;
         Swizzle4<T, 2, 0, 1, 1, 0> xyyx;
         Swizzle4<T, 2, 0, 1, 1, 1> xyyy;
         Swizzle4<T, 2, 1, 0, 0, 0> yxxx;
         Swizzle4<T, 2, 1, 0, 0, 1> yxxy;
         Swizzle4<T, 2, 1, 0, 1, 0> yxyx;
         Swizzle4<T, 2, 1, 0, 1, 1> yxyy;
         Swizzle4<T, 2, 1, 1, 0, 0> yyxx;
         Swizzle4<T, 2, 1, 1, 0, 1> yyxy;
         Swizzle4<T, 2, 1, 1, 1, 0> yyyx;
         Swizzle4<T, 2, 1, 1, 1, 1> yyyy;
      };
      GML_CI Vector2() {};
      GML_CI Vector2(const Vector2<T>& v) : array(v.array) {}
      GML_CI Vector2(const Vector1<T>& a) : array({ a.array[0], a.array[0] }) {}
      GML_CI Vector2(const Vector1<T>& a, const Vector1<T>& b) : array({ a.array[0], b.array[0] }) {}
      template<int S, int X, int Y> GML_CI Vector2(const Swizzle2<T, S, X, Y>& v) noexcept : array({ v.array[X], v.array[Y] }) {}
      template<int S, int X>        GML_CI Vector2(const Swizzle1<T, S, X   >& v) noexcept : array({ v.array[X], v.array[X] }) {}
      template<int S1, int S2, int X1, int X2> GML_CI Vector2(const Swizzle1<T, S1, X1>& v1, const Swizzle1<T, S2, X2>& v2) noexcept : array({ v1.array[X1], v2.array[X2] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)    > GML_CI Vector2(N1 v) noexcept : array({ T(v),T(v) }) {}
      template<class N1, class N2, GML_ENABLE_IF_NUMBER2(N1, N2)> GML_CI Vector2(N1 x, N2 y) noexcept : array({ T(x),T(y) }) {}
      GML_CI T& operator[](int i) noexcept { return array[i]; }
      GML_CI const T& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T>
   struct Vector3 {
      static_assert(IsArithmetic<T>, "gml::Vector2's template param must be arithmetic");
      union {
         Array<T, 3> array;
         Swizzle1<T, 3, 0> x;
         Swizzle1<T, 3, 1> y;
         Swizzle1<T, 3, 2> z;
         Swizzle2<T, 3, 0, 0> xx;
         Swizzle2<T, 3, 0, 1> xy;
         Swizzle2<T, 3, 0, 2> xz;
         Swizzle2<T, 3, 1, 0> yx;
         Swizzle2<T, 3, 1, 1> yy;
         Swizzle2<T, 3, 1, 2> yz;
         Swizzle2<T, 3, 2, 0> zx;
         Swizzle2<T, 3, 2, 1> zy;
         Swizzle2<T, 3, 2, 2> zz;
         Swizzle3<T, 3, 0, 0, 0> xxx;
         Swizzle3<T, 3, 0, 0, 1> xxy;
         Swizzle3<T, 3, 0, 0, 2> xxz;
         Swizzle3<T, 3, 0, 1, 0> xyx;
         Swizzle3<T, 3, 0, 1, 1> xyy;
         Swizzle3<T, 3, 0, 1, 2> xyz;
         Swizzle3<T, 3, 0, 2, 0> xzx;
         Swizzle3<T, 3, 0, 2, 1> xzy;
         Swizzle3<T, 3, 0, 2, 2> xzz;
         Swizzle3<T, 3, 1, 0, 0> yxx;
         Swizzle3<T, 3, 1, 0, 1> yxy;
         Swizzle3<T, 3, 1, 0, 2> yxz;
         Swizzle3<T, 3, 1, 1, 0> yyx;
         Swizzle3<T, 3, 1, 1, 1> yyy;
         Swizzle3<T, 3, 1, 1, 2> yyz;
         Swizzle3<T, 3, 1, 2, 0> yzx;
         Swizzle3<T, 3, 1, 2, 1> yzy;
         Swizzle3<T, 3, 1, 2, 2> yzz;
         Swizzle3<T, 3, 2, 0, 0> zxx;
         Swizzle3<T, 3, 2, 0, 1> zxy;
         Swizzle3<T, 3, 2, 0, 2> zxz;
         Swizzle3<T, 3, 2, 1, 0> zyx;
         Swizzle3<T, 3, 2, 1, 1> zyy;
         Swizzle3<T, 3, 2, 1, 2> zyz;
         Swizzle3<T, 3, 2, 2, 0> zzx;
         Swizzle3<T, 3, 2, 2, 1> zzy;
         Swizzle3<T, 3, 2, 2, 2> zzz;
         Swizzle4<T, 3, 0, 0, 0, 0> xxxx;
         Swizzle4<T, 3, 0, 0, 0, 1> xxxy;
         Swizzle4<T, 3, 0, 0, 0, 2> xxxz;
         Swizzle4<T, 3, 0, 0, 1, 0> xxyx;
         Swizzle4<T, 3, 0, 0, 1, 1> xxyy;
         Swizzle4<T, 3, 0, 0, 1, 2> xxyz;
         Swizzle4<T, 3, 0, 0, 2, 0> xxzx;
         Swizzle4<T, 3, 0, 0, 2, 1> xxzy;
         Swizzle4<T, 3, 0, 0, 2, 2> xxzz;
         Swizzle4<T, 3, 0, 1, 0, 0> xyxx;
         Swizzle4<T, 3, 0, 1, 0, 1> xyxy;
         Swizzle4<T, 3, 0, 1, 0, 2> xyxz;
         Swizzle4<T, 3, 0, 1, 1, 0> xyyx;
         Swizzle4<T, 3, 0, 1, 1, 1> xyyy;
         Swizzle4<T, 3, 0, 1, 1, 2> xyyz;
         Swizzle4<T, 3, 0, 1, 2, 0> xyzx;
         Swizzle4<T, 3, 0, 1, 2, 1> xyzy;
         Swizzle4<T, 3, 0, 1, 2, 2> xyzz;
         Swizzle4<T, 3, 0, 2, 0, 0> xzxx;
         Swizzle4<T, 3, 0, 2, 0, 1> xzxy;
         Swizzle4<T, 3, 0, 2, 0, 2> xzxz;
         Swizzle4<T, 3, 0, 2, 1, 0> xzyx;
         Swizzle4<T, 3, 0, 2, 1, 1> xzyy;
         Swizzle4<T, 3, 0, 2, 1, 2> xzyz;
         Swizzle4<T, 3, 0, 2, 2, 0> xzzx;
         Swizzle4<T, 3, 0, 2, 2, 1> xzzy;
         Swizzle4<T, 3, 0, 2, 2, 2> xzzz;
         Swizzle4<T, 3, 1, 0, 0, 0> yxxx;
         Swizzle4<T, 3, 1, 0, 0, 1> yxxy;
         Swizzle4<T, 3, 1, 0, 0, 2> yxxz;
         Swizzle4<T, 3, 1, 0, 1, 0> yxyx;
         Swizzle4<T, 3, 1, 0, 1, 1> yxyy;
         Swizzle4<T, 3, 1, 0, 1, 2> yxyz;
         Swizzle4<T, 3, 1, 0, 2, 0> yxzx;
         Swizzle4<T, 3, 1, 0, 2, 1> yxzy;
         Swizzle4<T, 3, 1, 0, 2, 2> yxzz;
         Swizzle4<T, 3, 1, 1, 0, 0> yyxx;
         Swizzle4<T, 3, 1, 1, 0, 1> yyxy;
         Swizzle4<T, 3, 1, 1, 0, 2> yyxz;
         Swizzle4<T, 3, 1, 1, 1, 0> yyyx;
         Swizzle4<T, 3, 1, 1, 1, 1> yyyy;
         Swizzle4<T, 3, 1, 1, 1, 2> yyyz;
         Swizzle4<T, 3, 1, 1, 2, 0> yyzx;
         Swizzle4<T, 3, 1, 1, 2, 1> yyzy;
         Swizzle4<T, 3, 1, 1, 2, 2> yyzz;
         Swizzle4<T, 3, 1, 2, 0, 0> yzxx;
         Swizzle4<T, 3, 1, 2, 0, 1> yzxy;
         Swizzle4<T, 3, 1, 2, 0, 2> yzxz;
         Swizzle4<T, 3, 1, 2, 1, 0> yzyx;
         Swizzle4<T, 3, 1, 2, 1, 1> yzyy;
         Swizzle4<T, 3, 1, 2, 1, 2> yzyz;
         Swizzle4<T, 3, 1, 2, 2, 0> yzzx;
         Swizzle4<T, 3, 1, 2, 2, 1> yzzy;
         Swizzle4<T, 3, 1, 2, 2, 2> yzzz;
         Swizzle4<T, 3, 2, 0, 0, 0> zxxx;
         Swizzle4<T, 3, 2, 0, 0, 1> zxxy;
         Swizzle4<T, 3, 2, 0, 0, 2> zxxz;
         Swizzle4<T, 3, 2, 0, 1, 0> zxyx;
         Swizzle4<T, 3, 2, 0, 1, 1> zxyy;
         Swizzle4<T, 3, 2, 0, 1, 2> zxyz;
         Swizzle4<T, 3, 2, 0, 2, 0> zxzx;
         Swizzle4<T, 3, 2, 0, 2, 1> zxzy;
         Swizzle4<T, 3, 2, 0, 2, 2> zxzz;
         Swizzle4<T, 3, 2, 1, 0, 0> zyxx;
         Swizzle4<T, 3, 2, 1, 0, 1> zyxy;
         Swizzle4<T, 3, 2, 1, 0, 2> zyxz;
         Swizzle4<T, 3, 2, 1, 1, 0> zyyx;
         Swizzle4<T, 3, 2, 1, 1, 1> zyyy;
         Swizzle4<T, 3, 2, 1, 1, 2> zyyz;
         Swizzle4<T, 3, 2, 1, 2, 0> zyzx;
         Swizzle4<T, 3, 2, 1, 2, 1> zyzy;
         Swizzle4<T, 3, 2, 1, 2, 2> zyzz;
         Swizzle4<T, 3, 2, 2, 0, 0> zzxx;
         Swizzle4<T, 3, 2, 2, 0, 1> zzxy;
         Swizzle4<T, 3, 2, 2, 0, 2> zzxz;
         Swizzle4<T, 3, 2, 2, 1, 0> zzyx;
         Swizzle4<T, 3, 2, 2, 1, 1> zzyy;
         Swizzle4<T, 3, 2, 2, 1, 2> zzyz;
         Swizzle4<T, 3, 2, 2, 2, 0> zzzx;
         Swizzle4<T, 3, 2, 2, 2, 1> zzzy;
         Swizzle4<T, 3, 2, 2, 2, 2> zzzz;
      };
      GML_CI Vector3() {}
      GML_CI Vector3(const Vector3<T>& v) : array(v.array) {}
      GML_CI Vector3(const Vector2<T>& xy, const Vector1<T>& z) : array({ xy[0], xy[1], z[0] }) {}
      GML_CI Vector3(const Vector1<T>& x, const Vector2<T>& yz) : array({ x[0], yz[0], yz[1] }) {}
      GML_CI Vector3(const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z) : array({ x[0], y[0], z[0] }) {}
      GML_CI Vector3(const Vector1<T>& v) : array({ v[0], v[0], v[0] }) {}
      template<int S, int X, int Y, int Z>                     GML_CI Vector3(const Swizzle3<T, S, X, Y, Z>& v) : array({ v[X], v[Y], v[Z] }) {}
      template<int S1, int X1, int Y1, int S2, int X2>         GML_CI Vector3(const Swizzle2<T, S1, X1, Y1>& xy, const Swizzle1<T, S2, X2>& z) : array({ xy[X1], xy[Y1], z[X2] }) {}
      template<int S1, int X1, int S2, int X2, int Y2>         GML_CI Vector3(const Swizzle1<T, S1, X1>& x, const Swizzle2<T, S2, X2, Y2>& yz) : array({ x[X1], yz[X2], yz[Y2] }) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3> GML_CI Vector3(const Swizzle1<T, S1, X1>& x, const Swizzle1<T, S2, X2>& y, const Swizzle1<T, S3, X3>& z) : array({ x[X1], y[X2], z[X3] }) {}
      template<int S1, int X1> GML_CI Vector3(const Swizzle1<T, S1, X1>& v) : array({ v[X1], v[X1], v[X1] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)> GML_CI Vector3(N1 v) noexcept : array({ T(v),T(v),T(v) }) {}
      template<class N1, class N2, class N3, GML_ENABLE_IF_NUMBER3(N1, N2, N3)> GML_CI Vector3(N1 x, N2 y, N3 z) noexcept : array({ T(x),T(y),T(z) }) {}
      GML_CI T& operator[](int i) noexcept { return array[i]; }
      GML_CI const T& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T>
   struct Vector4 {
      static_assert(IsArithmetic<T>, "gml::Vector2's template param must be arithmetic");
      union {
         Array<T, 4> array;
         Swizzle1<T, 4, 0> x;
         Swizzle1<T, 4, 1> y;
         Swizzle1<T, 4, 2> z;
         Swizzle1<T, 4, 3> w;
         Swizzle2<T, 4, 0, 0> xx;
         Swizzle2<T, 4, 0, 1> xy;
         Swizzle2<T, 4, 0, 2> xz;
         Swizzle2<T, 4, 0, 3> xw;
         Swizzle2<T, 4, 1, 0> yx;
         Swizzle2<T, 4, 1, 1> yy;
         Swizzle2<T, 4, 1, 2> yz;
         Swizzle2<T, 4, 1, 3> yw;
         Swizzle2<T, 4, 2, 0> zx;
         Swizzle2<T, 4, 2, 1> zy;
         Swizzle2<T, 4, 2, 2> zz;
         Swizzle2<T, 4, 2, 3> zw;
         Swizzle2<T, 4, 3, 0> wx;
         Swizzle2<T, 4, 3, 1> wy;
         Swizzle2<T, 4, 3, 2> wz;
         Swizzle2<T, 4, 3, 3> ww;
         Swizzle3<T, 4, 0, 0, 0> xxx;
         Swizzle3<T, 4, 0, 0, 1> xxy;
         Swizzle3<T, 4, 0, 0, 2> xxz;
         Swizzle3<T, 4, 0, 0, 3> xxw;
         Swizzle3<T, 4, 0, 1, 0> xyx;
         Swizzle3<T, 4, 0, 1, 1> xyy;
         Swizzle3<T, 4, 0, 1, 2> xyz;
         Swizzle3<T, 4, 0, 1, 3> xyw;
         Swizzle3<T, 4, 0, 2, 0> xzx;
         Swizzle3<T, 4, 0, 2, 1> xzy;
         Swizzle3<T, 4, 0, 2, 2> xzz;
         Swizzle3<T, 4, 0, 2, 3> xzw;
         Swizzle3<T, 4, 0, 3, 0> xwx;
         Swizzle3<T, 4, 0, 3, 1> xwy;
         Swizzle3<T, 4, 0, 3, 2> xwz;
         Swizzle3<T, 4, 0, 3, 3> xww;
         Swizzle3<T, 4, 1, 0, 0> yxx;
         Swizzle3<T, 4, 1, 0, 1> yxy;
         Swizzle3<T, 4, 1, 0, 2> yxz;
         Swizzle3<T, 4, 1, 0, 3> yxw;
         Swizzle3<T, 4, 1, 1, 0> yyx;
         Swizzle3<T, 4, 1, 1, 1> yyy;
         Swizzle3<T, 4, 1, 1, 2> yyz;
         Swizzle3<T, 4, 1, 1, 3> yyw;
         Swizzle3<T, 4, 1, 2, 0> yzx;
         Swizzle3<T, 4, 1, 2, 1> yzy;
         Swizzle3<T, 4, 1, 2, 2> yzz;
         Swizzle3<T, 4, 1, 2, 3> yzw;
         Swizzle3<T, 4, 1, 3, 0> ywx;
         Swizzle3<T, 4, 1, 3, 1> ywy;
         Swizzle3<T, 4, 1, 3, 2> ywz;
         Swizzle3<T, 4, 1, 3, 3> yww;
         Swizzle3<T, 4, 2, 0, 0> zxx;
         Swizzle3<T, 4, 2, 0, 1> zxy;
         Swizzle3<T, 4, 2, 0, 2> zxz;
         Swizzle3<T, 4, 2, 0, 3> zxw;
         Swizzle3<T, 4, 2, 1, 0> zyx;
         Swizzle3<T, 4, 2, 1, 1> zyy;
         Swizzle3<T, 4, 2, 1, 2> zyz;
         Swizzle3<T, 4, 2, 1, 3> zyw;
         Swizzle3<T, 4, 2, 2, 0> zzx;
         Swizzle3<T, 4, 2, 2, 1> zzy;
         Swizzle3<T, 4, 2, 2, 2> zzz;
         Swizzle3<T, 4, 2, 2, 3> zzw;
         Swizzle3<T, 4, 2, 3, 0> zwx;
         Swizzle3<T, 4, 2, 3, 1> zwy;
         Swizzle3<T, 4, 2, 3, 2> zwz;
         Swizzle3<T, 4, 2, 3, 3> zww;
         Swizzle3<T, 4, 3, 0, 0> wxx;
         Swizzle3<T, 4, 3, 0, 1> wxy;
         Swizzle3<T, 4, 3, 0, 2> wxz;
         Swizzle3<T, 4, 3, 0, 3> wxw;
         Swizzle3<T, 4, 3, 1, 0> wyx;
         Swizzle3<T, 4, 3, 1, 1> wyy;
         Swizzle3<T, 4, 3, 1, 2> wyz;
         Swizzle3<T, 4, 3, 1, 3> wyw;
         Swizzle3<T, 4, 3, 2, 0> wzx;
         Swizzle3<T, 4, 3, 2, 1> wzy;
         Swizzle3<T, 4, 3, 2, 2> wzz;
         Swizzle3<T, 4, 3, 2, 3> wzw;
         Swizzle3<T, 4, 3, 3, 0> wwx;
         Swizzle3<T, 4, 3, 3, 1> wwy;
         Swizzle3<T, 4, 3, 3, 2> wwz;
         Swizzle3<T, 4, 3, 3, 3> www;
         Swizzle4<T, 4, 0, 0, 0, 0> xxxx;
         Swizzle4<T, 4, 0, 0, 0, 1> xxxy;
         Swizzle4<T, 4, 0, 0, 0, 2> xxxz;
         Swizzle4<T, 4, 0, 0, 0, 3> xxxw;
         Swizzle4<T, 4, 0, 0, 1, 0> xxyx;
         Swizzle4<T, 4, 0, 0, 1, 1> xxyy;
         Swizzle4<T, 4, 0, 0, 1, 2> xxyz;
         Swizzle4<T, 4, 0, 0, 1, 3> xxyw;
         Swizzle4<T, 4, 0, 0, 2, 0> xxzx;
         Swizzle4<T, 4, 0, 0, 2, 1> xxzy;
         Swizzle4<T, 4, 0, 0, 2, 2> xxzz;
         Swizzle4<T, 4, 0, 0, 2, 3> xxzw;
         Swizzle4<T, 4, 0, 0, 3, 0> xxwx;
         Swizzle4<T, 4, 0, 0, 3, 1> xxwy;
         Swizzle4<T, 4, 0, 0, 3, 2> xxwz;
         Swizzle4<T, 4, 0, 0, 3, 3> xxww;
         Swizzle4<T, 4, 0, 1, 0, 0> xyxx;
         Swizzle4<T, 4, 0, 1, 0, 1> xyxy;
         Swizzle4<T, 4, 0, 1, 0, 2> xyxz;
         Swizzle4<T, 4, 0, 1, 0, 3> xyxw;
         Swizzle4<T, 4, 0, 1, 1, 0> xyyx;
         Swizzle4<T, 4, 0, 1, 1, 1> xyyy;
         Swizzle4<T, 4, 0, 1, 1, 2> xyyz;
         Swizzle4<T, 4, 0, 1, 1, 3> xyyw;
         Swizzle4<T, 4, 0, 1, 2, 0> xyzx;
         Swizzle4<T, 4, 0, 1, 2, 1> xyzy;
         Swizzle4<T, 4, 0, 1, 2, 2> xyzz;
         Swizzle4<T, 4, 0, 1, 2, 3> xyzw;
         Swizzle4<T, 4, 0, 1, 3, 0> xywx;
         Swizzle4<T, 4, 0, 1, 3, 1> xywy;
         Swizzle4<T, 4, 0, 1, 3, 2> xywz;
         Swizzle4<T, 4, 0, 1, 3, 3> xyww;
         Swizzle4<T, 4, 0, 2, 0, 0> xzxx;
         Swizzle4<T, 4, 0, 2, 0, 1> xzxy;
         Swizzle4<T, 4, 0, 2, 0, 2> xzxz;
         Swizzle4<T, 4, 0, 2, 0, 3> xzxw;
         Swizzle4<T, 4, 0, 2, 1, 0> xzyx;
         Swizzle4<T, 4, 0, 2, 1, 1> xzyy;
         Swizzle4<T, 4, 0, 2, 1, 2> xzyz;
         Swizzle4<T, 4, 0, 2, 1, 3> xzyw;
         Swizzle4<T, 4, 0, 2, 2, 0> xzzx;
         Swizzle4<T, 4, 0, 2, 2, 1> xzzy;
         Swizzle4<T, 4, 0, 2, 2, 2> xzzz;
         Swizzle4<T, 4, 0, 2, 2, 3> xzzw;
         Swizzle4<T, 4, 0, 2, 3, 0> xzwx;
         Swizzle4<T, 4, 0, 2, 3, 1> xzwy;
         Swizzle4<T, 4, 0, 2, 3, 2> xzwz;
         Swizzle4<T, 4, 0, 2, 3, 3> xzww;
         Swizzle4<T, 4, 0, 3, 0, 0> xwxx;
         Swizzle4<T, 4, 0, 3, 0, 1> xwxy;
         Swizzle4<T, 4, 0, 3, 0, 2> xwxz;
         Swizzle4<T, 4, 0, 3, 0, 3> xwxw;
         Swizzle4<T, 4, 0, 3, 1, 0> xwyx;
         Swizzle4<T, 4, 0, 3, 1, 1> xwyy;
         Swizzle4<T, 4, 0, 3, 1, 2> xwyz;
         Swizzle4<T, 4, 0, 3, 1, 3> xwyw;
         Swizzle4<T, 4, 0, 3, 2, 0> xwzx;
         Swizzle4<T, 4, 0, 3, 2, 1> xwzy;
         Swizzle4<T, 4, 0, 3, 2, 2> xwzz;
         Swizzle4<T, 4, 0, 3, 2, 3> xwzw;
         Swizzle4<T, 4, 0, 3, 3, 0> xwwx;
         Swizzle4<T, 4, 0, 3, 3, 1> xwwy;
         Swizzle4<T, 4, 0, 3, 3, 2> xwwz;
         Swizzle4<T, 4, 0, 3, 3, 3> xwww;
         Swizzle4<T, 4, 1, 0, 0, 0> yxxx;
         Swizzle4<T, 4, 1, 0, 0, 1> yxxy;
         Swizzle4<T, 4, 1, 0, 0, 2> yxxz;
         Swizzle4<T, 4, 1, 0, 0, 3> yxxw;
         Swizzle4<T, 4, 1, 0, 1, 0> yxyx;
         Swizzle4<T, 4, 1, 0, 1, 1> yxyy;
         Swizzle4<T, 4, 1, 0, 1, 2> yxyz;
         Swizzle4<T, 4, 1, 0, 1, 3> yxyw;
         Swizzle4<T, 4, 1, 0, 2, 0> yxzx;
         Swizzle4<T, 4, 1, 0, 2, 1> yxzy;
         Swizzle4<T, 4, 1, 0, 2, 2> yxzz;
         Swizzle4<T, 4, 1, 0, 2, 3> yxzw;
         Swizzle4<T, 4, 1, 0, 3, 0> yxwx;
         Swizzle4<T, 4, 1, 0, 3, 1> yxwy;
         Swizzle4<T, 4, 1, 0, 3, 2> yxwz;
         Swizzle4<T, 4, 1, 0, 3, 3> yxww;
         Swizzle4<T, 4, 1, 1, 0, 0> yyxx;
         Swizzle4<T, 4, 1, 1, 0, 1> yyxy;
         Swizzle4<T, 4, 1, 1, 0, 2> yyxz;
         Swizzle4<T, 4, 1, 1, 0, 3> yyxw;
         Swizzle4<T, 4, 1, 1, 1, 0> yyyx;
         Swizzle4<T, 4, 1, 1, 1, 1> yyyy;
         Swizzle4<T, 4, 1, 1, 1, 2> yyyz;
         Swizzle4<T, 4, 1, 1, 1, 3> yyyw;
         Swizzle4<T, 4, 1, 1, 2, 0> yyzx;
         Swizzle4<T, 4, 1, 1, 2, 1> yyzy;
         Swizzle4<T, 4, 1, 1, 2, 2> yyzz;
         Swizzle4<T, 4, 1, 1, 2, 3> yyzw;
         Swizzle4<T, 4, 1, 1, 3, 0> yywx;
         Swizzle4<T, 4, 1, 1, 3, 1> yywy;
         Swizzle4<T, 4, 1, 1, 3, 2> yywz;
         Swizzle4<T, 4, 1, 1, 3, 3> yyww;
         Swizzle4<T, 4, 1, 2, 0, 0> yzxx;
         Swizzle4<T, 4, 1, 2, 0, 1> yzxy;
         Swizzle4<T, 4, 1, 2, 0, 2> yzxz;
         Swizzle4<T, 4, 1, 2, 0, 3> yzxw;
         Swizzle4<T, 4, 1, 2, 1, 0> yzyx;
         Swizzle4<T, 4, 1, 2, 1, 1> yzyy;
         Swizzle4<T, 4, 1, 2, 1, 2> yzyz;
         Swizzle4<T, 4, 1, 2, 1, 3> yzyw;
         Swizzle4<T, 4, 1, 2, 2, 0> yzzx;
         Swizzle4<T, 4, 1, 2, 2, 1> yzzy;
         Swizzle4<T, 4, 1, 2, 2, 2> yzzz;
         Swizzle4<T, 4, 1, 2, 2, 3> yzzw;
         Swizzle4<T, 4, 1, 2, 3, 0> yzwx;
         Swizzle4<T, 4, 1, 2, 3, 1> yzwy;
         Swizzle4<T, 4, 1, 2, 3, 2> yzwz;
         Swizzle4<T, 4, 1, 2, 3, 3> yzww;
         Swizzle4<T, 4, 1, 3, 0, 0> ywxx;
         Swizzle4<T, 4, 1, 3, 0, 1> ywxy;
         Swizzle4<T, 4, 1, 3, 0, 2> ywxz;
         Swizzle4<T, 4, 1, 3, 0, 3> ywxw;
         Swizzle4<T, 4, 1, 3, 1, 0> ywyx;
         Swizzle4<T, 4, 1, 3, 1, 1> ywyy;
         Swizzle4<T, 4, 1, 3, 1, 2> ywyz;
         Swizzle4<T, 4, 1, 3, 1, 3> ywyw;
         Swizzle4<T, 4, 1, 3, 2, 0> ywzx;
         Swizzle4<T, 4, 1, 3, 2, 1> ywzy;
         Swizzle4<T, 4, 1, 3, 2, 2> ywzz;
         Swizzle4<T, 4, 1, 3, 2, 3> ywzw;
         Swizzle4<T, 4, 1, 3, 3, 0> ywwx;
         Swizzle4<T, 4, 1, 3, 3, 1> ywwy;
         Swizzle4<T, 4, 1, 3, 3, 2> ywwz;
         Swizzle4<T, 4, 1, 3, 3, 3> ywww;
         Swizzle4<T, 4, 2, 0, 0, 0> zxxx;
         Swizzle4<T, 4, 2, 0, 0, 1> zxxy;
         Swizzle4<T, 4, 2, 0, 0, 2> zxxz;
         Swizzle4<T, 4, 2, 0, 0, 3> zxxw;
         Swizzle4<T, 4, 2, 0, 1, 0> zxyx;
         Swizzle4<T, 4, 2, 0, 1, 1> zxyy;
         Swizzle4<T, 4, 2, 0, 1, 2> zxyz;
         Swizzle4<T, 4, 2, 0, 1, 3> zxyw;
         Swizzle4<T, 4, 2, 0, 2, 0> zxzx;
         Swizzle4<T, 4, 2, 0, 2, 1> zxzy;
         Swizzle4<T, 4, 2, 0, 2, 2> zxzz;
         Swizzle4<T, 4, 2, 0, 2, 3> zxzw;
         Swizzle4<T, 4, 2, 0, 3, 0> zxwx;
         Swizzle4<T, 4, 2, 0, 3, 1> zxwy;
         Swizzle4<T, 4, 2, 0, 3, 2> zxwz;
         Swizzle4<T, 4, 2, 0, 3, 3> zxww;
         Swizzle4<T, 4, 2, 1, 0, 0> zyxx;
         Swizzle4<T, 4, 2, 1, 0, 1> zyxy;
         Swizzle4<T, 4, 2, 1, 0, 2> zyxz;
         Swizzle4<T, 4, 2, 1, 0, 3> zyxw;
         Swizzle4<T, 4, 2, 1, 1, 0> zyyx;
         Swizzle4<T, 4, 2, 1, 1, 1> zyyy;
         Swizzle4<T, 4, 2, 1, 1, 2> zyyz;
         Swizzle4<T, 4, 2, 1, 1, 3> zyyw;
         Swizzle4<T, 4, 2, 1, 2, 0> zyzx;
         Swizzle4<T, 4, 2, 1, 2, 1> zyzy;
         Swizzle4<T, 4, 2, 1, 2, 2> zyzz;
         Swizzle4<T, 4, 2, 1, 2, 3> zyzw;
         Swizzle4<T, 4, 2, 1, 3, 0> zywx;
         Swizzle4<T, 4, 2, 1, 3, 1> zywy;
         Swizzle4<T, 4, 2, 1, 3, 2> zywz;
         Swizzle4<T, 4, 2, 1, 3, 3> zyww;
         Swizzle4<T, 4, 2, 2, 0, 0> zzxx;
         Swizzle4<T, 4, 2, 2, 0, 1> zzxy;
         Swizzle4<T, 4, 2, 2, 0, 2> zzxz;
         Swizzle4<T, 4, 2, 2, 0, 3> zzxw;
         Swizzle4<T, 4, 2, 2, 1, 0> zzyx;
         Swizzle4<T, 4, 2, 2, 1, 1> zzyy;
         Swizzle4<T, 4, 2, 2, 1, 2> zzyz;
         Swizzle4<T, 4, 2, 2, 1, 3> zzyw;
         Swizzle4<T, 4, 2, 2, 2, 0> zzzx;
         Swizzle4<T, 4, 2, 2, 2, 1> zzzy;
         Swizzle4<T, 4, 2, 2, 2, 2> zzzz;
         Swizzle4<T, 4, 2, 2, 2, 3> zzzw;
         Swizzle4<T, 4, 2, 2, 3, 0> zzwx;
         Swizzle4<T, 4, 2, 2, 3, 1> zzwy;
         Swizzle4<T, 4, 2, 2, 3, 2> zzwz;
         Swizzle4<T, 4, 2, 2, 3, 3> zzww;
         Swizzle4<T, 4, 2, 3, 0, 0> zwxx;
         Swizzle4<T, 4, 2, 3, 0, 1> zwxy;
         Swizzle4<T, 4, 2, 3, 0, 2> zwxz;
         Swizzle4<T, 4, 2, 3, 0, 3> zwxw;
         Swizzle4<T, 4, 2, 3, 1, 0> zwyx;
         Swizzle4<T, 4, 2, 3, 1, 1> zwyy;
         Swizzle4<T, 4, 2, 3, 1, 2> zwyz;
         Swizzle4<T, 4, 2, 3, 1, 3> zwyw;
         Swizzle4<T, 4, 2, 3, 2, 0> zwzx;
         Swizzle4<T, 4, 2, 3, 2, 1> zwzy;
         Swizzle4<T, 4, 2, 3, 2, 2> zwzz;
         Swizzle4<T, 4, 2, 3, 2, 3> zwzw;
         Swizzle4<T, 4, 2, 3, 3, 0> zwwx;
         Swizzle4<T, 4, 2, 3, 3, 1> zwwy;
         Swizzle4<T, 4, 2, 3, 3, 2> zwwz;
         Swizzle4<T, 4, 2, 3, 3, 3> zwww;
         Swizzle4<T, 4, 3, 0, 0, 0> wxxx;
         Swizzle4<T, 4, 3, 0, 0, 1> wxxy;
         Swizzle4<T, 4, 3, 0, 0, 2> wxxz;
         Swizzle4<T, 4, 3, 0, 0, 3> wxxw;
         Swizzle4<T, 4, 3, 0, 1, 0> wxyx;
         Swizzle4<T, 4, 3, 0, 1, 1> wxyy;
         Swizzle4<T, 4, 3, 0, 1, 2> wxyz;
         Swizzle4<T, 4, 3, 0, 1, 3> wxyw;
         Swizzle4<T, 4, 3, 0, 2, 0> wxzx;
         Swizzle4<T, 4, 3, 0, 2, 1> wxzy;
         Swizzle4<T, 4, 3, 0, 2, 2> wxzz;
         Swizzle4<T, 4, 3, 0, 2, 3> wxzw;
         Swizzle4<T, 4, 3, 0, 3, 0> wxwx;
         Swizzle4<T, 4, 3, 0, 3, 1> wxwy;
         Swizzle4<T, 4, 3, 0, 3, 2> wxwz;
         Swizzle4<T, 4, 3, 0, 3, 3> wxww;
         Swizzle4<T, 4, 3, 1, 0, 0> wyxx;
         Swizzle4<T, 4, 3, 1, 0, 1> wyxy;
         Swizzle4<T, 4, 3, 1, 0, 2> wyxz;
         Swizzle4<T, 4, 3, 1, 0, 3> wyxw;
         Swizzle4<T, 4, 3, 1, 1, 0> wyyx;
         Swizzle4<T, 4, 3, 1, 1, 1> wyyy;
         Swizzle4<T, 4, 3, 1, 1, 2> wyyz;
         Swizzle4<T, 4, 3, 1, 1, 3> wyyw;
         Swizzle4<T, 4, 3, 1, 2, 0> wyzx;
         Swizzle4<T, 4, 3, 1, 2, 1> wyzy;
         Swizzle4<T, 4, 3, 1, 2, 2> wyzz;
         Swizzle4<T, 4, 3, 1, 2, 3> wyzw;
         Swizzle4<T, 4, 3, 1, 3, 0> wywx;
         Swizzle4<T, 4, 3, 1, 3, 1> wywy;
         Swizzle4<T, 4, 3, 1, 3, 2> wywz;
         Swizzle4<T, 4, 3, 1, 3, 3> wyww;
         Swizzle4<T, 4, 3, 2, 0, 0> wzxx;
         Swizzle4<T, 4, 3, 2, 0, 1> wzxy;
         Swizzle4<T, 4, 3, 2, 0, 2> wzxz;
         Swizzle4<T, 4, 3, 2, 0, 3> wzxw;
         Swizzle4<T, 4, 3, 2, 1, 0> wzyx;
         Swizzle4<T, 4, 3, 2, 1, 1> wzyy;
         Swizzle4<T, 4, 3, 2, 1, 2> wzyz;
         Swizzle4<T, 4, 3, 2, 1, 3> wzyw;
         Swizzle4<T, 4, 3, 2, 2, 0> wzzx;
         Swizzle4<T, 4, 3, 2, 2, 1> wzzy;
         Swizzle4<T, 4, 3, 2, 2, 2> wzzz;
         Swizzle4<T, 4, 3, 2, 2, 3> wzzw;
         Swizzle4<T, 4, 3, 2, 3, 0> wzwx;
         Swizzle4<T, 4, 3, 2, 3, 1> wzwy;
         Swizzle4<T, 4, 3, 2, 3, 2> wzwz;
         Swizzle4<T, 4, 3, 2, 3, 3> wzww;
         Swizzle4<T, 4, 3, 3, 0, 0> wwxx;
         Swizzle4<T, 4, 3, 3, 0, 1> wwxy;
         Swizzle4<T, 4, 3, 3, 0, 2> wwxz;
         Swizzle4<T, 4, 3, 3, 0, 3> wwxw;
         Swizzle4<T, 4, 3, 3, 1, 0> wwyx;
         Swizzle4<T, 4, 3, 3, 1, 1> wwyy;
         Swizzle4<T, 4, 3, 3, 1, 2> wwyz;
         Swizzle4<T, 4, 3, 3, 1, 3> wwyw;
         Swizzle4<T, 4, 3, 3, 2, 0> wwzx;
         Swizzle4<T, 4, 3, 3, 2, 1> wwzy;
         Swizzle4<T, 4, 3, 3, 2, 2> wwzz;
         Swizzle4<T, 4, 3, 3, 2, 3> wwzw;
         Swizzle4<T, 4, 3, 3, 3, 0> wwwx;
         Swizzle4<T, 4, 3, 3, 3, 1> wwwy;
         Swizzle4<T, 4, 3, 3, 3, 2> wwwz;
         Swizzle4<T, 4, 3, 3, 3, 3> wwww;
      };
      GML_CI Vector4() {}
      GML_CI Vector4(const Vector4<T>& v) : array(v.array) {}
      GML_CI Vector4(const Vector3<T>& xyz, const Vector1<T>&   w) : array({ xyz[0], xyz[1], xyz[2], w[0] }) {}
      GML_CI Vector4(const Vector1<T>&   x, const Vector3<T>& yzw) : array({ x[0], yzw[0], yzw[1], yzw[2] }) {}
      GML_CI Vector4(const Vector2<T>&  xy, const Vector2<T>&  zw) : array({ xy[0], xy[1], zw[0], zw[1] }) {}
      GML_CI Vector4(const Vector2<T>& xy, const Vector1<T>&  z, const Vector1<T>&  w) : array({ xy[0], xy[1], z[0], w[0] }) {}
      GML_CI Vector4(const Vector1<T>&  x, const Vector2<T>& yz, const Vector1<T>&  w) : array({ x[0], yz[0], yz[1], w[0] }) {}
      GML_CI Vector4(const Vector1<T>&  x, const Vector1<T>&  y, const Vector2<T>& zw) : array({ x[0], y[0], zw[0], zw[1] }) {}
      GML_CI Vector4(const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z, const Vector1<T>& w) : array({ x[0], y[0], z[0], w[0] }) {}
      GML_CI Vector4(const Vector1<T>& v) : array({ v[0], v[0], v[0], v[0] }) {}
      template<int S1, int X1>                                                 GML_CI Vector4(const Swizzle1<T, S1, X1>&           v) noexcept : array({ v[X1], v[X1], v[X1], v[X1] }) {}
      template<int S, int X, int Y, int Z, int W>                              GML_CI Vector4(const Swizzle4<T, S, X, Y, Z, W>&    v) noexcept : array({ v[X], v[Y], v[Z], v[W] }) {}
      template<int S1, int X1, int Y1, int Z1, int S2, int X2>                 GML_CI Vector4(const Swizzle3<T, S1, X1, Y1, Z1>& xyz, const Swizzle1<T, S2, X2>&           w) noexcept : array({ xyz[X1], xyz[Y1], xyz[Z1], w[X2] }) {}
      template<int S1, int X1, int S2, int X2, int Y2, int Z2>                 GML_CI Vector4(const Swizzle1<T, S1, X1>&           x, const Swizzle3<T, S2, X2, Y2, Z2>& yzw) noexcept : array({ x[X1], yzw[X2], yzw[Y2], yzw[Z2] }) {}
      template<int S1, int X1, int Y1, int S2, int X2, int Y2>                 GML_CI Vector4(const Swizzle2<T, S1, X1, Y1>&      xy, const Swizzle2<T, S2, X2, Y2>&      zw) noexcept : array({ xy[X1], xy[Y1], zw[X2], zw[Y2] }) {}
      template<int S1, int X1, int Y1, int S2, int X2, int S3, int X3>         GML_CI Vector4(const Swizzle2<T, S1, X1, Y1>& xy, const Swizzle1<T, S2, X2>&      z, const Swizzle1<T, S3, X3>&      w) noexcept : array({ xy[X1], xy[Y1], z[X2], w[X3] }) {}
      template<int S1, int X1, int S2, int X2, int Y2, int S3, int X3>         GML_CI Vector4(const Swizzle1<T, S1, X1>&      x, const Swizzle2<T, S2, X2, Y2>& yz, const Swizzle1<T, S3, X3>&      w) noexcept : array({ x[X1], yz[X2], yz[Y2], w[X3] }) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3, int Y3>         GML_CI Vector4(const Swizzle1<T, S1, X1>&      x, const Swizzle1<T, S2, X2>&      y, const Swizzle2<T, S3, X3, Y3>& zw) noexcept : array({ x[X1], y[X2], zw[X3], zw[Y3] }) {}
      template<int S1, int X1, int S2, int X2, int S3, int X3, int S4, int X4> GML_CI Vector4(const Swizzle1<T, S1, X1>& x, const Swizzle1<T, S2, X2>& y, const Swizzle1<T, S3, X3>& z, const Swizzle1<T, S4, X4>& w) noexcept : array({ x[X1], y[X2], z[X3], w[X4] }) {}
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)> GML_CI Vector4(N1 v) noexcept : array({ T(v),T(v),T(v),T(v) }) {}
      template<class N1, class N2, class N3, class N4, GML_ENABLE_IF_NUMBER4(N1, N2, N3, N4)> GML_CI Vector4(N1 x, N2 y, N3 z, N4 w) noexcept : array({ T(x),T(y),T(z),T(w) }) {}
      GML_CI T& operator[](int i) noexcept { return array[i]; }
      GML_CI const T& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T> GML_CI bool operator==(const Vector2<T>& a, const Vector2<T>& b) noexcept {
      return
         a.array[0] == b.array[0] &&
         a.array[1] == b.array[1];
   }
   template<class T> GML_CI bool operator==(const Vector3<T>& a, const Vector3<T>& b) noexcept {
      return
         a.array[0] == b.array[0] &&
         a.array[1] == b.array[1] &&
         a.array[2] == b.array[2];
   }
   template<class T> GML_CI bool operator==(const Vector4<T>& a, const Vector4<T>& b) noexcept {
      return
         a.array[0] == b.array[0] &&
         a.array[1] == b.array[1] &&
         a.array[2] == b.array[2] &&
         a.array[3] == b.array[3];
   }
   template<class T, int S, int A, int B> GML_CI bool operator==(const Vector2<T>& a, const Swizzle2<T, S, A, B>& b) noexcept {
      return
         a.array[0] == b.array[A] &&
         a.array[1] == b.array[B];
   }
   template<class T, int S, int A, int B> GML_CI bool operator==(const Swizzle2<T, S, A, B>& a, const Vector2<T>& b) noexcept { return b == a; }
   template<class T, int S, int A, int B, int C> GML_CI bool operator==(const Vector3<T>& a, const Swizzle3<T, S, A, B, C>& b) noexcept {
      return
         a.array[0] == b.array[A] &&
         a.array[1] == b.array[B] &&
         a.array[2] == b.array[C];
   }
   template<class T, int S, int A, int B, int C> GML_CI bool operator==(const Swizzle3<T, S, A, B, C>& a, const Vector3<T>& b) noexcept { return b == a; }
   template<class T, int S, int A, int B, int C, int D> GML_CI bool operator==(const Vector4<T>& a, const Swizzle4<T, S, A, B, C, D>& b) noexcept {
      return
         a.array[0] == b.array[A] &&
         a.array[1] == b.array[B] &&
         a.array[2] == b.array[C] &&
         a.array[3] == b.array[D];
   }
   template<class T, int S, int A, int B, int C, int D> GML_CI bool operator==(const Swizzle4<T, S, A, B, C, D>& a, const Vector4<T>& b) noexcept { return b == a; }

   template<class T> GML_CI Vector1<T> operator+(const Vector1<T>& v) noexcept { return v; }
   template<class T> GML_CI Vector2<T> operator+(const Vector2<T>& v) noexcept { return v; }
   template<class T> GML_CI Vector3<T> operator+(const Vector3<T>& v) noexcept { return v; }
   template<class T> GML_CI Vector4<T> operator+(const Vector4<T>& v) noexcept { return v; }

   template<class T> GML_CI Vector1<T> operator-(const Vector1<T>& v) noexcept { return { -v[0] }; }
   template<class T> GML_CI Vector2<T> operator-(const Vector2<T>& v) noexcept { return { -v[0], -v[1] }; }
   template<class T> GML_CI Vector3<T> operator-(const Vector3<T>& v) noexcept { return { -v[0], -v[1], -v[2] }; }
   template<class T> GML_CI Vector4<T> operator-(const Vector4<T>& v) noexcept { return { -v[0], -v[1], -v[2], -v[3] }; }

   template<class T> GML_CI Vector1<T> operator+(const Vector1<T>& a, const Vector1<T>& b) { return {a[0] + b[0]}; }
   template<class T> GML_CI Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) { return {a[0] + b[0], a[1] + b[1]}; }
   template<class T> GML_CI Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) { return {a[0] + b[0], a[1] + b[1], a[2] + b[2]}; }
   template<class T> GML_CI Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b) { return {a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3] }; }
   template<class T> GML_CI Vector2<T> operator+(const Vector2<T>& a, const Vector1<T>& b) { return { a[0] + b[0], a[1] + b[0] }; }
   template<class T> GML_CI Vector3<T> operator+(const Vector3<T>& a, const Vector1<T>& b) { return { a[0] + b[0], a[1] + b[0], a[2] + b[0] }; }
   template<class T> GML_CI Vector4<T> operator+(const Vector4<T>& a, const Vector1<T>& b) { return { a[0] + b[0], a[1] + b[0], a[2] + b[0], a[3] + b[0] }; }

   template<class T> GML_CI Vector1<T> operator-(const Vector1<T>& a, const Vector1<T>& b) { return { a[0] - b[0] }; }
   template<class T> GML_CI Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) { return { a[0] - b[0], a[1] - b[1] }; }
   template<class T> GML_CI Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) { return { a[0] - b[0], a[1] - b[1], a[2] - b[2] }; }
   template<class T> GML_CI Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b) { return { a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3] }; }
   template<class T> GML_CI Vector2<T> operator-(const Vector2<T>& a, const Vector1<T>& b) { return { a[0] - b[0], a[1] - b[0] }; }
   template<class T> GML_CI Vector3<T> operator-(const Vector3<T>& a, const Vector1<T>& b) { return { a[0] - b[0], a[1] - b[0], a[2] - b[0] }; }
   template<class T> GML_CI Vector4<T> operator-(const Vector4<T>& a, const Vector1<T>& b) { return { a[0] - b[0], a[1] - b[0], a[2] - b[0], a[3] - b[0] }; }

   template<class T> GML_CI Vector1<T> operator*(const Vector1<T>& a, const Vector1<T>& b) { return { a[0] * b[0] }; }
   template<class T> GML_CI Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b) { return { a[0] * b[0], a[1] * b[1] }; }
   template<class T> GML_CI Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b) { return { a[0] * b[0], a[1] * b[1], a[2] * b[2] }; }
   template<class T> GML_CI Vector4<T> operator*(const Vector4<T>& a, const Vector4<T>& b) { return { a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3] }; }
   template<class T> GML_CI Vector2<T> operator*(const Vector2<T>& a, const Vector1<T>& b) { return { a[0] * b[0], a[1] * b[0] }; }
   template<class T> GML_CI Vector3<T> operator*(const Vector3<T>& a, const Vector1<T>& b) { return { a[0] * b[0], a[1] * b[0], a[2] * b[0] }; }
   template<class T> GML_CI Vector4<T> operator*(const Vector4<T>& a, const Vector1<T>& b) { return { a[0] * b[0], a[1] * b[0], a[2] * b[0], a[3] * b[0] }; }

   template<class T> GML_CI Vector1<T> operator/(const Vector1<T>& a, const Vector1<T>& b) { return { a[0] / b[0] }; }
   template<class T> GML_CI Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b) { return { a[0] / b[0], a[1] / b[1] }; }
   template<class T> GML_CI Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b) { return { a[0] / b[0], a[1] / b[1], a[2] / b[2] }; }
   template<class T> GML_CI Vector4<T> operator/(const Vector4<T>& a, const Vector4<T>& b) { return { a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3] }; }
   template<class T> GML_CI Vector2<T> operator/(const Vector2<T>& a, const Vector1<T>& b) { return { a[0] / b[0], a[1] / b[0] }; }
   template<class T> GML_CI Vector3<T> operator/(const Vector3<T>& a, const Vector1<T>& b) { return { a[0] / b[0], a[1] / b[0], a[2] / b[0] }; }
   template<class T> GML_CI Vector4<T> operator/(const Vector4<T>& a, const Vector1<T>& b) { return { a[0] / b[0], a[1] / b[0], a[2] / b[0], a[3] / b[0] }; }

   template<class T> GML_CI Vector1<T> operator+=(Vector1<T>& a, const Vector1<T>& b) { a = a + b; return a; }
   template<class T> GML_CI Vector2<T> operator+=(Vector2<T>& a, const Vector2<T>& b) { a = a + b; return a; }
   template<class T> GML_CI Vector3<T> operator+=(Vector3<T>& a, const Vector3<T>& b) { a = a + b; return a; }
   template<class T> GML_CI Vector4<T> operator+=(Vector4<T>& a, const Vector4<T>& b) { a = a + b; return a; }

   template<class T> GML_CI Vector1<T> operator-=(Vector1<T>& a, const Vector1<T>& b) { a = a - b; return a; }
   template<class T> GML_CI Vector2<T> operator-=(Vector2<T>& a, const Vector2<T>& b) { a = a - b; return a; }
   template<class T> GML_CI Vector3<T> operator-=(Vector3<T>& a, const Vector3<T>& b) { a = a - b; return a; }
   template<class T> GML_CI Vector4<T> operator-=(Vector4<T>& a, const Vector4<T>& b) { a = a - b; return a; }

   template<class T> GML_CI Vector1<T> operator*=(Vector1<T>& a, const Vector1<T>& b) { a = a * b; return a; }
   template<class T> GML_CI Vector2<T> operator*=(Vector2<T>& a, const Vector2<T>& b) { a = a * b; return a; }
   template<class T> GML_CI Vector3<T> operator*=(Vector3<T>& a, const Vector3<T>& b) { a = a * b; return a; }
   template<class T> GML_CI Vector4<T> operator*=(Vector4<T>& a, const Vector4<T>& b) { a = a * b; return a; }

   template<class T> GML_CI Vector1<T> operator/=(Vector1<T>& a, const Vector1<T>& b) { a = a / b; return a; }
   template<class T> GML_CI Vector2<T> operator/=(Vector2<T>& a, const Vector2<T>& b) { a = a / b; return a; }
   template<class T> GML_CI Vector3<T> operator/=(Vector3<T>& a, const Vector3<T>& b) { a = a / b; return a; }
   template<class T> GML_CI Vector4<T> operator/=(Vector4<T>& a, const Vector4<T>& b) { a = a / b; return a; }

   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator+(const Vector1<T>& a, U b) { return a + Vector1<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator+(const Vector2<T>& a, U b) { return a + Vector2<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator+(const Vector3<T>& a, U b) { return a + Vector3<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator+(const Vector4<T>& a, U b) { return a + Vector4<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator-(const Vector1<T>& a, U b) { return a - Vector1<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator-(const Vector2<T>& a, U b) { return a - Vector2<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator-(const Vector3<T>& a, U b) { return a - Vector3<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator-(const Vector4<T>& a, U b) { return a - Vector4<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator*(const Vector1<T>& a, U b) { return a * Vector1<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator*(const Vector2<T>& a, U b) { return a * Vector2<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator*(const Vector3<T>& a, U b) { return a * Vector3<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator*(const Vector4<T>& a, U b) { return a * Vector4<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator/(const Vector1<T>& a, U b) { return a / Vector1<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator/(const Vector2<T>& a, U b) { return a / Vector2<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator/(const Vector3<T>& a, U b) { return a / Vector3<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator/(const Vector4<T>& a, U b) { return a / Vector4<T>(b); }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator+(U a, const Vector1<T>& b) { return Vector1<T>(a) + b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator+(U a, const Vector2<T>& b) { return Vector2<T>(a) + b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator+(U a, const Vector3<T>& b) { return Vector3<T>(a) + b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator+(U a, const Vector4<T>& b) { return Vector4<T>(a) + b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator-(U a, const Vector1<T>& b) { return Vector1<T>(a) - b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator-(U a, const Vector2<T>& b) { return Vector2<T>(a) - b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator-(U a, const Vector3<T>& b) { return Vector3<T>(a) - b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator-(U a, const Vector4<T>& b) { return Vector4<T>(a) - b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator*(U a, const Vector1<T>& b) { return Vector1<T>(a) * b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator*(U a, const Vector2<T>& b) { return Vector2<T>(a) * b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator*(U a, const Vector3<T>& b) { return Vector3<T>(a) * b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator*(U a, const Vector4<T>& b) { return Vector4<T>(a) * b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator/(U a, const Vector1<T>& b) { return Vector1<T>(a) / b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector2<T>) operator/(U a, const Vector2<T>& b) { return Vector2<T>(a) / b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector3<T>) operator/(U a, const Vector3<T>& b) { return Vector3<T>(a) / b; }
   template<class T, class U> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector4<T>) operator/(U a, const Vector4<T>& b) { return Vector4<T>(a) / b; }

   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator+(const Swizzle1<T, S, A>& a, U b) { return Vector1<T>(a) + Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator+(U a, const Swizzle1<T, S, A>& b) { return Vector1<T>(a) + Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator-(const Swizzle1<T, S, A>& a, U b) { return Vector1<T>(a) - Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator-(U a, const Swizzle1<T, S, A>& b) { return Vector1<T>(a) - Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator*(const Swizzle1<T, S, A>& a, U b) { return Vector1<T>(a) * Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator*(U a, const Swizzle1<T, S, A>& b) { return Vector1<T>(a) * Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator/(const Swizzle1<T, S, A>& a, U b) { return Vector1<T>(a) / Vector1<T>(b); }
   template<class T, class U, int S, int A> GML_CI GML_ENABLE_IF_NUMBER_R(U, Vector1<T>) operator/(U a, const Swizzle1<T, S, A>& b) { return Vector1<T>(a) / Vector1<T>(b); }

   template<class T, int S, int A> GML_CI Vector1<T> operator+(const Swizzle1<T, S, A>& a, const Vector1<T>& b) { return Vector1<T>(a) + b; }
   template<class T, int S, int A> GML_CI Vector1<T> operator-(const Swizzle1<T, S, A>& a, const Vector1<T>& b) { return Vector1<T>(a) - b; }
   template<class T, int S, int A> GML_CI Vector1<T> operator*(const Swizzle1<T, S, A>& a, const Vector1<T>& b) { return Vector1<T>(a) * b; }
   template<class T, int S, int A> GML_CI Vector1<T> operator/(const Swizzle1<T, S, A>& a, const Vector1<T>& b) { return Vector1<T>(a) / b; }

   template<class T, int S, int A> GML_CI Vector1<T> operator-(const Swizzle1<T, S, A>& a) { return -Vector1<T>(a); }

   template<class T, int S, int A> GML_CI                      Swizzle1<T, S, A>&          operator+=(Swizzle1<T, S, A>&          a, const Vector1<T>& b) { a = Vector1<T>(a) + b; return a; }
   template<class T, int S, int A> GML_CI                      Swizzle1<T, S, A>&          operator-=(Swizzle1<T, S, A>&          a, const Vector1<T>& b) { a = Vector1<T>(a) - b; return a; }
   template<class T, int S, int A> GML_CI                      Swizzle1<T, S, A>&          operator*=(Swizzle1<T, S, A>&          a, const Vector1<T>& b) { a = Vector1<T>(a) * b; return a; }
   template<class T, int S, int A> GML_CI                      Swizzle1<T, S, A>&          operator/=(Swizzle1<T, S, A>&          a, const Vector1<T>& b) { a = Vector1<T>(a) / b; return a; }
   template<class T, int S, int A, int B> GML_CI               Swizzle2<T, S, A, B>&       operator+=(Swizzle2<T, S, A, B>&       a, const Vector2<T>& b) { a = Vector2<T>(a) + b; return a; }
   template<class T, int S, int A, int B> GML_CI               Swizzle2<T, S, A, B>&       operator-=(Swizzle2<T, S, A, B>&       a, const Vector2<T>& b) { a = Vector2<T>(a) - b; return a; }
   template<class T, int S, int A, int B> GML_CI               Swizzle2<T, S, A, B>&       operator*=(Swizzle2<T, S, A, B>&       a, const Vector2<T>& b) { a = Vector2<T>(a) * b; return a; }
   template<class T, int S, int A, int B> GML_CI               Swizzle2<T, S, A, B>&       operator/=(Swizzle2<T, S, A, B>&       a, const Vector2<T>& b) { a = Vector2<T>(a) / b; return a; }
   template<class T, int S, int A, int B, int C> GML_CI        Swizzle3<T, S, A, B, C>&    operator+=(Swizzle3<T, S, A, B, C>&    a, const Vector3<T>& b) { a = Vector3<T>(a) + b; return a; }
   template<class T, int S, int A, int B, int C> GML_CI        Swizzle3<T, S, A, B, C>&    operator-=(Swizzle3<T, S, A, B, C>&    a, const Vector3<T>& b) { a = Vector3<T>(a) - b; return a; }
   template<class T, int S, int A, int B, int C> GML_CI        Swizzle3<T, S, A, B, C>&    operator*=(Swizzle3<T, S, A, B, C>&    a, const Vector3<T>& b) { a = Vector3<T>(a) * b; return a; }
   template<class T, int S, int A, int B, int C> GML_CI        Swizzle3<T, S, A, B, C>&    operator/=(Swizzle3<T, S, A, B, C>&    a, const Vector3<T>& b) { a = Vector3<T>(a) / b; return a; }
   template<class T, int S, int A, int B, int C, int D> GML_CI Swizzle4<T, S, A, B, C, D>& operator+=(Swizzle4<T, S, A, B, C, D>& a, const Vector4<T>& b) { a = Vector4<T>(a) + b; return a; }
   template<class T, int S, int A, int B, int C, int D> GML_CI Swizzle4<T, S, A, B, C, D>& operator-=(Swizzle4<T, S, A, B, C, D>& a, const Vector4<T>& b) { a = Vector4<T>(a) - b; return a; }
   template<class T, int S, int A, int B, int C, int D> GML_CI Swizzle4<T, S, A, B, C, D>& operator*=(Swizzle4<T, S, A, B, C, D>& a, const Vector4<T>& b) { a = Vector4<T>(a) * b; return a; }
   template<class T, int S, int A, int B, int C, int D> GML_CI Swizzle4<T, S, A, B, C, D>& operator/=(Swizzle4<T, S, A, B, C, D>& a, const Vector4<T>& b) { a = Vector4<T>(a) / b; return a; }
   
   template<class T, int S1, int X1                        , int S2, int X2>                         GML_CI Swizzle1<T, S1, X1>&             operator+=(Swizzle1<T, S1, X1>&             a, const Swizzle1<T, S2, X2>&            b) { a = Vector1<T>(a) + Vector1<T>(b); return a; }
   template<class T, int S1, int X1                        , int S2, int X2>                         GML_CI Swizzle1<T, S1, X1>&             operator-=(Swizzle1<T, S1, X1>&             a, const Swizzle1<T, S2, X2>&            b) { a = Vector1<T>(a) - Vector1<T>(b); return a; }
   template<class T, int S1, int X1                        , int S2, int X2>                         GML_CI Swizzle1<T, S1, X1>&             operator*=(Swizzle1<T, S1, X1>&             a, const Swizzle1<T, S2, X2>&            b) { a = Vector1<T>(a) * Vector1<T>(b); return a; }
   template<class T, int S1, int X1                        , int S2, int X2>                         GML_CI Swizzle1<T, S1, X1>&             operator/=(Swizzle1<T, S1, X1>&             a, const Swizzle1<T, S2, X2>&            b) { a = Vector1<T>(a) / Vector1<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2, int Y2>                 GML_CI Swizzle2<T, S1, X1, Y1>&         operator+=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle2<T, S2, X2, Y2>&        b) { a = Vector2<T>(a) + Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2, int Y2>                 GML_CI Swizzle2<T, S1, X1, Y1>&         operator-=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle2<T, S2, X2, Y2>&        b) { a = Vector2<T>(a) - Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2, int Y2>                 GML_CI Swizzle2<T, S1, X1, Y1>&         operator*=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle2<T, S2, X2, Y2>&        b) { a = Vector2<T>(a) * Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2, int Y2>                 GML_CI Swizzle2<T, S1, X1, Y1>&         operator/=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle2<T, S2, X2, Y2>&        b) { a = Vector2<T>(a) / Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2, int Y2, int Z2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator+=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle3<T, S2, X2, Y2, Z2>&    b) { a = Vector3<T>(a) + Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2, int Y2, int Z2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator-=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle3<T, S2, X2, Y2, Z2>&    b) { a = Vector3<T>(a) - Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2, int Y2, int Z2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator*=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle3<T, S2, X2, Y2, Z2>&    b) { a = Vector3<T>(a) * Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2, int Y2, int Z2>         GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator/=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle3<T, S2, X2, Y2, Z2>&    b) { a = Vector3<T>(a) / Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator+=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>&b) { a = Vector4<T>(a) + Vector4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator-=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>&b) { a = Vector4<T>(a) - Vector4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator*=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>&b) { a = Vector4<T>(a) * Vector4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2, int Y2, int Z2, int W2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator/=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle4<T, S2, X2, Y2, Z2, W2>&b) { a = Vector4<T>(a) / Vector4<T>(b); return a; }
   
   template<class T, int S1, int X1, int Y1                , int S2, int X2> GML_CI Swizzle2<T, S1, X1, Y1>&         operator+=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle1<T, S2, X2>& b) { a = Vector2<T>(a) + Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2> GML_CI Swizzle2<T, S1, X1, Y1>&         operator-=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle1<T, S2, X2>& b) { a = Vector2<T>(a) - Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2> GML_CI Swizzle2<T, S1, X1, Y1>&         operator*=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle1<T, S2, X2>& b) { a = Vector2<T>(a) * Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1                , int S2, int X2> GML_CI Swizzle2<T, S1, X1, Y1>&         operator/=(Swizzle2<T, S1, X1, Y1>&         a, const Swizzle1<T, S2, X2>& b) { a = Vector2<T>(a) / Vector2<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2> GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator+=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle1<T, S2, X2>& b) { a = Vector3<T>(a) + Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2> GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator-=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle1<T, S2, X2>& b) { a = Vector3<T>(a) - Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2> GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator*=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle1<T, S2, X2>& b) { a = Vector3<T>(a) * Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1        , int S2, int X2> GML_CI Swizzle3<T, S1, X1, Y1, Z1>&     operator/=(Swizzle3<T, S1, X1, Y1, Z1>&     a, const Swizzle1<T, S2, X2>& b) { a = Vector3<T>(a) / Vector3<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator+=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) { a = Vector4<T>(a) + Vector4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator-=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) { a = Vector4<T>(a) - Vector4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator*=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) { a = Vector4<T>(a) * Vector4<T>(b); return a; }
   template<class T, int S1, int X1, int Y1, int Z1, int W1, int S2, int X2> GML_CI Swizzle4<T, S1, X1, Y1, Z1, W1>& operator/=(Swizzle4<T, S1, X1, Y1, Z1, W1>& a, const Swizzle1<T, S2, X2>& b) { a = Vector4<T>(a) / Vector4<T>(b); return a; }

   GML_CI float  Sqrt(float  x, float  curr, float  prev) noexcept { return curr == prev ? curr : Sqrt(x, 0.5f * (curr + x / curr), curr); }
   GML_CI double Sqrt(double x, double curr, double prev) noexcept { return curr == prev ? curr : Sqrt(x, 0.5  * (curr + x / curr), curr); }
   GML_CI Vector2<float> Sqrt(Vector2<float> x, Vector2<float> curr, Vector2<float> prev) noexcept { return curr == prev ? curr : Sqrt(x, (curr + x / curr) * 0.5f, curr); }
   GML_CI Vector3<float> Sqrt(Vector3<float> x, Vector3<float> curr, Vector3<float> prev) noexcept { return curr == prev ? curr : Sqrt(x, (curr + x / curr) * 0.5f, curr); }
   GML_CI Vector4<float> Sqrt(Vector4<float> x, Vector4<float> curr, Vector4<float> prev) noexcept { return curr == prev ? curr : Sqrt(x, (curr + x / curr) * 0.5f, curr); }
   
   template<class T>
   GML_CI T Sqrt(T x) {
      return x >= 0 && x < std::numeric_limits<T>::infinity() ? Sqrt<T>(x, x, static_cast<T>(0)) : std::numeric_limits<T>::quiet_NaN();
   }
   GML_I float Sqrt(float x) { return sqrtf(x); }
   GML_I double Sqrt(double x) { return sqrt(x); }
   template<class T> GML_CI T LengthSqr(const Vector2<T>& v) noexcept { return v[0] * v[0] + v[1] * v[1]; }
   template<class T> GML_CI T LengthSqr(const Vector3<T>& v) noexcept { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
   template<class T> GML_CI T LengthSqr(const Vector4<T>& v) noexcept { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]; }
   template<class T> GML_CI T Length(const Vector2<T>& v) noexcept { return Sqrt(LengthSqr(v)); }
   template<class T> GML_CI T Length(const Vector3<T>& v) noexcept { return Sqrt(LengthSqr(v)); }
   template<class T> GML_CI T Length(const Vector4<T>& v) noexcept { return Sqrt(LengthSqr(v)); }
   template<class T> GML_CI Vector2<T> Normalize(const Vector2<T>& v) noexcept { return v / Length(v); }
   template<class T> GML_CI Vector3<T> Normalize(const Vector3<T>& v) noexcept { return v / Length(v); }
   template<class T> GML_CI Vector4<T> Normalize(const Vector4<T>& v) noexcept { return v / Length(v); }
}
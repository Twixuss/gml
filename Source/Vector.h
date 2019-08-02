#pragma once
#include <corecrt_math.h> // sqrt
#include <xtr1common>
#define GML_I __forceinline
#define GML_C constexpr
#define GML_CI GML_C GML_I
#define GML_ENABLE_IF_NUMBER1(A)       class = EnableIf<IsArithmetic<A>>
#define GML_ENABLE_IF_NUMBER2(A,B)     class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>>
#define GML_ENABLE_IF_NUMBER3(A,B,C)   class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>&&IsArithmetic<C>>
#define GML_ENABLE_IF_NUMBER4(A,B,C,D) class = EnableIf<IsArithmetic<A>&&IsArithmetic<B>&&IsArithmetic<C>&&IsArithmetic<D>>
namespace gml {
   template<bool b, class T = void> struct EnableIf_ {};
   template<class T> struct EnableIf_<true, T> { using Type = T; };
   template<bool b, class T = void>
   using EnableIf = typename EnableIf_<b, T>::Type;

   template<class T> inline constexpr bool IsArithmetic = false;
   template<> inline constexpr bool IsArithmetic<bool> = true;
   template<> inline constexpr bool IsArithmetic<signed char> = true;
   template<> inline constexpr bool IsArithmetic<signed short> = true;
   template<> inline constexpr bool IsArithmetic<signed int> = true;
   template<> inline constexpr bool IsArithmetic<signed long> = true;
   template<> inline constexpr bool IsArithmetic<signed long long> = true;
   template<> inline constexpr bool IsArithmetic<unsigned char> = true;
   template<> inline constexpr bool IsArithmetic<unsigned short> = true;
   template<> inline constexpr bool IsArithmetic<unsigned int> = true;
   template<> inline constexpr bool IsArithmetic<unsigned long> = true;
   template<> inline constexpr bool IsArithmetic<unsigned long long> = true;
   template<> inline constexpr bool IsArithmetic<float> = true;
   template<> inline constexpr bool IsArithmetic<double> = true;
   template<> inline constexpr bool IsArithmetic<long double> = true;

   template<class T, int S>
   struct Array {
      T v[S];
      GML_CI T& operator[](size_t i) { return v[i]; }
      GML_CI const T& operator[](size_t i)  const { return v[i]; }
   };
   template<class T, int S, int A>                      struct Swizzle1;
   template<class T, int S, int A, int B>               struct Swizzle2;
   template<class T, int S, int A, int B, int C>        struct Swizzle3;
   template<class T, int S, int A, int B, int C, int D> struct Swizzle4;
   template<class T> struct Vector2;
   template<class T> struct Vector3;
   template<class T> struct Vector4;

   template<class T, int S, int A>
   struct Swizzle1 {
      Array<T, S> array;
      GML_CI operator T& () noexcept { return array[A]; }
      GML_CI operator const T& () const noexcept { return array[A]; }
   };
   template<class T, int S, int A, int B>
   struct Swizzle2 {
      Array<T, S> array;
      GML_C Swizzle2& operator=(const Vector2<T>& v) noexcept {
         check();
         array[A] = v.array[0];
         array[B] = v.array[1];
         return *this;
      }
      template<int S2, int X>
      GML_C Swizzle2& operator=(const Swizzle1<T, S2, X>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[X];
         return *this;
      }
      template<int S2, int X, int Y>
      GML_C Swizzle2& operator=(const Swizzle2<T, S2, X, Y>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[Y];
         return *this;
      }
   private:
      static GML_CI void check() noexcept {
         static_assert(A != B, "assign on repeating swizzle is not allowed");
      }
   };
   template<class T, int S, int A, int B, int C>
   struct Swizzle3 {
      Array<T, S> array;
      GML_C Swizzle3& operator=(const Vector3<T>& v) noexcept {
         check();
         array[A] = v.array[0];
         array[B] = v.array[1];
         array[C] = v.array[2];
         return *this;
      }
      template<int S2, int X>
      GML_C Swizzle3& operator=(const Swizzle1<T, S2, X>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[X];
         array[C] = v.array[X];
         return *this;
      }
      template<int S2, int X, int Y, int Z>
      GML_C Swizzle3& operator=(const Swizzle3<T, S2, X, Y, Z>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[Y];
         array[C] = v.array[Z];
         return *this;
      }
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
      template<int S2, int X>
      GML_C Swizzle4& operator=(const Swizzle1<T, S2, X>& v) noexcept {
         check();
         array[A] = v.array[X];
         array[B] = v.array[X];
         array[C] = v.array[X];
         array[D] = v.array[X];
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
   private:
      static GML_CI void check() noexcept {
         static_assert(A != B && A != C && A != D && B != C && B != D && C != D, "assign on repeating swizzle is not allowed");
      }
   };
   template<class T>
   struct Vector2 {
      static_assert(std::is_arithmetic_v<T>, "gml::Vector2's template param must be arithmetic");
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
      GML_CI Vector2() = default;
      GML_CI Vector2(const Vector2&) = default;
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)> GML_CI Vector2(N1 v) noexcept : array({ T(v),T(v) }) {}
      template<class N1, class N2, GML_ENABLE_IF_NUMBER2(N1, N2)> GML_CI Vector2(N1 x, N2 y) noexcept : array({ T(x),T(y) }) {}
      template<int S, int A, int B> GML_CI Vector2(const Swizzle2<T, S, A, B>& v) noexcept : array({v.array[A], v.array[B]}) {}
      GML_CI T& operator[](int i) noexcept { return array[i]; }
      GML_CI const T& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T>
   struct Vector3 {
      static_assert(std::is_arithmetic_v<T>, "gml::Vector2's template param must be arithmetic");
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
      GML_CI Vector3() = default;
      GML_CI Vector3(const Vector3&) = default;
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)> GML_CI Vector3(N1 v) noexcept : array({ T(v),T(v),T(v) }) {}
      template<class N1, class N2, class N3, GML_ENABLE_IF_NUMBER3(N1, N2, N3)> GML_CI Vector3(N1 x, N2 y, N3 z) noexcept : array({ T(x),T(y),T(z) }) {}
      template<int S, int A, int B, int C> GML_CI Vector3(const Swizzle3<T, S, A, B, C>& v) noexcept : array({v.array[A], v.array[B], v.array[C]}) {}
      GML_CI T& operator[](int i) noexcept { return array[i]; }
      GML_CI const T& operator[](int i) const noexcept { return array[i]; }
   };
   template<class T>
   struct Vector4 {
      static_assert(std::is_arithmetic_v<T>, "gml::Vector2's template param must be arithmetic");
      union {
         Array<T, 4> array;
         Swizzle1<T, 4, 0> x;
         Swizzle1<T, 4, 1> y;
         Swizzle1<T, 4, 2> z;
         Swizzle2<T, 4, 0, 0> xx;
         Swizzle2<T, 4, 0, 1> xy;
         Swizzle2<T, 4, 0, 2> xz;
         Swizzle2<T, 4, 1, 0> yx;
         Swizzle2<T, 4, 1, 1> yy;
         Swizzle2<T, 4, 1, 2> yz;
         Swizzle2<T, 4, 2, 0> zx;
         Swizzle2<T, 4, 2, 1> zy;
         Swizzle2<T, 4, 2, 2> zz;
         Swizzle3<T, 4, 0, 0, 0> xxx;
         Swizzle3<T, 4, 0, 0, 1> xxy;
         Swizzle3<T, 4, 0, 0, 2> xxz;
         Swizzle3<T, 4, 0, 1, 0> xyx;
         Swizzle3<T, 4, 0, 1, 1> xyy;
         Swizzle3<T, 4, 0, 1, 2> xyz;
         Swizzle3<T, 4, 0, 2, 0> xzx;
         Swizzle3<T, 4, 0, 2, 1> xzy;
         Swizzle3<T, 4, 0, 2, 2> xzz;
         Swizzle3<T, 4, 1, 0, 0> yxx;
         Swizzle3<T, 4, 1, 0, 1> yxy;
         Swizzle3<T, 4, 1, 0, 2> yxz;
         Swizzle3<T, 4, 1, 1, 0> yyx;
         Swizzle3<T, 4, 1, 1, 1> yyy;
         Swizzle3<T, 4, 1, 1, 2> yyz;
         Swizzle3<T, 4, 1, 2, 0> yzx;
         Swizzle3<T, 4, 1, 2, 1> yzy;
         Swizzle3<T, 4, 1, 2, 2> yzz;
         Swizzle3<T, 4, 2, 0, 0> zxx;
         Swizzle3<T, 4, 2, 0, 1> zxy;
         Swizzle3<T, 4, 2, 0, 2> zxz;
         Swizzle3<T, 4, 2, 1, 0> zyx;
         Swizzle3<T, 4, 2, 1, 1> zyy;
         Swizzle3<T, 4, 2, 1, 2> zyz;
         Swizzle3<T, 4, 2, 2, 0> zzx;
         Swizzle3<T, 4, 2, 2, 1> zzy;
         Swizzle3<T, 4, 2, 2, 2> zzz;
         Swizzle4<T, 4, 0, 0, 0, 0> xxxx;
         Swizzle4<T, 4, 0, 0, 0, 1> xxxy;
         Swizzle4<T, 4, 0, 0, 0, 2> xxxz;
         Swizzle4<T, 4, 0, 0, 1, 0> xxyx;
         Swizzle4<T, 4, 0, 0, 1, 1> xxyy;
         Swizzle4<T, 4, 0, 0, 1, 2> xxyz;
         Swizzle4<T, 4, 0, 0, 2, 0> xxzx;
         Swizzle4<T, 4, 0, 0, 2, 1> xxzy;
         Swizzle4<T, 4, 0, 0, 2, 2> xxzz;
         Swizzle4<T, 4, 0, 1, 0, 0> xyxx;
         Swizzle4<T, 4, 0, 1, 0, 1> xyxy;
         Swizzle4<T, 4, 0, 1, 0, 2> xyxz;
         Swizzle4<T, 4, 0, 1, 1, 0> xyyx;
         Swizzle4<T, 4, 0, 1, 1, 1> xyyy;
         Swizzle4<T, 4, 0, 1, 1, 2> xyyz;
         Swizzle4<T, 4, 0, 1, 2, 0> xyzx;
         Swizzle4<T, 4, 0, 1, 2, 1> xyzy;
         Swizzle4<T, 4, 0, 1, 2, 2> xyzz;
         Swizzle4<T, 4, 0, 2, 0, 0> xzxx;
         Swizzle4<T, 4, 0, 2, 0, 1> xzxy;
         Swizzle4<T, 4, 0, 2, 0, 2> xzxz;
         Swizzle4<T, 4, 0, 2, 1, 0> xzyx;
         Swizzle4<T, 4, 0, 2, 1, 1> xzyy;
         Swizzle4<T, 4, 0, 2, 1, 2> xzyz;
         Swizzle4<T, 4, 0, 2, 2, 0> xzzx;
         Swizzle4<T, 4, 0, 2, 2, 1> xzzy;
         Swizzle4<T, 4, 0, 2, 2, 2> xzzz;
         Swizzle4<T, 4, 1, 0, 0, 0> yxxx;
         Swizzle4<T, 4, 1, 0, 0, 1> yxxy;
         Swizzle4<T, 4, 1, 0, 0, 2> yxxz;
         Swizzle4<T, 4, 1, 0, 1, 0> yxyx;
         Swizzle4<T, 4, 1, 0, 1, 1> yxyy;
         Swizzle4<T, 4, 1, 0, 1, 2> yxyz;
         Swizzle4<T, 4, 1, 0, 2, 0> yxzx;
         Swizzle4<T, 4, 1, 0, 2, 1> yxzy;
         Swizzle4<T, 4, 1, 0, 2, 2> yxzz;
         Swizzle4<T, 4, 1, 1, 0, 0> yyxx;
         Swizzle4<T, 4, 1, 1, 0, 1> yyxy;
         Swizzle4<T, 4, 1, 1, 0, 2> yyxz;
         Swizzle4<T, 4, 1, 1, 1, 0> yyyx;
         Swizzle4<T, 4, 1, 1, 1, 1> yyyy;
         Swizzle4<T, 4, 1, 1, 1, 2> yyyz;
         Swizzle4<T, 4, 1, 1, 2, 0> yyzx;
         Swizzle4<T, 4, 1, 1, 2, 1> yyzy;
         Swizzle4<T, 4, 1, 1, 2, 2> yyzz;
         Swizzle4<T, 4, 1, 2, 0, 0> yzxx;
         Swizzle4<T, 4, 1, 2, 0, 1> yzxy;
         Swizzle4<T, 4, 1, 2, 0, 2> yzxz;
         Swizzle4<T, 4, 1, 2, 1, 0> yzyx;
         Swizzle4<T, 4, 1, 2, 1, 1> yzyy;
         Swizzle4<T, 4, 1, 2, 1, 2> yzyz;
         Swizzle4<T, 4, 1, 2, 2, 0> yzzx;
         Swizzle4<T, 4, 1, 2, 2, 1> yzzy;
         Swizzle4<T, 4, 1, 2, 2, 2> yzzz;
         Swizzle4<T, 4, 2, 0, 0, 0> zxxx;
         Swizzle4<T, 4, 2, 0, 0, 1> zxxy;
         Swizzle4<T, 4, 2, 0, 0, 2> zxxz;
         Swizzle4<T, 4, 2, 0, 1, 0> zxyx;
         Swizzle4<T, 4, 2, 0, 1, 1> zxyy;
         Swizzle4<T, 4, 2, 0, 1, 2> zxyz;
         Swizzle4<T, 4, 2, 0, 2, 0> zxzx;
         Swizzle4<T, 4, 2, 0, 2, 1> zxzy;
         Swizzle4<T, 4, 2, 0, 2, 2> zxzz;
         Swizzle4<T, 4, 2, 1, 0, 0> zyxx;
         Swizzle4<T, 4, 2, 1, 0, 1> zyxy;
         Swizzle4<T, 4, 2, 1, 0, 2> zyxz;
         Swizzle4<T, 4, 2, 1, 1, 0> zyyx;
         Swizzle4<T, 4, 2, 1, 1, 1> zyyy;
         Swizzle4<T, 4, 2, 1, 1, 2> zyyz;
         Swizzle4<T, 4, 2, 1, 2, 0> zyzx;
         Swizzle4<T, 4, 2, 1, 2, 1> zyzy;
         Swizzle4<T, 4, 2, 1, 2, 2> zyzz;
         Swizzle4<T, 4, 2, 2, 0, 0> zzxx;
         Swizzle4<T, 4, 2, 2, 0, 1> zzxy;
         Swizzle4<T, 4, 2, 2, 0, 2> zzxz;
         Swizzle4<T, 4, 2, 2, 1, 0> zzyx;
         Swizzle4<T, 4, 2, 2, 1, 1> zzyy;
         Swizzle4<T, 4, 2, 2, 1, 2> zzyz;
         Swizzle4<T, 4, 2, 2, 2, 0> zzzx;
         Swizzle4<T, 4, 2, 2, 2, 1> zzzy;
         Swizzle4<T, 4, 2, 2, 2, 2> zzzz;
      };
      GML_CI Vector4() = default;
      GML_CI Vector4(const Vector4&) = default;
      template<class N1, GML_ENABLE_IF_NUMBER1(N1)> GML_CI Vector4(N1 v) noexcept : array({ T(v),T(v),T(v),T(v) }) {}
      template<class N1, class N2, class N3, class N4, GML_ENABLE_IF_NUMBER4(N1, N2, N3, N4)> GML_CI Vector4(N1 x, N2 y, N3 z, N4 w) noexcept : array({T(x),T(y),T(z),T(w)}) {}
      template<int S, int A, int B, int C, int D> GML_CI Vector4(const Swizzle4<T, S, A, B, C, D>& v) noexcept : array({v.array[A], v.array[B], v.array[C], v.array[D]}) {}
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
   template<class T> Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) noexcept { return { a[0] + b[0], a[1] + b[1] }; }
   template<class T> Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) noexcept { return { a[0] - b[0], a[1] - b[1] }; }
   template<class T> Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b) noexcept { return { a[0] * b[0], a[1] * b[1] }; }
   template<class T> Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b) noexcept { return { a[0] / b[0], a[1] / b[1] }; }
   template<class T> Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) noexcept { return { a[0] + b[0], a[1] + b[1], a[2] + b[2] }; }
   template<class T> Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) noexcept { return { a[0] - b[0], a[1] - b[1], a[2] - b[2] }; }
   template<class T> Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b) noexcept { return { a[0] * b[0], a[1] * b[1], a[2] * b[2] }; }
   template<class T> Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b) noexcept { return { a[0] / b[0], a[1] / b[1], a[2] / b[2] }; }
   template<class T> Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b) noexcept { return { a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3] }; }
   template<class T> Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b) noexcept { return { a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3] }; }
   template<class T> Vector4<T> operator*(const Vector4<T>& a, const Vector4<T>& b) noexcept { return { a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3] }; }
   template<class T> Vector4<T> operator/(const Vector4<T>& a, const Vector4<T>& b) noexcept { return { a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3] }; }
   template<class T> Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b) noexcept { a[0] += b[0]; a[1] += b[1]; return a; }
   template<class T> Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b) noexcept { a[0] -= b[0]; a[1] -= b[1]; return a; }
   template<class T> Vector2<T>& operator*=(Vector2<T>& a, const Vector2<T>& b) noexcept { a[0] *= b[0]; a[1] *= b[1]; return a; }
   template<class T> Vector2<T>& operator/=(Vector2<T>& a, const Vector2<T>& b) noexcept { a[0] /= b[0]; a[1] /= b[1]; return a; }
   template<class T> Vector3<T>& operator+=(Vector3<T>& a, const Vector3<T>& b) noexcept { a[0] += b[0]; a[1] += b[1]; a[2] += b[2]; return a; }
   template<class T> Vector3<T>& operator-=(Vector3<T>& a, const Vector3<T>& b) noexcept { a[0] -= b[0]; a[1] -= b[1]; a[2] -= b[2]; return a; }
   template<class T> Vector3<T>& operator*=(Vector3<T>& a, const Vector3<T>& b) noexcept { a[0] *= b[0]; a[1] *= b[1]; a[2] *= b[2]; return a; }
   template<class T> Vector3<T>& operator/=(Vector3<T>& a, const Vector3<T>& b) noexcept { a[0] /= b[0]; a[1] /= b[1]; a[2] /= b[2]; return a; }
   template<class T> Vector4<T>& operator+=(Vector4<T>& a, const Vector4<T>& b) noexcept { a[0] += b[0]; a[1] += b[1]; a[2] += b[2]; a[3] += b[3]; return a; }
   template<class T> Vector4<T>& operator-=(Vector4<T>& a, const Vector4<T>& b) noexcept { a[0] -= b[0]; a[1] -= b[1]; a[2] -= b[2]; a[3] -= b[3]; return a; }
   template<class T> Vector4<T>& operator*=(Vector4<T>& a, const Vector4<T>& b) noexcept { a[0] *= b[0]; a[1] *= b[1]; a[2] *= b[2]; a[3] *= b[3]; return a; }
   template<class T> Vector4<T>& operator/=(Vector4<T>& a, const Vector4<T>& b) noexcept { a[0] /= b[0]; a[1] /= b[1]; a[2] /= b[2]; a[3] /= b[3]; return a; }
   template<class T> Vector2<T> operator+(const Vector2<T>& a, T b) noexcept { return a + Vector2<T>(b); }
   template<class T> Vector2<T> operator-(const Vector2<T>& a, T b) noexcept { return a - Vector2<T>(b); }
   template<class T> Vector2<T> operator*(const Vector2<T>& a, T b) noexcept { return a * Vector2<T>(b); }
   template<class T> Vector2<T> operator/(const Vector2<T>& a, T b) noexcept { return a / Vector2<T>(b); }
   template<class T> Vector3<T> operator+(const Vector3<T>& a, T b) noexcept { return a + Vector3<T>(b); }
   template<class T> Vector3<T> operator-(const Vector3<T>& a, T b) noexcept { return a - Vector3<T>(b); }
   template<class T> Vector3<T> operator*(const Vector3<T>& a, T b) noexcept { return a * Vector3<T>(b); }
   template<class T> Vector3<T> operator/(const Vector3<T>& a, T b) noexcept { return a / Vector3<T>(b); }
   template<class T> Vector4<T> operator+(const Vector4<T>& a, T b) noexcept { return a + Vector4<T>(b); }
   template<class T> Vector4<T> operator-(const Vector4<T>& a, T b) noexcept { return a - Vector4<T>(b); }
   template<class T> Vector4<T> operator*(const Vector4<T>& a, T b) noexcept { return a * Vector4<T>(b); }
   template<class T> Vector4<T> operator/(const Vector4<T>& a, T b) noexcept { return a / Vector4<T>(b); }
   template<class T> Vector2<T> operator+(T a, const Vector2<T>& b) noexcept { return Vector2<T>(a) + b; }
   template<class T> Vector2<T> operator-(T a, const Vector2<T>& b) noexcept { return Vector2<T>(a) - b; }
   template<class T> Vector2<T> operator*(T a, const Vector2<T>& b) noexcept { return Vector2<T>(a) * b; }
   template<class T> Vector2<T> operator/(T a, const Vector2<T>& b) noexcept { return Vector2<T>(a) / b; }
   template<class T> Vector3<T> operator+(T a, const Vector3<T>& b) noexcept { return Vector3<T>(a) + b; }
   template<class T> Vector3<T> operator-(T a, const Vector3<T>& b) noexcept { return Vector3<T>(a) - b; }
   template<class T> Vector3<T> operator*(T a, const Vector3<T>& b) noexcept { return Vector3<T>(a) * b; }
   template<class T> Vector3<T> operator/(T a, const Vector3<T>& b) noexcept { return Vector3<T>(a) / b; }
   template<class T> Vector4<T> operator+(T a, const Vector4<T>& b) noexcept { return Vector4<T>(a) + b; }
   template<class T> Vector4<T> operator-(T a, const Vector4<T>& b) noexcept { return Vector4<T>(a) - b; }
   template<class T> Vector4<T> operator*(T a, const Vector4<T>& b) noexcept { return Vector4<T>(a) * b; }
   template<class T> Vector4<T> operator/(T a, const Vector4<T>& b) noexcept { return Vector4<T>(a) / b; }
   template<class T> Vector2<T>& operator+=(Vector2<T>& a, T b) noexcept { return a += Vector2<T>(b); }
   template<class T> Vector2<T>& operator-=(Vector2<T>& a, T b) noexcept { return a += Vector2<T>(b); }
   template<class T> Vector2<T>& operator*=(Vector2<T>& a, T b) noexcept { return a += Vector2<T>(b); }
   template<class T> Vector2<T>& operator/=(Vector2<T>& a, T b) noexcept { return a += Vector2<T>(b); }
   template<class T> Vector3<T>& operator+=(Vector3<T>& a, T b) noexcept { return a += Vector3<T>(b); }
   template<class T> Vector3<T>& operator-=(Vector3<T>& a, T b) noexcept { return a += Vector3<T>(b); }
   template<class T> Vector3<T>& operator*=(Vector3<T>& a, T b) noexcept { return a += Vector3<T>(b); }
   template<class T> Vector3<T>& operator/=(Vector3<T>& a, T b) noexcept { return a += Vector3<T>(b); }
   template<class T> Vector4<T>& operator+=(Vector4<T>& a, T b) noexcept { return a += Vector4<T>(b); }
   template<class T> Vector4<T>& operator-=(Vector4<T>& a, T b) noexcept { return a += Vector4<T>(b); }
   template<class T> Vector4<T>& operator*=(Vector4<T>& a, T b) noexcept { return a += Vector4<T>(b); }
   template<class T> Vector4<T>& operator/=(Vector4<T>& a, T b) noexcept { return a += Vector4<T>(b); }
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
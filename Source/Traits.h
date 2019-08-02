#pragma once
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
}
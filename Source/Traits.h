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

   template<class A, class B> struct MostPrecision_ {};
   template<class T> struct MostPrecision_<T, T> { using Type = T; };
   template<> struct MostPrecision_<char, short>                            { using Type = short; };
   template<> struct MostPrecision_<char, int>                              { using Type = int; };
   template<> struct MostPrecision_<char, long>                             { using Type = long; };
   template<> struct MostPrecision_<char, long long>                        { using Type = long long; };
   template<> struct MostPrecision_<unsigned char, unsigned short>          { using Type = unsigned short; };
   template<> struct MostPrecision_<unsigned char, unsigned int>            { using Type = unsigned int; };
   template<> struct MostPrecision_<unsigned char, unsigned long>           { using Type = unsigned long; };
   template<> struct MostPrecision_<unsigned char, unsigned long long>      { using Type = unsigned long long; };
   template<> struct MostPrecision_<short, char>                            { using Type = short; };
   template<> struct MostPrecision_<short, int>                             { using Type = int; };
   template<> struct MostPrecision_<short, long>                            { using Type = long; };
   template<> struct MostPrecision_<short, long long>                       { using Type = long long; };
   template<> struct MostPrecision_<unsigned short, unsigned char>          { using Type = unsigned short; };
   template<> struct MostPrecision_<unsigned short, unsigned int>           { using Type = unsigned int; };
   template<> struct MostPrecision_<unsigned short, unsigned long>          { using Type = unsigned long; };
   template<> struct MostPrecision_<unsigned short, unsigned long long>     { using Type = unsigned long long; };
   template<> struct MostPrecision_<int, char>                              { using Type = int; };
   template<> struct MostPrecision_<int, short>                             { using Type = int; };
   template<> struct MostPrecision_<int, long>                              { using Type = long; };
   template<> struct MostPrecision_<int, long long>                         { using Type = long long; };
   template<> struct MostPrecision_<unsigned int, unsigned char>            { using Type = unsigned int; };
   template<> struct MostPrecision_<unsigned int, unsigned short>           { using Type = unsigned int; };
   template<> struct MostPrecision_<unsigned int, unsigned long>            { using Type = unsigned long; };
   template<> struct MostPrecision_<unsigned int, unsigned long long>       { using Type = unsigned long long; };
   template<> struct MostPrecision_<long, char>                             { using Type = long; };
   template<> struct MostPrecision_<long, int>                              { using Type = long; };
   template<> struct MostPrecision_<long, long>                             { using Type = long; };
   template<> struct MostPrecision_<long, long long>                        { using Type = long long; };
   template<> struct MostPrecision_<unsigned long, unsigned char>           { using Type = unsigned long; };
   template<> struct MostPrecision_<unsigned long, unsigned short>          { using Type = unsigned long; };
   template<> struct MostPrecision_<unsigned long, unsigned int>            { using Type = unsigned long; };
   template<> struct MostPrecision_<unsigned long, unsigned long long>      { using Type = unsigned long long; };
   template<> struct MostPrecision_<long long, char>                        { using Type = long long; };
   template<> struct MostPrecision_<long long, int>                         { using Type = long long; };
   template<> struct MostPrecision_<long long, long>                        { using Type = long long; };
   template<> struct MostPrecision_<long long, long long>                   { using Type = long long; };
   template<> struct MostPrecision_<unsigned long long, unsigned char>      { using Type = unsigned long long; };
   template<> struct MostPrecision_<unsigned long long, unsigned short>     { using Type = unsigned long long; };
   template<> struct MostPrecision_<unsigned long long, unsigned int>       { using Type = unsigned long long; };
   template<> struct MostPrecision_<unsigned long long, unsigned long long> { using Type = unsigned long long; };

   template<> struct MostPrecision_<int, float> { using Type = float; };
   template<> struct MostPrecision_<int, double> { using Type = double; };

   template<> struct MostPrecision_<float, int> { using Type = float; };
   template<> struct MostPrecision_<float, double> { using Type = double; };

   template<> struct MostPrecision_<double, int> { using Type = double; };
   template<> struct MostPrecision_<double, float> { using Type = double; };

   template<class A, class B>
   using MostPrecision = typename MostPrecision_<A, B>::Type;
}
#pragma once
#define GML_SWIZZLE_X(T)         \
Swizzle1<T, 1, 0> x;             \
Swizzle2<T, 1, 0, 0> xx;         \
Swizzle3<T, 1, 0, 0, 0> xxx;     \
Swizzle4<T, 1, 0, 0, 0, 0> xxxx

#define GML_SWIZZLE_XY(T)        \
Swizzle1<T, 2, 0> x;             \
Swizzle1<T, 2, 1> y;             \
Swizzle2<T, 2, 0, 0> xx;         \
Swizzle2<T, 2, 0, 1> xy;         \
Swizzle2<T, 2, 1, 0> yx;         \
Swizzle2<T, 2, 1, 1> yy;         \
Swizzle3<T, 2, 0, 0, 0> xxx;     \
Swizzle3<T, 2, 0, 0, 1> xxy;     \
Swizzle3<T, 2, 0, 1, 0> xyx;     \
Swizzle3<T, 2, 0, 1, 1> xyy;     \
Swizzle3<T, 2, 1, 0, 0> yxx;     \
Swizzle3<T, 2, 1, 0, 1> yxy;     \
Swizzle3<T, 2, 1, 1, 0> yyx;     \
Swizzle3<T, 2, 1, 1, 1> yyy;     \
Swizzle4<T, 2, 0, 0, 0, 0> xxxx; \
Swizzle4<T, 2, 0, 0, 0, 1> xxxy; \
Swizzle4<T, 2, 0, 0, 1, 0> xxyx; \
Swizzle4<T, 2, 0, 0, 1, 1> xxyy; \
Swizzle4<T, 2, 0, 1, 0, 0> xyxx; \
Swizzle4<T, 2, 0, 1, 0, 1> xyxy; \
Swizzle4<T, 2, 0, 1, 1, 0> xyyx; \
Swizzle4<T, 2, 0, 1, 1, 1> xyyy; \
Swizzle4<T, 2, 1, 0, 0, 0> yxxx; \
Swizzle4<T, 2, 1, 0, 0, 1> yxxy; \
Swizzle4<T, 2, 1, 0, 1, 0> yxyx; \
Swizzle4<T, 2, 1, 0, 1, 1> yxyy; \
Swizzle4<T, 2, 1, 1, 0, 0> yyxx; \
Swizzle4<T, 2, 1, 1, 0, 1> yyxy; \
Swizzle4<T, 2, 1, 1, 1, 0> yyyx; \
Swizzle4<T, 2, 1, 1, 1, 1> yyyy

#define GML_SWIZZLE_XYZ(T)       \
Swizzle1<T, 3, 0> x;             \
Swizzle1<T, 3, 1> y;             \
Swizzle1<T, 3, 2> z;             \
Swizzle2<T, 3, 0, 0> xx;         \
Swizzle2<T, 3, 0, 1> xy;         \
Swizzle2<T, 3, 0, 2> xz;         \
Swizzle2<T, 3, 1, 0> yx;         \
Swizzle2<T, 3, 1, 1> yy;         \
Swizzle2<T, 3, 1, 2> yz;         \
Swizzle2<T, 3, 2, 0> zx;         \
Swizzle2<T, 3, 2, 1> zy;         \
Swizzle2<T, 3, 2, 2> zz;         \
Swizzle3<T, 3, 0, 0, 0> xxx;     \
Swizzle3<T, 3, 0, 0, 1> xxy;     \
Swizzle3<T, 3, 0, 0, 2> xxz;     \
Swizzle3<T, 3, 0, 1, 0> xyx;     \
Swizzle3<T, 3, 0, 1, 1> xyy;     \
Swizzle3<T, 3, 0, 1, 2> xyz;     \
Swizzle3<T, 3, 0, 2, 0> xzx;     \
Swizzle3<T, 3, 0, 2, 1> xzy;     \
Swizzle3<T, 3, 0, 2, 2> xzz;     \
Swizzle3<T, 3, 1, 0, 0> yxx;     \
Swizzle3<T, 3, 1, 0, 1> yxy;     \
Swizzle3<T, 3, 1, 0, 2> yxz;     \
Swizzle3<T, 3, 1, 1, 0> yyx;     \
Swizzle3<T, 3, 1, 1, 1> yyy;     \
Swizzle3<T, 3, 1, 1, 2> yyz;     \
Swizzle3<T, 3, 1, 2, 0> yzx;     \
Swizzle3<T, 3, 1, 2, 1> yzy;     \
Swizzle3<T, 3, 1, 2, 2> yzz;     \
Swizzle3<T, 3, 2, 0, 0> zxx;     \
Swizzle3<T, 3, 2, 0, 1> zxy;     \
Swizzle3<T, 3, 2, 0, 2> zxz;     \
Swizzle3<T, 3, 2, 1, 0> zyx;     \
Swizzle3<T, 3, 2, 1, 1> zyy;     \
Swizzle3<T, 3, 2, 1, 2> zyz;     \
Swizzle3<T, 3, 2, 2, 0> zzx;     \
Swizzle3<T, 3, 2, 2, 1> zzy;     \
Swizzle3<T, 3, 2, 2, 2> zzz;     \
Swizzle4<T, 3, 0, 0, 0, 0> xxxx; \
Swizzle4<T, 3, 0, 0, 0, 1> xxxy; \
Swizzle4<T, 3, 0, 0, 0, 2> xxxz; \
Swizzle4<T, 3, 0, 0, 1, 0> xxyx; \
Swizzle4<T, 3, 0, 0, 1, 1> xxyy; \
Swizzle4<T, 3, 0, 0, 1, 2> xxyz; \
Swizzle4<T, 3, 0, 0, 2, 0> xxzx; \
Swizzle4<T, 3, 0, 0, 2, 1> xxzy; \
Swizzle4<T, 3, 0, 0, 2, 2> xxzz; \
Swizzle4<T, 3, 0, 1, 0, 0> xyxx; \
Swizzle4<T, 3, 0, 1, 0, 1> xyxy; \
Swizzle4<T, 3, 0, 1, 0, 2> xyxz; \
Swizzle4<T, 3, 0, 1, 1, 0> xyyx; \
Swizzle4<T, 3, 0, 1, 1, 1> xyyy; \
Swizzle4<T, 3, 0, 1, 1, 2> xyyz; \
Swizzle4<T, 3, 0, 1, 2, 0> xyzx; \
Swizzle4<T, 3, 0, 1, 2, 1> xyzy; \
Swizzle4<T, 3, 0, 1, 2, 2> xyzz; \
Swizzle4<T, 3, 0, 2, 0, 0> xzxx; \
Swizzle4<T, 3, 0, 2, 0, 1> xzxy; \
Swizzle4<T, 3, 0, 2, 0, 2> xzxz; \
Swizzle4<T, 3, 0, 2, 1, 0> xzyx; \
Swizzle4<T, 3, 0, 2, 1, 1> xzyy; \
Swizzle4<T, 3, 0, 2, 1, 2> xzyz; \
Swizzle4<T, 3, 0, 2, 2, 0> xzzx; \
Swizzle4<T, 3, 0, 2, 2, 1> xzzy; \
Swizzle4<T, 3, 0, 2, 2, 2> xzzz; \
Swizzle4<T, 3, 1, 0, 0, 0> yxxx; \
Swizzle4<T, 3, 1, 0, 0, 1> yxxy; \
Swizzle4<T, 3, 1, 0, 0, 2> yxxz; \
Swizzle4<T, 3, 1, 0, 1, 0> yxyx; \
Swizzle4<T, 3, 1, 0, 1, 1> yxyy; \
Swizzle4<T, 3, 1, 0, 1, 2> yxyz; \
Swizzle4<T, 3, 1, 0, 2, 0> yxzx; \
Swizzle4<T, 3, 1, 0, 2, 1> yxzy; \
Swizzle4<T, 3, 1, 0, 2, 2> yxzz; \
Swizzle4<T, 3, 1, 1, 0, 0> yyxx; \
Swizzle4<T, 3, 1, 1, 0, 1> yyxy; \
Swizzle4<T, 3, 1, 1, 0, 2> yyxz; \
Swizzle4<T, 3, 1, 1, 1, 0> yyyx; \
Swizzle4<T, 3, 1, 1, 1, 1> yyyy; \
Swizzle4<T, 3, 1, 1, 1, 2> yyyz; \
Swizzle4<T, 3, 1, 1, 2, 0> yyzx; \
Swizzle4<T, 3, 1, 1, 2, 1> yyzy; \
Swizzle4<T, 3, 1, 1, 2, 2> yyzz; \
Swizzle4<T, 3, 1, 2, 0, 0> yzxx; \
Swizzle4<T, 3, 1, 2, 0, 1> yzxy; \
Swizzle4<T, 3, 1, 2, 0, 2> yzxz; \
Swizzle4<T, 3, 1, 2, 1, 0> yzyx; \
Swizzle4<T, 3, 1, 2, 1, 1> yzyy; \
Swizzle4<T, 3, 1, 2, 1, 2> yzyz; \
Swizzle4<T, 3, 1, 2, 2, 0> yzzx; \
Swizzle4<T, 3, 1, 2, 2, 1> yzzy; \
Swizzle4<T, 3, 1, 2, 2, 2> yzzz; \
Swizzle4<T, 3, 2, 0, 0, 0> zxxx; \
Swizzle4<T, 3, 2, 0, 0, 1> zxxy; \
Swizzle4<T, 3, 2, 0, 0, 2> zxxz; \
Swizzle4<T, 3, 2, 0, 1, 0> zxyx; \
Swizzle4<T, 3, 2, 0, 1, 1> zxyy; \
Swizzle4<T, 3, 2, 0, 1, 2> zxyz; \
Swizzle4<T, 3, 2, 0, 2, 0> zxzx; \
Swizzle4<T, 3, 2, 0, 2, 1> zxzy; \
Swizzle4<T, 3, 2, 0, 2, 2> zxzz; \
Swizzle4<T, 3, 2, 1, 0, 0> zyxx; \
Swizzle4<T, 3, 2, 1, 0, 1> zyxy; \
Swizzle4<T, 3, 2, 1, 0, 2> zyxz; \
Swizzle4<T, 3, 2, 1, 1, 0> zyyx; \
Swizzle4<T, 3, 2, 1, 1, 1> zyyy; \
Swizzle4<T, 3, 2, 1, 1, 2> zyyz; \
Swizzle4<T, 3, 2, 1, 2, 0> zyzx; \
Swizzle4<T, 3, 2, 1, 2, 1> zyzy; \
Swizzle4<T, 3, 2, 1, 2, 2> zyzz; \
Swizzle4<T, 3, 2, 2, 0, 0> zzxx; \
Swizzle4<T, 3, 2, 2, 0, 1> zzxy; \
Swizzle4<T, 3, 2, 2, 0, 2> zzxz; \
Swizzle4<T, 3, 2, 2, 1, 0> zzyx; \
Swizzle4<T, 3, 2, 2, 1, 1> zzyy; \
Swizzle4<T, 3, 2, 2, 1, 2> zzyz; \
Swizzle4<T, 3, 2, 2, 2, 0> zzzx; \
Swizzle4<T, 3, 2, 2, 2, 1> zzzy; \
Swizzle4<T, 3, 2, 2, 2, 2> zzzz

#define GML_SWIZZLE_XYZW(T)      \
Swizzle1<T, 4, 0> x;             \
Swizzle1<T, 4, 1> y;             \
Swizzle1<T, 4, 2> z;             \
Swizzle1<T, 4, 3> w;             \
Swizzle2<T, 4, 0, 0> xx;         \
Swizzle2<T, 4, 0, 1> xy;         \
Swizzle2<T, 4, 0, 2> xz;         \
Swizzle2<T, 4, 0, 3> xw;         \
Swizzle2<T, 4, 1, 0> yx;         \
Swizzle2<T, 4, 1, 1> yy;         \
Swizzle2<T, 4, 1, 2> yz;         \
Swizzle2<T, 4, 1, 3> yw;         \
Swizzle2<T, 4, 2, 0> zx;         \
Swizzle2<T, 4, 2, 1> zy;         \
Swizzle2<T, 4, 2, 2> zz;         \
Swizzle2<T, 4, 2, 3> zw;         \
Swizzle2<T, 4, 3, 0> wx;         \
Swizzle2<T, 4, 3, 1> wy;         \
Swizzle2<T, 4, 3, 2> wz;         \
Swizzle2<T, 4, 3, 3> ww;         \
Swizzle3<T, 4, 0, 0, 0> xxx;     \
Swizzle3<T, 4, 0, 0, 1> xxy;     \
Swizzle3<T, 4, 0, 0, 2> xxz;     \
Swizzle3<T, 4, 0, 0, 3> xxw;     \
Swizzle3<T, 4, 0, 1, 0> xyx;     \
Swizzle3<T, 4, 0, 1, 1> xyy;     \
Swizzle3<T, 4, 0, 1, 2> xyz;     \
Swizzle3<T, 4, 0, 1, 3> xyw;     \
Swizzle3<T, 4, 0, 2, 0> xzx;     \
Swizzle3<T, 4, 0, 2, 1> xzy;     \
Swizzle3<T, 4, 0, 2, 2> xzz;     \
Swizzle3<T, 4, 0, 2, 3> xzw;     \
Swizzle3<T, 4, 0, 3, 0> xwx;     \
Swizzle3<T, 4, 0, 3, 1> xwy;     \
Swizzle3<T, 4, 0, 3, 2> xwz;     \
Swizzle3<T, 4, 0, 3, 3> xww;     \
Swizzle3<T, 4, 1, 0, 0> yxx;     \
Swizzle3<T, 4, 1, 0, 1> yxy;     \
Swizzle3<T, 4, 1, 0, 2> yxz;     \
Swizzle3<T, 4, 1, 0, 3> yxw;     \
Swizzle3<T, 4, 1, 1, 0> yyx;     \
Swizzle3<T, 4, 1, 1, 1> yyy;     \
Swizzle3<T, 4, 1, 1, 2> yyz;     \
Swizzle3<T, 4, 1, 1, 3> yyw;     \
Swizzle3<T, 4, 1, 2, 0> yzx;     \
Swizzle3<T, 4, 1, 2, 1> yzy;     \
Swizzle3<T, 4, 1, 2, 2> yzz;     \
Swizzle3<T, 4, 1, 2, 3> yzw;     \
Swizzle3<T, 4, 1, 3, 0> ywx;     \
Swizzle3<T, 4, 1, 3, 1> ywy;     \
Swizzle3<T, 4, 1, 3, 2> ywz;     \
Swizzle3<T, 4, 1, 3, 3> yww;     \
Swizzle3<T, 4, 2, 0, 0> zxx;     \
Swizzle3<T, 4, 2, 0, 1> zxy;     \
Swizzle3<T, 4, 2, 0, 2> zxz;     \
Swizzle3<T, 4, 2, 0, 3> zxw;     \
Swizzle3<T, 4, 2, 1, 0> zyx;     \
Swizzle3<T, 4, 2, 1, 1> zyy;     \
Swizzle3<T, 4, 2, 1, 2> zyz;     \
Swizzle3<T, 4, 2, 1, 3> zyw;     \
Swizzle3<T, 4, 2, 2, 0> zzx;     \
Swizzle3<T, 4, 2, 2, 1> zzy;     \
Swizzle3<T, 4, 2, 2, 2> zzz;     \
Swizzle3<T, 4, 2, 2, 3> zzw;     \
Swizzle3<T, 4, 2, 3, 0> zwx;     \
Swizzle3<T, 4, 2, 3, 1> zwy;     \
Swizzle3<T, 4, 2, 3, 2> zwz;     \
Swizzle3<T, 4, 2, 3, 3> zww;     \
Swizzle3<T, 4, 3, 0, 0> wxx;     \
Swizzle3<T, 4, 3, 0, 1> wxy;     \
Swizzle3<T, 4, 3, 0, 2> wxz;     \
Swizzle3<T, 4, 3, 0, 3> wxw;     \
Swizzle3<T, 4, 3, 1, 0> wyx;     \
Swizzle3<T, 4, 3, 1, 1> wyy;     \
Swizzle3<T, 4, 3, 1, 2> wyz;     \
Swizzle3<T, 4, 3, 1, 3> wyw;     \
Swizzle3<T, 4, 3, 2, 0> wzx;     \
Swizzle3<T, 4, 3, 2, 1> wzy;     \
Swizzle3<T, 4, 3, 2, 2> wzz;     \
Swizzle3<T, 4, 3, 2, 3> wzw;     \
Swizzle3<T, 4, 3, 3, 0> wwx;     \
Swizzle3<T, 4, 3, 3, 1> wwy;     \
Swizzle3<T, 4, 3, 3, 2> wwz;     \
Swizzle3<T, 4, 3, 3, 3> www;     \
Swizzle4<T, 4, 0, 0, 0, 0> xxxx; \
Swizzle4<T, 4, 0, 0, 0, 1> xxxy; \
Swizzle4<T, 4, 0, 0, 0, 2> xxxz; \
Swizzle4<T, 4, 0, 0, 0, 3> xxxw; \
Swizzle4<T, 4, 0, 0, 1, 0> xxyx; \
Swizzle4<T, 4, 0, 0, 1, 1> xxyy; \
Swizzle4<T, 4, 0, 0, 1, 2> xxyz; \
Swizzle4<T, 4, 0, 0, 1, 3> xxyw; \
Swizzle4<T, 4, 0, 0, 2, 0> xxzx; \
Swizzle4<T, 4, 0, 0, 2, 1> xxzy; \
Swizzle4<T, 4, 0, 0, 2, 2> xxzz; \
Swizzle4<T, 4, 0, 0, 2, 3> xxzw; \
Swizzle4<T, 4, 0, 0, 3, 0> xxwx; \
Swizzle4<T, 4, 0, 0, 3, 1> xxwy; \
Swizzle4<T, 4, 0, 0, 3, 2> xxwz; \
Swizzle4<T, 4, 0, 0, 3, 3> xxww; \
Swizzle4<T, 4, 0, 1, 0, 0> xyxx; \
Swizzle4<T, 4, 0, 1, 0, 1> xyxy; \
Swizzle4<T, 4, 0, 1, 0, 2> xyxz; \
Swizzle4<T, 4, 0, 1, 0, 3> xyxw; \
Swizzle4<T, 4, 0, 1, 1, 0> xyyx; \
Swizzle4<T, 4, 0, 1, 1, 1> xyyy; \
Swizzle4<T, 4, 0, 1, 1, 2> xyyz; \
Swizzle4<T, 4, 0, 1, 1, 3> xyyw; \
Swizzle4<T, 4, 0, 1, 2, 0> xyzx; \
Swizzle4<T, 4, 0, 1, 2, 1> xyzy; \
Swizzle4<T, 4, 0, 1, 2, 2> xyzz; \
Swizzle4<T, 4, 0, 1, 2, 3> xyzw; \
Swizzle4<T, 4, 0, 1, 3, 0> xywx; \
Swizzle4<T, 4, 0, 1, 3, 1> xywy; \
Swizzle4<T, 4, 0, 1, 3, 2> xywz; \
Swizzle4<T, 4, 0, 1, 3, 3> xyww; \
Swizzle4<T, 4, 0, 2, 0, 0> xzxx; \
Swizzle4<T, 4, 0, 2, 0, 1> xzxy; \
Swizzle4<T, 4, 0, 2, 0, 2> xzxz; \
Swizzle4<T, 4, 0, 2, 0, 3> xzxw; \
Swizzle4<T, 4, 0, 2, 1, 0> xzyx; \
Swizzle4<T, 4, 0, 2, 1, 1> xzyy; \
Swizzle4<T, 4, 0, 2, 1, 2> xzyz; \
Swizzle4<T, 4, 0, 2, 1, 3> xzyw; \
Swizzle4<T, 4, 0, 2, 2, 0> xzzx; \
Swizzle4<T, 4, 0, 2, 2, 1> xzzy; \
Swizzle4<T, 4, 0, 2, 2, 2> xzzz; \
Swizzle4<T, 4, 0, 2, 2, 3> xzzw; \
Swizzle4<T, 4, 0, 2, 3, 0> xzwx; \
Swizzle4<T, 4, 0, 2, 3, 1> xzwy; \
Swizzle4<T, 4, 0, 2, 3, 2> xzwz; \
Swizzle4<T, 4, 0, 2, 3, 3> xzww; \
Swizzle4<T, 4, 0, 3, 0, 0> xwxx; \
Swizzle4<T, 4, 0, 3, 0, 1> xwxy; \
Swizzle4<T, 4, 0, 3, 0, 2> xwxz; \
Swizzle4<T, 4, 0, 3, 0, 3> xwxw; \
Swizzle4<T, 4, 0, 3, 1, 0> xwyx; \
Swizzle4<T, 4, 0, 3, 1, 1> xwyy; \
Swizzle4<T, 4, 0, 3, 1, 2> xwyz; \
Swizzle4<T, 4, 0, 3, 1, 3> xwyw; \
Swizzle4<T, 4, 0, 3, 2, 0> xwzx; \
Swizzle4<T, 4, 0, 3, 2, 1> xwzy; \
Swizzle4<T, 4, 0, 3, 2, 2> xwzz; \
Swizzle4<T, 4, 0, 3, 2, 3> xwzw; \
Swizzle4<T, 4, 0, 3, 3, 0> xwwx; \
Swizzle4<T, 4, 0, 3, 3, 1> xwwy; \
Swizzle4<T, 4, 0, 3, 3, 2> xwwz; \
Swizzle4<T, 4, 0, 3, 3, 3> xwww; \
Swizzle4<T, 4, 1, 0, 0, 0> yxxx; \
Swizzle4<T, 4, 1, 0, 0, 1> yxxy; \
Swizzle4<T, 4, 1, 0, 0, 2> yxxz; \
Swizzle4<T, 4, 1, 0, 0, 3> yxxw; \
Swizzle4<T, 4, 1, 0, 1, 0> yxyx; \
Swizzle4<T, 4, 1, 0, 1, 1> yxyy; \
Swizzle4<T, 4, 1, 0, 1, 2> yxyz; \
Swizzle4<T, 4, 1, 0, 1, 3> yxyw; \
Swizzle4<T, 4, 1, 0, 2, 0> yxzx; \
Swizzle4<T, 4, 1, 0, 2, 1> yxzy; \
Swizzle4<T, 4, 1, 0, 2, 2> yxzz; \
Swizzle4<T, 4, 1, 0, 2, 3> yxzw; \
Swizzle4<T, 4, 1, 0, 3, 0> yxwx; \
Swizzle4<T, 4, 1, 0, 3, 1> yxwy; \
Swizzle4<T, 4, 1, 0, 3, 2> yxwz; \
Swizzle4<T, 4, 1, 0, 3, 3> yxww; \
Swizzle4<T, 4, 1, 1, 0, 0> yyxx; \
Swizzle4<T, 4, 1, 1, 0, 1> yyxy; \
Swizzle4<T, 4, 1, 1, 0, 2> yyxz; \
Swizzle4<T, 4, 1, 1, 0, 3> yyxw; \
Swizzle4<T, 4, 1, 1, 1, 0> yyyx; \
Swizzle4<T, 4, 1, 1, 1, 1> yyyy; \
Swizzle4<T, 4, 1, 1, 1, 2> yyyz; \
Swizzle4<T, 4, 1, 1, 1, 3> yyyw; \
Swizzle4<T, 4, 1, 1, 2, 0> yyzx; \
Swizzle4<T, 4, 1, 1, 2, 1> yyzy; \
Swizzle4<T, 4, 1, 1, 2, 2> yyzz; \
Swizzle4<T, 4, 1, 1, 2, 3> yyzw; \
Swizzle4<T, 4, 1, 1, 3, 0> yywx; \
Swizzle4<T, 4, 1, 1, 3, 1> yywy; \
Swizzle4<T, 4, 1, 1, 3, 2> yywz; \
Swizzle4<T, 4, 1, 1, 3, 3> yyww; \
Swizzle4<T, 4, 1, 2, 0, 0> yzxx; \
Swizzle4<T, 4, 1, 2, 0, 1> yzxy; \
Swizzle4<T, 4, 1, 2, 0, 2> yzxz; \
Swizzle4<T, 4, 1, 2, 0, 3> yzxw; \
Swizzle4<T, 4, 1, 2, 1, 0> yzyx; \
Swizzle4<T, 4, 1, 2, 1, 1> yzyy; \
Swizzle4<T, 4, 1, 2, 1, 2> yzyz; \
Swizzle4<T, 4, 1, 2, 1, 3> yzyw; \
Swizzle4<T, 4, 1, 2, 2, 0> yzzx; \
Swizzle4<T, 4, 1, 2, 2, 1> yzzy; \
Swizzle4<T, 4, 1, 2, 2, 2> yzzz; \
Swizzle4<T, 4, 1, 2, 2, 3> yzzw; \
Swizzle4<T, 4, 1, 2, 3, 0> yzwx; \
Swizzle4<T, 4, 1, 2, 3, 1> yzwy; \
Swizzle4<T, 4, 1, 2, 3, 2> yzwz; \
Swizzle4<T, 4, 1, 2, 3, 3> yzww; \
Swizzle4<T, 4, 1, 3, 0, 0> ywxx; \
Swizzle4<T, 4, 1, 3, 0, 1> ywxy; \
Swizzle4<T, 4, 1, 3, 0, 2> ywxz; \
Swizzle4<T, 4, 1, 3, 0, 3> ywxw; \
Swizzle4<T, 4, 1, 3, 1, 0> ywyx; \
Swizzle4<T, 4, 1, 3, 1, 1> ywyy; \
Swizzle4<T, 4, 1, 3, 1, 2> ywyz; \
Swizzle4<T, 4, 1, 3, 1, 3> ywyw; \
Swizzle4<T, 4, 1, 3, 2, 0> ywzx; \
Swizzle4<T, 4, 1, 3, 2, 1> ywzy; \
Swizzle4<T, 4, 1, 3, 2, 2> ywzz; \
Swizzle4<T, 4, 1, 3, 2, 3> ywzw; \
Swizzle4<T, 4, 1, 3, 3, 0> ywwx; \
Swizzle4<T, 4, 1, 3, 3, 1> ywwy; \
Swizzle4<T, 4, 1, 3, 3, 2> ywwz; \
Swizzle4<T, 4, 1, 3, 3, 3> ywww; \
Swizzle4<T, 4, 2, 0, 0, 0> zxxx; \
Swizzle4<T, 4, 2, 0, 0, 1> zxxy; \
Swizzle4<T, 4, 2, 0, 0, 2> zxxz; \
Swizzle4<T, 4, 2, 0, 0, 3> zxxw; \
Swizzle4<T, 4, 2, 0, 1, 0> zxyx; \
Swizzle4<T, 4, 2, 0, 1, 1> zxyy; \
Swizzle4<T, 4, 2, 0, 1, 2> zxyz; \
Swizzle4<T, 4, 2, 0, 1, 3> zxyw; \
Swizzle4<T, 4, 2, 0, 2, 0> zxzx; \
Swizzle4<T, 4, 2, 0, 2, 1> zxzy; \
Swizzle4<T, 4, 2, 0, 2, 2> zxzz; \
Swizzle4<T, 4, 2, 0, 2, 3> zxzw; \
Swizzle4<T, 4, 2, 0, 3, 0> zxwx; \
Swizzle4<T, 4, 2, 0, 3, 1> zxwy; \
Swizzle4<T, 4, 2, 0, 3, 2> zxwz; \
Swizzle4<T, 4, 2, 0, 3, 3> zxww; \
Swizzle4<T, 4, 2, 1, 0, 0> zyxx; \
Swizzle4<T, 4, 2, 1, 0, 1> zyxy; \
Swizzle4<T, 4, 2, 1, 0, 2> zyxz; \
Swizzle4<T, 4, 2, 1, 0, 3> zyxw; \
Swizzle4<T, 4, 2, 1, 1, 0> zyyx; \
Swizzle4<T, 4, 2, 1, 1, 1> zyyy; \
Swizzle4<T, 4, 2, 1, 1, 2> zyyz; \
Swizzle4<T, 4, 2, 1, 1, 3> zyyw; \
Swizzle4<T, 4, 2, 1, 2, 0> zyzx; \
Swizzle4<T, 4, 2, 1, 2, 1> zyzy; \
Swizzle4<T, 4, 2, 1, 2, 2> zyzz; \
Swizzle4<T, 4, 2, 1, 2, 3> zyzw; \
Swizzle4<T, 4, 2, 1, 3, 0> zywx; \
Swizzle4<T, 4, 2, 1, 3, 1> zywy; \
Swizzle4<T, 4, 2, 1, 3, 2> zywz; \
Swizzle4<T, 4, 2, 1, 3, 3> zyww; \
Swizzle4<T, 4, 2, 2, 0, 0> zzxx; \
Swizzle4<T, 4, 2, 2, 0, 1> zzxy; \
Swizzle4<T, 4, 2, 2, 0, 2> zzxz; \
Swizzle4<T, 4, 2, 2, 0, 3> zzxw; \
Swizzle4<T, 4, 2, 2, 1, 0> zzyx; \
Swizzle4<T, 4, 2, 2, 1, 1> zzyy; \
Swizzle4<T, 4, 2, 2, 1, 2> zzyz; \
Swizzle4<T, 4, 2, 2, 1, 3> zzyw; \
Swizzle4<T, 4, 2, 2, 2, 0> zzzx; \
Swizzle4<T, 4, 2, 2, 2, 1> zzzy; \
Swizzle4<T, 4, 2, 2, 2, 2> zzzz; \
Swizzle4<T, 4, 2, 2, 2, 3> zzzw; \
Swizzle4<T, 4, 2, 2, 3, 0> zzwx; \
Swizzle4<T, 4, 2, 2, 3, 1> zzwy; \
Swizzle4<T, 4, 2, 2, 3, 2> zzwz; \
Swizzle4<T, 4, 2, 2, 3, 3> zzww; \
Swizzle4<T, 4, 2, 3, 0, 0> zwxx; \
Swizzle4<T, 4, 2, 3, 0, 1> zwxy; \
Swizzle4<T, 4, 2, 3, 0, 2> zwxz; \
Swizzle4<T, 4, 2, 3, 0, 3> zwxw; \
Swizzle4<T, 4, 2, 3, 1, 0> zwyx; \
Swizzle4<T, 4, 2, 3, 1, 1> zwyy; \
Swizzle4<T, 4, 2, 3, 1, 2> zwyz; \
Swizzle4<T, 4, 2, 3, 1, 3> zwyw; \
Swizzle4<T, 4, 2, 3, 2, 0> zwzx; \
Swizzle4<T, 4, 2, 3, 2, 1> zwzy; \
Swizzle4<T, 4, 2, 3, 2, 2> zwzz; \
Swizzle4<T, 4, 2, 3, 2, 3> zwzw; \
Swizzle4<T, 4, 2, 3, 3, 0> zwwx; \
Swizzle4<T, 4, 2, 3, 3, 1> zwwy; \
Swizzle4<T, 4, 2, 3, 3, 2> zwwz; \
Swizzle4<T, 4, 2, 3, 3, 3> zwww; \
Swizzle4<T, 4, 3, 0, 0, 0> wxxx; \
Swizzle4<T, 4, 3, 0, 0, 1> wxxy; \
Swizzle4<T, 4, 3, 0, 0, 2> wxxz; \
Swizzle4<T, 4, 3, 0, 0, 3> wxxw; \
Swizzle4<T, 4, 3, 0, 1, 0> wxyx; \
Swizzle4<T, 4, 3, 0, 1, 1> wxyy; \
Swizzle4<T, 4, 3, 0, 1, 2> wxyz; \
Swizzle4<T, 4, 3, 0, 1, 3> wxyw; \
Swizzle4<T, 4, 3, 0, 2, 0> wxzx; \
Swizzle4<T, 4, 3, 0, 2, 1> wxzy; \
Swizzle4<T, 4, 3, 0, 2, 2> wxzz; \
Swizzle4<T, 4, 3, 0, 2, 3> wxzw; \
Swizzle4<T, 4, 3, 0, 3, 0> wxwx; \
Swizzle4<T, 4, 3, 0, 3, 1> wxwy; \
Swizzle4<T, 4, 3, 0, 3, 2> wxwz; \
Swizzle4<T, 4, 3, 0, 3, 3> wxww; \
Swizzle4<T, 4, 3, 1, 0, 0> wyxx; \
Swizzle4<T, 4, 3, 1, 0, 1> wyxy; \
Swizzle4<T, 4, 3, 1, 0, 2> wyxz; \
Swizzle4<T, 4, 3, 1, 0, 3> wyxw; \
Swizzle4<T, 4, 3, 1, 1, 0> wyyx; \
Swizzle4<T, 4, 3, 1, 1, 1> wyyy; \
Swizzle4<T, 4, 3, 1, 1, 2> wyyz; \
Swizzle4<T, 4, 3, 1, 1, 3> wyyw; \
Swizzle4<T, 4, 3, 1, 2, 0> wyzx; \
Swizzle4<T, 4, 3, 1, 2, 1> wyzy; \
Swizzle4<T, 4, 3, 1, 2, 2> wyzz; \
Swizzle4<T, 4, 3, 1, 2, 3> wyzw; \
Swizzle4<T, 4, 3, 1, 3, 0> wywx; \
Swizzle4<T, 4, 3, 1, 3, 1> wywy; \
Swizzle4<T, 4, 3, 1, 3, 2> wywz; \
Swizzle4<T, 4, 3, 1, 3, 3> wyww; \
Swizzle4<T, 4, 3, 2, 0, 0> wzxx; \
Swizzle4<T, 4, 3, 2, 0, 1> wzxy; \
Swizzle4<T, 4, 3, 2, 0, 2> wzxz; \
Swizzle4<T, 4, 3, 2, 0, 3> wzxw; \
Swizzle4<T, 4, 3, 2, 1, 0> wzyx; \
Swizzle4<T, 4, 3, 2, 1, 1> wzyy; \
Swizzle4<T, 4, 3, 2, 1, 2> wzyz; \
Swizzle4<T, 4, 3, 2, 1, 3> wzyw; \
Swizzle4<T, 4, 3, 2, 2, 0> wzzx; \
Swizzle4<T, 4, 3, 2, 2, 1> wzzy; \
Swizzle4<T, 4, 3, 2, 2, 2> wzzz; \
Swizzle4<T, 4, 3, 2, 2, 3> wzzw; \
Swizzle4<T, 4, 3, 2, 3, 0> wzwx; \
Swizzle4<T, 4, 3, 2, 3, 1> wzwy; \
Swizzle4<T, 4, 3, 2, 3, 2> wzwz; \
Swizzle4<T, 4, 3, 2, 3, 3> wzww; \
Swizzle4<T, 4, 3, 3, 0, 0> wwxx; \
Swizzle4<T, 4, 3, 3, 0, 1> wwxy; \
Swizzle4<T, 4, 3, 3, 0, 2> wwxz; \
Swizzle4<T, 4, 3, 3, 0, 3> wwxw; \
Swizzle4<T, 4, 3, 3, 1, 0> wwyx; \
Swizzle4<T, 4, 3, 3, 1, 1> wwyy; \
Swizzle4<T, 4, 3, 3, 1, 2> wwyz; \
Swizzle4<T, 4, 3, 3, 1, 3> wwyw; \
Swizzle4<T, 4, 3, 3, 2, 0> wwzx; \
Swizzle4<T, 4, 3, 3, 2, 1> wwzy; \
Swizzle4<T, 4, 3, 3, 2, 2> wwzz; \
Swizzle4<T, 4, 3, 3, 2, 3> wwzw; \
Swizzle4<T, 4, 3, 3, 3, 0> wwwx; \
Swizzle4<T, 4, 3, 3, 3, 1> wwwy; \
Swizzle4<T, 4, 3, 3, 3, 2> wwwz; \
Swizzle4<T, 4, 3, 3, 3, 3> wwww

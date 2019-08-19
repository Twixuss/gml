#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include "gml.h"
#include "gmlIO.h"
using namespace gml;
using namespace std;
using namespace chrono;

template<class T>
void syntest() {
   Vector1<T> o(1);

   Vector1<T> a(1);
   +a;
   -a;
   a + o;
   a + o.x;
   a + o.xx;
   a + o.xxx;
   a + o.xxxx;
   a + 1;
   a.x + o;
   a.x + o.x;
   a.x + o.xx;
   a.x + o.xxx;
   a.x + o.xxxx;
   a.x + 1;
   a.xx + o;
   a.xx + o.x;
   a.xx + o.xx;
   a.xx + 1;
   a.xxx + o;
   a.xxx + o.x;
   a.xxx + o.xxx;
   a.xxx + 1;
   a.xxxx + o;
   a.xxxx + o.x;
   a.xxxx + o.xxxx;
   a.xxxx + 1;
   1 + o;
   1 + o.x;
   1 + o.xx;
   1 + o.xxx;
   1 + o.xxxx;
   a += o;
   a += o.x;
   a += 1;
   a.x += o;
   a.x += o.x;
   a.x += 1;

   Vector2<T> b(1, 2);
   +b;
   -b;
   b + o;
   b + b;
   b + b.x;
   b + b.xy;
   b + 1;
   b.x + o;
   b.x + b;
   b.x + b.x;
   b.x + b.xy;
   b.x + b.xyx;
   b.x + b.xyxy;
   b.x + 1;
   b.xy + o;
   b.xy + b;
   b.xy + b.x;
   b.xy + b.xy;
   b.xy + 1;
   b.xyx + o;
   b.xyx + b.x;
   b.xyx + b.xyx;
   b.xyx + 1;
   b.xyxy + o;
   b.xyxy + b.x;
   b.xyxy + b.xyxy;
   b.xyxy + 1;
   1 + b;
   1 + b.x;
   1 + b.xy;
   1 + b.xyx;
   1 + b.xyxy;
   b += o;
   b += b;
   b += b.x;
   b += b.xy;
   b += 1;
   b.xy += o;
   b.xy += b;
   b.xy += b.x;
   b.xy += b.xy;
   b.xy += 1;

   Vector3<T> c(1, 2, 3);
   +c;
   -c;
   c + o;
   c + c;
   c + c.x;
   c + c.xyz;
   c + 1;
   c.x + o;
   c.x + c;
   c.x + c.x;
   c.x + c.xy;
   c.x + c.xyz;
   c.x + c.xyzx;
   c.x + 1;
   c.xy + o;
   c.xy + c.x;
   c.xy + 1;
   c.xyz + o;
   c.xyz + c;
   c.xyz + c.x;
   c.xyz + c.xyz;
   c.xyz + 1;
   1 + c;
   1 + c.x;
   1 + c.xy;
   1 + c.xyz;
   1 + c.xyzx;
   c += o;
   c += c;
   c += c.x;
   c += c.xyz;
   c += 1;
   c.xyz += o;
   c.xyz += c;
   c.xyz += c.x;
   c.xyz += c.xyz;
   c.xyz += 1;

   Vector4<T> d(1, 2, 3, 4);
   +d;
   -d;
   d + o;
   d + d;
   d + d.x;
   d + d.xyzw;
   d + 1;
   d.x + o;
   d.x + d;
   d.x + d.x;
   d.x + d.xy;
   d.x + d.xyz;
   d.x + d.xyzw;
   d.x + 1;
   d.xy + o;
   d.xy + d.x;
   d.xy + d.xy;
   d.xy + 1;
   d.xyz + o;
   d.xyz + d.x;
   d.xyz + d.xyz;
   d.xyz + 1;
   d.xyzw + o;
   d.xyzw + d;
   d.xyzw + d.x;
   d.xyzw + d.xyzw;
   d.xyzw + 1;
   1 + d;
   1 + d.x;
   1 + d.xy;
   1 + d.xyz;
   1 + d.xyzw;
   d += o;
   d += d;
   d += d.x;
   d += d.xyzw;
   d += 1;
   d.xyzw += o;
   d.xyzw += d;
   d.xyzw += d.x;
   d.xyzw += d.xyzw;
   d.xyzw += 1;
}
template<class T>
void asserts() {
   Vector4<T> v4(0);
   v4.wyxz += Vector4<T>(1, 2, 3, 4);
   GML_ASSERT(v4 == Vector4<T>(3, 2, 4, 1));
}
struct Timer {
   Timer() : start(steady_clock::now()) {}
   ~Timer() {
      printf("%5.1f ms\n", (steady_clock::now() - start).count() / 1000000.0f);
   }
   steady_clock::time_point start;
};
void negtest() {
   float sum = 31245728.0f;
   vector<Vector4<float>> vec(1024 * 1024);
   for (auto& v : vec) v ={ rand(), rand(), rand(), rand() };
   puts("randomized");
   {
      Timer _;
      for (auto& v : vec)
         v = -v;
   }
   for (auto& v : vec)
      sum += v[0];
   printf("%5.1f\n", sum);
}
void sumFloats1(float* a, const float* b, size_t count) {
   if (count % 4 == 0) {
      count /= 4;
      if (count % 8 == 0) {
         count /= 8;
         for (int i = 0; i < count; ++i) {
            _mm_storeu_ps(a + 0x00, _mm_add_ps(_mm_loadu_ps(a + 0x00), _mm_loadu_ps(b + 0x00)));
            _mm_storeu_ps(a + 0x04, _mm_add_ps(_mm_loadu_ps(a + 0x04), _mm_loadu_ps(b + 0x04)));
            _mm_storeu_ps(a + 0x08, _mm_add_ps(_mm_loadu_ps(a + 0x08), _mm_loadu_ps(b + 0x08)));
            _mm_storeu_ps(a + 0x0C, _mm_add_ps(_mm_loadu_ps(a + 0x0C), _mm_loadu_ps(b + 0x0C)));
            _mm_storeu_ps(a + 0x10, _mm_add_ps(_mm_loadu_ps(a + 0x10), _mm_loadu_ps(b + 0x10)));
            _mm_storeu_ps(a + 0x14, _mm_add_ps(_mm_loadu_ps(a + 0x14), _mm_loadu_ps(b + 0x14)));
            _mm_storeu_ps(a + 0x18, _mm_add_ps(_mm_loadu_ps(a + 0x18), _mm_loadu_ps(b + 0x18)));
            _mm_storeu_ps(a + 0x1C, _mm_add_ps(_mm_loadu_ps(a + 0x1C), _mm_loadu_ps(b + 0x1C)));
         }
      }
   }
}

void vec3test() {
   const int siz = 1024 * 1024 * 8;
   vector<Vector3<float>> arr31(siz);
   vector<Vector3<float>> arr32(siz);
   vector<Vector4<float>> arr41(siz);
   vector<Vector4<float>> arr42(siz);
   for (auto& v : arr31) v ={ rand(), rand(), rand() };
   for (auto& v : arr32) v ={ rand(), rand(), rand() };
   for (auto& v : arr41) v ={ rand(), rand(), rand(), rand() };
   for (auto& v : arr42) v ={ rand(), rand(), rand(), rand() };
   puts("randomized");
   printf("vec3: ");
   {
      Timer _;
      for (int i = 0; i < siz / 8; ++i) {
         arr31[i] += arr32[i];
         arr31[i+1] += arr32[i+1];
         arr31[i+2] += arr32[i+2];
         arr31[i+3] += arr32[i+3];
         arr31[i+4] += arr32[i+4];
         arr31[i+5] += arr32[i+5];
         arr31[i+6] += arr32[i+6];
         arr31[i+7] += arr32[i+7];
      }
   }
   printf("vec4: ");
   {
      Timer _;
      for (int i = 0; i < siz / 8; ++i) {
         arr41[i] += arr42[i];
         arr41[i + 1] += arr42[i + 1];
         arr41[i + 2] += arr42[i + 2];
         arr41[i + 3] += arr42[i + 3];
         arr41[i + 4] += arr42[i + 4];
         arr41[i + 5] += arr42[i + 5];
         arr41[i + 6] += arr42[i + 6];
         arr41[i + 7] += arr42[i + 7];
      }
   }
   float sum = -1613573;
   for (auto& v : arr31) sum += v.x;
   for (auto& v : arr41) sum += v.x;
   printf("%f", sum);
}
int main() {
   //vec3test();
   syntest<float>();
   syntest<int>();
   asserts<float>();
   //negtest();
   Vector4<float> v(1, 2, 3, 4);
   v = v + v.wwww;
   system("pause");
}
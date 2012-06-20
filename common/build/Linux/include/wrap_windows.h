#ifndef _WRAP_WINDOWS__H
#define _WRAP_WINDOWS__H

#include <cstdlib>
#include <stdint.h>
typedef int64_t __int64;
typedef int64_t Int64;
typedef uint64_t Uint64;

inline int _strnicmp(const char* x, const char* y, size_t l) {
  register char a, b;
  for (size_t i = 0; i++ < l; ++x, ++y) {
    if ((a = x[i]) != (b = y[i])) {
      if (a >= 'A' and a <= 'Z')
        if (b >= 'a' and b <= 'Z')  b -= 'a' - 'A'; else {}
      else if (a >= 'a' and a <= 'z')
        if (b >= 'A' and b <= 'Z')  b += 'a' - 'A';
      if (a != b)
        return a - b;
    }
  }
  return 0;
}

#include <cmath>
#define _isnan isnan
#define _finite finite

#include <cstdlib>
#define OutputDebugString perror

#include <pthread.h>
#define GetCurrentThreadId pthread_self

#define TRUE 1
#define FALSE 0

typedef unsigned char BYTE;

#endif

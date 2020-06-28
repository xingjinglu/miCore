#ifndef __macro_h__
#define __macro_h__

#define STR(s) #s
#define PSIZE(n,m) (((n)+(m))&(~(m)))

#if __GNUC__>=4
  #define __local_func __attribute__((visibility("hidden")))
#else
  #define __local_func
#endif

#endif
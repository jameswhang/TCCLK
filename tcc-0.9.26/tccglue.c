#include "tccglue.h"

int atoi(const char *buf) 
{
    int ret = 0;

    while (*buf >= '0' && *buf <= '9') {
       ret *= 10;
       ret += *buf - '0';
       buf++;
    }

    return ret;
}

// From kernel
unsigned long simple_strtoul(const char *,char **,unsigned int);
long simple_strtol(const char *,char **,unsigned int);
unsigned long long simple_strtoull(const char *,char **,unsigned int);
long long simple_strtoll(const char *,char **,unsigned int);


unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
  return simple_strtol(nptr,endptr,base);
}

long long int strtoll(const char *nptr, char **endptr, int base)
{
  return simple_strtoll(nptr,endptr,base);
}

unsigned long long int strtoull(const char *nptr, char **endptr, int base)
{
  return simple_strtoull(nptr,endptr,base);
}

#if 1
long double strtold (const char* str, char** endptr)
{
  return 0.0; // SHOULD NOT HAPPEN - PAD
}
#endif

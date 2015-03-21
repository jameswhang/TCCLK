int printk(char *fmt, ...);
void * __symbol_get(const char * symbol);

#define printf(...) printk(__VA_ARGS__)
#define fprintf(targ,...) printk(__VA_ARGS__)

#define jmp_buf void *
#define FILE void *

#define NULL ((void*)0)

#define time_t int
#define size_t unsigned long long
#define uintptr_t unsigned long long
#define ucontext_t void*
#define siginfo_t void*

static int errno;

size_t strlen(const char *str);
char *strchr(const char *str, int ch);
char *strrchr(char *str, int ch);
char *strstr(char *str1, const char *str2);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
char *strcpy(char *dest, const char *src);

long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);
long long int strtoll(const char *nptr, char **endptr, int base);
unsigned long long int strtoull(const char *nptr, char **endptr, int base);
int atoi(const char *str);

void *memset(void *ptr, const int val, const size_t num);
void *memcpy(void *dest, const void *src, const size_t num);
int memcmp(const void *str1, const void *str2, const size_t num);
void * memmove ( void * destination, const void * source, size_t num );



void vfree(void *p);
void *tcc_kmalloc(size_t n);
void *tcc_krealloc(void *p, size_t n);


int sscanf(const char *str, const char *fmt, ...);
int sprintf(char *str, const char *fmt, ...);

static inline int read(int fd, void *buf, int n) { printk("Write read()\n"); return 0; }
#define SEEK_SET 0
#define SEEK_CUR 1
static inline int lseek(int fd, int n, int whence) { printk("Write lseek()\n"); return 0;}
static inline void exit(int num) { printk("Write exit()\n"); }
static inline char *getcwd(char *buf, size_t n) { printk("Write getcwd()\n"); return 0; }
static inline char *getenv(char *var) { printk("Write getenv()\n"); return 0; }
static inline int setjmp(jmp_buf env) { printk("Write setjmp()\n"); return 0; }
static inline void longjmp(jmp_buf env, int val) { printk("Write longjmp()\n");  }


#define RTLD_DEFAULT 0
#define RTLD_GLOBAL 1
#define RTLD_LAZY   2
static inline void *dlopen(const char *fn, int flag) { printk("Write dlopen()\n"); return 0; }
static inline void *dlsym(void *handle, const char *symbol) { printk("Write dlsym()\n"); return 0; }
static inline int *dlclose(void *h) { printk("Write dlclose()\n");  return 0;}



// BROKEN
typedef __builtin_va_list __gnuc_va_list;
#define va_list __gnuc_va_list

#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_copy(d,s)    __builtin_va_copy(d,s)

int snprintf(char *s, size_t n, const char *fmt, ...);
int vsnprintf(char * s, size_t n, const char * format, va_list arg);

//static inline void time(time_t *t) { *t=0; }
#define time(x) 

#define stderr 0
#define stdout 0
#define stdin  0
static inline FILE *fdopen(int fd, const char *mode) { printk("Write fdopen()\n"); return 0;}
static inline int fclose(FILE *f) { printk("Write fclose()\n"); return 0; }
static inline int fflush(FILE *f) { printk("Write fflush()\n"); return 0; }
static inline int fputc ( int character, FILE * stream ) { printk("Write fputc()\n"); return 0; } 
static inline int fputs(const char *str, FILE *f) { printk("Write fputs()\n"); return 0;}
static inline size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream ) { printk("Write fwrite()\n"); return 0;}
static inline int vfprintf ( FILE * stream, const char * format, va_list arg ) { printk("Write vfprintf()\n"); return 0;}

static inline int unlink(const char p) { printk("Write unlink()\n"); return 0;}
#define O_WRONLY 1
#define O_CREAT 2
#define O_TRUNC 3
static inline int open(const char *path, int oflag, ... ) { printk("Write open();\n"); return -1;}

#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
static inline int mprotect(const void *addr, size_t len, int prot) { printk("Write mprotect()\n"); return -1; }

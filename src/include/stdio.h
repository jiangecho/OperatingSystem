#ifndef STDIO_H_
#define STDIO_H_

struct _IO_FILE {
	char *_IO_read_ptr;
	char *_IO_read_end;
	char *_IO_read_base;
	char *_IO_write_base;
	char *_IO_write_ptr;
	char *_IO_write_end;
	char *_IO_buf_base;
	char *_IO_buf_end;
};
typedef struct _IO_FILE FILE;

extern FILE *stdout;
extern FILE *stdin;
extern FILE *stderr;

extern void     clearerr(FILE *);
extern char    *ctermid(char *);
extern int      fclose(FILE *);
extern FILE    *fdopen(int, const char *);
extern int      feof(FILE *);
extern int      ferror(FILE *);
extern int      fflush(FILE *);
extern int      fgetc(FILE *);
extern int      fgetpos(FILE *restrict, fpos_t *restrict);
extern char    *fgets(char *restrict, int, FILE *restrict);
extern int      fileno(FILE *);
extern void     flockfile(FILE *);
extern FILE    *fopen(const char *restrict, const char *restrict);
extern int      fprintf(FILE *restrict, const char *restrict, ...);
extern int      fputc(int, FILE *);
extern int      fputs(const char *restrict, FILE *restrict);
extern size_t   fread(void *restrict, size_t, size_t, FILE *restrict);
extern FILE    *freopen(const char *restrict, const char *restrict,
             FILE *restrict);
extern int      fscanf(FILE *restrict, const char *restrict, ...);
extern int      fseek(FILE *, long, int);
extern int      fseeko(FILE *, off_t, int);
extern int      fsetpos(FILE *, const fpos_t *);
extern long     ftell(FILE *);
extern off_t    ftello(FILE *);
extern int      ftrylockfile(FILE *);
extern void     funlockfile(FILE *);
extern size_t   fwrite(const void *restrict, size_t, size_t, FILE *restrict);
extern int      getc(FILE *);
extern int      getchar(void);
extern int      getc_unlocked(FILE *);
extern int      getchar_unlocked(void);
extern char    *gets(char *);
extern int      pclose(FILE *);
extern void     perror(const char *);
extern FILE    *popen(const char *, const char *);
extern int      printf(const char *restrict, ...);
extern int      putc(int, FILE *);
extern int      putchar(int);
extern int      putc_unlocked(int, FILE *);
extern int      putchar_unlocked(int);
extern int      puts(const char *);
extern int      remove(const char *);
extern int      rename(const char *, const char *);
extern void     rewind(FILE *);
extern int      scanf(const char *restrict, ...);
extern void     setbuf(FILE *restrict, char *restrict);
extern int      setvbuf(FILE *restrict, char *restrict, int, size_t);
extern int      snprintf(char *restrict, size_t, const char *restrict, ...);
extern int      sprintf(char *restrict, const char *restrict, ...);
extern int      sscanf(const char *restrict, const char *restrict, int ...);
extern char    *tempnam(const char *, const char *);
extern FILE    *tmpfile(void);
extern char    *tmpnam(char *);
extern int      ungetc(int, FILE *);
extern int      vfprintf(FILE *restrict, const char *restrict, va_list);
extern int      vfscanf(FILE *restrict, const char *restrict, va_list);
extern int      vprintf(const char *restrict, va_list);
extern int      vscanf(const char *restrict, va_list);
extern int      vsnprintf(char *restrict, size_t, const char *restrict,
             va_list);
extern int      vsprintf(char *restrict, const char *restrict, va_list);
extern int      vsscanf(const char *restrict, const char *restrict,
             va_list arg);

#endif

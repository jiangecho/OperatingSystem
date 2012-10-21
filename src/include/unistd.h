/**
 * I defined all things in POSIX.
 */
#ifndef UNISTD_H_
#define UNISTD_H_

// Version Test Macros
#define _POSIX_VERSION 200112L
#define _POSIX2_VERSION 200112L
#define _XOPEN_VERSION 600
// Constants for Options and Option Groups
#define _POSIX_ADVISORY_INFO -1
#define _POSIX_ASYNCHRONOUS_IO -1
#define _POSIX_CHOWN_RESTRICTED 1 // *
#define _POSIX_CLOCK_SELECTION -1
#define _POSIX_CPUTIME -1
#define _POSIX_FSYNC -1
#define _POSIX_IPV6 -1
#define _POSIX_JOB_CONTROL 1
#define _POSIX_MAPPED_FILES -1
#define _POSIX_MEMLOCK -1
#define _POSIX_MEMLOCK_RANGE -1
#define _POSIX_MEMORY_PROTECTION -1
#define _POSIX_MESSAGE_PASSING -1
#define _POSIX_MONOTONIC_CLOCK -1
#define _POSIX_NO_TRUNC 0 // *
#define _POSIX_PRIORITIZED_IO -1
#define _POSIX_PRIORITY_SCHEDULING 1
#define _POSIX_RAW_SOCKETS -1
#define _POSIX_READER_WRITER_LOCKS -1
#define _POSIX_REALTIME_SIGNALS -1
#define _POSIX_REGEXP 1 // *
#define _POSIX_SAVED_IDS 1 // *
#define _POSIX_SEMAPHORES -1
#define _POSIX_SHARED_MEMORY_OBJECTS -1
#define _POSIX_SHELL 1 // *
#define _POSIX_SPAWN -1
#define _POSIX_SPIN_LOCKS -1
#define _POSIX_SPORADIC_SERVER -1
#define _POSIX_SYNCHRONIZED_IO -1
#define _POSIX_THREAD_ATTR_STACKADDR -1
#define _POSIX_THREAD_ATTR_STACKSIZE -1
#define _POSIX_THREAD_CPUTIME -1
#define _POSIX_THREAD_PRIO_INHERIT -1
#define _POSIX_THREAD_PRIO_PROTECT -1
#define _POSIX_THREAD_PRIORITY_SCHEDULING -1
#define _POSIX_THREAD_PROCESS_SHARED -1
#define _POSIX_THREAD_SAFE_FUNCTIONS -1
#define _POSIX_THREAD_SPORADIC_SERVER -1
#define _POSIX_THREADS -1
#define _POSIX_TIMEOUTS -1
#define _POSIX_TIMERS -1
#define _POSIX_TRACE -1
#define _POSIX_TRACE_EVENT_FILTER -1
#define _POSIX_TRACE_INHERIT -1
#define _POSIX_TRACE_LOG -1
#define _POSIX_TYPED_MEMORY_OBJECTS -1
#define _POSIX_VDISABLE 0 // *
#define _POSIX2_C_BIND 200112L // *
#define _POSIX2_C_DEV -1
#define _POSIX2_CHAR_TERM 1 // *
#define _POSIX2_FORT_DEV -1
#define _POSIX2_FORT_RUN -1
#define _POSIX2_LOCALEDEF -1
#define _POSIX2_PBS -1
#define _POSIX2_PBS_ACCOUNTING -1
#define _POSIX2_PBS_CHECKPOINT -1
#define _POSIX2_PBS_LOCATE -1
#define _POSIX2_PBS_MESSAGE -1
#define _POSIX2_PBS_TRACK -1
#define _POSIX2_SW_DEV -1
#define _POSIX2_UPE -1
#define _POSIX_V6_ILP32_OFF32 // *
#define _XOPEN_ENH_I18N 0 // *
#define _XOPEN_SHM 0 // *
#define NULL (void *)0
#define F_OK 0xA0001
#define R_OK 0xA0010
#define W_OK 0xA0100
#define X_OK 0xA1000
#define _CS_PATH // ?
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS 1
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS 1
#define _CS_POSIX_V6_ILP32_OFF32_LIBS 1
#define SEEK_CUR 0xB001
#define SEEK_END 0xB010
#define SEEK_SET 0xB100
#define F_LOCK 123
#define F_TEST 1234
#define F_TLOCK 12345
#define F_ULOCK 123456
#define _PC_2_SYMLINKS
#define _PC_ALLOC_SIZE_MIN
#define _PC_ASYNC_IO
#define _PC_CHOWN_RESTRICTED
#define _PC_FILESIZEBITS
#define _PC_LINK_MAX
#define _PC_MAX_CANON
#define _PC_MAX_INPUT
#define _PC_NAME_MAX
#define _PC_NO_TRUNC
#define _PC_PATH_MAX
#define _PC_PIPE_BUF
#define _PC_PRIO_IO
#define _PC_REC_INCR_XFER_SIZE
#define _PC_REC_MIN_XFER_SIZE
#define _PC_REC_XFER_ALIGN
#define _PC_SYMLINK_MAX
#define _PC_SYNC_IO
#define _PC_VDISABLE
#define STDERR_FILENO 2
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
/* *************************************************************** *
 * The following symbolic constants shall be defined for sysconf() *
 * *************************************************************** */
#define _SC_2_C_BIND
#define _SC_2_C_DEV
#define _SC_2_CHAR_TERM
#define _SC_2_FORT_DEV
#define _SC_2_FORT_RUN
#define _SC_2_LOCALEDEF
#define _SC_2_PBS
#define _SC_2_PBS_ACCOUNTING
#define _SC_2_PBS_CHECKPOINT
#define _SC_2_PBS_LOCATE
#define _SC_2_PBS_MESSAGE
#define _SC_2_PBS_TRACK
#define _SC_2_SW_DEV
#define _SC_2_UPE
#define _SC_2_VERSION
#define _SC_ADVISORY_INFO
#define _SC_AIO_LISTIO_MAX
#define _SC_AIO_MAX
#define _SC_AIO_PRIO_DELTA_MAX
#define _SC_ARG_MAX
#define _SC_ASYNCHRONOUS_IO
#define _SC_ATEXIT_MAX
#define _SC_BARRIERS
#define _SC_BC_BASE_MAX
#define _SC_BC_DIM_MAX
#define _SC_BC_SCALE_MAX
#define _SC_BC_STRING_MAX
#define _SC_CHILD_MAX
#define _SC_CLK_TCK
#define _SC_CLOCK_SELECTION
#define _SC_COLL_WEIGHTS_MAX
#define _SC_CPUTIME
#define _SC_DELAYTIMER_MAX
#define _SC_EXPR_NEST_MAX
#define _SC_FSYNC
#define _SC_GETGR_R_SIZE_MAX
#define _SC_GETPW_R_SIZE_MAX
#define _SC_HOST_NAME_MAX
#define _SC_IOV_MAX
#define _SC_IPV6
#define _SC_JOB_CONTROL
#define _SC_LINE_MAX
#define _SC_LOGIN_NAME_MAX
#define _SC_MAPPED_FILES
#define _SC_MEMLOCK
#define _SC_MEMLOCK_RANGE
#define _SC_MEMORY_PROTECTION
#define _SC_MESSAGE_PASSING
#define _SC_MONOTONIC_CLOCK
#define _SC_MQ_OPEN_MAX
#define _SC_MQ_PRIO_MAX
#define _SC_NGROUPS_MAX
#define _SC_OPEN_MAX
#define _SC_PAGE_SIZE
#define _SC_PAGESIZE
#define _SC_PRIORITIZED_IO
#define _SC_PRIORITY_SCHEDULING
#define _SC_RAW_SOCKETS
#define _SC_RE_DUP_MAX
#define _SC_READER_WRITER_LOCKS
#define _SC_REALTIME_SIGNALS
#define _SC_REGEXP
#define _SC_RTSIG_MAX
#define _SC_SAVED_IDS
#define _SC_SEM_NSEMS_MAX
#define _SC_SEM_VALUE_MAX
#define _SC_SEMAPHORES
#define _SC_SHARED_MEMORY_OBJECTS
#define _SC_SHELL
#define _SC_SIGQUEUE_MAX
#define _SC_SPAWN
#define _SC_SPIN_LOCKS
#define _SC_SPORADIC_SERVER
#define _SC_SS_REPL_MAX
#define _SC_STREAM_MAX
#define _SC_SYMLOOP_MAX
#define _SC_SYNCHRONIZED_IO
#define _SC_THREAD_ATTR_STACKADDR
#define _SC_THREAD_ATTR_STACKSIZE
#define _SC_THREAD_CPUTIME
#define _SC_THREAD_DESTRUCTOR_ITERATIONS
#define _SC_THREAD_KEYS_MAX
#define _SC_THREAD_PRIO_INHERIT
#define _SC_THREAD_PRIO_PROTECT
#define _SC_THREAD_PRIORITY_SCHEDULING
#define _SC_THREAD_PROCESS_SHARED
#define _SC_THREAD_SAFE_FUNCTIONS
#define _SC_THREAD_SPORADIC_SERVER
#define _SC_THREAD_STACK_MIN
#define _SC_THREAD_THREADS_MAX
#define _SC_THREADS
#define _SC_TIMEOUTS
#define _SC_TIMER_MAX
#define _SC_TIMERS
#define _SC_TRACE
#define _SC_TRACE_EVENT_FILTER
#define _SC_TRACE_EVENT_NAME_MAX
#define _SC_TRACE_INHERIT
#define _SC_TRACE_LOG
#define _SC_TRACE_NAME_MAX
#define _SC_TRACE_SYS_MAX
#define _SC_TRACE_USER_EVENT_MAX
#define _SC_TTY_NAME_MAX
#define _SC_TYPED_MEMORY_OBJECTS
#define _SC_TZNAME_MAX
#define _SC_V6_ILP32_OFF32
#define _SC_V6_ILP32_OFFBIG
#define _SC_V6_LP64_OFF64
#define _SC_V6_LPBIG_OFFBIG
#define _SC_VERSION
#define _SC_XBS5_ILP32_OFF32 // (LEGACY)
#define _SC_XBS5_ILP32_OFFBIG // (LEGACY)
#define _SC_XBS5_LP64_OFF64 // (LEGACY)
#define _SC_XBS5_LPBIG_OFFBIG // (LEGACY)
#define _SC_XOPEN_CRYPT
#define _SC_XOPEN_ENH_I18N
#define _SC_XOPEN_LEGACY
#define _SC_XOPEN_REALTIME
#define _SC_XOPEN_REALTIME_THREADS
#define _SC_XOPEN_SHM
#define _SC_XOPEN_STREAMS
#define _SC_XOPEN_UNIX
#define _SC_XOPEN_VERSION
/* ************************************ *
 *                END                   *
 * ************************************ */
extern int          access(const char *, int);
extern unsigned     alarm(unsigned);
extern int          chdir(const char *);
extern int          chown(const char *, uid_t, gid_t);
extern int          close(int);
extern size_t       confstr(int, char *, size_t);
extern char        *crypt(const char *, const char *);
extern char        *ctermid(char *);
extern int          dup(int);
extern int          dup2(int, int);
extern void         encrypt(char[64], int);
extern int          execl(const char *, const char *, ...);
extern int          execle(const char *, const char *, ...);
extern int          execlp(const char *, const char *, ...);
extern int          execv(const char *, char *const []);
extern int          execve(const char *, char *const [], char *const []);
extern int          execvp(const char *, char *const []);
extern void        _exit(int);
extern int          fchown(int, uid_t, gid_t);
extern int          fchdir(int);
extern int          fdatasync(int);
extern pid_t        fork(void);
extern long         fpathconf(int, int);
extern int          fsync(int);
extern int          ftruncate(int, off_t);
extern char        *getcwd(char *, size_t);
extern gid_t        getegid(void);
extern uid_t        geteuid(void);
extern gid_t        getgid(void);
extern int          getgroups(int, gid_t []);
extern long         gethostid(void);
extern int          gethostname(char *, size_t);
extern char        *getlogin(void);
extern int          getlogin_r(char *, size_t);
extern int          getopt(int, char * const [], const char *);
extern pid_t        getpgid(pid_t);
extern pid_t        getpgrp(void);
extern pid_t        getpid(void);
extern pid_t        getppid(void);
extern pid_t        getsid(pid_t);
extern uid_t        getuid(void);
extern char        *getwd(char *); // (LEGACY )
extern int          isatty(int);
extern int          lchown(const char *, uid_t, gid_t);
extern int          link(const char *, const char *);
extern int          lockf(int, int, off_t);
extern off_t        lseek(int, off_t, int);
extern int          nice(int);
extern long         pathconf(const char *, int);
extern int          pause(void);
extern int          pipe(int [2]);
extern ssize_t      pread(int, void *, size_t, off_t);
extern ssize_t      pwrite(int, const void *, size_t, off_t);
extern ssize_t      read(int, void *, size_t);
extern ssize_t      readlink(const char *restrict, char *restrict, size_t);
extern int          rmdir(const char *);
extern int          setegid(gid_t);
extern int          seteuid(uid_t);
extern int          setgid(gid_t);
extern int          setpgid(pid_t, pid_t);
extern pid_t        setpgrp(void);
extern int          setregid(gid_t, gid_t);
extern int          setreuid(uid_t, uid_t);
extern pid_t        setsid(void);
extern int          setuid(uid_t);
extern unsigned     sleep(unsigned);
extern void         swab(const void *restrict, void *restrict, ssize_t);
extern int          symlink(const char *, const char *);
extern void         sync(void);
extern long         sysconf(int);
extern pid_t        tcgetpgrp(int);
extern int          tcsetpgrp(int, pid_t);
extern int          truncate(const char *, off_t);
extern char        *ttyname(int);
extern int          ttyname_r(int, char *, size_t);
extern useconds_t   ualarm(useconds_t, useconds_t);
extern int          unlink(const char *);
extern int          usleep(useconds_t);
extern pid_t        vfork(void);
extern ssize_t      write(int, const void *, size_t);

extern char  *optarg;
extern int    optind, opterr, optopt;

#endif

; system calls
;                                  rax  ; rdi                               rsi                                   rdx                                  r10                            r8                                   r9
%define SYS_READ                   0    ; unsigned int fd                   char *buf                             size_t count
%define SYS_WRITE                  1    ; unsigned int fd                   const char *buf                       size_t count
%define SYS_OPEN                   2    ; const char *filename              int flags                             int mode
%define SYS_CLOSE                  3    ; unsigned int fd
%define SYS_STAT                   4    ; const char *filename              struct stat *statbuf
%define SYS_FSTAT                  5    ; unsigned int fd                   struct stat *statbuf
%define SYS_LSTAT                  6    ; fconst char *filename             struct stat *statbuf
%define SYS_POLL                   7    ; struct poll_fd *ufds              unsigned int nfds                     long timeout_msecs
%define SYS_LSEEK                  8    ; unsigned int fd                   off_t offset                          unsigned int origin
%define SYS_MMAP                   9    ; unsigned long addr                unsigned long len                     unsigned long prot                   unsigned long flags            unsigned long fd                     unsigned long off
%define SYS_MPROTECT               10   ; unsigned long start               size_t len                            unsigned long prot
%define SYS_MUNMAP                 11   ; unsigned long addr                size_t len
%define SYS_BRK                    12   ; unsigned long brk
%define SYS_RT_SIGACTION           13   ; int sig                           const struct sigaction *act           struct sigaction *oact               size_t sigsetsize
%define SYS_RT_SIGPROCMASK         14   ; int how                           sigset_t *nset                        sigset_t *oset                       size_t sigsetsize
%define SYS_RT_SIGRETURN           15   ; unsigned long __unused
%define SYS_IOCTL                  16   ; unsigned int fd                   unsigned int cmd                      unsigned long arg
%define SYS_PREAD64                17   ; unsigned long fd                  char *buf                             size_t count                         loff_t pos
%define SYS_PWRITE64               18   ; unsigned int fd                   const char *buf                       size_t count                         loff_t pos
%define SYS_READV                  19   ; unsigned long fd                  const struct iovec *vec               unsigned long vlen
%define SYS_WRITEV                 20   ; unsigned long fd                  const struct iovec *vec               unsigned long vlen
%define SYS_ACCESS                 21   ; const char *filename              int mode
%define SYS_PIPE                   22   ; int *filedes
%define SYS_SELECT                 23   ; int n                             fd_set *inp                           fd_set *outp                         fd_set*exp                     struct timeval *tvp
%define SYS_SCHED_YIELD            24   ;
%define SYS_MREMAP                 25   ; unsigned long addr                unsigned long old_len                 unsigned long new_len                unsigned long flags            unsigned long new_addr
%define SYS_MSYNC                  26   ; unsigned long start               size_t len                            int flags
%define SYS_MINCORE                27   ; unsigned long start               size_t len                            unsigned char *vec
%define SYS_MADVISE                28   ; unsigned long start               size_t len_in                         int behavior
%define SYS_SHMGET                 29   ; key_t key                         size_t size                           int shmflg
%define SYS_SHMAT                  30   ; int shmid                         char *shmaddr                         int shmflg
%define SYS_SHMCTL                 31   ; int shmid                         int cmd                               struct shmid_ds *buf
%define SYS_DUP                    32   ; unsigned int fildes
%define SYS_DUP2                   33   ; unsigned int oldfd                unsigned int newfd
%define SYS_PAUSE                  34   ;
%define SYS_NANOSLEEP              35   ; struct timespec *rqtp             struct timespec *rmtp
%define SYS_GETITIMER              36   ; int which                         struct itimerval *value
%define SYS_ALARM                  37   ; unsigned int seconds
%define SYS_SETITIMER              38   ; int which                         struct itimerval *value               struct itimerval *ovalue
%define SYS_GETPID                 39   ;
%define SYS_SENDFILE               40   ; int out_fd                        int in_fd                             off_t *offset                        size_t count
%define SYS_SOCKET                 41   ; int family                        int type                              int protocol
%define SYS_CONNECT                42   ; int fd                            struct sockaddr *uservaddr            int addrlen
%define SYS_ACCEPT                 43   ; int fd                            struct sockaddr *upeer_sockaddr       int *upeer_addrlen
%define SYS_SENDTO                 44   ; int fd                            void *buff                            size_t len                           unsigned flags                 struct sockaddr *addr                int addr_len
%define SYS_RECVFROM               45   ; int fd                            void *ubuf                            size_t size                          unsigned flags                 struct sockaddr *addr                int *addr_len
%define SYS_SENDMSG                46   ; int fd                            struct msghdr *msg                    unsigned flags
%define SYS_RECVMSG                47   ; int fd                            struct msghdr *msg                    unsigned int flags
%define SYS_SHUTDOWN               48   ; int fd                            int how
%define SYS_BIND                   49   ; int fd                            struct sokaddr *umyaddr               int addrlen
%define SYS_LISTEN                 50   ; int fd                            int backlog
%define SYS_GETSOCKNAME            51   ; int fd                            struct sockaddr *usockaddr            int *usockaddr_len
%define SYS_GETPEERNAME            52   ; int fd                            struct sockaddr *usockaddr            int *usockaddr_len
%define SYS_SOCKETPAIR             53   ; int family                        int type                              int protocol                         int *usockvec
%define SYS_SETSOCKOPT             54   ; int fd                            int level                             int optname                          char *optval                   int optlen
%define SYS_GETSOCKOPT             55   ; int fd                            int level                             int optname                          char *optval                   int *optlen
%define SYS_CLONE                  56   ; unsigned long clone_flags         unsigned long newsp                   void *parent_tid                     void *child_tid
%define SYS_FORK                   57   ;
%define SYS_VFORK                  58   ;
%define SYS_EXECVE                 59   ; const char *filename              const char *const argv[]              const char *const envp[]
%define SYS_EXIT                   60   ; int error_code
%define SYS_WAIT4                  61   ; pid_t upid                        int *stat_addr                        int options                          struct rusage *ru
%define SYS_KILL                   62   ; pid_t pid                         int sig
%define SYS_UNAME                  63   ; struct old_utsname *name
%define SYS_SEMGET                 64   ; key_t key                         int nsems                             int semflg
%define SYS_SEMOP                  65   ; int semid                         struct sembuf *tsops                  unsigned nsops
%define SYS_SEMCTL                 66   ; int semid                         int semnum                            int cmd                              union semun arg
%define SYS_SHMDT                  67   ; char *shmaddr
%define SYS_MSGGET                 68   ; key_t key                         int msgflg
%define SYS_MSGSND                 69   ; int msqid                         struct msgbuf *msgp                   size_t msgsz                         int msgflg
%define SYS_MSGRCV                 70   ; int msqid                         struct msgbuf *msgp                   size_t msgsz                         long msgtyp                    int msgflg
%define SYS_MSGCTL                 71   ; int msqid                         int cmd                               struct msqid_ds *buf
%define SYS_FCNTL                  72   ; unsigned int fd                   unsigned int cmd                      unsigned long arg
%define SYS_FLOCK                  73   ; unsigned int fd                   unsigned int cmd
%define SYS_FSYNC                  74   ; unsigned int fd
%define SYS_FDATASYNC              75   ; unsigned int fd
%define SYS_TRUNCATE               76   ; const char *path                  long length
%define SYS_FTRUNCATE              77   ; unsigned int fd                   unsigned long length
%define SYS_GETDENTS               78   ; unsigned int fd                   struct linux_dirent *dirent           unsigned int count
%define SYS_GETCWD                 79   ; char *buf                         unsigned long size
%define SYS_CHDIR                  80   ; const char *filename
%define SYS_FCHDIR                 81   ; unsigned int fd
%define SYS_RENAME                 82   ; const char *oldname               const char *newname
%define SYS_MKDIR                  83   ; const char *pathname              int mode
%define SYS_RMDIR                  84   ; const char *pathname
%define SYS_CREAT                  85   ; const char *pathname              int mode
%define SYS_LINK                   86   ; const char *oldname               const char *newname
%define SYS_UNLINK                 87   ; const char *pathname
%define SYS_SYMLINK                88   ; const char *oldname               const char *newname
%define SYS_READLINK               89   ; const char *path                  char *buf                             int bufsiz
%define SYS_CHMOD                  90   ; const char *filename              mode_t mode
%define SYS_FCHMOD                 91   ; unsigned int fd                   mode_t mode
%define SYS_CHOWN                  92   ; const char *filename              uid_t user                            git_t group
%define SYS_FCHOWN                 93   ; unsigned int fd                   uid_t user                            git_t group
%define SYS_LCHOWN                 94   ; const char *filename              uid_t user                            git_t group
%define SYS_UMASK                  95   ; int mask
%define SYS_GETTIMEOFDAY           96   ; struct timeval *tv                struct timezone *tz
%define SYS_GETRLIMIT              97   ; unsigned int resource             struct rlimit *rlim
%define SYS_GETRUSAGE              98   ; int who                           struct rusage *ru
%define SYS_SYSINFO                99   ; struct sysinfo *info
%define SYS_TIMES                  100  ; struct sysinfo *info
%define SYS_PTRACE                 101  ; long request                      long pid                              unsigned long addr                   unsigned long data
%define SYS_GETUID                 102  ;
%define SYS_SYSLOG                 103  ; int type                          char *buf                             int len
%define SYS_GETGID                 104  ;
%define SYS_SETUID                 105  ; uid_t uid
%define SYS_SETGID                 106  ; git_t gid
%define SYS_GETEUID                107  ;
%define SYS_GETEGID                108  ;
%define SYS_SETPGID                109  ; pid_t pid                         pid_t pgid
%define SYS_GETPPID                110  ;
%define SYS_GETPGRP                111  ;
%define SYS_SETSID                 112  ;
%define SYS_SETREUID               113  ; uid_t ruid                        uid_t euid
%define SYS_SETREGID               114  ; git_t rgid                        gid_t egid
%define SYS_GETGROUPS              115  ; int gidsetsize                    gid_t *grouplist
%define SYS_SETGROUPS              116  ; int gidsetsize                    gid_t *grouplist
%define SYS_SETRESUID              117  ; uid_t *ruid                       uid_t *euid                           uid_t *suid
%define SYS_GETRESUID              118  ; uid_t *ruid                       uid_t *euid                           uid_t *suid
%define SYS_SETRESGID              119  ; gid_t rgid                        gid_t egid                            gid_t sgid
%define SYS_GETRESGID              120  ; git_t *rgid                       git_t *egid                           git_t *sgid
%define SYS_GETPGID                121  ; pid_t pid
%define SYS_SETFSUID               122  ; uid_t uid
%define SYS_SETFSGID               123  ; gid_t gid
%define SYS_GETSID                 124  ; pid_t pid
%define SYS_CAPGET                 125  ; cap_user_header_t header          cap_user_data_t dataptr
%define SYS_CAPSET                 126  ; cap_user_header_t header          const cap_user_data_t data
%define SYS_RT_SIGPENDING          127  ; sigset_t *set                     size_t sigsetsize
%define SYS_RT_SIGTIMEDWAIT        128  ; const sigset_t *uthese            siginfo_t *uinfo                      const struct timespec *uts           size_t sigsetsize
%define SYS_RT_SIGQUEUEINFO        129  ; pid_t pid                         int sig                               siginfo_t *uinfo
%define SYS_RT_SIGSUSPEND          130  ; sigset_t *unewset                 size_t sigsetsize
%define SYS_SIGALTSTACK            131  ; const stack_t *uss                stack_t *uoss
%define SYS_UTIME                  132  ; char *filename                    struct utimbuf *times
%define SYS_MKNOD                  133  ; const char *filename              int mode                              unsigned dev
%define SYS_USELIB                 134  ; NOT IMPLEMENTED
%define SYS_PERSONALITY            135  ; unsigned int personality
%define SYS_USTAT                  136  ; unsigned dev                      struct ustat *ubuf
%define SYS_STATFS                 137  ; const char *pathname              struct statfs *buf
%define SYS_FSTATFS                138  ; unsigned int fd                   struct statfs *buf
%define SYS_SYSFS                  139  ; int option                        unsigned long arg1                    unsigned long arg2
%define SYS_GETPRIORITY            140  ; int which                         int who
%define SYS_SETPRIORITY            141  ; int which                         int who                               int niceval
%define SYS_SCHED_SETPARAM         142  ; pid_t pid                         struct sched_param *param
%define SYS_SCHED_GETPARAM         143  ; pid_t pid                         struct sched_param *param
%define SYS_SCHED_SETSCHEDULER     144  ; pid_t pid                         int policy                            struct sched_param *param
%define SYS_SCHED_GETSCHEDULER     145  ; pid_t pid
%define SYS_SCHED_GET_PRIORITY_MAX 146  ; int policy
%define SYS_SCHED_GET_PRIORITY_MIN 147  ; int policy
%define SYS_SCHED_RR_GET_INTERVAL  148  ; pid_t pid                         struct timespec *interval
%define SYS_MLOCK                  149  ; unsigned long start               size_t len
%define SYS_MUNLOCK                150  ; unsigned long start               size_t len
%define SYS_MLOCKALL               151  ; int flags
%define SYS_MUNLOCKALL             152  ;
%define SYS_VHANGUP                153  ;
%define SYS_MODIFY_LDT             154  ; int func                          void *ptr                             unsigned long bytecount
%define SYS_PIVOT_ROOT             155  ; const char *new_root              const char *put_old
%define SYS__SYSCTL                156  ; struct __sysctl_args *args
%define SYS_PRCTL                  157  ; int option                        unsigned long arg2                    unsigned long arg3                   unsigned long arg4                                                  unsigned long arg5
%define SYS_ARCH_PRCTL             158  ; struct task_struct *task          int code                              unsigned long *addr
%define SYS_ADJTIMEX               159  ; struct timex *txc_p
%define SYS_SETRLIMIT              160  ; unsigned int resource             struct rlimit *rlim
%define SYS_CHROOT                 161  ; const char *filename
%define SYS_SYNC                   162  ;
%define SYS_ACCT                   163  ; const char *name
%define SYS_SETTIMEOFDAY           164  ; struct timeval *tv                struct timezone *tz
%define SYS_MOUNT                  165  ; char *dev_name                    char *dir_name                        char *type                           unsigned long flags            void *data
%define SYS_UMOUNT2                166  ; const char *target                int flags
%define SYS_SWAPON                 167  ; const char *specialfile           int swap_flags
%define SYS_SWAPOFF                168  ; const char *specialfile
%define SYS_REBOOT                 169  ; int magic1                        int magic2                            unsigned int cmd                     void *arg
%define SYS_SETHOSTNAME            170  ; char *name                        int len
%define SYS_SETDOMAINNAME          171  ; char *name                        int len
%define SYS_IOPL                   172  ; unsigned int level                struct pt_regs *regs
%define SYS_IOPERM                 173  ; unsigned long from                unsigned long num                     int turn_on
%define SYS_CREATE_MODULE          174  ; REMOVED IN Linux 2.6
%define SYS_INIT_MODULE            175  ; void *umod                        unsigned long len                     const char *uargs
%define SYS_DELETE_MODULE          176  ; const chat *name_user             unsigned int flags
%define SYS_GET_KERNEL_SYMS        177  ; REMOVED IN Linux 2.6
%define SYS_QUERY_MODULE           178  ; REMOVED IN Linux 2.6
%define SYS_QUOTACTL               179  ; unsigned int cmd                  const char *special                   qid_t id                             void *addr
%define SYS_NFSSERVCTL             180  ; NOT IMPLEMENTED
%define SYS_GETPMSG                181  ; NOT IMPLEMENTED
%define SYS_PUTPMSG                182  ; NOT IMPLEMENTED
%define SYS_AFS_SYSCALL            183  ; NOT IMPLEMENTED
%define SYS_TUXCALL                184  ; NOT IMPLEMENTED
%define SYS_SECURITY               185  ; NOT IMPLEMENTED
%define SYS_GETTID                 186  ;
%define SYS_READAHEAD              187  ; int fd                            loff_t offset                         size_t count
%define SYS_SETXATTR               188  ; const char *pathname              const char *name                      const void *value                    size_t size                    int flags
%define SYS_LSETXATTR              189  ; const char *pathname              const char *name                      const void *value                    size_t size                    int flags
%define SYS_FSETXATTR              190  ; int fd                            const char *name                      const void *value                    size_t size                    int flags
%define SYS_GETXATTR               191  ; const char *pathname              const char *name                      void *value                          size_t size
%define SYS_LGETXATTR              192  ; const char *pathname              const char *name                      void *value                          size_t size
%define SYS_FGETXATTR              193  ; int fd                            const har *name                       void *value                          size_t size
%define SYS_LISTXATTR              194  ; const char *pathname              char *list                            size_t size
%define SYS_LLISTXATTR             195  ; const char *pathname              char *list                            size_t size
%define SYS_FLISTXATTR             196  ; int fd                            char *list                            size_t size
%define SYS_REMOVEXATTR            197  ; const char *pathname              const char *name
%define SYS_LREMOVEXATTR           198  ; const char *pathname              const char *name
%define SYS_FREMOVEXATTR           199  ; int fd                            const char *name
%define SYS_TKILL                  200  ; pid_t pid                         ing sig
%define SYS_TIME                   201  ; time_t *tloc
%define SYS_FUTEX                  202  ; u32 *uaddr                        int op                                u32 val                              struct timespec *utime         u32 *uaddr2                          u32 val3
%define SYS_SCHED_SETAFFINITY      203  ; pid_t pid                         unsigned int len                      unsigned long *user_mask_ptr
%define SYS_SCHED_GETAFFINITY      204  ; pid_t pid                         unsigned int len                      unsigned long *user_mask_ptr
%define SYS_SET_THREAD_AREA        205  ; NOT IMPLEMENTED. Use arch_prctl
%define SYS_IO_SETUP               206  ; unsigned nr_events                aio_context_t *ctxp
%define SYS_IO_DESTROY             207  ; aio_context_t ctx
%define SYS_IO_GETEVENTS           208  ; aio_context_t ctx_id              long min_nr                           long nr                              struct io_event *events
%define SYS_IO_SUBMIT              209  ; aio_context_t ctx_id              long nr                               struct iocb **iocbpp
%define SYS_IO_CANCEL              210  ; aio_context_t ctx_id              struct iocb *iocb                     struct io_event *result
%define SYS_GET_THREAD_AREA        211  ; NOT IMPLEMENTED. Use arch_prctl
%define SYS_LOOKUP_DCOOKIE         212  ; u64 cookie64                      long buf                              long len
%define SYS_EPOLL_CREATE           213  ; int size
%define SYS_EPOLL_CTL_OLD          214  ; NOT IMPLEMENTED
%define SYS_EPOLL_WAIT_OLD         215  ; NOT IMPLEMENTED
%define SYS_REMAP_FILE_PAGES       216  ; unsigned long start               unsigned long size                    unsigned long prot                   unsigned long pgoff            unsigned long flags
%define SYS_GETDENTS64             217  ; unsigned int fd                   struct linux_dirent64 *dirent         unsigned int count
%define SYS_SET_TID_ADDRESS        218  ; int *tidptr
%define SYS_RESTART_SYSCALL        219  ;
%define SYS_SEMTIMEDOP             220  ; int semid                         struct sembuf *tsops                  unsigned nsops                       const struct timespec *timeout
%define SYS_FADVISE64              221  ; int fd                            loff_t offset                         size_t len                           int advice
%define SYS_TIMER_CREATE           222  ; const clockid_t which_clock       struct sigevent *timer_event_spec     timer_t *created_timer_id
%define SYS_TIMER_SETTIME          223  ; timer_t timer_id                  int flags                             const struct itimerspec *new_setting struct itimerspec *old_setting
%define SYS_TIMER_GETTIME          224  ; timer_t timer_id                  struct itimerspec *setting
%define SYS_TIMER_GETOVERRUN       225  ; timer_t timer_id
%define SYS_TIMER_DELETE           226  ; timer_t timer_id
%define SYS_CLOCK_SETTIME          227  ; const clockid_t which_clock       const struct timespec *tp
%define SYS_CLOCK_GETTIME          228  ; const clockid_t which_clock       struct timespec *tp
%define SYS_CLOCK_GETRES           229  ; const clockid_t which_clock       struct timespec *tp
%define SYS_CLOCK_NANOSLEEP        230  ; const clockid_t which_clock       int flags                             const struct timespec *rqtp          struct timespec *rmtp
%define SYS_EXIT_GROUP             231  ; int error_code
%define SYS_EPOLL_WAIT             232  ; int epfd                          struct epoll_event *events            int maxevents                        int timeout
%define SYS_EPOLL_CTL              233  ; int epfd                          int op                                int fd                               struct epoll_event *event
%define SYS_TGKILL                 234  ; pid_t tgid                        pid_t pid                             int sig
%define SYS_UTIMES                 235  ; char *filename                    struct timeval *utimes
%define SYS_VSERVER                236  ; NOT IMPLEMENTED
%define SYS_MBIND                  237  ; unsigned long start               unsigned long len                     unsigned long mode                   unsigned long *nmask           unsigned long maxnode                unsigned flags
%define SYS_SET_MEMPOLICY          238  ; int mode                          unsigned long *nmask                  unsigned long maxnode
%define SYS_GET_MEMPOLICY          239  ; int *policy                       unsigned long *nmask                  unsigned long maxnode                unsigned long addr             unsigned long flags
%define SYS_MQ_OPEN                240  ; const char *u_name                int oflag                             mode_t mode                          struct mq_attr *u_attr
%define SYS_MQ_UNLINK              241  ; const char *u_name
%define SYS_MQ_TIMEDSEND           242  ; mqd_t mqdes                       const char *u_msg_ptr                 size_t msg_len                       unsigned int msg_prio          const stuct timespec *u_abs_timeout
%define SYS_MQ_TIMEDRECEIVE        243  ; mqd_t mqdes                       char *u_msg_ptr                       size_t msg_len                       unsigned int *u_msg_prio       const struct timespec *u_abs_timeout
%define SYS_MQ_NOTIFY              244  ; mqd_t mqdes                       const struct sigevent *u_notification
%define SYS_MQ_GETSETATTR          245  ; mqd_t mqdes                       const struct mq_attr *u_mqstat        struct mq_attr *u_omqstat
%define SYS_KEXEC_LOAD             246  ; unsigned long entry               unsigned long nr_segments             struct kexec_segment *segments       unsigned long flags
%define SYS_WAITID                 247  ; int which                         pid_t upid                            struct siginfo *infop                int options                    struct rusage *ru
%define SYS_ADD_KEY                248  ; const char *_type                 const char *_description              const void *_payload                 size_t plen
%define SYS_REQUEST_KEY            249  ; const char *_type                 const char *_description              const char *_callout_info            key_serial_t destringid
%define SYS_KEYCTL                 250  ; int option                        unsigned long arg2                    unsigned long arg3                   unsigned long arg4             unsigned long arg5
%define SYS_IOPRIO_SET             251  ; int which                         int who                               int ioprio
%define SYS_IOPRIO_GET             252  ; int which                         int who
%define SYS_INOTIFY_INIT           253  ;
%define SYS_INOTIFY_ADD_WATCH      254  ; int fd                            const char *pathname                  u32 mask
%define SYS_INOTIFY_RM_WATCH       255  ; int fd                            __s32 wd
%define SYS_MIGRATE_PAGES          256  ; pid_t pid                         unsigned long maxnode                 const unsigned long *old_nodes       const unsigned long *new_nodes
%define SYS_OPENAT                 257  ; int dfd                           const char *filename                  int flags                            int mode
%define SYS_MKDIRAT                258  ; int dfd                           const char *pathname                  int mode
%define SYS_MKNODAT                259  ; int dfd                           const char *filename                  int mode                             unsigned dev
%define SYS_FCHOWNAT               260  ; int dfd                           const char *filename                  uid_t user                           gid_t group                    int flag
%define SYS_FUTIMESAT              261  ; int dfd                           const char *filename                  struct timeval *utimes
%define SYS_NEWFSTATAT             262  ; int dfd                           const char *filename                  struct stat *statbuf                 int flag
%define SYS_UNLINKAT               263  ; int dfd                           const char *pathname                  int flag
%define SYS_RENAMEAT               264  ; int oldfd                         const char *oldname                   int newfd                            const char *newname
%define SYS_LINKAT                 265  ; int oldfd                         const char *oldname                   int newfd                            const char *newname            int flags
%define SYS_SYMLINKAT              266  ; const char *oldname               int newfd                             const char *newname
%define SYS_READLINKAT             267  ; int dfd                           const char *pathname                  char *buf                            int bufsiz
%define SYS_FCHMODAT               268  ; int dfd                           const char *filename                  mode_t mode
%define SYS_FACCESSAT              269  ; int dfd                           const char *filename                  int mode
%define SYS_PSELECT6               270  ; int n                             fd_set *inp                           fd_set *outp                         fd_set *exp                    struct timespec *tsp                 void *sig
%define SYS_PPOLL                  271  ; struct pollfd *ufds               unsigned int nfds                     struct timespec *tsp                 const sigset_t *sigmask        size_t sigsetsize
%define SYS_UNSHARE                272  ; unsigned long unshare_flags
%define SYS_SET_ROBUST_LIST        273  ; struct robust_list_head *head     size_t len
%define SYS_GET_ROBUST_LIST        274  ; int pid                           struct robust_list_head **head_ptr    size_t *len_ptr
%define SYS_SPLICE                 275  ; int fd_in                         loff_t *off_in                        int fd_out                           loff_t *off_out                size_t len                           unsigned int flags
%define SYS_TEE                    276  ; int fdin                          int fdout                             size_t len                           unsigned int flags
%define SYS_SYNC_FILE_RANGE        277  ; long fd                           loff_t offset                         loff_t bytes                         long flags
%define SYS_VMSPLICE               278  ; int fd                            const struct iovec *iov               unsigned long nr_segs                unsigned int flags
%define SYS_MOVE_PAGES             279  ; pid_t pid                         unsigned long nr_pages                const void **pages                   const int *nodes               int *status                          int flags
%define SYS_UTIMENSAT              280  ; int dfd                           const char *filename                  struct timespec *utimes              int flags
%define SYS_EPOLL_PWAIT            281  ; int epfd                          struct epoll_event *events            int maxevents                        int timeout                    const sigset_t *sigmask              size_t sigsetsize
%define SYS_SIGNALFD               282  ; int ufd                           sigset_t *user_mask                   size_t sizemask
%define SYS_TIMERFD_CREATE         283  ; int clockid                       int flags
%define SYS_EVENTFD                284  ; unsigned int count
%define SYS_FALLOCATE              285  ; long fd                           long mode                             loff_t offset                        loff_t len
%define SYS_TIMERFD_SETTIME        286  ; int ufd                           int flags                             const struct itimerspec *utmr        struct itimerspec *otmr
%define SYS_TIMERFD_GETTIME        287  ; int ufd                           struct itimerspec *otmr
%define SYS_ACCEPT4                288  ; int fd                            struct sockaddr *upeer_sockaddr       int *upeer_addrlen                   int flags
%define SYS_SIGNALFD4              289  ; int ufd                           sigset_t *user_mask                   size_t sizemask                      int flags
%define SYS_EVENTFD2               290  ; unsigned int count                int flags
%define SYS_EPOLL_CREATE1          291  ; int flags
%define SYS_DUP3                   292  ; unsigned int oldfd                unsigned int newfd                    int flags
%define SYS_PIPE2                  293  ; int *filedes                      int flags
%define SYS_INOTIFY_INIT1          294  ; int flags
%define SYS_PREADV                 295  ; unsigned long fd                  const struct iovec *vec               unsigned long vlen                   unsigned long pos_l            unsigned long pos_h
%define SYS_PWRITEV                296  ; unsigned long fd                  const struct iovec *vec               unsigned long vlen                   unsigned long pos_l            unsigned long pos_h
%define SYS_RT_TGSIGQUEUEINFO      297  ; pid_t tgid                        pid_t pid                             int sig                              siginfo_t *uinfo
%define SYS_PERF_EVENT_OPEN        298  ; struct perf_event_attr *attr_uptr pid_t pid                             int cpu                              int group_fd                   unsigned long flags
%define SYS_RECVMMSG               299  ; int fd                            struct msghdr *mmsg                   unsigned int vlen                    unsigned int flags             struct timespec *timeout
%define SYS_FANOTIFY_INIT          300  ; unsigned int flags                unsigned int event_f_flags
%define SYS_FANOTIFY_MARK          301  ; long fanotify_fd                  long flags                            __u64 mask                           long dfd                       long pathname
%define SYS_PRLIMIT64              302  ; pid_t pid                         unsigned int resource                 const struct rlimit64 *new_rlim      struct rlimit64 *old_rlim
%define SYS_NAME_TO_HANDLE_AT      303  ; int dfd                           const char *name                      struct file_handle *handle           int *mnt_id                    int flag
%define SYS_OPEN_BY_HANDLE_AT      304  ; int dfd                           const char *name                      struct file_handle *handle           int *mnt_id                    int flags
%define SYS_CLOCK_ADJTIME          305  ; clockid_t which_clock             struct timex *tx
%define SYS_SYNCFS                 306  ; int fd
%define SYS_SENDMMSG               307  ; int fd                            struct mmsghdr *mmsg                  unsigned int vlen                    unsigned int flags
%define SYS_SETNS                  308  ; int fd                            int nstype
%define SYS_GETCPU                 309  ; unsigned *cpup                    unsigned *nodep                       struct getcpu_cache *unused
%define SYS_PROCESS_VM_READV       310  ; pid_t pid                         const struct iovec *lvec              unsigned long liovcnt                const struct iovec *rvec       unsigned long riovcnt                unsigned long flags
%define SYS_PROCESS_VM_WRITEV      311  ; pid_t pid                         const struct iovec *lvec              unsigned long liovcnt                const struct iovcc *rvec       unsigned long riovcnt                unsigned long flags

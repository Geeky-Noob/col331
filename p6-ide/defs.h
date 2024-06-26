struct buf;
struct rtcdate;

// bio.c
void            binit(void);
struct buf*     bread(uint, uint);
void            bwrite(struct buf*);
void            brelse(struct buf *b);

// console.c
void            cprintf(char*, ...);
void            halt(void) __attribute__((noreturn));
void            panic(char*) __attribute__((noreturn));
void            consoleintr(int(*)(void));
void            consputc(int);

// ide.c
void            ideinit(void);
void            ideintr(void);
void            iderw(struct buf*);

// ioapic.c
void            ioapicenable(int irq, int cpu);
extern uchar    ioapicid;
void            ioapicinit(void);

// lapic.c
void            cmostime(struct rtcdate *r);
int             lapicid(void);
extern volatile uint*    lapic;
void            lapiceoi(void);
void            lapicinit(void);
void            lapicstartap(uchar, uint);
void            microdelay(int);

// mp.c
extern int      ismp;
void            mpinit(void);

// picirq.c
void            picenable(int);
void            picinit(void);

// proc.c
int             cpuid(void);
struct cpu*     mycpu(void);

// spinlock.c
void            getcallerpcs(void*, uint*);

// string.c
int             memcmp(const void*, const void*, uint);
void*           memmove(void*, const void*, uint);
void*           memset(void*, int, uint);
char*           safestrcpy(char*, const char*, int);
int             strlen(const char*);
int             strncmp(const char*, const char*, uint);
char*           strncpy(char*, const char*, int);

// trap.c
void            idtinit(void);
extern uint     ticks;
void            tvinit(void);

// uart.c
void            uartinit(void);
void            uartintr(void);
void            uartputc(int);

// number of elements in fixed-size array
#define NELEM(x) (sizeof(x)/sizeof((x)[0]))

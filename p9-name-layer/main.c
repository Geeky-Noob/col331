#include "types.h"
#include "defs.h"
#include "x86.h"
#include "fs.h"
#include "buf.h"
#include "param.h"
#include "stat.h"

extern char end[]; // first address after kernel loaded from ELF file

static inline void
welcome(void) {
  struct inode* wtxt = namei("/welcome.txt");
  iread(wtxt);
  struct stat st;
  stati(wtxt, &st);
  cprintf("\nwelcome.txt stats: Device %d, inode number %d, type %d, number of links %d, size %d\n", 
  st.dev, st.ino, st.type, st.nlink, st.size);

  char greet[512];
  int n = readi(wtxt, greet, 0, st.size);
  cprintf("Read %d bytes from welcome.txt\n", n);
  cprintf("%s\n", greet);
}

// Bootstrap processor starts running C code here.
// Allocate a real stack and switch to it, first
// doing some setup required for memory allocator to work.
int
main(void)
{
  mpinit();        // detect other processors
  lapicinit();     // interrupt controller
  picinit();       // disable pic
  ioapicinit();    // another interrupt controller
  uartinit();      // serial port
  ideinit();       // disk 
  tvinit();        // trap vectors
  binit();         // buffer cache
  idtinit();       // load idt register
  sti();           // enable interrupts
  iinit(ROOTDEV);  // Read superblock to start reading inodes
  welcome();       // print welcome message
  for(;;)
    wfi();
}

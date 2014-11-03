#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define LTKB_IOC_HEADER 'b'

#define LTKB_IOC_RESET _IO(LTKB_IOC_HEADER, 0)
#define LTKB_IOC_PING  _IOWR(LTKB_IOC_HEADER, 1, char)

#define LTKB_IOC_MAXNR 1


int main(void)
{
  int fd;

  if ((fd=open("ltkb0", O_RDWR|O_SYNC))<0)
  {
      perror("open");
      exit(-1);
  }

  char buffer[200] = "hello";
  write(fd, (void *)&buffer, 6);

  char c = 'a';
  printf("%c ",c);
  ioctl(fd, LTKB_IOC_PING, &c);
  printf("%c ",c);
  ioctl(fd, LTKB_IOC_PING, &c);
  printf("%c\n",c);
  close(fd);
  return(0);
}


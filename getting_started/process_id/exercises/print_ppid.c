#include <stdio.h>
#include <unistd.h>

/**
 * Get parent pid
 */

int main()
{
  pid_t my_pid;

  my_pid = getppid();
  printf("Process id: %u\n", my_pid);
  return (0);
}

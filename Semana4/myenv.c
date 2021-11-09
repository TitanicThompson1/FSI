#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main()
{
  char *argv[2];
  argv[0] = "/usr/bin/env";
  argv[1] = NULL;

  if (execve("/usr/bin/env", argv, environ) != 0) {
    perror("shell code error");
  }
  return 0;
}
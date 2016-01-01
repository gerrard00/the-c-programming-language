#include <stdio.h>
#include <unistd.h>

int main() 
{
  while(1) {
    printf("%d-", getpid());
    fflush(stdout);
    sleep(1);
  }
}

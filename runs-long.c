#include <stdio.h>
#include <unistd.h>

// stupid comments for testing strip-comments
// our main function
int main() 
{
  while(1) {
    printf("%d-", getpid());
    fflush(stdout);
    // this is what slows it down
    sleep(1);
  }
}

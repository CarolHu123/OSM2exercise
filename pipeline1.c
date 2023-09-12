#include <stdio.h>    // puts(), printf(), perror(), getchar()
#include <stdlib.h>   // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // getpid(), getppid(),fork()
#include <sys/wait.h> // wait()

#define READ  0
#define WRITE 1

void child_a(int fd[]) {

  // TODO: Add code here.
  close(fd[0]);
  dup2(fd[1],1); 
  close(fd[1]);

  execlp("/bin/ls","ls","-F","-1",NULL);
  perror("execlp failed");
  exit(EXIT_FAILURE);

}

void child_b(int fd[]) {

  // TODO: Add code here.
  close(fd[1]);
  dup2(fd[0],0);
  close(fd[0]);

  execlp("nl","nl",NULL);
  perror("execlp failed");
  exit(EXIT_FAILURE);
  

}

int main(void) {
  int fd[2];
  int status1,status2;
// TODO: Add code here.
  if(pipe(fd) == -1){
    printf("pipe open failed\n");
    return 1;
  }

pid_t child1,child2;

child1 = fork();

if(child1 == 0){
  child_a(fd);
  exit(EXIT_SUCCESS);
}else
{
  child2 = fork();
  if(child2 == 0){
  child_b(fd);
  exit(EXIT_SUCCESS);
  
}


}

close(fd[1]);
close(fd[0]);
wait(&status1);
wait(&status2);

return 0;
}

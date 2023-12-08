#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
	pid_t pid;

	printf("Before fork\n");

	pid = fork();

	if (pid == -1) {
		perror("Error in fork");
		return (1);
	}

    if (pid > 0){
		printf("Parent process. PID: %d\n", getpid());
	} else
   	{
	    
		printf("Child process. PID: %d\n", getpid());
	}

	printf("After fork\n");

	return 0;
}

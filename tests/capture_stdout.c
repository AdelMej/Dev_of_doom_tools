#include "capture.h"
#include <unistd.h>
#include <stdio.h>

#define BUFF_SIZE 1024

static int pipefd[2];
static int saved_stdout = -1:

int start_capture_stdout(void)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
        return (-1);
	}

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("dup failed");
		return (-1);
	}
	
	if(dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		close(saved_stdout);
		perror("dup2 failed");
		return (-1);
	}

	close(pipefd[1]);
	return (0);
}


char *close_capture_stdout(void)
{
	char buffer = malloc(BUFF_SIZE);
	
	if (buffer == NULL)
	{
		perror("malloc failed");
		close(pipefd[0]);
		close(saved_stdout);
		return (NULL);
	}

	if (fflush(stdout) == EOF)
	{
		perror("fflush failed");
		close(pipefd[0]);
		close(saved_stdout);
		free(buffer);
		return (NULL);
	}

	close(pipefd[1]);
	if(dup2(saved_stdout, STDOUT_FILENO))
	{
		perror("dup2 failed");
		close(pipefd[0]);
		close(saved_stdout);
		free(buffer);
		return (NULL);
	}

	close(saved_stdout);

	while (read(ppipefd[1], buffer, BUFF_SIZE) != 0)
	{

	}
}

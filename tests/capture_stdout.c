#include "capture.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int pipefd[2];
static int saved_stdout = -1;

/**
 * start_capture_stdout - Starts capturing stdout output by redirecting it.
 *
 * This function creates a pipe, saves the current stdout file descriptor,
 * and redirects stdout to the write end of the pipe. The original stdout
 * is saved to be restored later.
 *
 * Return: 0 on success, -1 on failure with perror output.
 */
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
		pipefd[0] = -1;
		close(pipefd[1]);
		pipefd[1] = -1;
		perror("dup failed");
		return (-1);
	}
	
	if(dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[0]);
		pipefd[0] = -1;
		close(pipefd[1]);
		pipefd[1] = -1;
		close(saved_stdout);
		saved_stdout = -1;
		perror("dup2 failed");
		return (-1);
	}

	close(pipefd[1]);
	pipefd[1] = -1;
	return (0);
}

/**
 * close_capture_stdout - Closes pipe and saved stdout, captures output.
 *
 * This function reads all data from the pipe, restores the saved stdout
 * file descriptor, and returns the captured output as a dynamically
 * allocated null-terminated string.
 *
 * Return: Pointer to the captured output string on success,
 *         NULL on failure.
 */
char *close_capture_stdout(void)
{
	char *buffer = malloc(BUFF_SIZE);
	char *output, *tmp;
	ssize_t bytes_read = -1;
	size_t total_bytes_written = 0;

	if (buffer == NULL)
	{
		perror("malloc failed");
		close(pipefd[0]);
		pipefd[0] = -1;
		close(saved_stdout);
		saved_stdout = -1;
		return (NULL);
	}

	output = malloc(1);
	if (output == NULL)
	{
		perror("malloc failed");
		close(pipefd[0]);
		pipefd[0] = -1;
		close(saved_stdout);
		saved_stdout = -1;
		free(buffer);
		return (NULL);
	}

	output[0] = '\0';
	if (fflush(stdout) == EOF)
	{
		perror("fflush failed");
		close(pipefd[0]);
		pipefd[0] = -1;
		close(saved_stdout);
		saved_stdout = -1;
		free(buffer);
		free(output);
		return (NULL);
	}

	if(dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		close(pipefd[0]);
		pipefd[0] = -1;
		close(saved_stdout);
		saved_stdout = -1;
		free(buffer);
		free(output);
		return (NULL);
	}

	close(saved_stdout);
	saved_stdout = -1;
	while ((bytes_read = read(pipefd[0], buffer, BUFF_SIZE)) > 0)
	{
		total_bytes_written += bytes_read;
		tmp = realloc(output, total_bytes_written +1);
		if (tmp == NULL)
		{
			close(pipefd[0]);
			pipefd[0] = -1;
			free(buffer);
			free(output);
			perror("malloc failed");
			return (NULL);
		}
		output = tmp;
		memcpy(output + total_bytes_written - bytes_read, buffer,bytes_read);
	}

	if (bytes_read == -1)
	{
		close(pipefd[0]);
		pipefd[0] = -1;
		free(buffer);
		free(output);
		perror("read failed");
		return (NULL);
	}
	output[total_bytes_written] = '\0';

	close(pipefd[0]);
	pipefd[0] = -1;
	free(buffer);
	return (output);
}

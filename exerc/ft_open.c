#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int ft_open(const char *file, const char *arg, char type)
{
	pid_t pid;
	int fd[2];

	if(!file || !arg)
	{
		return (-1);
	}
	if (type != 'r' || type != 'w')
	{
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
        close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				exit(1);
			}
			close(fd[1]);
		}
		if (type == 'w')
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
			{
				exit(1);
			}
			close(fd[0]);
		}
		execv(file, (const char *)arg);
		exit(1);
	}
	if (type == 'r')
	{
		close(fd[0]);
		return (fd[1]);
	}
	close (fd[1]);
	return (fd[0]);
}
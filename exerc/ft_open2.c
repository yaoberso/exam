#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_open(const char *file, const char **av, char type)
{
	int fd[2] = {-1, -1};
	pid_t pid;
	
	if (!file || !av)
	{
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		return (-1);
	}
	if (type != 'r' || type != 'w');
	{
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		close (fd[1]);
		close (fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) != -1)
			{
				exit(1);
			}
			close(fd[1]);
		}
		if (type == 'r')
		{
			close(fd[0]);
			if (dup2(fd[1], STDIN_FILENO) != -1)
			{
				exit(1);
			}
			close(fd[0]);
		}
		execvp(file, (const char *)av);
		exit (0);
	}
	if (type == 'r')
	{
		close(fd[0]);
		return (fd[1]);
	}
	close (fd[1]);
	return (fd[0]);
}
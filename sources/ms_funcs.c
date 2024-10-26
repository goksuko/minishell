#include "../includes/minishell.h"

void	ms_dup2(t_data *data, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		ft_exit_perror(data, ERROR_DUP2);
	return ;
}

void    ms_close(t_data *data, int fd)
{
	if (close(fd) < 0)
		ft_exit_perror(data, ERROR_CLOSE);
	return ;
}

int    ms_open(t_data *data, char *file, int flags, int mode)
{
	int fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
		"token->next->value");
		data->exit_code = ERROR_NO_FILE_DIR;
		free_system(data);
		return (-1);
	}
	return (fd);
}

void    ms_pipe(t_data *data, int *pipefd)
{
	if (pipe(pipefd) < 0)
		ft_exit_perror(data, ERROR_PIPE);
	return ;
}

int    ms_fork(t_data *data)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		ft_exit_perror(data, ERROR_FORK);
	return (pid);
}

void    ms_unlink(t_data *data, char *file)
{
	if (!data->info->limiter)
		return ;	
	if (unlink(file) < 0)
		ft_exit_perror(data, ERROR_UNLINK);
	return ;
}

void	**ms_calloc(t_data *data, size_t nmemb, size_t size)
{
	void **ptr;

	ptr = ft_calloc(nmemb, size);
	if (ptr == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (ptr);
}

char	*ms_strjoin(t_data *data, const char *s1, const char *s2)
{
	char *str;

	str = ft_strjoin(s1, s2);
	if (str == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (str);
}

char	*ms_strdup(t_data *data, const char *s)
{
	char *str;

	str = ft_strdup(s);
	if (str == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (str);
}

char	**ms_split(t_data *data, char const *s, char c)
{
	char **array;

	array = ft_split(s, c);
	if (array == NULL || errno == ENOMEM)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (array);
}
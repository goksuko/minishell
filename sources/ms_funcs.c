#include "../includes/minishell.h"

void    ms_dup2(t_data *data, int old_fd, int new_fd)
{
    if (dup2(old_fd, new_fd) < 0)
        ft_exit_data_perror(data, ERROR_DUP2, ft_print_error(ERROR_DUP2));
    return ;
}

void    ms_close(t_data *data, int fd)
{
    if (close(fd) < 0)
        ft_exit_data_perror(data, ERROR_CLOSE, ft_print_error(ERROR_CLOSE));
    return ;
}

void    ms_open(t_data *data, char *file, int flags, int mode)
{
    int fd;

    fd = open(file, flags, mode);
    if (fd < 0)
        ft_exit_data_perror(data, ERROR_FILE_OPEN, ft_print_error(ERROR_FILE_OPEN));
    return ;
}

void    ms_pipe(t_data *data, int *pipefd)
{
    if (pipe(pipefd) < 0)
        ft_exit_data_perror(data, ERROR_PIPE, ft_print_error(ERROR_PIPE));
    return ;
}

void    ms_fork(t_data *data)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        ft_exit_data_perror(data, ERROR_FORK, ft_print_error(ERROR_FORK));
    return ;
}

void    ms_unlink(t_data *data, char *file)
{
    if (unlink(file) < 0)
        ft_exit_data_perror(data, ERROR_UNLINK, ft_print_error(ERROR_UNLINK));
    return ;
}
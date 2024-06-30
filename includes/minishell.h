/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/29 21:30:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/01 00:13:15 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include "../Libft/includes/libft.h"
# include "../Libft/ft_utils/includes/ft_utils.h"
# include "../Libft/ft_printf_fd/includes/ft_printf_fd.h"

typedef enum e_error {
	NO_ERROR,
	ERROR_PERM = 1,
	ERROR_ARGUMENT_COUNT,
	ERROR_INVALID_ARGUMENTS,
	ERROR_ALLOCATION,
	ERROR_FILE_OPEN,
	ERROR_NULL_PATH,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_CLOSE,
	ERROR_DUP2,
	ERROR_EXECVE,
	UNDEFINED_ERROR,
	ERROR_NOT_DIR = 127,
}	t_error;

typedef struct s_pipex
{
	int		pipefd[2];
	int		fd_in;
	int		fd_out;
	int		nbr_of_cmds;
	int		curr_cmd;
}	t_pipex;


// errors.c

int	ft_print_error(t_error code);
void	ft_exit_perror(t_error code, char *s);
void	ft_exit_str_fd(t_error code, int fd);
void	ft_close_exit_perror(t_pipex *info, char **matrix, t_error code, char *s);

// Libft functions //

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_calloc(size_t nmemb, size_t size);

// Utils functions //
char	*put_main_command(char *command, char space);
void	start_exec(t_pipex *info, char **argv, char **envp);
void	*free_matrix(char **matrix);
void	close_pipex(t_pipex *info, char **matrix);

// Path functions //
char	*find_path(char *cmd, char **envp);
int		find_path_index(char **envp);
int		command_not_found(char *argv[]);

// Ft_putstr2_fd functions //
void	ft_putstr2_fd(char *s1, char *s2, int fd);
void	ft_putstr3_fd(char *s1, char *s2, char *s3, int fd);

// utils2.c

int	close_safe(int fd, t_pipex *info);
int	dup2_safe(int oldfd, int newfd, t_pipex *info);

#endif

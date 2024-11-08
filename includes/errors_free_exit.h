/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors_free_exit.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 14:41:19 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/04 14:41:19 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_error
{
	NO_ERROR,
	ERROR_PERM = 1,
	ERROR_ARGUMENT_COUNT,
	ERROR_NO_ENVP,
	ERROR_TOO_MANY_ARGS,
	ERROR_NUMERIC_ARG,
	ERROR_INVALID_ARGUMENTS,
	ERROR_ALLOCATION,
	ERROR_FILE_OPEN,
	ERROR_NULL_PATH,
	ERROR_CMD_NOT_FOUND,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_CLOSE,
	ERROR_DUP2,
	ERROR_UNLINK,
	ERROR_EXECVE,
	ERROR_HOME_DIR,
	ERROR_PARENT_DIR,
	ERROR_OLDPWD,
	ERROR_NO_FILE_DIR,
	ERROR_QUOTE,
	ERROR_WRONG_CHAR,
	ERROR_FILE_NOT_FOUND,
	ERROR_META,
	ERROR_SYNTAX,
	ERROR_EMPTY_LINE,
	UNDEFINED_ERROR,
	ERROR_INVALID_IDENTIFIER,
	ERROR_NOT_DIR = 127,
}					t_error;

char	*ft_error(t_error code);
void	ft_system_error(t_data *data, t_error code);
void	free_info(t_info *info);
void	free_env(t_env **env_var);
int		error_assign(t_data *data, t_error code);

// Freeing
void	free_and_null(char **ptr);
void	free_2d_null(char ***ptr);
void	free_matrix(char **matrix);
void	free_system(t_data *data);
void	free_data(t_data **data);

// Error messages
void	ft_exit_str_free_fd(t_error code, char *str, int fd);
void	ft_exit_str_fd(t_error code, int fd);
int		ft_print_error(t_error code);
void	ft_putstr3_fd(char *s1, char *s2, char *s3, int fd);
void	ft_putstr2_fd(char *s1, char *s2, int fd);

// Exiting system or program
void	free_system_error(t_data *data, t_error code);
void	free_system_perror(t_data *data, t_error code, char *s);
void	ft_exit_perror(t_data *data, t_error code);
void	ft_exit_data_error(t_data *data, t_error code);
void	ft_exit_data_perror(t_data *data, t_error code, char *s);
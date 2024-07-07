/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/07 00:26:53 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*line_read = (char *)NULL;

int	check_pipe(char *line)
{
	int	i;
	int	count;

	ft_printf("check_pipe\n");
	i = 0;
	count = 0;
	while (line && line[i])
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

int	find_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}


void	check_characters(char *line)
{
	int	i;
	int	count;
	int	wrong_char;

	ft_printf("check_characters\n");
	count = 0;
	i = 0;
	wrong_char = 0;
	while (line && line[i])
	{
		if (line[i] == '"')
			count++;
		if (line[i] == '\\' || line[i] == ';')
			wrong_char++;
		i++;
	}
	if (count % 2 != 0)
		ft_exit_str_free_fd((ERROR_QUOTE), line, STDERR_FILENO);
	if (wrong_char)
		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
	return ;
}

// int check_args(char *line, char **envp)
// {
// 	int		exit_code;

// 	exit_code = 0;
// 	ft_printf("check_args\n");
// 	exit_code = check_characters(line);
// 	if (exit_code)
// 		return (ft_print_error(exit_code));
// 	if (check_pipe(line))
// 		return (pipex(line, envp));
// 	return (exit_code);
// }

void	init_data(t_data *data, char *line, char **envp)
{
	ft_printf("init_data\n");
	data->line = line;
	data->envp = envp;
	data->exit_code = 0;
	return ;
}

char	*rl_gets(void)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("\033[36mminishell of \U0001F9B8 \033[35mGoksu\033[36m & \U0001F9DA \033[33mVanessa\033[36m > \033[0m");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	make_initial_path_checks(char **envp)
{
	int	path_no;

	ft_printf("make_initial_path_checks\n");
	path_no = find_path_index(envp);
	printf("path_no: %d\n", path_no);
	if (envp[path_no] == NULL)
	{
		ft_print_error(ERROR_NULL_PATH);
		exit(ERROR_NULL_PATH);
	}
	if (path_no == 0)
	{
		ft_print_error(ERROR_CMD_NOT_FOUND);
		exit(ERROR_CMD_NOT_FOUND);
	}
	ft_printf("path_no: %d\n", path_no);
	ft_printf("envp[path_no]: %s\n", envp[path_no]);
	return ;
}

int	main(int argc, char **envp)
{
	char	*line;
	t_data	*data;

	if (argc != 1)
		return (ft_print_error(ERROR_ARGUMENT_COUNT));
	// make_initial_path_checks(envp);
	line = NULL;
	while ((line = rl_gets()))
	{
		check_characters(line);
		data = (t_data *)ft_calloc(1, sizeof(t_data));
		if (data == NULL || errno == ENOMEM)
		{
			free(line);
			ft_exit_perror(ERROR_ALLOCATION, "data in main");
		}
		init_data(data, line, envp);
		if (check_pipe(line))
			data->exit_code = pipex(data);
		free_system(data);
	}
	return (data->exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/04 15:07:02 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static char	*line_read = (char *)NULL; NOT SURE IF ACTUALLY NEEDED!We should only have one global variable in the whole project that is used for the signal handling

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

// void	make_initial_path_checks(char **envp)
// {
// 	int	path_no;

// 	ft_printf("make_initial_path_checks\n");
// 	path_no = find_path_index(envp);
// 	printf("path_no: %d\n", path_no);
// 	if (envp[path_no] == NULL)
// 	{
// 		ft_print_error(ERROR_NULL_PATH);
// 		exit(ERROR_NULL_PATH);
// 	}
// 	if (path_no == 0)
// 	{
// 		ft_print_error(ERROR_CMD_NOT_FOUND);
// 		exit(ERROR_CMD_NOT_FOUND);
// 	}
// 	ft_printf("path_no: %d\n", path_no);
// 	ft_printf("envp[path_no]: %s\n", envp[path_no]);
// 	return ;
// }

void	initial_path_checks(char **array) //useless function only written to overcome error in main as envp was not used. still need to write proper path check
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

int	main(int argc, char **envp)
{
	char	*line;
	t_token *token;
	t_tree	*ast;

	if (argc != 1)
		return (ft_print_error(ERROR_ARGUMENT_COUNT));
	// signal_handling();
	// make_initial_path_checks(envp); //LATER V
	initial_path_checks(envp);
	line = NULL;
	while (1)
	{
		if ((line = rl_gets()) == NULL)
			break;
		token = lexical_analysis(line);
		ft_print_tokens(token); // only for testing purposes
		ast = syntax_analysis(token);
		print_ast(ast); // only for testing purposes
		execute_shell(&ast); // includes builtins
		// if (check_pipe(line))
			// data->exit_code = pipex(data); // to be put in semantic analysis
		// 
		// free_system(data);
	}
	// return (data->exit_code);
}

// int main(int argc, char *argv[], char **envp)
// {
//     int i = 0;
// 	(void)argc;
// 	(void)argv;
//     while (envp[i] != NULL) {
//         printf("%s\n", envp[i]);
//         i++;
//     }
// 	return (0);

// }

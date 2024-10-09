/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/09 23:29:40 by akaya-oz      ########   odam.nl         */
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
		printf("envp[%d]: %s\n", i, envp[i]);
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

// void	init_data(t_data *data, char **envp)
// {
// 	ft_printf("init_data\n");
// 	// data->line = line;
// 	data->envp = envp;
// 	data->exit_code = 0;
// 	return ;
// }


void	make_initial_path_checks(char **envp, t_data *shell_data)
{
	t_env	*head;
	t_env	*node;
	int		i;
	
	// ft_printf("---make_initial_path_checks---\n");
	if (!envp && !(*envp))
		ft_printf("there is no envp\n"); // think of memory management
	i = 1;
	head = ft_envp_node(envp[0]);
	shell_data->env_list = head;
	node = head;
	while (envp[i])
	{
		node->next = ft_envp_node(envp[i]);
		if (!node->next) 
		{
			free_prev_nodes(head); // rewrite memory stuff
		}
		node = node->next;
		i++;
	}
	shell_data->env_list = head;
	update_path(shell_data);
	update_shell(&shell_data->env_list);
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	
	char	*line;
	t_data	*shell_data;

	(void)argv;
	if (argc != 1)
		return (ft_print_error(ERROR_ARGUMENT_COUNT));
	shell_data = ft_calloc(sizeof(t_data), 1);
	if (errno == ENOMEM || shell_data == NULL)
		ft_exit_perror(1, "shell_data in main");
	make_initial_path_checks(envp, shell_data);
	shell_data->envp = envp;
	line = NULL;
	while (1)
	{
		// set_signals_interactive();
		if ((line = rl_gets()) == NULL)
			break;
		// set_signals_noninteractive();
		// if (line == shell_data->info->limiter)
		// 	break;
		shell_data->line = line;
		shell_data->tokens = lexical_analysis(shell_data, line);
		expander(&shell_data);
		ft_print_tokens(shell_data->tokens); // only for testing purposes	
		semantic_analysis(shell_data);
		printf_array(shell_data->info->cmds); // only for testing purposes
		char **command = ft_split(shell_data->info->cmds[0], ' '); // only for testing purposes
		printf_array(command); // only for testing purposes
		printf("is_builtin: %d\n", is_builtin(command[0])); // only for testing purposes
		if (is_builtin(command[0])) // only for testing purposes
			shell_data->exit_code = execute_builtin(command, shell_data); // only for testing purposes
		execute_shell(shell_data); // includes builtins
		// if (check_pipe(line))
		// 	data->exit_code = pipex(data); // to be put in semantic analysis
		
		// free_system(data);
		output_signal_keys();
	}

	// return (data->exit_code);
}
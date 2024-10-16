/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/16 21:40:37 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_initial_path_checks(char **envp, t_data *data)
{
	t_env	*head;
	t_env	*node;
	int		i;
	
	if (!envp && !(*envp))
		ft_exit_data_error(data, ERROR_NO_ENVP);
	i = 1;
	head = ft_envp_node(envp[0]);
	data->env_list = head;
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
	data->env_list = head;
	update_path(data);
	update_shell(&data->env_list);
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	
	char	*line;
	t_data	*data;

	(void)argv;
	if (argc != 1)
		return (ft_print_error(ERROR_ARGUMENT_COUNT));
	data = ft_calloc(sizeof(t_data), 1);
	if (errno == ENOMEM || data == NULL)
		ft_exit_perror(ERROR_ALLOCATION, "data in main");
	make_initial_path_checks(envp, data);
	data->envp = envp;
	line = NULL;
	while (1)
	{
		handle_signals(PARENT);
		if ((line = rl_gets()) == NULL)
			break;
		// if (line == data->info->limiter)
		// 	break;
		// data->line = line;
		data->tokens = lexical_analysis(data, line);
		// ft_print_tokens(data->tokens); // only for testing purposes	
		expander(&data);
		semantic_analysis(data);
		// printf_array(data->info->cmds); // only for testing purposes
		// char **command = ft_split(data->info->cmds[0], ' '); // only for testing purposes
		// // printf_array(command); // only for testing purposes
		// printf("is_builtin: %d\n", is_builtin(command[0])); // only for testing purposes
		// if (is_builtin(command[0])) // only for testing purposes
		// 	data->exit_code = execute_builtin(command, data); // only for testing purposes
		// printf("cmds before execute_shell: \n");
		// printf_array(data->info->cmds);
		execute_shell(data); // includes builtins
	
		// free_system(data);
	}

	return (data->exit_code);
}
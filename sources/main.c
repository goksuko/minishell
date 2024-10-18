/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/18 10:20:29 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_initial_path_checks(char **envp, t_data *data)
{
	t_env	*head;
	t_env	*node;
	int		i;
	
	// printf_array(envp);
	if (!envp && !(*envp))
		ft_exit_data_error(data, ERROR_NO_ENVP);
	i = 1;
	head = ft_envp_node(data, envp[0]);
	data->env_list = head;
	node = head;
	while (envp[i])
	{
		node->next = ft_envp_node(data, envp[i]);
		if (!node->next) 
		{
			free_prev_nodes(head); // rewrite memory stuff
		}
		node = node->next;
		i++;
	}
	data->env_list = head;
	// data->envp = NULL;
	update_path(data);
	update_shell(data, &data->env_list);
	return ;
}

bool minishell_routine(t_data *data, char *line)
{
	handle_signals(PARENT);
	if ((line = rl_gets()) == NULL)
		return (false);
	data->tokens = lexical_analysis(data, line);
	expander(&data);
	semantic_analysis(data);
	execute_shell(data);
	return (true);
}

void init_data(t_data *data)
{
	data->cmds = NULL;
	data->line = NULL;
	data->path = NULL;
	data->exit_code = 0;
	data->expanded_cmds = NULL;
	data->info = NULL;
	data->env_list = NULL;
	data->tokens = NULL;
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	
	char	*line;
	
	t_data	*data;

	(void)argv;
	if (argc != 1)
	{
		ft_printf_fd(STDERR_FILENO, "%s\n", ft_print_error(ERROR_ARGUMENT_COUNT));
		return (ERROR_ARGUMENT_COUNT);
	}
	data = ft_calloc(sizeof(t_data), 1);
	if (errno == ENOMEM || data == NULL)
		ft_exit_perror(ERROR_ALLOCATION, "data in main");
	data->envp = envp;
	init_data(data);
	make_initial_path_checks(envp, data);
	line = NULL;
	while (1)
	{
		if (minishell_routine(data, line) == false)
			break;
	}
	return (data->exit_code);
}
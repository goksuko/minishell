/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/26 23:26:18 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rl_gets(void)
{
	char	*line_read;

	line_read = readline(">[minishell]: ");
	if (line_read == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (line_is_empty(line_read) == true)
	{
		free(line_read);
		return (ft_strdup(" "));
	}
	if (line_is_whitespace(line_read) == true)
	{
		add_history(line_read);
		free(line_read);
		return (ft_strdup(" "));
	}
	if (line_read != NULL && *line_read != '\0')
		add_history(line_read);
	return (line_read);
}

void	make_initial_path_checks(t_data *data, char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

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
			free_prev_nodes(head);
		node = node->next;
		i++;
	}
	data->env_list = head;
	update_path(data);
	update_shell(data, &data->env_list);
	return ;
}

bool	minishell_routine(t_data *data, char *line)
{
	if ((line = rl_gets()) == NULL)
		return (false);
	data->tokens = lexical_analysis(data, line);
	if (data->tokens == NULL)
		return (true);
	expander(&data);
	printf("expander done\n");
	if (semantic_analysis(data) == false)
		return (false);
	printf("\n**********Result*********\n\n");
	if (execute_shell(data) == false)
		return (false);
	ms_unlink(data, "0ur_h3r3_d0c");
	printf("\n**********Exit code: %d***\n", data->exit_code);
	return (true);
}

void	init_data(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	data->envp = envp;
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_data	*data;

	(void)argv;
	if (argc != 1)
		return (ft_printf_fd(STDERR_FILENO, "%s\n",
				ft_print_error(ERROR_ARGUMENT_COUNT)));
	data = ft_calloc(sizeof(t_data), 1);
	if (!data || errno == ENOMEM)
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	init_data(data, envp);
	make_initial_path_checks(data, envp);
	line = NULL;
	while (1)
	{
		printf("inside while loop\n");
		// handle_signals(PARENT); // recheck position 
		set_signals(data);
		minishell_routine(data, line);
		free_system(data);
	}
	return (data->exit_code);
}
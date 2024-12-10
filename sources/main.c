/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/12/10 12:48:43 by akaya-oz      ########   odam.nl         */
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
		return (ft_strdup("  "));
	}
	if (line_is_whitespace(line_read) == true)
	{
		add_history(line_read);
		free(line_read);
		return (ft_strdup("  "));
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

	printf("make_initial_path_checks\n");
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	// printf("cwd: %s\n", data->cd_data->cwd);
	if (!envp && !(*envp))
		ft_exit_data_error(data, ERROR_NO_ENVP);
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	// printf("cwd: %s\n", data->cd_data->cwd);
	i = 1;
	printf("|%s|\n", envp[0]);
	head = ft_envp_node(data, envp[0]);
	data->env_list = head;
	node = head;
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	printf("cwd: %s\n", data->cd_data->cwd);
	while (envp[i])
	{
		node->next = ft_envp_node(data, envp[i]);
		if (!node->next)
			free_prev_nodes(head);
		node = node->next;
		i++;
	}
	data->env_list = head;
	// printf("loop done\n");
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	// printf("cwd: %s\n", data->cd_data->cwd);
	update_path(data);
	// printf("path updated\n");
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	// printf("cwd: %s\n", data->cd_data->cwd);
	update_shell(data, &data->env_list);
	// printf("shell updated\n");
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	// printf("cwd: %s\n", data->cd_data->cwd);
	data->cd_data->env_list = data->env_list;
	// printf("old_cwd: %s\n", data->cd_data->old_cwd);
	// printf("cwd: %s\n", data->cd_data->cwd);
	return ;
}

bool	minishell_routine(t_data *data)
{
	char		*line;

	line = rl_gets();
	if (line == NULL)
		return (false);
	if (ft_strncmp(line, "  ", 2) == 0)
		return (free_and_null(&line), true);
	data->tokens = lexical_analysis(data, line);
	if (data->tokens == NULL)
		return (free_and_null(&line), true);
	expander(&data);
	free_and_null(&line);
	// ft_print_tokens(data->tokens); //DEBUGGING PURPOSES!
	if (semantic_analysis(data) == false)
		return (false);
	// printf("\n**********Result*********\n\n");
	if (execute_shell(data) == false)
		return (false);
	ms_unlink(data, "0ur_h3r3_d0c");
	// printf("\n**********Exit code: %d***\n", data->exit_code);
	return (true);
}

void	init_cd_data(t_data	*data, t_cd_data *cd_data)
{
	char *wd;

	wd = getcwd(NULL, 0);
	cd_data->data = data;
	cd_data->cwd = ms_strdup(data, wd);
	cd_data->old_cwd = ms_strdup(data, wd);
	cd_data->env_list = NULL;
	// printf("init_cd_data\n");
	// printf("old_cwd: %s\n", cd_data->old_cwd);
	// printf("cwd: %s\n", cd_data->cwd);
	free_and_null(&wd);
	return ;
}

void	init_data(t_info *info, t_data *data, char **envp)
{
	t_cd_data	cd_data;
	
	ft_bzero(data, sizeof(t_data));
	ft_bzero(info, sizeof(t_info));
	ft_bzero(&cd_data, sizeof(t_cd_data));
	data->cmds = NULL;
	data->line = NULL;
	data->envp = envp;
	data->path = NULL;
	data->info = info;
	data->tokens = NULL;
	init_cd_data(data, &cd_data);
	data->cd_data = &cd_data;
	// printf("old_cwd: %s\n", cd_data.old_cwd);
	// printf("cwd: %s\n", cd_data.cwd);	
	return ;
}

int	main(int argc, char *argv[], char **envp)
{
	t_data		data;
	t_info		info;

	(void)argv;
	if (argc != 1)
		return (ft_printf_fd(STDERR_FILENO, "%s\n",
				ft_print_error(ERROR_ARGUMENT_COUNT)));
	init_data(&info, &data, envp);
	make_initial_path_checks(&data, envp);
	// printf("old_cwd: %s\n", data.cd_data->old_cwd);
	// printf("cwd: %s\n", data.cd_data->cwd);	
	printf("path: %s\n", data.path);
	while (1)
	{
		// handle_signals(PARENT); // recheck position
		set_signals(&data);
		// printf("old_cwd: %s\n", data.cd_data->old_cwd);
		// printf("cwd: %s\n", data.cd_data->cwd);	
		if(minishell_routine(&data) == false)
			close_fds(&data, &info); //why only in false? I have to think about it
		free_system(&data);
	}
	return (data.exit_code);
}

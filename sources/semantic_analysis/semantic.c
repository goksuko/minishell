#include "../../includes/minishell.h"

void	initialize_fds(t_pipex *info, t_data *shell_data)
{
	int		i;
	t_token	*current;

	printf("---initialize_fds---\n");
	i = 0;
	while (i < 100)
	{
		info->fds[i][0] = -10;
		info->fds[i][1] = -10;
		i++;
	}
	i = 0;
	current = shell_data->tokens;
	while (current)
	{
		// if (current->fd_in != -10)
		// 	printf("current->fd_in: %d\n", current->fd_in);
		// if (current->fd_out != -10)
		// 	printf("current->fd_out: %d\n", current->fd_out);
		if (current->fd_in != -10)
		{
			info->fds[i][0] = current->fd_in;
			info->infile = current->value;
		}
		if (current->fd_out != -10)
		{
			info->fds[i][1] = current->fd_out;
			info->outfile = current->value;
		}
		if (current->type == T_PIPE)
			i++;
		current = current->next;
	}
	// printf("info->fds[0][0]: %d\n", info->fds[0][0]);
	// printf("info->fds[0][1]: %d\n", info->fds[0][1]);
}

void	semantic_analysis(t_data *shell_data)
{
	t_pipex	*info;

	printf("---SEMANTIC ANALYSIS---\n");
	shell_data->exit_code = 0;
	shell_data->nbr_of_tokens = count_tokens(shell_data->line);
	shell_data->nbr_of_pipes = find_pipe_count(shell_data->tokens);
	printf("nbr_of_pipes: %d\n", shell_data->nbr_of_pipes);
	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (info == NULL || errno == ENOMEM)
		ft_exit_data_perror(shell_data, ERROR_ALLOCATION, "info in pipex");
	info->nbr_of_cmds = shell_data->nbr_of_pipes + 1;
	shell_data->info = info;
	// shell_data->cmds = shell_data->ast->argument;
	shell_data->here_doc = NULL;
	//here_doc should be done after pipe
	if (is_heredoc(shell_data->tokens))
	{
		do_heredoc(shell_data);
		shell_data->cmds = find_cmd_of_heredoc(shell_data->tokens);
		// finish_heredoc(shell_data);
	}
	else
		shell_data->cmds = cmds_from_tokens(shell_data);
	info->cmds = shell_data->cmds;
	initialize_info(info, shell_data);
	initialize_fds(info, shell_data);
}

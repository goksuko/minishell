#include "../../includes/minishell.h"

void semantic_analysis(t_data *shell_data)
{
	t_pipex *info;
	
	printf("---SEMANTIC ANALYSIS---\n");
	shell_data->exit_code = 0;
	shell_data->nbr_of_pipes = find_pipe_count(shell_data->line);
	// printf("nbr_of_pipes: %d\n", shell_data->nbr_of_pipes);
	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (info == NULL || errno == ENOMEM)
		ft_exit_data_perror(shell_data, ERROR_ALLOCATION, "info in pipex");
	shell_data->info = info;
	info->nbr_of_cmds = shell_data->nbr_of_pipes + 1;
	// shell_data->cmds = shell_data->ast->argument;
	shell_data->cmds = shell_data->expanded_cmds;
	info->cmds = shell_data->cmds;
	initialize_cmds(shell_data, info);
	initialize_info(info, shell_data);
}
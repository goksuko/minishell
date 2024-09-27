#include "../../includes/minishell.h"

int		find_pipe_count(t_token *tokens)
{
	int	pipe_count;
	t_token	*current;

	pipe_count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == T_PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count);
}

// char **clean_spaces(char **matrix)
// {
// 	int		i;

// 	i = 0;
// 	while (matrix[i] != NULL)
// 	{
// 		matrix[i] = ft_strtrim(matrix[i], " ");
// 		i++;
// 	}
// 	return (matrix);
// }

// void	initialize_cmds(t_data *data, t_pipex *info)
// {
// 	char	**cmds;

// 	ft_printf("---initialize_cmds---\n");
// 	cmds = ft_split(data->line, '|');
// 	cmds = clean_spaces(cmds);

// 	// cmds = clean_up_to_redir(cmds); //wromg place
// 	// printf_array(cmds);
// 	// cmds = data->ast->argument;
// 	// if (cmds)
// 	// 	printf_array(cmds);
// 	// else
// 	// 	printf("cmds is NULL\n");
// 	if (cmds == NULL || errno == ENOMEM)
// 		ft_exit_data_perror(data, ERROR_ALLOCATION, "cmds in initialize");
// 	// data->cmds = cmds;
// 	info->cmds = cmds;
// 	data->nbr_of_cmds = info->nbr_of_cmds;
	
// 	return ;
// }

void	initialize_info(t_pipex *info, t_data *data)
{
	ft_printf("\n---initialize_info---\n");
	info->path_from_getenv = getenv("PATH");
	if (info->path_from_getenv == NULL)
	{
		close_pipex(info, NULL);
		ft_exit_data_error(data, ERROR_NULL_PATH);
	}
	info->data = data;
	info->curr_cmd = 1;
	info->pipe_read_end = STDIN_FILENO;
	// info->special_command = NULL;
	// info->limiter = NULL; //defined in cmds between pipes
	// info->infile = NULL;
	// info->outfile = NULL;
	// info->fd_in = -10;
	// info->fd_out = -10;
	return ;
}
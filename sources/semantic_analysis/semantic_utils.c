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

void	initialize_info(t_info *info, t_data *data)
{
	ft_printf("\n---initialize_info---\n");
	info->path_from_getenv = getenv("PATH");
	if (errno == ENOMEM || info->path_from_getenv == NULL)
		ft_exit_data_perror(data, ERROR_NULL_PATH, "PATH in initialize_info");
	info->data = data;
	info->curr_cmd = 0;
	info->pipe_read_end = STDIN_FILENO;
	// info->cmds = data->cmds;
	// info->special_command = NULL;
	// info->limiter = NULL; //defined in cmds between pipes
	// info->infile = NULL;
	// info->outfile = NULL;
	// info->fd_in = -10;
	// info->fd_out = -10;
	return ;
}
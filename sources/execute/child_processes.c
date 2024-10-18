#include "../../includes/minishell.h"

void	do_commands(t_data *data, int i)
{
	if (data->info->curr_cmd == data->info->here_doc_cmd)
	{
		init_heredoc(data);
		data->info->fds[i][0] = open("0ur_h3r3_d0c", O_RDONLY, 0777);
		if (data->info->fds[i][0] == -1)
			ft_exit_data_perror(data, ERROR_FILE_OPEN, "0ur_h3r3_d0c");
	}
	data->info->fd_in = data->info->fds[i][0];
	data->info->fd_out = data->info->fds[i][1];
	if (i != data->nbr_of_cmds - 1)
	{
		if (pipe(data->info->pipefd) == -1)
			ft_exit_data_perror(data, ERROR_PIPE, "pipe in create children");
	}
	data->info->pipe_read_end = data->info->pipefd[0];
}

int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	handle_signals(CHILD); // TO BE CHECKED IF CORRECT POSITION 
	i = 0;
	data->info->pipe_read_end = STDIN_FILENO;
	data->info->here_doc_cmd = heredoc_position(data->tokens);
	while (i < data->nbr_of_cmds)
	{
		do_commands(data, i);
		pid = child_process(data->info);
		data->info->curr_cmd++;
		i++;
	}
	if (data->info->limiter)
		unlink("0ur_h3r3_d0c");
	waitpid(pid, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}

void	do_child_of_child(t_info *info)
{
	char	**command;

	command = NULL;
	if (info->curr_cmd == info->data->nbr_of_cmds - 1)
		do_last_child(info);
	else if (info->curr_cmd == 0)
		do_first_child(info);
	else
		do_middle_child(info);
	command = ft_split(info->data->cmds[info->curr_cmd], ' ');
	if (is_builtin(command[0]))
		info->data->exit_code = execute_builtin(command, info->data);
	else
		start_exec(info);
}

void	do_parent_of_child(t_info *info)
{
	if (info->pipe_read_end != STDIN_FILENO
		&& info->curr_cmd == info->data->nbr_of_cmds - 1)
		close_safe(info->pipe_read_end, info);
	if (info->fd_out != -10)
		close_safe(info->fd_out, info);
	if (info->fd_in != -10)
		close_safe(info->fd_in, info);
	if (info->curr_cmd != info->data->nbr_of_cmds - 1)
		close_safe(info->pipefd[1], info);
}

pid_t	child_process(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit_data_perror(info->data, ERROR_FORK, "fork in child process");
	else if (pid == 0)
		do_child_of_child(info);
	else
		do_parent_of_child(info);
	return (pid);
}

bool	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;
	char	**command_array;

	status = 0;
	i = 0;
	printf("---cmds:\n"); // DEBUGGING PURPOSES!
	printf_array(data->cmds); // DEBUGGING PURPOSES!
	printf("--------\n"); // DEBUGGING PURPOSES!
	while (i < data->nbr_of_cmds && data->exit_code == 0)
	{

		if (data->info->curr_cmd == data->info->here_doc_cmd)
		{
			if (init_heredoc(data) == false)
				return (false);
			data->info->fds[i][0] = ms_open(data, "0ur_h3r3_d0c", O_RDONLY, 0777);
		}
		data->info->fd_in = data->info->fds[i][0];
		data->info->fd_out = data->info->fds[i][1];
		if (i != data->nbr_of_cmds - 1)
			ms_pipe(data, data->info->pipefd);
		data->info->pipe_read_end = data->info->pipefd[0];
		command_array = make_command_array(info->data); // returns NULL if not builtin
		// printf("----COMMAND ARRAY----\n"); // DEBUGGING PURPOSES!
		// printf_array(command_array); // DEBUGGING PURPOSES!
		pid = ms_fork(info->data);
		if (pid == 0)
		{
			signals_for_kids();
			handle_child_type(info); //does dup2s
			if (command_array)
			{
				if (handle_builtin(info, command_array) == false)
				{
					printf("--HANDLE BUILTIN RETURNED FALSE\n"); // DEBUG
					close_fds(data, info);
					close_fds_from_next_cmds(info);
					exit(EXIT_FAILURE);
				}
				else
				{
					printf("---HANLDE BUILTIN RETURNED TRUE---\n"); // DEBUG
					close_fds(data, info);
					printf("---Close FDs done in do_child\n");
					close_fds_from_next_cmds(info);
					exit(EXIT_SUCCESS);
				}
			}
			else
			{
				// data->exit_code = SUCCESS;
				if (start_exec(info) == false)
					return (false);
		}
		else
		{
			unset_signals();
			// if (do_parent(info->data, info, command_array) == false)
			// 	pid = -125;
		}
		close_fds(info->data, info);
		free_2d_null(&command_array);
		if (pid < 0)
			return (false); //break??
		data->info->curr_cmd++;
		i++;
	}
	// close_fds(data, data->info); // probably not needed
	waitpid(pid, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		data->exit_code = WEXITSTATUS(status);
		return (true);
	}
	return (true);
}
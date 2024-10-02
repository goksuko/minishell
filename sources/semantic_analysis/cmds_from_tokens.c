#include "../../includes/minishell.h"

void limiter_check(t_data *shell_data)
{
	t_token	*current;

	current = shell_data->tokens;
	while (current)
	{
		if (current->limiter)
		{
			shell_data->info->limiter = ft_strdup(current->limiter);
			printf("limiter: %s\n", shell_data->info->limiter);
		}	
		current = current->next;
	}
}

t_token *redir_first(t_token *current)
{
	t_token	*temp;
	t_token	*smaller;
	t_token *file;
	t_token *next_token;

	if (current->next == NULL || current->next->next == NULL)
		return (NULL);
	smaller = current;
	file = current->next;
	temp = current->next->next;
	next_token = temp->next;
	temp->next = smaller;
	temp->prev = NULL;
	smaller->prev = temp;
	file->next = next_token;
	return (temp);
}

char *do_cat_addition(t_token *current, char *cmd)
{
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, current->next->value);
	// printf("cmd: %s\n", cmd);
	return (cmd);
}

bool is_first_after_pipe(t_token *current)
{
	if (current->prev == NULL || current->prev->type == T_PIPE)
		return (true);
	return (false);
}

char **find_cmd_of_heredoc(t_token *current, char **cmds)
{
	int		i;

	i = 0;
	if (current->next && current->next->next)
		current = current->next->next;
	else
		return (NULL);
	cmds[0] = ft_strdup(current->value);
	while (current && current->type != T_PIPE)
	{
		cmds[0] = ft_strjoin(cmds[i], " ");
		cmds[0] = ft_strjoin(cmds[i], current->value);
		current = current->next;
	}
	cmds[1] = NULL;
	return (cmds);
}


char **do_heredoc(t_data *shell_data, t_token *current, char **cmds)
{
	char	*limiter;
	char	*line;
	char	*temp;

	limiter = shell_data->info->limiter;
	line = readline("> ");
	temp = NULL;
	while (line && (ft_strlen(line) == ft_strlen(limiter)) && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		temp = ft_strjoin(temp, line);
		temp = ft_strjoin(temp, "\n");
		free(line);
		line = readline("> ");
	}
	shell_data->here_doc = ft_strdup(temp);
	free(temp);
	return (find_cmd_of_heredoc(current, cmds));
}

char **cmds_between_pipes(t_data *shell_data, char **cmds)
{
	int		j;
	t_token	*current;
	bool	cat_cmd;

	cat_cmd = false;
	j = 0;
	current = shell_data->tokens;
	while (current && current->type != T_PIPE)
	{
		while (current && current->type != T_PIPE)
		{
			if (is_redir_except_heredoc(current) && is_first_after_pipe(current))
			{
				current = redir_first(current);
				if (!current)
					return (NULL);
			}
			if (is_heredoc(current))
				return(do_heredoc(shell_data, current, cmds));
			if (ft_strncmp(current->value, "cat", 4) == 0)
				cat_cmd = true;
			if (is_first_after_pipe(current))
			{
				cmds[j] = ft_strdup(current->value);
				current = current->next;
			}
			if (current && is_redir_except_heredoc(current))
			{
				if (cat_cmd)
				{
					cmds[j] = do_cat_addition(current, cmds[j]);
					cat_cmd = false;
				}
				current = current->next->next;
			}
			else if (current && current->type != T_PIPE)
			{
				cmds[j] = ft_strjoin(cmds[j], " ");
				cmds[j] = ft_strjoin(cmds[j], current->value);
				current = current->next;
			}
		}
		if (current && current->type == T_PIPE)
			current = current->next;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

void finish_heredoc(t_data *shell_data)
{
	ft_printf_fd(shell_data->info->fd_in, "%s", shell_data->here_doc);

}

char **cmds_from_tokens(t_data *shell_data)
{
	char	**cmds;
	// int		i;
	// int		j;

	printf("---cmds_from_tokens---\n");
	// i = 0;
	// j = 0;
	cmds = (char **)malloc(sizeof(char *) * (shell_data->nbr_of_pipes + 2));
	if (cmds == NULL)
	{
		free_shell_data(&shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in cmds_from_tokens");
	}
	cmds = cmds_between_pipes(shell_data, cmds);
	if (shell_data->here_doc)
		finish_heredoc(shell_data);
	printf("cmds are ready\n");
	printf_array(cmds);
	return(cmds);

}

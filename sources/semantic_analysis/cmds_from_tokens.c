#include "../../includes/minishell.h"

bool	limiter_check(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
		{
			data->info->limiter = ft_strdup(current->limiter);
			if (data->info->limiter == NULL)
				return (false);
		}
		current = current->next;
	}
	return (true);
}

int	here_doc_fd_check(t_data *data)
{
	t_token	*current;
	int		temp_fd;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
			temp_fd = current->here_doc_fd;
		current = current->next;
	}
	return (temp_fd);
}

t_token	*redir_first(t_token *current)
{
	t_token	*temp;
	t_token	*smaller;
	t_token	*file;
	t_token	*next_token;

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

char	*do_cat_addition(t_token *current, char *cmd)
{
	cmd = ft_strjoin(cmd, " ");
	if (cmd == NULL)
		return (NULL);
	cmd = ft_strjoin(cmd, current->next->expanded_value);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

bool	is_first_after_pipe(t_token *current)
{
	if (current && (current->prev == NULL || current->prev->type == T_PIPE))
		return (true);
	return (false);
}

bool	init_heredoc(t_data *data)
{
	char	*limiter;
	char	*line;
	int		here_doc_fd;

	handle_signals(HEREDOC);
	here_doc_fd = here_doc_fd_check(data);
	if (limiter_check(data) == false)
		return (false);
	limiter = data->info->limiter;
	line = readline("> ");
	while (line)
	{
		if ((ft_strlen(line) == ft_strlen(limiter)) && ft_strncmp(line, limiter,
				ft_strlen(limiter)) == 0)
			break ;
		write(here_doc_fd, line, ft_strlen(line));
		write(here_doc_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (close(here_doc_fd) < 0)
		return (false);
	free(line);
	return (true);
}

// char	**cmds_between_pipes(t_data *data, char **cmds)
// {
// 	int		j;
// 	t_token	*current;
// 	bool	cat_cmd;

// 	cat_cmd = false;
// 	j = 0;
// 	current = data->tokens;
// 	while (current && current->type != T_PIPE)
// 	{
// 		while (current && current->type != T_PIPE)
// 		{
// 			if (is_heredoc(current))
// 			{
// 				if (current->next && current->next->next)
// 					current = current->next->next;
// 				cmds[j] = ft_strdup(current->expanded_value);
// 				if (cmds[j] == NULL)
// 					return (NULL);
// 				current = current->next;
// 				while (current && current->type != T_PIPE)
// 				{
// 					cmds[j] = ft_strjoin(cmds[j], " ");
// 					if (cmds[j] == NULL)
// 						return (NULL);
// 					cmds[j] = ft_strjoin(cmds[j], current->expanded_value);
// 					if (cmds[j] == NULL)
// 						return (NULL);
// 					current = current->next;
// 				}
// 			}
// 			if (is_redir_except_heredoc(current)
// 				&& is_first_after_pipe(current))
// 			{
// 				current = redir_first(current);
// 				if (!current)
// 					return (NULL);
// 			}
// 			if (current && ft_strncmp(current->expanded_value, "cat", 3) == 0)
// 				cat_cmd = true;
// 			if (is_first_after_pipe(current))
// 			{
// 				cmds[j] = ft_strdup(current->expanded_value);
// 				if (cmds[j] == NULL)
// 					return (NULL);
// 				current = current->next;
// 			}
// 			if (current && is_redir_except_heredoc(current))
// 			{
// 				if (cat_cmd)
// 				{
// 					cmds[j] = do_cat_addition(current, cmds[j]);
// 					if (cmds[j] == NULL)
// 						return (NULL);
// 					cat_cmd = false;
// 				}
// 				current = current->next->next;
// 			}
// 			else if (current && current->type != T_PIPE)
// 			{
// 				cmds[j] = ft_strjoin(cmds[j], " ");
// 				if (cmds[j] == NULL)
// 					return (NULL);
// 				cmds[j] = ft_strjoin(cmds[j], current->expanded_value);
// 				if (cmds[j] == NULL)
// 					return (NULL);
// 				current = current->next;
// 			}
// 		}
// 		printf("cmds[%d]: %s\n", j, cmds[j]);
// 		if (current && current->type == T_PIPE)
// 			current = current->next;
// 		j++;
// 	}
// 	cmds[j] = NULL;
// 	return (cmds);
// }

bool handle_heredoc(t_token **current, char **cmds, int *j)
{
	if ((*current)->next && (*current)->next->next)
		(*current) = (*current)->next->next;
	cmds[*j] = ft_strdup((*current)->expanded_value);
	if (cmds[*j] == NULL)
		return (false);
	(*current) = (*current)->next;
	while ((*current) && (*current)->type != T_PIPE)
	{
		cmds[*j] = ft_strjoin(cmds[*j], " ");
		if (cmds[*j] == NULL)
			return (false);
		cmds[*j] = ft_strjoin(cmds[*j], (*current)->expanded_value);
		if (cmds[*j] == NULL)
			return (false);
		(*current) = (*current)->next;
	}
	return (true);
}

bool handle_redirection(t_token **current, bool *cat_cmd)
{
	if (is_redir_except_heredoc(*current) && is_first_after_pipe(*current))
	{
		*current = redir_first(*current);
		if (!*current)
			return (false);
	}
	if (*current && ft_strncmp((*current)->expanded_value, "cat", 3) == 0)
		*cat_cmd = true;
	return (true);
}

bool handle_redirection2(t_token **current, char **cmds, int *j, bool *cat_cmd)
{
	if (is_first_after_pipe(*current))
	{
		cmds[*j] = ft_strdup((*current)->expanded_value);
		if (cmds[*j] == NULL)
			return (false);
		(*current) = (*current)->next;
	}
	if ((*current) && is_redir_except_heredoc(*current))
	{
		if (*cat_cmd)
		{
			cmds[*j] = do_cat_addition(*current, cmds[*j]);
			if (cmds[*j] == NULL)
				return (false);
			*cat_cmd = false;
		}
		(*current) = (*current)->next->next;
	}
	return (true);
}

bool	handle_command(t_token **current, char **cmds, int *j)
{
	if ((*current) && (*current)->type != T_PIPE)
	{
		cmds[*j] = ft_strjoin(cmds[*j], " ");
		if (cmds[*j] == NULL)
			return (false);
		cmds[*j] = ft_strjoin(cmds[*j], (*current)->expanded_value);
		if (cmds[*j] == NULL)
			return (false);
		(*current) = (*current)->next;
	}
	return (true);
}

char	**cmds_between_pipes(t_data *data, char **cmds)
{
	int		j;
	t_token	*current;
	bool	cat_cmd;

	cat_cmd = false;
	j = 0;
	current = data->tokens;
	while (current && current->type != T_PIPE)
	{
		while (current && current->type != T_PIPE)
		{
			if (is_heredoc(current))
			{
				if (!handle_heredoc(&current, cmds, &j))
					return (NULL);
			}
			if (!handle_redirection(&current, &cat_cmd))
				return (NULL);
			if (!handle_redirection2(&current, cmds, &j, &cat_cmd))
				return (NULL);
			if (!handle_command(&current, cmds, &j))
				return (NULL);
		}
		if (current && current->type == T_PIPE)
			current = current->next;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

char	**cmds_from_tokens(t_data *data)
{
	char	**cmds;

	cmds = (char **)ft_calloc(sizeof(char *), (data->nbr_of_pipes + 2));
	if (errno == ENOMEM || cmds == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION, "cmds in cmds_from_tokens");
		return (NULL);
	}
	cmds = cmds_between_pipes(data, cmds);
	if (cmds == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION, "cmds in cmds_from_tokens");
		return (NULL);
	}
	return (cmds);
}

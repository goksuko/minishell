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

char **find_cmd_of_heredoc(t_token *current)
{
	char	**array;

	array = (char **)malloc(sizeof(char *) * 50);
	if (array == NULL)
	{
		ft_exit_perror(ERROR_ALLOCATION, "malloc in find_cmd_of_heredoc");
	}
	printf("---find_cmd_of_heredoc---\n");
	if (current->next && current->next->next)
		current = current->next->next;
	else
	{
		printf("current->next->next is NULL\n");
		return (NULL);
	}
	printf("current->value: %s\n", current->value);	
	array[0] = ft_strdup(current->value);
	printf("cmds[0]: %s\n", array[0]);
	current = current->next;
	while (current && current->type != T_PIPE)
	{
		array[0] = ft_strjoin(array[0], " ");
		array[0] = ft_strjoin(array[0], current->value);
		current = current->next;
	}
	array[1] = NULL;
	return (array);
}


char **do_heredoc(t_data *shell_data, t_token *current)
{
	char	*limiter;
	char	*line;
	char	*temp;

	printf("---do_heredoc---\n");
	limiter = shell_data->info->limiter;
	line = readline("> ");
	temp = NULL;
	printf("line: %s\n", line);
	while (line && (ft_strlen(line) == ft_strlen(limiter)) && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		printf("inside while\n");
		temp = ft_strjoin(temp, line);
		temp = ft_strjoin(temp, "\n");
		free(line);
		printf("temp: %s\n", temp);
		line = readline("> ");
	}
	shell_data->here_doc = ft_strdup(temp);
	free(temp);
	return (find_cmd_of_heredoc(current));
}

char **cmds_between_pipes(t_data *shell_data, char **cmds)
{
	int		j;
	t_token	*current;
	bool	cat_cmd;

	printf("---cmds_between_pipes---\n");
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

// void finish_heredoc(t_data *shell_data)
// {
// 	ft_printf_fd(shell_data->info->fd_in, "%s", shell_data->here_doc);

// }

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
	printf("cmds are ready\n");
	printf_array(cmds);
	return(cmds);
}

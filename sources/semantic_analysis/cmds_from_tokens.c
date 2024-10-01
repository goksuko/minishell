#include "../../includes/minishell.h"

// int	next_redirection(t_token *tokens, int i)
// {
// 	// t_token	*temp;

// 	// temp = tokens;
// 	// while (tokens)
// 	// {
// 	// 	printf("tokens[%d]->type: %d\n", i, tokens[i]->type);
// 	// 	if (redirection_check(tokens[i]))
// 	// 	{
// 	// 		printf("returning i: %d\n", i);
// 	// 		return (i);
// 	// 	}
// 	// 	printf("i: %d\n", i);
// 	// 	i++;
// 	// 	printf("tokens[%d]->type: %d\n", i, tokens[i]->type);
// 	}
// 	if (i == temp)
// 		return (-1);
// 	return (i);
// }

// int next_pipe_token(t_token *tokens, int i)
// {
// 	int		temp;

// 	temp = i;
// 	while (tokens[i])
// 	{
// 		if (tokens[i]->type == T_PIPE)
// 			return (i);
// 		i++;
// 	}
// 	if (i == temp)
// 		return (-1);
// 	return (i);
// }

// char *cmd_till(t_token *tokens, int i, int till)
// {
// 	char	*cmd;

// 	printf("---cmd_till---\n");
// 	cmd = (char *)malloc(sizeof(char) * 1);
// 	if (cmd == NULL)
// 		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
// 	cmd[0] = '\0';
// 	while (i < till)
// 	{
// 		cmd = ft_strjoin(cmd, tokens[i].value);
// 		i++;
// 	}
// 	return (cmd);
// }

// char **cmds_from_tokens(t_data *shell_data)
// {
// 	int		i;
// 	int		j;
// 	int		next_redir;
// 	int		next_pipe;
// 	char	**cmds;
	
// 	printf("---cmds_from_tokens---\n");
// 	i = 0;
// 	j = 0;
// 	cmds = (char **)malloc(sizeof(char *) * (shell_data->nbr_of_pipes + 2));
// 	if (cmds == NULL)
// 	{
// 		free_shell_data(&shell_data);
// 		ft_exit_perror(ERROR_ALLOCATION, "malloc in cmds_from_tokens");
// 	}
// 	// cmds[0] = NULL;
// 	// cmds[shell_data->nbr_of_pipes + 1] = NULL;
// 	printf("nbr_of_tokens: %d\n", shell_data->nbr_of_tokens);
// 	next_redir = next_redirection(&shell_data->tokens, i);
// 	printf("next_redir: %d\n", next_redir);
// 	next_pipe = next_pipe_token(&shell_data->tokens, i);
// 	while (j < shell_data->nbr_of_tokens)
// 	{
// 		printf("next_redir: %d\n", next_redir);
// 		printf("next_pipe: %d\n", next_pipe);
		
// 		if (next_redir == -1 && next_pipe == -1)
// 			cmds[j] = ft_strdup(cmd_till(shell_data->tokens, 0, shell_data->nbr_of_tokens));
// 		else if (next_redir == -1 || next_pipe > next_redir)
// 			cmds[j] = ft_strdup(cmd_till(shell_data->tokens, i, next_pipe));
// 		else
// 			cmds[j] = ft_strdup(cmd_with_redir(shell_data->tokens, i, next_pipe));
// 		j++;
// 		i = next_pipe + 1;
// 		next_pipe = next_pipe_token(&shell_data->tokens, i);
// 		next_redir = next_redirection(&shell_data->tokens, i);
// 	}
// 	cmds[j] = NULL;
// 	return (cmds);
// }

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

// char *do_cat_addition(t_token *current, char *cmd)
// {
// 	cmd = ft_strjoin(cmd, current->next->value);
// 	cmd = ft_strjoin(cmd, " ");
// 	printf("cmd: %s\n", cmd);
// 	return (cmd);
// }

// char *smaller_first(t_token *current)
// {
// 	char	*cmd;
// 	t_token	*temp;
// 	int		i;

// 	i = 3;
// 	cmd = ft_strdup(current->next->next->value);
// 	cmd = ft_strjoin(cmd, " ");
// 	if (ft_strncmp(current->next->next->value, "cat", 4) == 0)
// 	{
// 		cmd = ft_strjoin(cmd, current->next->value);
// 		cmd = ft_strjoin(cmd, " ");
// 		printf("cmd: %s\n", cmd);
// 	}
// 	temp = current;
// 	while (temp && i--)
// 		temp = temp->next;
	
// 	// while (temp && temp->type != T_PIPE)
// 	// {
// 	// 	cmd = ft_strjoin(cmd, temp->value);
// 	// 	cmd = ft_strjoin(cmd, " ");
// 	// 	temp = temp->next;
// 	// 	printf("cmd: %s\n", cmd);
// 	// }
// 	return (cmd);
// }

t_token *smaller_first(t_token *current)
{
	t_token	*temp;
	t_token	*smaller;
	t_token *file;
	t_token *next_token;

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

char **cmds_between_pipes(t_data *shell_data, char **cmds)
{
	// int		i;
	int		j;
	t_token	*current;
	bool	cat_cmd;

	cat_cmd = false;

	printf("---cmds_between_pipes---\n");
	// i = 0;
	j = 0;
	current = shell_data->tokens;
	while (current && current->type != T_PIPE)
	{
		while (current && current->type != T_PIPE)
		{
			printf("current->value: %s\n", current->value);
			if ((current->type == T_GREATER || current->type == T_DGREATER || current->type == T_SMALLER) && (current->prev == NULL || current->prev->type == T_PIPE))
				current = smaller_first(current);
			if (ft_strncmp(current->value, "cat", 4) == 0)
				cat_cmd = true;
			if (current->prev == NULL || current->prev->type == T_PIPE)
			{
				cmds[j] = ft_strdup(current->value);
				current = current->next;
			}
			printf("cmds[%d] in the beginning: %s\n", j, cmds[j]);
			if (current->type == T_GREATER || current->type == T_DGREATER || current->type == T_SMALLER)
			{
				if (cat_cmd)
				{
					printf("cmds[%d] before cat addition: %s\n", j, cmds[j]);					
					cmds[j] = do_cat_addition(current, cmds[j]);
					printf("cmds[%d] after cat addition: %s\n", j, cmds[j]);
					cat_cmd = false;
				}
				// else
				current = current->next->next;
			}
			else
			{
				cmds[j] = ft_strjoin(cmds[j], " ");
				cmds[j] = ft_strjoin(cmds[j], current->value);
				current = current->next;
			}
		}
		if (current && current->type == T_PIPE)
			current = current->next;


		// if (current->type == T_SMALLER && (current->prev == NULL || current->prev->type == T_PIPE))
		// {
		// 	cmds[j] = smaller_first(current);
		// 	printf("cmds[%d]: %s\n", j, cmds[j]);
		// 	while (current && current->type != T_PIPE)
		// 		current = current->next;
		// 	// if (current->type == T_PIPE)
		// 	// 	current = current->next;
		// 	while (current && current->type != T_PIPE)
		// 	{
		// 		if (current->type == T_GREATER || current->type == T_DGREATER || current->type == T_SMALLER)
		// 			current = current->next->next;
		// 		else
		// 		{
		// 			cmds[j] = ft_strjoin(cmds[j], " ");
		// 			cmds[j] = ft_strjoin(cmds[j], current->value);
		// 			current = current->next;
		// 		}
		// 	}
		// 	// if (current && current->type == T_PIPE)
		// 	// 	current = current->next;
		// }
		// else if (current->type == T_DSMALLER)
		// {

		// 	shell_data->info->limiter = ft_strdup(current->next->value);
		// 	printf("limiter heyey: %s\n", shell_data->info->limiter);

		// 	if (current->next->next)
		// 		cmds[j] = ft_strdup(current->next->next->value);
		// 	else
		// 		cmds[j] = NULL;
		// 	current = NULL;
		// }
		// else
		// {
		// 	cmds[j] = ft_strdup(current->value);
		// 	if (ft_strncmp(current->value, "cat", 4) == 0)
		// 	{
		// 		cmds[j] = ft_strjoin(cmds[j], " ");
		// 		cmds[j] = ft_strjoin(cmds[j], current->next->next->value);
		// 	}
		// 	current = current->next;

		// 	while (current && current->type != T_PIPE)
		// 	{
		// 		if (current->type == T_GREATER || current->type == T_DGREATER || current->type == T_SMALLER)
		// 			current = current->next->next;
		// 		else
		// 		{
		// 			cmds[j] = ft_strjoin(cmds[j], " ");
		// 			cmds[j] = ft_strjoin(cmds[j], current->value);
		// 			current = current->next;
		// 		}
		// 	}
		// 	// if (current && current->type == T_PIPE)
		// 	// 	current = current->next;

		// }
		printf("cmds[%d]: %s\n", j, cmds[j]);
		j++;
	}
	cmds[j] = NULL;
	printf_array(cmds);
	return (cmds);
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
	return(cmds);

}

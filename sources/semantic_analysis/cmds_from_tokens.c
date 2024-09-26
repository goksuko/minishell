#include "../../includes/minishell.h"

int	next_redirection(t_token *tokens, int i)
{
	// t_token	*temp;

	// temp = tokens;
	// while (tokens)
	// {
	// 	printf("tokens[%d]->type: %d\n", i, tokens[i]->type);
	// 	if (redirection_check(tokens[i]))
	// 	{
	// 		printf("returning i: %d\n", i);
	// 		return (i);
	// 	}
	// 	printf("i: %d\n", i);
	// 	i++;
	// 	printf("tokens[%d]->type: %d\n", i, tokens[i]->type);
	}
	if (i == temp)
		return (-1);
	return (i);
}

int next_pipe_token(t_token *tokens, int i)
{
	int		temp;

	temp = i;
	while (tokens[i])
	{
		if (tokens[i]->type == T_PIPE)
			return (i);
		i++;
	}
	if (i == temp)
		return (-1);
	return (i);
}

char *cmd_till(t_token *tokens, int i, int till)
{
	char	*cmd;

	printf("---cmd_till---\n");
	cmd = (char *)malloc(sizeof(char) * 1);
	if (cmd == NULL)
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	cmd[0] = '\0';
	while (i < till)
	{
		cmd = ft_strjoin(cmd, tokens[i].value);
		i++;
	}
	return (cmd);
}

char **cmds_from_tokens(t_data *shell_data)
{
	int		i;
	int		j;
	int		next_redir;
	int		next_pipe;
	char	**cmds;
	
	printf("---cmds_from_tokens---\n");
	i = 0;
	j = 0;
	cmds = (char **)malloc(sizeof(char *) * (shell_data->nbr_of_pipes + 2));
	if (cmds == NULL)
	{
		free_shell_data(&shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in cmds_from_tokens");
	}
	// cmds[0] = NULL;
	// cmds[shell_data->nbr_of_pipes + 1] = NULL;
	printf("nbr_of_tokens: %d\n", shell_data->nbr_of_tokens);
	next_redir = next_redirection(&shell_data->tokens, i);
	printf("next_redir: %d\n", next_redir);
	next_pipe = next_pipe_token(&shell_data->tokens, i);
	while (j < shell_data->nbr_of_tokens)
	{
		printf("next_redir: %d\n", next_redir);
		printf("next_pipe: %d\n", next_pipe);
		
		if (next_redir == -1 && next_pipe == -1)
			cmds[j] = ft_strdup(cmd_till(shell_data->tokens, 0, shell_data->nbr_of_tokens));
		else if (next_redir == -1 || next_pipe > next_redir)
			cmds[j] = ft_strdup(cmd_till(shell_data->tokens, i, next_pipe));
		else
			cmds[j] = ft_strdup(cmd_with_redir(shell_data->tokens, i, next_pipe));
		j++;
		i = next_pipe + 1;
		next_pipe = next_pipe_token(&shell_data->tokens, i);
		next_redir = next_redirection(&shell_data->tokens, i);
	}
	cmds[j] = NULL;
	return (cmds);
}
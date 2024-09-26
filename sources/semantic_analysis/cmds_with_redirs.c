#include "../../includes/minishell.h"

char *cmd_with_redir(t_token *tokens, int i, int next_pipe)
{
	char	*cmd;
	int		next_redir;

	cmd = NULL;
	if (tokens[i].type == T_GREATER)
	{
		cmd = ft_strjoin(cmd, tokens[i + 2].value);
		cmd = ft_strjoin(cmd, " ");
		cmd = ft_strjoin(cmd, tokens[i + 1].value);
		cmd = ft_strjoin(cmd, " ");
		i += 3;
	}
	next_redir = next_redirection(&tokens, i);
	while (next_redir != -1 && next_redir < next_pipe)
	{
		while (i < next_redir && i < next_pipe)
		{
			cmd = ft_strjoin(cmd, tokens[i].value);
			cmd = ft_strjoin(cmd, " ");
			i++;
		}
		i += 2;
		next_redir = next_redirection(&tokens, i);
	}
	return (cmd);
}
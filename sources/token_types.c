#include "../includes/minishell.h"

const char	*token_type_to_string(t_token_type type)
{
	static const char *str[] = {
		[COMMAND] = "COMMAND",
		[ARGUMENT] = "ARGUMENT",
		[REDIRECTION] = "REDIRECTION",
		[PIPE] = "PIPE",
		[ENV_VARIABLE] = "ENV_VARIABLE",
		[FLAG] = "FLAG",
		[SINGLE_QUOTES] = "SINGLE_QUOTES",
		[DOUBLE_QUOTES] = "DOUBLE_QUOTES",
		[UNKNOWN] = "UNKNOWN"};
	if (type < 0 || type >= sizeof(str) / sizeof(str[0])) // need to check this
		return (str[UNKNOWN]);
	return (str[type]);
}

t_token_type	check_command(char *token)
{
	if (ft_strncmp(token, "echo", 4) == 0)
		return (COMMAND);
	if (ft_strncmp(token, "cd", 2) == 0)
		return (COMMAND);
	if (ft_strncmp(token, "pwd", 3) == 0)
		return (COMMAND);
	if (ft_strncmp(token, "export", 6) == 0)
		return (COMMAND);
	if (ft_strncmp(token, "unset", 5) == 0)
		return (COMMAND);
	if (ft_strncmp(token, "env", 3) == 0)
		return (COMMAND);
	if (ft_strncmp(token, "exit", 4) == 0)
		return (COMMAND);
	return (UNKNOWN);
}

t_token_type	check_env_variable(char *token)
{
	if (ft_strncmp(token, "PATH", 4) == 0)
		return (ENV_VARIABLE);
	if (ft_strncmp(token, "$", 1) == 0)
		return (ENV_VARIABLE);
	return (UNKNOWN);
}

t_token_type	check_redirection(char *token)
{
	if (ft_strncmp(token, "<", 1) == 0)
		return (REDIRECTION);
	if (ft_strncmp(token, ">", 1) == 0)
		return (REDIRECTION);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (REDIRECTION);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (REDIRECTION);
	return (UNKNOWN);
}

t_token_type	check_pipes(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return (PIPE);
	return (UNKNOWN);
}

t_token_type	check_flag(char *token)
{
	if (ft_strncmp(token, "-", 1) == 0)
		return (FLAG);
	return (UNKNOWN);
}

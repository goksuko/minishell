#include "../../includes/minishell.h"

const char	*token_type_to_string(t_token_type type) // to be deleted later
{
	static const char	*str[] = {
	[T_COMMAND] = "COMMAND",
	[T_IDENTIFIER] = "IDENTIFIER",
	[T_SMALLER] = "SMALLER",
	[T_GREATER] = "GREATER",
	[T_DSMALLER] = "DSMALLER",
	[T_DGREATER] = "DGREATER",
	[T_PIPE] = "PIPE",
	[T_ENV_VARIABLE] = "ENV_VARIABLE",
	[T_FLAG] = "FLAG",
	[T_SINGLE_QUOTES] = "SINGLE_QUOTES",
	[T_DOUBLE_QUOTES] = "DOUBLE_QUOTES",
	[T_UNKNOWN] = "UNKNOWN"};

	if (type < 0 || type >= sizeof(str) / sizeof(str[0])) // need to check this
		return (str[T_UNKNOWN]);
	return (str[type]);
}

t_token_type	check_command(char *token)
{
	if (ft_strncmp(token, "echo", 4) == 0)
		return (T_COMMAND);
	if (ft_strncmp(token, "cd", 2) == 0)
		return (T_COMMAND);
	if (ft_strncmp(token, "pwd", 3) == 0)
		return (T_COMMAND);
	if (ft_strncmp(token, "export", 6) == 0)
		return (T_COMMAND);
	if (ft_strncmp(token, "unset", 5) == 0)
		return (T_COMMAND);
	if (ft_strncmp(token, "env", 3) == 0)
		return (T_COMMAND);
	if (ft_strncmp(token, "exit", 4) == 0)
		return (T_COMMAND);
	return (T_UNKNOWN);
}

t_token_type	check_env_variable(char *token)
{
	if (ft_strncmp(token, "PATH", 4) == 0)
		return (T_ENV_VARIABLE);
	if (ft_strncmp(token, "$", 1) == 0)
		return (T_ENV_VARIABLE);
	return (T_UNKNOWN);
}

t_token_type	check_redirection(char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0)
		return (T_DGREATER);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (T_DSMALLER);
	if (ft_strncmp(token, "<", 1) == 0)
		return (T_SMALLER);
	if (ft_strncmp(token, ">", 1) == 0)
		return (T_GREATER);
	return (T_UNKNOWN);
}

t_token_type	check_pipes(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return (T_PIPE);
	return (T_UNKNOWN);
}

t_token_type	check_flag(char *token)
{
	if (ft_strncmp(token, "-", 1) == 0)
		return (T_FLAG);
	return (T_UNKNOWN);
}
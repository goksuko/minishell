#include "../../includes/minishell.h"

bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

bool	arg_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_digit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

int	exit_atoi(char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	skip_whitespace(str, &i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (is_digit(str[i]) == true)
	{
		number = number * 10 + (str[i] - '0');
		if (number > INT_MAX)
			return (-1);
		i++;
	}
	number = number * sign;
	return (number);
}

void	ft_exit(t_tree **ast, t_env **env_var)
{
	if ((*ast)->expanded_argument[1] == NULL)
	{
		free_tree_env(ast, env_var);
		exit(SUCCESS);
	}
	else if ((*ast)->expanded_argument[2] != NULL)
	{
		free_tree_env(ast, env_var);
		ft_exit_str_fd(ERROR_TOO_MAY_ARGS, STDERR_FILENO);
	}
	else if ((*ast)->expanded_argument[1] != NULL)
	{
		if (arg_is_digit((*ast)->expanded_argument[1]) == false)
		{
			free_tree_env(ast, env_var);
			ft_exit_str_fd(ERROR_NUMERIC_ARG, STDERR_FILENO);
		}
		else
		{
			free_tree_env(ast, env_var); //cannot free ast here because it is used in exit_atoi
			exit(exit_atoi((*ast)->expanded_argument[1])); // seg faulting here
		}
	}
}

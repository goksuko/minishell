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

int	get_sign(char c, int *i)
{
	int	sign;

	sign = 1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	exit_atoi(char *str, t_env **env_var)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	skip_whitespace(str, &i);
	sign = get_sign(str[i], &i);
	while (is_digit(str[i]) == true)
	{
		number = number * 10 + (str[i] - '0');
		if (number > INT_MAX)
		{
			//free_tree_env(ast, env_var); free shel_data
			ft_exit_str_fd(ERROR_NUMERIC_ARG, STDERR_FILENO);
		}
		i++;
	}
	number = ((number * sign) % 256);
	return (number);
}
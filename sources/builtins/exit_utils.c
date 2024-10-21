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

int	exit_atoi(char *exit_code, t_data *data)
{
	int i;
	int sign;
	long number;

	i = 0;
	sign = 1;
	number = 0;
	skip_whitespace(exit_code, &i);
	sign = get_sign(exit_code[i], &i);
	while (is_digit(exit_code[i]) == true)
	{
		number = number * 10 + (exit_code[i] - '0');
		if (errno == ENOMEM || number > INT_MAX)
		{
			free_system_error(data, ERROR_NUMERIC_ARG);
			return (ERROR_NUMERIC_ARG);
		}
		i++;
	}
	number = ((number * sign) % 256);
	data->exit_code = number;
	return (SUCCESS);
}
#include "../../includes/minishell.h"

int	get_end_dollar(char *str, int i)
{
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i - 1);
}

char	*get_env_str(t_data *data, char *str)
{
	char	*env;

	env = ft_get_env(data->env_list, str);
	if (env == NULL)
		return (ft_strdup_safe(data, ""));
	return (env);
}

char	*handle_dollar_sign(t_data **data, char *str)
{
	int		i;
	int		start_dollar;
	int		end_dollar;
	char	*temp;
	char	*middle_to_add;

	i = 0;
	start_dollar = 0;
	end_dollar = 0;
	temp = ft_strdup_safe(*data, "");
	if (temp == NULL)
	{
		free_data(data);
		// exit code and string to print
	}
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start_dollar = i;
			if (str[i + 1] == '?')
			{
				middle_to_add = ft_itoa((*data)->exit_code);
				if (middle_to_add == NULL)
				{
					free_data(data);
					// exit code and string to print
				}
				end_dollar = start_dollar + 1;
			}
			else if (str[i + 1] == '$')
			{
				middle_to_add = ft_itoa(getpid());
				if (middle_to_add == NULL)
				{
					free_data(data);
					// exit code and string to print
				}
				end_dollar = start_dollar + 1;
			}
			else if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == ' '))
			{
				middle_to_add = get_env_str(*data, str + i + 1);
				if (middle_to_add == NULL)
				{
					free_data(data);
					// exit code and string to print
				}
				end_dollar = get_end_dollar(str, i + 1); // + 1 because i is the index of the dollar sign
			}
			temp = ft_strjoin_safe(*data, temp, middle_to_add);
			i = end_dollar + 1; // Jump to end_dollar
		}
		else
		{
			temp = ft_strjoin_c_safe(*data, temp, str[i]);
			i++;
		}
	}
	return (temp);
}

bool	dollar_sign_check(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
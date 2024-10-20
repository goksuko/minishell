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
	{
		env = ft_strdup("");
		if (env == NULL)
			return (NULL);
	}
	return (env);
}

// char	*dollar_exit_code(t_data *data, int start_dollar, int *end_dollar)
// {
// 	char	*exit_code_str;

// 	exit_code_str = ft_itoa(data->exit_code);
// 	if (exit_code_str == NULL)
// 		return (NULL);
// 	*end_dollar = start_dollar + 1;
// 	return (exit_code_str);
// }

// char	*dollar_pid(int start_dollar, int *end_dollar)
// {
// 	char	*pid_str;

// 	pid_str = ft_itoa(getpid());
// 	if (pid_str == NULL)
// 		return (NULL);
// 	*end_dollar = start_dollar + 1;
// 	return (pid_str);
// }

// char	*dollar_env_value(t_data *data, char *str, int *end_dollar, int i)
// {
// 	char	*env_value;

// 	env_value = get_env_str(data, str + i + 1);
// 	if (env_value == NULL)
// 		return (NULL);
// 	*end_dollar = get_end_dollar(str, i + 1);
// 	return (env_value);
// }

// char	*get_dollar_replacement(t_data **data, char *str, int i,
// 		int *end_dollar)
// {
// 	if (str[i + 1] == '?')
// 		return (dollar_exit_code(*data, i, end_dollar));
// 	else if (str[i + 1] == '$')
// 		return (dollar_pid(i, end_dollar));
// 	else if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1]) == 1 || str[i
// 			+ 1] == ' '))
// 		return (dollar_env_value(*data, str, end_dollar, i));
// 	return (NULL);
// }

// char	*handle_dollar_sign(t_data **data, char *str)
// {
// 	int		i;
// 	int		end_dollar;
// 	char	*temp;
// 	char	*new_temp;
// 	char	*middle_to_add;
// 	char	*new_temp;
// 	char	*new_temp;

// 	i = 0;
// 	end_dollar = 0;
// 	temp = ft_strdup("");
// 	if (temp == NULL)
// 		return (NULL);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			middle_to_add = get_dollar_replacement(data, str, i, &end_dollar);
// 			if (middle_to_add == NULL)
// 			{
// 				free(temp);
// 				return (NULL);
// 			}
// 			new_temp = ft_strjoin(temp, middle_to_add);
// 			free(temp);
// 			free(middle_to_add);
// 			if (new_temp == NULL)
// 				return (NULL);
// 			temp = new_temp;
// 			i = end_dollar + 1;
// 		}
// 		else
// 		{
// 			new_temp = ft_strjoin_c(temp, str[i]);
// 			free(temp);
// 			if (new_temp == NULL)
// 				return (NULL);
// 			temp = new_temp;
// 			i++;
// 		}
// 	}
// 	return (temp);
// }

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
	temp = ft_strdup("");
	if (temp == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start_dollar = i;
			if (str[i + 1] == '?')
			{
				middle_to_add = ft_itoa((*data)->exit_code);
				if (middle_to_add == NULL)
					return (NULL);
				end_dollar = start_dollar + 1;
			}
			else if (str[i + 1] == '$')
			{
				middle_to_add = ft_itoa(getpid());
				if (middle_to_add == NULL)
					return (NULL);
				end_dollar = start_dollar + 1;
			}
			else if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1]) == 1 || str[i
+ 1] == ' '))
			{
				middle_to_add = get_env_str(*data, str + i + 1);
				if (middle_to_add == NULL)
					return (NULL);
				end_dollar = get_end_dollar(str, i + 1); // +1 because i is the index of the dollar sign
			}
			temp = ft_strjoin(temp, middle_to_add);
			if (temp == NULL)
					return (NULL);
			i = end_dollar + 1; // Jump to end_dollar
		}
		else
		{
			temp = ft_strjoin_c(temp, str[i]);
			if (temp == NULL)
				return (NULL);
			i++;
		}
	}
	return (temp);
}

bool	dollar_sign_check(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
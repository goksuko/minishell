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

// char	*expand_exit_code(t_data *data)
// {
// 	char	*middle_str;

// 	middle_str = NULL;
// 	middle_str = ft_itoa(data->exit_code);
// 	if (middle_str == NULL)
// 		return (NULL);
// 	return (middle_str);
// }

// char	*expand_pid(void)
// {
// 	char	*middle_str;
	
// 	middle_str = ft_itoa(getpid()); // to be checked of this one can be used or the one from env!!
// 	if (middle_str == NULL)
// 		return (NULL);
// 	return (middle_str);
// }

// char	*expand_pid_dollar(t_data *data, char *str, int start_dollar, int *end_dollar)
// {
// 	char	*middle_str;

// 	middle_str = NULL;
// 	if (*str == '?')
// 		middle_str = expand_exit_code(data);
// 	else if (*str == '$')
// 		middle_str = expand_pid();
// 	if (middle_str != NULL)
// 		*end_dollar = start_dollar + 1;
// 	return (middle_str);
// }

// char	*expand_env(t_data *data, char *str, int i, int *end_dollar)
// {
// 	char	*middle_str;

// 	middle_str = get_env_str(data, str);
// 	if (middle_str == NULL)
// 		return (NULL);
// 	*end_dollar = get_end_dollar(str, i + 1); // +1 because i is the index of the dollar sign
// 	printf("end dollar: %c\n", str[*end_dollar]);
// 	return (middle_str);
// }

// bool	init_variables(int *i, int *start_dollar, int *end_dollar, char **temp)
// {
// 	*i = 0;
// 	*start_dollar = 0;
// 	*end_dollar = 0;
// 	*temp = ft_strdup("");
// 	if (temp == NULL)
// 		return (false);
// 	return (true);
// }

// char	*handle_dollar_sign(t_data **data, char *str)
// {
// 	int		i;
// 	int		start_dollar;
// 	int		end_dollar;
// 	char	*temp;
// 	char	*middle_to_add;

// 	if (init_variables(&i, &start_dollar, &end_dollar, &temp) == false)
// 		return (NULL);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			start_dollar = i;
// 			if (str[i + 1] == '?' || str[i + 1] == '$')
// 				middle_to_add = expand_pid_dollar(*data, &str[i + 1], start_dollar, &end_dollar);
// 			else if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1]) == 1 || str[i+ 1] == ' '))
// 				middle_to_add = expand_env(*data, &str[i + 1], i, &end_dollar);
// 			if (middle_to_add == NULL)
// 				return (NULL);
// 			printf("Middle to add: %s\n", middle_to_add);
// 			temp = ft_strjoin(temp, middle_to_add);
// 			if (temp == NULL)
// 					return (NULL);
// 			i = end_dollar + 1; // Jump to end_dollar
// 			printf("%c\n", str[i]);
// 		}
// 		else
// 		{
// 			temp = ft_strjoin_c(temp, str[i]);
// 			if (temp == NULL)
// 				return (NULL);
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
			else if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1]) == 1 || str[i+ 1] == ' '))
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
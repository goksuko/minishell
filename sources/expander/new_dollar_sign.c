#include "../../includes/minishell.h"

char	*get_env_str(t_data *data, char *str) // add memory handling
{
	printf("----GET_ENV_STR----\n");
	printf("str: %s\n", str);
	char	*env;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = NULL;
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	temp = (char *)ft_calloc(sizeof(char), i + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		temp[j++] = str[i++];
	temp[j] = '\0';
	printf("temp: %s\n", temp);
	env = ft_get_env(data->env_list, temp);
	if (env == NULL)
	{
		env = ft_strdup("");
		if (env == NULL)
			return (NULL);
	}
	free(temp);
	return (env);
}

char	*expand_exit_code(t_data *data)
{
	printf("----EXPAND_EXIT_CODE----\n");
	char	*temp;

	temp = NULL;
	temp = ft_itoa(data->exit_code);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*expand_pid(void)
{
	printf("----EXPAND_PID----\n");
	char	*temp;

	temp = NULL;
	temp = ft_itoa(getpid());
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*expand_env_variable(t_data *data, char *str)
{
	printf("----EXPAND_ENV_VARIABLE----\n");
	char	*temp;

	temp = NULL;
	temp = get_env_str(data, str);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*add_temp_to_new(char *str, char *to_add)
{
	printf("----ADD_TEMP_TO_NEW----\n");
	char	*new;

	new = NULL;
	new = ft_strjoin(str, to_add);
	if (new == NULL)
		return (NULL);
	// free(str);
	printf("---ADDED TEMP TO NEW DONE---\n");
	return (new);
}

void	update_i(int *i, char *str)
{
	printf("----UPDATE_I----\n");
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '$')
		(*i)++;
	printf("Character after updating index i: %c\n", str[*i]);
	printf("Index i: %d\n", *i);
	printf("----UPDATE_I_DONE----\n");
}

char	*process_dollar_sign(t_data *data, char *str, char *new_str, int *i)
{
	printf("----PROCESS_DOLLAR_SIGN----\n");
	char	*temp;
	char	*new;
	int		start_expansion;

	temp = NULL;
	new = NULL;
	start_expansion = *i;
	if (str[0] == '?')
		temp = expand_exit_code(data);
	else if (str[0] == '$')
		temp = expand_pid();
	else if (str[0] != '\0' && (ft_isalnum(str[0]) == 1 || str[0] == ' '))
		temp = expand_env_variable(data, str);
	if (temp == NULL)
		return (NULL);
	new = add_temp_to_new(new_str, temp);
	if (new == NULL)
		return (NULL);
	free(temp);
	update_i(i, str);
	*i += start_expansion;
	printf("Character after updating index i: %c\n", str[*i]);
	return (new);
}

char	*handle_dollar_sign(t_data **data, char *str)
{
	printf("----HANDLE_DOLLAR_SIGN----\n");
	printf("Length of str: %zu\n", ft_strlen(str));
	int		i;
	char	*new;
	char	*temp;

	i = 0;
	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		printf("Character at beginning of loop: %c\n", str[i]);
		printf("New string: %s\n", new);
		printf("Index i: %d\n", i);
		if (str[i] == '$')
		{
			i++;
			temp = process_dollar_sign(*data, &str[i], new, &i);
			if (temp == NULL)
				return (NULL);
			free(new);
			new = temp;
			continue ;
		}
		temp = ft_strjoin_c(new, str[i]);
		if (temp == NULL)
			return (NULL);
		free(new);
		new = temp;
		i++;
	}
	return (new);
}

bool	dollar_sign_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

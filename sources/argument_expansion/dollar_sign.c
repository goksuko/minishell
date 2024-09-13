#include "../../includes/minishell.h"

int	env_len(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i);
}

int	get_len_to_skip(char *str)
{
	printf("---REPLACE DOLLAR WITH ENV VALUE---\n");
	printf("str: %s\n", str); // only for testing
	int		len;
	char	*temp;

	temp = malloc((sizeof(char) * 1) + env_len(str));
	if (temp == NULL)
	{
		// free_shell_data(shell_data); // to be written 
		// exit code and string to print
	}
	temp = ft_strcpy(temp, str, env_len(str));
	printf("temp: %s\n", temp); // only for testing
	len = ft_strlen(temp);
	printf("len: %d\n", len); // only for testing
	return (len);
}

char	*get_env_str(char *str, int *i) // need to add shell_data struct
{
	printf("---REPLACE DOLLAR WITH ENV VALUE---\n");
	char	*temp;
	char	*env;

	temp = malloc((sizeof(char) * 1) + env_len(str));
	if (temp == NULL)
	{
		// free_shell_data(shell_data); // to be written 
		// exit code and string to print
	}
	temp = ft_strcpy(temp, str, env_len(str));
	printf("temp: %s\n", temp); // only for testing
	env = getenv(temp);
	if (env == NULL)
	{
		// free_shell_data(shell_data); // to be written 
		// exit code and string to print
	}
	printf("env: %s\n", env); // only for testing
	*i += ft_strlen(env);
	return (env);
}

char	*expanded_string(char *original_string, int start_dollar, char *string_to_add, int chars_to_remove)
{
    char *temp;
    int i = 0;
    int j = 0;

	printf("chars_to_remove in expanded_string: %d\n", chars_to_remove); // only for testing
    temp = malloc(sizeof(char) * (start_dollar + 1));
	// add error handling
    while (i < start_dollar)
	{
        temp[j] = original_string[i];
        j++;
        i++;
    }
    temp[j] = '\0';
    printf("after copying temp: %s\n", temp); // only for testing
    temp = ft_strjoin(temp, string_to_add);
    printf("first join temp: %s\n", temp); // only for testing
    i += chars_to_remove;
    temp = ft_strjoin(temp, original_string + i);
    printf("second join temp: %s\n", temp); // only for testing
    return temp;
}

char	*handle_dollar_sign(t_data **shell_data, char *str) // need to add shell_data struct
{
	int		i;
	int		start_dollar;
	char	*temp;
	char	*env;
	int		chars_to_remove;

	i = 0;
	temp = ft_strdup(str);
	if (temp == NULL)
	{
		// free_shell_data(shell_data); // to be written 
		// exit code and string to print
	}
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start_dollar = i;
			i++;
			printf("ONLY FOR TESTING str[i]: %c\n", str[i]);
			if (str[i] == '?' && str[i - 2] != '$') // check for correctness
			{
				chars_to_remove = get_len_to_skip(str + start_dollar);
				temp = expanded_string(temp, start_dollar, ft_itoa((*shell_data)->exit_code), chars_to_remove);
				printf("temp: %s\n", temp); // only for testing
				//create a new string and remove the dollar sign and ? and replace with the exit code and add the rest of the string
			}
			// if (str[i] == '$')
			// // get process ID (pid) of the shell but if there is a ? right after this one the question mark needs to simply be printed
			// {
			// 	// create a new string and remove the dollar sign and $ and replace with the pid and add the rest of the string
			// }
			else if (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
			{
				chars_to_remove = get_len_to_skip(str + start_dollar);
				printf("chars_to_remove in handle_dollar_sign: %d\n", chars_to_remove); // only for testing
				env = get_env_str(str + i, &i);
				printf("env back in handle_dollar_sign: %s\n", env); // only for testing
				temp = expanded_string(temp, start_dollar, env, chars_to_remove);
				printf("after env was replaced in handle_dollar_sign: temp: %s\n", temp); // only for testing
			}
		}
		i++;
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
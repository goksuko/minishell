#include "../../includes/minishell.h"

char	*ft_strjoin_c(char const *s1, char c)
{
	char	*new_str;
	char	*temp;

	if (s1 == NULL)
		return (NULL);
	new_str = (char *)ft_calloc((ft_strlen(s1)
				+ 1 + 1), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	temp = new_str;
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	new_str += ft_strlen(s1);
	*new_str = c;
	return (temp);
}

// char *ft_strnjoin(char *s1, char *s2, size_t n) {
// 	char *result;
// 	size_t i, j;

// 	if (!s1 || !s2)
// 		return NULL;

// 	result = malloc(strlen(s1) + n + 1); // +1 for the null-terminator
// 	if (!result)
// 		return NULL;

// 	i = 0;
// 	while (s1[i]) {
// 		result[i] = s1[i];
// 		i++;
// 	}

// 	j = 0;
// 	while (s2[j] && j < n) {
// 		result[i] = s2[j];
// 		i++;
// 		j++;
// 	}

// 	result[i] = '\0';
// 	return result;
// }

int	env_len(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i);
}

int	get_end_dollar(char *str, int i)
{
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i - 1);
}

char	*get_env_str(char *str) // need to add shell_data struct
{
	char	*temp;
	char	*env;

	temp = malloc((sizeof(char) * 1) + env_len(str));
	if (temp == NULL)
	{
		// free_shell_data(shell_data); // to be written 
		// exit code and string to print
	}
	temp = ft_strcpy(temp, str, env_len(str));
	env = getenv(temp);
	if (env == NULL)
		return (ft_strdup(""));
	return (env);
}

char	*handle_dollar_sign(t_data **shell_data, char *str) // need to add shell_data struct
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
	{
		// free_shell_data(shell_data); // to be written
		// exit code and string to print
	}
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start_dollar = i;
			if (str[i + 1] == '?')
			{
				middle_to_add = ft_itoa((*shell_data)->exit_code);
				if (middle_to_add == NULL)
				{
					// free_shell_data(shell_data); // to be written
					// exit code and string to print
				}
				end_dollar = start_dollar + 1;
			}
			else if (str[i + 1] == '$')
			{
				middle_to_add = ft_itoa(getpid());
				if (middle_to_add == NULL)
				{
					// free_shell_data(shell_data); // to be written
					// exit code and string to print
				}
				end_dollar = start_dollar + 1;
			}
			else if (str[i + 1] != '\0' && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == ' '))
			{
				middle_to_add = get_env_str(str + i + 1);
				if (middle_to_add == NULL)
				{
					// free_shell_data(shell_data); // to be written
					// exit code and string to print
				}
				end_dollar = get_end_dollar(str, i + 1); // + 1 because i is the index of the dollar sign
			}
			temp = ft_strjoin(temp, middle_to_add);
			if (temp == NULL)
			{
				// free_shell_data(shell_data); // to be written
				// exit code and string to print
			}
			i = end_dollar + 1; // Jump to end_dollar
		}
		else
		{
			temp = ft_strjoin_c(temp, str[i]);
			if (temp == NULL)
			{
				// free_shell_data(shell_data); // to be written
				// exit code and string to print
			}
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
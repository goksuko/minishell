#include "../../includes/minishell.h"

//TO BE CONTINUED AT HOME!!
char *create_expanded_str(char *str, int len, char *expanded_str, int chars_to_remove)
{
	char	*temp;

	temp = malloc(sizeof(char *) * (len+ 1));
	if (temp == NULL)
	{
		// free_shell_data(shell_data); // to be written 
		// exit code and string to print
	}
	temp = ft_strcpy(temp, str, len);
	temp = ft_strjoin(temp, expanded_str);
	len+= chars_to_remove;
	temp = ft_strjoin(temp, str + len);
	printf("temp: %s\n", temp); // only for testing
	return (temp);
}

char	*handle_dollar_sign(t_data **shell_data, char *str) // need to add shell_data struct
{
	int		i;
	int		start_dollar;
	char	*temp;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			start_dollar = i;
			i++;
			printf("ONLY FOR TESTING str[i]: %c\n", str[i]);
			if (str[i] == '?')
			{
				temp = create_expanded_str(str, start_dollar, ft_itoa((*shell_data)->exit_code), 2);
				printf("temp: %s\n", temp); // only for testing
				//create a new string and remove the dollar sign and ? and replace with the exit code and add the rest of the string
			}
			// env function to write for rest
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
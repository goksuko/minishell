#include "../../includes/minishell.h"

//TO BE CONTINUED AT HOME!!
char *create_expanded_str(char *str, int i, char *expanded_str)
{
	char	*temp;

	temp = malloc(sizeof(char *) * (i + 1));
	if (temp == NULL)
	{
		free
	}
}

void	handle_dollar_sign(t_data **shell_data, t_tree **node, char *str) // need to add shell_data struct
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
			if (str[i] == '?')
			{
				temp = create_expanded_str(str, i, ft_itoa((*shell_data)->exit_code));
				//create a new string and remove the dollar sign and ? and replace with the exit code and add the rest of the string
			}
			if (strncmp(str + i, "HOME", 4) == 0)
			{
				//create a new string and remove the dollar sign and HOME and replace with the HOME path
				//need to access the HOME path from the shell_data struct
			}
			if (strncmp(str + i, "PWD", 3) == 0)
			{
				//create a new string and remove the dollar sign and PWD and replace with the PWD path
				//need to access the PWD path from the shell_data struct
			}
			if (strncmp(str + i, "VAR", 3) == 0)
			{
				//create a new string and remove the dollar sign and VAR and replace with the VAR path
				//need to access the VAR path from the shell_data struct
			}
		}
		i++;
	}
}

bool	dollar_sign_check(t_tree **node, char *str)
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
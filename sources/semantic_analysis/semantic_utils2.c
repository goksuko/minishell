#include "../../includes/minishell.h"

char *ft_strjoin_array(char **array, char c)
{
	char *joined;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (array[i])
	{
		j += ft_strlen(array[i]);
		i++;
	}
	joined = (char *)ft_calloc(sizeof(char), j + i + 1);
	if (!joined || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "joined in ft_strjoin_array");
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			joined[k] = array[i][j];
			j++;
			k++;
		}
		if (array[i + 1])
		{
			joined[k] = c;
			k++;
		}
		i++;
	}
	return (joined);
}

char *clean_redirects(char *long_command)
{
	char *long_corrected_command;
	char **splitted;
	int i;

	splitted = ft_split(long_command, ' ');
	if (!splitted || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "splitted in clean_redirects");
	i = 0;
	while (splitted[i])
	{
		if (ft_strnstr(splitted[i], ">", ft_strlen(splitted[i]))
			|| ft_strnstr(splitted[i], "<", ft_strlen(splitted[i]))
			|| ft_strnstr(splitted[i], ">>", ft_strlen(splitted[i])))
		{
			free(splitted[i]);
			splitted[i] = NULL;
			free(splitted[i + 1]);
			splitted[i + 1] = NULL;
		}
		i++;
	}
	long_corrected_command = ft_strjoin_array(splitted, ' ');
	return (long_corrected_command);
}
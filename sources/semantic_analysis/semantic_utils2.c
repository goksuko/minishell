#include "../../includes/minishell.h"

void	free_and_null(char *str)
{
	if (*str)
	{
		free(str);
		str = NULL;
	}
}

char	*ft_strjoin_array(char **array, char c)
{
	char	*joined;
	int		i;
	int		j;
	int		k;

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

char	*clean_redirects(char *long_command)
{
	char *long_corrected_command;
	char **splitted;
	char *temp;
	int i;

	splitted = ft_split(long_command, ' ');
	if (!splitted || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "splitted in clean_redirects");
	printf("Splitted before:\n");
	printf_array(splitted);
	i = 0;
	if (splitted[0][0] == '<' && ft_strlen(splitted[i]) == 1)
	{
		free_and_null(splitted[0]);
		splitted[0] = ft_strdup(splitted[2]);
		free_and_null(splitted[2]);
	}
	else if (splitted[0][0] == '<' && splitted[0][1] != '<'
		&& splitted[0][1] != '\0')
	{
		temp = ft_strdup(splitted[0] + 1);
		free(splitted[0]);
		splitted[0] = ft_strdup(splitted[1]);
		free(splitted[1]);
		splitted[1] = ft_strdup(temp);
		free(temp);
	}
	else
	{
		while (splitted[i])
		{
			printf("splitted[%d]: %s\n", i, splitted[i]);
			if ((ft_strnstr(splitted[i], ">>", 2)
					&& ft_strlen(splitted[i]) == 2) || (ft_strnstr(splitted[i],
						">", 1) && ft_strlen(splitted[i]) == 1)
				|| (ft_strnstr(splitted[i], "<<", 2)
					&& ft_strlen(splitted[i]) == 2) || (ft_strnstr(splitted[i],
						"<", 1) && ft_strlen(splitted[i]) == 1))
			{
				free(splitted[i]);
				splitted[i] = NULL;
				i++;
				free(splitted[i]);
				splitted[i] = NULL;
			}
			else if ((ft_strnstr(splitted[i], ">>", 2)
					&& ft_strlen(splitted[i]) > 2) || (ft_strnstr(splitted[i],
						">", 1) && ft_strlen(splitted[i]) > 1)
				|| (ft_strnstr(splitted[i], "<<", 2)
					&& ft_strlen(splitted[i]) > 2) || (ft_strnstr(splitted[i],
						"<", 1) && ft_strlen(splitted[i]) > 1))
			{
				free(splitted[i]);
				splitted[i] = NULL;
			}
			i++;
		}
	}
	printf("Splitted:\n");
	printf_array(splitted);
	long_corrected_command = ft_strjoin_array(splitted, ' ');
	return (long_corrected_command);
}
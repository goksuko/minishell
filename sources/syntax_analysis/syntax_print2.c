#include "../../includes/minishell.h"

void	printf_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

const char	*node_type_to_string(t_node_type type)
{
	static const char	*str[] = {
	[N_COMMAND] = "COMMAND",
	[N_PIPE] = "PIPE",
	};

	if (type != N_COMMAND && type != N_PIPE)
		return ("UNKNOWN");
	return (str[type]);
}

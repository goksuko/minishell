/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_print2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:19 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/24 11:54:36 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_array(char **array)
{
	int	i;

	i = 0;
	if (*array == NULL)
	{
		printf("!!!!!!! Array is NULL !!!!!\n\n");
		return ;
	}
	while (array[i] != NULL)
	{
		printf("%d: %s\n", i, array[i]);
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

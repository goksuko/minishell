/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_sign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 15:49:58 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/24 15:49:58 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_str(char *to_update, char *str_to_add)
{
	char	*temp;

	temp = ft_strjoin(to_update, str_to_add);
	free(to_update);
	// free(str_to_add); commented out for now for memory check purposes
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*add_char(char *to_update, char char_to_add)
{
	char	*temp;

	temp = ft_strjoin_c(to_update, char_to_add);
	free(to_update);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

bool	dollar_in_loop(t_data *data, char **new, char *str, int *i)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	temp = process_dollar_sign(data, &str[*i], i);
	if (temp == NULL)
		return (false);
	*new = add_str(*new, temp);
	free(temp);
	if (*new == NULL)
		return (false);
	return (true);
}

char	*handle_dollar_sign(t_data *data, char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (dollar_in_loop(data, &new, str, &i) == false)
			{
				free (new);
				return (NULL);
			}
			continue ;
		}
		new = add_char(new, str[i]);
		if (new == NULL)
			return (NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 11:53:13 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/27 11:58:31 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_array(char **array) // for debugging
{
	int	i;

	if (!array)
	{
		printf("Array is NULL\n");
		return ;
	}
	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

bool	is_file_check(t_data *data, t_token *token_lst)
{
	t_token	*current;

	current = token_lst;
	while (current != NULL)
	{
		if (is_redir(current) == true)
			if (define_token_fd(data, current) == false)
				return (false);
		current = current->next;
	}
	return (true);
}

t_token	*lexical_analysis(t_data *data, char *line)
{
	char	**tokens;
	t_token	*token_lst;

	if (ft_strncmp(line, " ", 1) == 0 && ft_strlen(line) == 1)
	{
		free_system(data);
		data->exit_code = 0;
		return (NULL);
	}
	if (meta_character_check(data, line) == false)
	{
		free_system_error(data, ERROR_META);
		return (NULL);
	}
	tokens = create_token_array(data, line);
	if (tokens == NULL)
		return (NULL);
	token_lst = create_token_list(data, tokens);
	if (token_lst == NULL)
		return (NULL);
	if (is_file_check(data, token_lst) == false)
		return (NULL);
	return (token_lst);
}

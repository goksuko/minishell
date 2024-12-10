/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_funcs2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 12:02:00 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/25 13:55:40 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_unlink(t_data *data, char *file)
{
	if (!data->info->limiter)
		return ;
	if (unlink(file) < 0)
		ft_exit_perror(data, ERROR_UNLINK);
	return ;
}

void	**ms_calloc(t_data *data, size_t nmemb, size_t size)
{
	void	**ptr;

	ptr = ft_calloc(nmemb, size);
	if (ptr == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (ptr);
}

char	*ms_strjoin(t_data *data, const char *s1, const char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (str == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (str);
}

char	*ms_strjoin_with_free_1st(t_data *data, char *s1, const char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (str == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	free_and_null(&s1);
	return (str);
}

char	*ms_strdup(t_data *data, const char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (str == NULL)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (str);
}

char	**ms_split(t_data *data, char const *s, char c)
{
	char	**array;

	array = ft_split(s, c);
	if (array == NULL || errno == ENOMEM)
		ft_exit_perror(data, ERROR_ALLOCATION);
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 12:24:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/14 22:09:53 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_unclosed_quotes(t_token *token_lst)
{
    t_token	*current;
    char	quote;

    current = token_lst;
    while (current != NULL)
    {
        if (is_quote(current->value[0]) == true)
        {
            quote = current->value[0];
            if ((current->value[ft_strlen(current->value) - 1]) != quote)
                ft_exit_str_fd(ERROR_QUOTE, STDERR_FILENO);
        }
        current = current->next;
    }
}
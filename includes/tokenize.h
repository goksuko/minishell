/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:39:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/23 14:39:03 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef enum s_token_type // ADJUST AS NECESSARY
//NOT SURE IF I SHOULD ADD METACHARACTERS see: https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation
{
	TOKEN_COMMAND, //echo (with option -n), cd, pwd, export, unset, env, exit, etc.
    TOKEN_ARGUMENT, //path for cd, variables for export, and unset
	TOKEN_FLAG, // e.g. echo -n
    TOKEN_REDIRECTION, // <, <<, >, >>
    TOKEN_PIPE, // |
	TOKEN_O_QUOTES, // single quotes and double quotes opening --NOT interpret unclosed characters
	TOKEN_C_QUOTES, //single quotes and double quotes closing 
	TOKEN_LITERAL, // for strings within quotation marks?
	TOKEN_ENV_VARIABLE, // $VAR, or $?
    TOKEN_UNKNOWN // anyhting not defined and not categorized in tokens
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Token list utils
t_token	*ft_token_new(char *str, t_token_type type);
void	ft_token_lst_add_back(t_token **tokens, t_token *new_token);
t_token	*ft_token_last(t_token *token);
void	ft_print_tokens(t_token *tokens);

#endif

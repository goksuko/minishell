/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
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

// Tokens
char	**create_tokens(char *line);
void	check_characters(char *line);
int		count_tokens(char *line);
// char	**split_tokens(char *line, int number_tokens);
char	**split_tokens(char *line, int number_tokens, char **tokens);
char	*substring_from_quote(char *line, int *i);

// Tokens Utils
bool	is_meta(char c);
bool	is_quote(char c);
int 	skip_whitespace(char *line, int i);
char	*ft_strcpy(char *dest, char *src, int len);
int		skip_quotes(char *line, int i);

// Meta character check
bool	further_meta_check(char *line, int i, char meta);
bool	meta_character_check(char *line);

#endif

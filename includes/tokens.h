/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:39:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/12 21:30:26 by vbusekru      ########   odam.nl         */
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
	TOKEN_QUOTES, // single quotes and double quotes opening --NOT interpret unclosed characters
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
	struct s_token	*head;
	struct s_token	*tail;
}	t_token;

// Tokens
char	**create_tokens(char *line);
void	check_characters(char *line);
int		count_tokens(char *line);
char	**split_tokens(char *line, int number_tokens, char **tokens);
t_token	*array_to_list(t_token **token_lst, char **tokens);

// Tokens Utils
bool	is_meta(char c);
bool	is_quote(char c);
void 	skip_whitespace(char *line, int *i);
char	*ft_strcpy(char *dest, char *src, int len);
void	skip_quotes(char *line, int *i);
void	skip_meta(char *line, int *i);
void	free_2d_array(char **tokens);

// Meta character check
bool	further_meta_check(char *line, int i, char meta);
bool	meta_character_check(char *line);

// Token list utils
t_token	*init_list(void);
void	ft_print_tokens(t_token *tokens);
t_token	*ft_token_new(char *str, t_token_type type);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:39:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/14 22:10:07 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef enum s_token_type // ADJUST AS NECESSARY
//NOT SURE IF I SHOULD ADD METACHARACTERS see: https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation
{
	T_COMMAND, //echo (with option -n), cd, pwd, export, unset, env, exit, etc.
    T_ARGUMENT, //path for cd, variables for export, and unset
	T_FLAG, // e.g. echo -n
    T_REDIRECTION, // <, <<, >, >>
    T_PIPE, // |
	T_DOUBLE_QUOTES, // single quotes and double quotes opening --NOT interpret unclosed characters
	T_SINGLE_QUOTES, // single quotes and double quotes opening --NOT interpret unclosed characters
	T_ENV_VARIABLE, // $VAR, or $?
    T_UNKNOWN // anything not defined and not categorized in tokens
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Tokens
t_token	*lexical_analysis(char *line); // new
void	check_characters(char *line);
int		count_tokens(char *line);

// Splt Tokens
void	split_tokens(char *line, int number_tokens, t_token **token_lst); //NEW
t_token	*create_and_link_token(char *line, t_token *prev);
void	link_new_token(t_token *new_token, t_token *prev);
t_token	*create_new_token(char *substr);
char	*create_substr_and_update_token_start(char *line, \
		int *token_start, int *token_len);
int		len_new_token(char *line, int i);
void	new_token_start(char *line, int *i);
char	*create_substr(char *line, int len);

// Tokens Utils
bool	is_meta(char c);
bool	is_quote(char c);
void 	skip_whitespace(char *line, int *i);
char	*ft_strcpy(char *dest, char *src, int len);
void	skip_quotes(char *line, int *i);
void	skip_meta(char *line, int *i);
void	check_unclosed_quotes(t_token *token_lst);

// Meta character check
bool	further_meta_check(char *line, int i, char meta);
bool	meta_character_check(char *line);

// Token list utils
t_token	*init_list(void);
void	ft_print_tokens(t_token *tokens);
t_token	*ft_token_new(char *str, t_token_type type);
void	free_list_line_exit(t_token **tokens_lst, char *line);
void	free_list(t_token **tokens);

// Token types check
const char		*token_type_to_string(t_token_type type);
t_token_type	token_type_check(char *token);
t_token_type	check_flag(char *token);
t_token_type	check_pipes(char *token);
t_token_type	check_redirection(char *token);
t_token_type	check_env_variable(char *token);
t_token_type	check_command(char *token);
t_token_type	check_double_quotes(char *token);
t_token_type	check_single_quotes(char *token);

#endif

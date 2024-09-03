/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:39:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 19:30:16 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef enum s_token_type // ADJUST AS NECESSARY
//NOT SURE IF I SHOULD ADD METACHARACTERS see: https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation
{
	T_BUILTIN, //echo (with option -n), cd, pwd, export, unset, env, exit, etc.
    T_IDENTIFIER, //path for cd, variables for export, and unset
	T_FLAG, // e.g. echo -n
    T_SMALLER, // <
	T_DSMALLER, // <<
	T_GREATER, // >
	T_DGREATER,// >>
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
t_token	*lexical_analysis(char *line);
void	check_characters(char *line);
int		count_tokens(char *line);
char	**create_token_array(char *line);
t_token	*create_token_list(char **token_array);

// Splt Tokens
char	**split_tokens(char *line, int number_tokens, char **tokens);
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
void    free_array_exit(char **arrray);
void	free_array(char **array);
bool	line_is_empty(char *line);

// Meta character check
bool	further_meta_check(char *line, int i, char meta);
bool	meta_character_check(char *line);

// Token list utils
t_token	*init_list(void);
void	ft_print_tokens(t_token *tokens);
t_token	*ft_token_new(char *str, t_token_type type);
void	free_list(t_token **tokens);
void	free_list_array_exit(t_token *tokens_lst, char **array);

// Token types check
char		*token_type_to_string(t_token_type type);
t_token_type	token_type_check(char *token);
t_token_type	check_flag(char *token);
t_token_type	check_pipes(char *token);
t_token_type	check_redirection(char *token);
t_token_type	check_env_variable(char *token);
t_token_type	check_command(char *token);
t_token_type	check_double_quotes(char *token);
t_token_type	check_single_quotes(char *token);

#endif

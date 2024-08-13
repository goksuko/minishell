/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:39:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/13 19:01:08 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

typedef enum s_token_type // ADJUST AS NECESSARY
//NOT SURE IF I SHOULD ADD METACHARACTERS see: https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation
{
	COMMAND, //echo (with option -n), cd, pwd, export, unset, env, exit, etc.
    ARGUMENT, //path for cd, variables for export, and unset
	FLAG, // e.g. echo -n
    REDIRECTION, // <, <<, >, >>
    PIPE, // |
	DOUBLE_QUOTES, // single quotes and double quotes opening --NOT interpret unclosed characters
	SINGLE_QUOTES, // single quotes and double quotes opening --NOT interpret unclosed characters
	ENV_VARIABLE, // $VAR, or $?
    UNKNOWN // anything not defined and not categorized in tokens
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
char	**lexical_analysis(char *line);
void	check_characters(char *line);
int		count_tokens(char *line);
char	**split_tokens(char *line, int number_tokens, char **tokens);
void	array_to_list(t_token **token_lst, char **tokens);

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
void	free_list_array_exit(t_token *tokens_lst, char **array);
void	free_list(t_token *tokens);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_sem.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:39:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/25 10:21:35 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_SEM_H
# define LEXER_SEM_H

typedef enum s_token_type
{
	T_BUILTIN,
	T_IDENTIFIER,
	T_FLAG,
	T_SMALLER,
	T_DSMALLER,
	T_GREATER,
	T_DGREATER,
	T_PIPE,
	T_DOUBLE_QUOTES,
	T_SINGLE_QUOTES,
	T_UNKNOWN
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*expanded_value;
	// !! needs to be initialized and freed properly but to be aligned with goksu's code!!
	struct s_token	*next;
	struct s_token	*prev;
	int				token_count;
	int				fd_in;
	int				fd_out;
	int				here_doc_fd;
	bool			is_head;
	char			*limiter;
}					t_token;

// Lexical

t_token				*lexical_analysis(t_data *data, char *line);
bool				is_file_check(t_data *data, t_token *token_lst);

// Tokens
int					count_tokens(char *line);
char				**create_token_array(t_data *data, char *line);
t_token				*create_token_list(t_data *data, char **token_array);
bool				is_redir(t_token *current);
bool				is_redir_except_heredoc(t_token *current);
bool				is_heredoc(t_token *current);
bool				heredoc_inside(t_token *current);
int					heredoc_position(t_token *current);

// Splt Tokens
char				**split_tokens(char *line, int number_tokens,
						char **tokens);
int					len_new_token(char *line, int i);
void				new_token_start(char *line, int *i);
char				*create_substr(char *line, int len);

// Tokens Utils
bool				is_meta(char c);
bool				is_quote(char c);
void				skip_whitespace(char *line, int *i);
char				*ft_strcpy(char *dest, char *src, int len);
void				skip_quotes(char *line, int *i);
void				skip_meta(char *line, int *i);
bool				check_unclosed_quotes(t_data *data, t_token *token_lst);
void				free_token_list(t_token **tokens);
bool				line_is_empty(char *line);
bool				line_is_whitespace(char *line);
int					ft_isspace(int c);

// Meta character check
bool				further_meta_check(char *line, int i, char meta);
bool				meta_character_check(t_data *data, char *line);

// Token list utils
void				ft_print_tokens(t_token *tokens);
t_token				*init_new_token(char *str, t_token_type type,
						int token_count);
t_token				*array_to_list(char **tokens, int token_count);
void				free_matrix(char **matrix);

// Token types check
char				*token_type_to_string(t_token_type type);
t_token_type		token_type_check(char *token);
t_token_type		check_flag(char *token);
t_token_type		check_pipes(char *token);
t_token_type		check_redirection(char *token);
t_token_type		check_command(char *token);
t_token_type		check_double_quotes(char *token);
t_token_type		check_single_quotes(char *token);

// define_tokens

bool				define_token_fd(t_data *data, t_token *token);
bool				define_smaller(t_data *data, t_token *token);
bool				define_greater(t_data *data, t_token *token);
bool				define_dsmaller(t_data *data, t_token *token);
bool				define_dgreater(t_data *data, t_token *token);

//  cmds_from_tokens.c
t_token				*redir_first(t_token *current);
// char				*do_cat_addition(t_data *data, t_token *current, char *cmd);
bool				is_first_after_pipe(t_token *current);
char				**cmds_between_pipes(t_data *data, char **cmds);
char				**cmds_from_tokens(t_data *data);
bool				is_redir_inside(t_token *current);

// cmds_between_pipes.c
bool				handle_heredoc(t_data *data, t_token **current, char **cmds, int *j);
bool				handle_redirection(t_token **current, bool *cat_cmd, bool *no_cmd);
char				*handle_redirection2(t_data *data, t_token **current, bool *cat_cmd);
bool				handle_command(t_data *data, t_token **current, char **cmds, int *j);
bool				handle_loop(t_data *data, t_token **current, char **cmds, int *j);

// semantic.c
bool				handle_infile(t_data *data, t_info *info, int i, t_token *current);
bool				handle_outfile(t_data *data, t_info *info, int i, t_token *current);
void				initialize_fds_array(t_info *info);
bool				initialize_fds(t_info *info, t_data *data);
bool				semantic_analysis(t_data *data);

// semantic_utils.c
int					find_pipe_count(t_token *tokens);
void				initialize_info(t_info *info, t_data *data);

// heredoc_semantic.c
bool				limiter_check(t_data *data);
int					here_doc_fd_check(t_data *data);
bool				init_heredoc(t_data *data);

#endif

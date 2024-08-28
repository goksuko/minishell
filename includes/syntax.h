#ifndef SYNTAX_H
# define SYNTAX_H

# include "lexer.h"

typedef enum e_redirection_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_UNKNOWN
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		redirection_type;
	char					*file;
	char					**expanded_file;
	bool					here_doc;
	struct s_redirection	*next;
	struct s_redirection	*prev;
}	t_redirection;

typedef enum e_node_type
{
	N_COMMAND,
	N_PIPE,
}	t_node_type;

typedef struct s_tree
{
	t_node_type			type;
	t_redirection		*redirection;
	char				*argument;
	char				**expanded_argument;
	struct s_tree		*left;
	struct s_tree		*right;
}	t_tree;

// Syntax Analysis
t_tree				*syntax_analysis(t_token *tokens);
t_tree				*parse_tokens(t_token **tokens);
void				join_arguments(t_tree **node, t_token **token);
t_tree				*get_command_node(t_token **tokens);
t_tree				*combine_nodes(t_tree *left, t_tree *right);

// Utils
t_tree				*init_node(t_node_type type);
bool				redirection_check(t_token *current);
void				next_token(t_token **tokens);

// Printing utils
void				print_ast(t_tree *ast);
const char			*node_type_to_string(t_node_type type); // to be deleted later
const char			*redirection_type_to_string(t_redirection_type type); // only for testing purposes
void				ft_print_redirection(t_redirection *redirection_lst); // Only for testing purposes
void				printf_array(char **array);

// Redirections
void				handle_redirection(t_redirection **redirection_lst, \
		t_token **token, t_tree **node);
t_redirection		*init_redirection(t_tree **tree, t_token **token);
t_redirection_type	check_redirection_type(t_token_type type);
void				append_new_redir_node(t_redirection **list, t_redirection *new);

// Free and exit
void				free_list_tree_syntax_exit(t_token **tokens, t_tree **tree);
void 				free_list_tree_alloc_exit(t_token **tokens, t_tree **tree);
void				free_redirection_list(t_redirection **redirection);
void    			free_tree(t_tree **tree);
void				free_list_exit(t_token **tokens);

#endif
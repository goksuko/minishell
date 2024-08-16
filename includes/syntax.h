#ifndef SYNTAX_H
# define SYNTAX_H

# include "lexer.h"

typedef struct s_tree
{
	t_token_type	type;
	char			*value;
	struct s_tree	*prev;
	struct s_tree	*next;
}	t_tree;

t_tree	*syntax_analysis(t_token *tokens);

#endif
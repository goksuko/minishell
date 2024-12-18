#ifndef EXPANSION_H
# define EXPANSION_H

# include "lexer_sem.h" //added because of compilation error

bool	expander(t_data **data);
bool	expand_value(t_data **data, t_token *token, char *type);

// Quotes
char	*s_quotes(t_data **data, char *argument);
char	*d_quotes(t_data **data, char *argument);
char	*remove_quotation_marks(char *argument);
char	*expand_identifier(t_data **data, char *argument);

// Dollar sign
bool	dollar_sign_check(char *str);
char	*handle_dollar_sign(t_data *data, char *str);
char	*add_char(char *to_update, char char_to_add);
char	*add_str(char *to_update, char *str_to_add);
char	*process_dollar_sign(t_data *data, char *str, int *i);
char	*expand_env_variable(t_data *data, char *str, int *i);
char	*expand_pid(int *i);
char	*expand_exit_code(t_data *data, int *i);
char	*get_env_str(t_data *data, char *str, int *index);

// Utils
char	*ft_strjoin_c(char const *s1, char c);

#endif
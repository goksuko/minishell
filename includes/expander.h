#ifndef EXPANSION_H
# define EXPANSION_H

bool	expander(t_data **data);
bool	expand_value(t_data **data, t_token *token, char *type);

// Quotes
char	*s_quotes(t_data **data, char *argument);
char	*d_quotes(t_data **data, char *argument);
char	*remove_quotation_marks(char *argument);
char	*expand_identifier(t_data **data, char *argument);

// Dollar sign
bool	dollar_sign_check(char *str);
char	*handle_dollar_sign(t_data **data, char *str);
int		get_end_dollar(char *str, int i);
char	*get_env_str(t_data *data, char *str);
char	*ft_strjoin_c(char const *s1, char c);
char	*dollar_exit_code(t_data *data, int start_dollar, int *end_dollar);
char	*dollar_pid(int start_dollar, int *end_dollar);
char	*dollar_env_value(t_data *data, char *str, int *end_dollar, int i);
char	*handle_dollar_sign(t_data **data, char *str);

#endif
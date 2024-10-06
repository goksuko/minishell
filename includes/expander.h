#ifndef EXPANSION_H
# define EXPANSION_H

void	expander(t_data **shell_data);
void	expand_value(t_data **shell_data, t_token *token, char *type);

// Quotes
char	*s_quotes(t_data **shell_data, char *argument);
char	*d_quotes(t_data **shell_data, char *argument);
char	*remove_quotation_marks(char *argument);
char	*expand_identifier(t_data **shell_data, char *argument);

// Dollar sign
bool	dollar_sign_check(char *str);
char	*handle_dollar_sign(t_data **shell_data, char *str);
int		get_end_dollar(char *str, int i);
char	*get_env_str(t_data *shell_data, char *str);
char	*ft_strjoin_c(char const *s1, char c);

#endif
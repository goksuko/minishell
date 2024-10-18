#include "../includes/minishell.h"

char *ft_strjoin_c_safe(t_data *data, char *s1, char c)
{
    char	*str;
    
    str = ft_strjoin_c(s1, c);
    if (errno == ENOMEM || str == NULL)
    {
        free_system_perror(data, ERROR_ALLOCATION, "str in ft_strjoin_c_safe");
    }
    return (str);
}

char *ft_strjoin_safe(t_data *data, char *s1, char *s2)
{
    char	*str;
    
    str = ft_strjoin(s1, s2);
    if (errno == ENOMEM || str == NULL)
    {
        free_system_perror(data, ERROR_ALLOCATION, "str in ft_strjoin_safe");
    }
    return (str);
}

char *ft_strdup_safe(t_data *data, char *s1)
{
    char	*str;
    
    str = ft_strdup(s1);
    if (errno == ENOMEM || str == NULL)
    {
        free_system_perror(data, ERROR_ALLOCATION, "str in ft_strdup_safe");
    }
    return (str);
}


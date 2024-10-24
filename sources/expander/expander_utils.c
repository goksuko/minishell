#include "../../includes/minishell.h"

char	*remove_quotation_marks(char *argument) // ADJUSTED 
{
	printf("----REMOVE_QUOTATION_MARKS----\n");
	char	*clean_str;
	int		len;

	len = ft_strlen(argument);
	if (len < 2)
		return (ft_strdup(argument));
	clean_str = (char *)ft_calloc(sizeof(char), len - 2 + 1);
	if (clean_str == NULL)
		return (NULL);
	ft_strlcpy(clean_str, argument + 1, len - 1);
	printf("--Remove quotation marks done--\n");
	return (clean_str);
}

char	*ft_strjoin_c(char const *s1, char c)
{
	char *new_str;
	char *temp;

	temp = NULL;
	new_str = NULL;
	if (s1 == NULL)
		return (NULL);
	new_str = (char *)ft_calloc((ft_strlen(s1) + 2), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	temp = new_str;
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	new_str += ft_strlen(s1);
	*new_str = c;
	return (temp);
}
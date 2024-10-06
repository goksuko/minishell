#include "../../includes/minishell.h"

char	*remove_quotation_marks(char *argument)
{
	printf("----REMOVE_QUOTATION_MARKS----\n");
	char	*clean_str;

	clean_str = (char *)malloc(sizeof(char) * ((ft_strlen(argument) - 2) + 1));
	if (clean_str == NULL)
		return (NULL);
	clean_str = ft_strcpy(clean_str, argument + 1, ft_strlen(argument) - 2);
	return (clean_str);
}

char	*ft_strjoin_c(char const *s1, char c)
{
	char	*new_str;
	char	*temp;

	if (s1 == NULL)
		return (NULL);
	new_str = (char *)ft_calloc((ft_strlen(s1)
				+ 1 + 1), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	temp = new_str;
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	new_str += ft_strlen(s1);
	*new_str = c;
	return (temp);
}
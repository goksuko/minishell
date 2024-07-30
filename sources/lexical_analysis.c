/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/29 18:09:20 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while(src[i] != '\0' && len != 0)
	{
		dest[i] = src[i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	**split_tokens(char *line, int number_tokens)
{
	printf("Split tokens.\n"); // to remove later
	char	**tokens;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (line[i] != '\0')
	{
		while(is_whitespace(line[i]) == true && line[i] != '\0')
			i++;
		j = i;
		while (is_whitespace(line[i]) == false && line[i] != '\0')
			i++;
		if (i > j)
		{
			tokens[k] = malloc((i - j + 1) * sizeof(char));
			if (tokens[k] == NULL)
			{
				while (k-- != 0) // not sure if it should be greater than -1 as I am unsure if 0 also gets freed;
					free(tokens[k]);
				free(tokens);
				return (NULL);
			}
			tokens[k] = ft_strcpy(tokens[k], &line[j], i - j); // write strcpy function
			k++;
		}
	}
	tokens[k] = NULL;
	return (tokens);
}

int	count_tokens(char *line)
{
	printf("Count tokens\n"); // to remove later
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		while (is_whitespace(line[i]) == true && line[i] != '\0')
			i++;
		if (line[i] != '\0')
		{
			count++;
			printf("Token count: %d\n", count);
			printf("%c\n", line[i]);
		}
		while (is_whitespace(line[i]) == false && line[i] != '\0')
			i++;
	}
	printf("Final token count: %d\n", count); // to remove later
	return (count);
}

bool	further_meta_check(char *line, int i, char meta)
{
	printf("Further meta check\n"); // to remove later
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (false);
	else
	{
		if (meta == '>' && line[i] == '>' && line[i + 1] == ' ' && line[i + 1] != '\0') // not sure if +1 works here or if +2 is needed
			return (true);
		if (meta == '>' && line[i] == ' ' && line[i + 1] != '\0')
			return (true);
		if (meta == '<' && line[i] == '<' && line[i + 1] == ' ' && line[i + 1] != '\0') // not sure if +1 works here or if +2 is needed
			return (true);
		if (meta == '<' && line[i] == ' ' && line[i + 1] != '\0')
			return (true);
		if (meta == '|' && line[i] == ' ' && line[i + 1] != '\0')
			return (true);
		if (meta == '|' && line[i] == '|')
			return (false);
	}
	return (false);
}

bool	meta_character_check(char *line)
{
	printf("Meta character check\n"); // to remove later
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		while (is_whitespace(line[i]) == true)
			i++;
		//write(1, &line[i], 1);
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i]; // just so quote has the same character and we can compare after 
			while (line[i] != '\0' && line[i] != quote)
				i++;
			if (line[i] == '\0')
				return(false);
		}
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if (further_meta_check(line, i + 1, line[i]) == false)
				return (false);
		}
		i++;
	}
	return (true);
}

// void	check_characters(char *line)
// {
// 	int	i;
// 	int	count;
// 	int	wrong_char;

// 	ft_printf("check_characters\n");
// 	count = 0;
// 	i = 0;
// 	wrong_char = 0;
// 	while (line && line[i])
// 	{
// 		if (line[i] == '"') // make sure it does not handle unclosed quotes
// 			count++;
// 		if (line[i] == '\\' || line[i] == ';')
// 			wrong_char++;
// 		i++;
// 	}
// 	if (count % 2 != 0)
// 		ft_exit_str_free_fd((ERROR_QUOTE), line, STDERR_FILENO);
// 	if (wrong_char)
// 		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
// 	return ;
// }

char	*clean_up_string(char *line)
{
	char	*clean_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean_string = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (clean_string == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (is_whitespace(line[i]) == true)
		i++;
	while (line[i] != '\0')
	{
		if (is_whitespace(line[i]) == false)
			clean_string[j++] = line[i++];
		else
		{
			if (line[i] != '\0')
				clean_string[j++] = ' ';
			while (is_whitespace(line[i]) == true)
				i++;
		}
	}
	clean_string[j] = '\0';
	free(line);
	return (clean_string);
}

char	**lexical_analysis(char *line)
{
	char	**tokens;
	int		number_tokens;
	char	*clean_line;

	if (line[0] == '\0')
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	clean_line = clean_up_string(line);
	printf("Cleaned up string: %s\n", clean_line); //  to be removed later
	// check_characters(clean_line);
	if (meta_character_check(clean_line) == false)
		ft_exit_str_free_fd(ERROR_META, clean_line, STDERR_FILENO);
	number_tokens = count_tokens(clean_line);
	tokens = split_tokens(clean_line, number_tokens);
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (tokens != NULL) // to remove later
	{
		printf("%s\n", *tokens);
		free(*tokens);
		tokens++;
	}
	printf("Tokenization done\n");// to remove later
	return (tokens);
}


// 1. Input preprocessing: cleaning up the input text and preparing it for
	// the lexical analysis. E.g. removing comments, whitespaces and other non-essential characters
	// 2. Tokenization: breaking the input text into a sequence of tokens. Usually done by
	// matching the characters in the input text against a set of patterns or regular expressions
	// that define the different types of tokens
	// 3. Token classification: lexer determines the type of each token. 
	// E.g., keywords, identifiers, operators, and punctuation 
	// 4. Token validation: lexer checks that each token is valid according to the rules of the programming languague
	// E.g. migt check that a variable name is a valid identifier, or that an operator has correct syntax
	// 5. Output generation: lexer generates the output of the lexical analysis process, which is typically a list of tokens
	// list of tokens can be passed to the next stage, such as compilation or interpretation
	// 6. Lexical analyzer identifies the error with the help of the grammar of the C language, and gives
	// it row number and column number of the error
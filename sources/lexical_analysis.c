/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analysis.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/02 12:41:42 by vbusekru      ########   odam.nl         */
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

// Helper function to skip whitespace
int skip_whitespace(char *line, int i)
{
    while (is_whitespace(line[i]) == true && line[i] != '\0')
        i++;
    return i;
}

int	handle_quotes(char *line, int i, char quote_char)
{
	while (line[i] != '\0' && line[i] != quote_char)
		i++;
	if (line[i] == quote_char) // not sure about this
		i++;
	return (i);
}

char	*substring_from_quote(char *line, int *i)
{
	char	*substring;
	int		j;
	char	quote_char;

	quote_char = line[*i];
	j = *i;
	while (line[*i] != '\0' && line[*i] != quote_char)
		i++;
	if (line[*i] == quote_char)
	{
		substring = malloc((*i - j + 1) * sizeof(char));
		if (substring == NULL)
			return (NULL);
		substring = ft_strcpy(substring, &line[j], *i - j);
		i++;
		return (substring);
	}
	return (NULL);
}

char	**split_tokens(char *line, int number_tokens)
{
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
		i = skip_whitespace(line, i);
		j = i;
		if (line[i] == '\'' || line[i] == '\"')
			tokens[k] = substring_from_quote(&line[j], &i); //NULL check needed
		else
		{
			while (is_whitespace(line[i]) == false && line[i] != '\0')
				i++;
		}
		if (i > j)
		{
			tokens[k] = malloc((i - j + 1) * sizeof(char));
			if (tokens[k] == NULL)
			{
				while (--k >= 0)
					free(tokens[k]);
				free(tokens);
				return (NULL);
			}
			tokens[k] = ft_strcpy(tokens[k], &line[j], i - j);
			printf("Token %d:%s\n", k, tokens[k]); // to remove later
			k++;
		}
	}
	tokens[k] = NULL;
	return (tokens);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	is_meta(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

int	handle_quotes // need to write function 

int	count_tokens(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		while (is_whitespace(line[i]) == true && line[i] != '\0')
			i++;
		if (line[i] != '\0' && is_whitespace(line[i]) == false)
		{
			if (is_quote(line[i]) == true)
			{
				count++;
				i = handle_quotes(line, i, line[i]);
			}
			while (line[i] != '\0' && line[i] != quote_char)
				i++;
		}
		if (line[i] != '\0' && is_whitespace(line[i]) == false)
		{
			count++;
			while (is_whitespace(line[i]) == false && line[i] != '\0')
				i++;
		}
	}
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
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		i = skip_whitespace(line, i);
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

void	check_characters(char *line)
{
	int	i;
	int	count_single_quote;
	int	count_double_quote;
	int	wrong_char;

	count_single_quote = 0;
	count_double_quote = 0;
	i = 0;
	wrong_char = 0;
	while (line && line[i])
	{
		if (line[i] == '\'')
			count_single_quote++;
		else if (line[i] == '\"')
			count_double_quote++;
		else if (line[i] == '\\' || line[i] == ';')
			wrong_char++;
		i++;
	}
	if (count_single_quote % 2 != 0 || count_double_quote % 2 != 0)
		ft_exit_str_free_fd((ERROR_QUOTE), line, STDERR_FILENO);
	if (wrong_char)
		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
	return ;
}

char	**lexical_analysis(char *line)
{
	char	**tokens;
	int		number_tokens;

	if (line[0] == '\0')
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	printf("Check characters\n"); // to be removed later
	check_characters(line);
	printf("Meta character check\n"); // to remove later
	if (meta_character_check(line) == false)
		ft_exit_str_free_fd(ERROR_META, line, STDERR_FILENO);
	number_tokens = count_tokens(line);
	printf("Number of tokens: %d\n", number_tokens); // to be removed later
	printf("Split tokens.\n"); // to remove later
	tokens = split_tokens(line, number_tokens);
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
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
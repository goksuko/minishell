/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/04 15:50:11 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens(char *line) 
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		i = skip_whitespace(line, i);
		if (line[i] != '\0' && is_whitespace(line[i]) == false && is_quote(line[i]) == false && is_meta(line[i]) == false)
		{
			count++;
			while(line[i] != '\0' && is_whitespace(line[i]) == false)
				i++;
		}
		if (line[i] != '\0' && is_whitespace(line[i]) == false)
		{
			count++;
			if (is_quote(line[i]) == true)
				i = skip_quotes(line, i);
			else if (is_meta(line[i]) == true)
				i = skip_meta(line, i, line[i]);
		}
		i++;
	}
	return (count);
}

void	check_characters(char *line)
{
	int	i;
	// int	count_single_quote;
	// int	count_double_quote;
	int	wrong_char;

	// count_single_quote = 0;
	// count_double_quote = 0;
	i = 0;
	wrong_char = 0;
	while (line && line[i])
	{
		// if (line[i] == '\'')
		// 	count_single_quote++;
		// else if (line[i] == '\"')
		// 	count_double_quote++;
		if (line[i] == '\\' || line[i] == ';')
			wrong_char++;
		i++;
	}
	// if (count_single_quote % 2 != 0 || count_double_quote % 2 != 0)
		// ft_exit_str_free_fd((ERROR_QUOTE), line, STDERR_FILENO);
	if (wrong_char)
		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
	return ;
}

char	**create_tokens(char *line)
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
	printf("Count tokens\n");
	number_tokens = count_tokens(line);
	printf("Number of tokens: %d\n", number_tokens); // to be removed later
	printf("Split tokens.\n"); // to remove later
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	tokens = split_tokens(line, number_tokens, tokens);
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
#include <expander.h>
#include <libft.h>
#include <parse.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Handle quotes to toggle the quote status
void	ft_handle_quotes(char quote, enum e_quotes_type *quotes_type)
{
	if (quote == '\'')
	{
		if (*quotes_type == no_quotes)
			*quotes_type = single_quote;
		else if (*quotes_type == single_quote)
			*quotes_type = no_quotes;
	}
	else if (quote == '\"')
	{
		if (*quotes_type == no_quotes)
			*quotes_type = double_quotes;
		else if (*quotes_type == double_quotes)
			*quotes_type = no_quotes;
	}
}

/**
 * @brief Copies a null-terminated string from `src` to `dest`.
 *
 * Copies the characters from `src` into `dest`, including the null terminator.

	* The caller must ensure that `dest` has enough space to hold the copied string.
 *
 * @param dest Pointer to the destination buffer.
 * @param src Pointer to the source string.
 * @return char* Pointer to the destination buffer (`dest`).
 */
char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	if (!dest || !src)
		return (NULL);
	while ((*dest++ = *src++) != '\0')
		; // Copy each character, including the null terminator
	return (dest_start);
}

/**
 * @brief Processes unquoted content to calculate length, detect quotes,
 *        and check for environment variables.
 *
 * @param content Pointer to the string content.
 * @param envar Pointer to a boolean to flag the presence of `$`.
 * @param quotes Pointer to a boolean to flag the presence of quotes.
 * @return size_t Length of the unquoted content.
 */
static size_t	process_unquoted_content(const char *content, bool *envar,
		bool *quotes)
{
	size_t				len;
	enum e_quotes_type	status;

	len = 0;
	status = no_quotes;
	while (*content)
	{
		if (*content == '$' && status != single_quote)
			*envar = true;
		if ((*content == '\'' || *content == '\"') && status != no_quotes)
			*quotes = true;
		if (*content == '\'' || *content == '\"')
			ft_handle_quotes(*content, &status);
		len++;
		content++;
	}
	return (len);
}

/**
 * @brief Calculates the length of the string excluding outer quotes,
 *        checks for environment variables, and flags the presence of quotes.
 *
 * @param content Pointer to the string content.
 * @param envar Pointer to a boolean to flag the presence of `$`.
 * @param quotes Pointer to a boolean to flag the presence of quotes.
 * @return size_t Length of the processed content.
 */
static size_t	count_len_set_bool(const char *content, bool *envar,
		bool *quotes)
{
	size_t	len;
	char	outer_quote;

	len = 0;
	if (*content == '\'' || *content == '\"')
	{
		*quotes = true;
		outer_quote = *content;
		content++;
		while (*content && *content != outer_quote)
		{
			if (*content == '$' && outer_quote != '\'')
				*envar = true;
			len++;
			content++;
		}
	}
	else
	{
		len = process_unquoted_content(content, envar, quotes);
	}
	return (len);
}

/**

	* @brief Removes outer quotes from the string and copies the content into `dest`.
 *
 * @param dest Pointer to the destination buffer.
 * @param src Pointer to the source string.
 */
void	remove_quotes(char *dest, const char *src)
{
	char	outer_quote;

	if (!src || !dest)
		return ;
	outer_quote = *src;
	if (outer_quote != '\'' && outer_quote != '\"')
	{
		// If no quotes, copy as-is
		ft_strcpy(dest, src);
		return ;
	}
	src++; // Skip the opening quote
	while (*src && *src != outer_quote)
		*dest++ = *src++;
	*dest = '\0'; // Null-terminate the string
}

/**

	* @brief Processes a string to remove outer quotes and expand environment variables.
 *
 * Allocates memory for a new string where:
 * - Outer quotes are removed.
 * - Environment variables are expanded (if not inside single quotes).
 *
 * @param content Pointer to the input string.

	* @return t_ret* Pointer to a t_ret struct containing the status and the processed string.
 */
t_ret	*ft_process_args(const char *content)
{
	bool	quotes;
	bool	envar;
	t_ret	*result;
	size_t	str_len;
	char	*expanded;
	char	*str_ret;

	quotes = false;
	envar = false;
	result = ft_calloc(1, sizeof(t_ret));
	if (!result)
		return (NULL);
	str_len = count_len_set_bool(content, &envar, &quotes);
	str_ret = ft_calloc(str_len + 1, sizeof(char));
	if (!str_ret)
	{
		free(result);
		return (NULL);
	}
	if (quotes)
		remove_quotes(str_ret, content);
	else
		ft_strcpy(str_ret, content);
	if (envar)
	{
		expanded = ft_strdup(str_ret);
		if (!expanded)
		{
			free(str_ret);
			free(result);
			return (NULL);
		}
		expand_var(expanded);
		free(str_ret);
		str_ret = expanded;
	}
	result->status = 1;
	result->ret = str_ret;
	return (result);
}

/**
 * @brief Entry point to test the `ft_process_args` function.
 *
 * Reads input strings, processes them using `ft_process_args`,
 * and prints the results.
 */
int	main(void)
{
	const char	**current_input;
	t_ret		*result;
	const char	*test_inputs[] = {"Hello $USER, welcome to '$HOME'.",
			"No quotes and $PATH variable.",
			"'Single-quoted $should_not_expand'",
			"\"Double-quoted $should_expand\"",
			"Plain string without variables.", "$?", NULL};

	current_input = test_inputs;
	printf("Testing `ft_process_args`:\n");
	while (*current_input)
	{
		printf("\nInput: %s\n", *current_input);
		result = ft_process_args(*current_input);
		if (result)
		{
			printf("Processed string: %s\n", (char *)result->ret);
			printf("Status: %d\n", result->status);
			free(result->ret);
			free(result);
		}
		else
		{
			printf("Error: Processing failed!\n");
		}
		current_input++;
	}
	return (0);
}

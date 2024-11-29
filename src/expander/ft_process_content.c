/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:58:26 by root              #+#    #+#             */
/*   Updated: 2024/11/29 16:44:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <libft.h>
#include <parse.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
		len = process_unquoted_content(content, envar, quotes);
	return (len);
}

/**
 * @brief Prepares the string for processing by removing quotes and
 *allocating memory.
 *
 * @param content The input string to process.
 * @param result Pointer to the t_ret structure to store the processed string.
 * @param envar Pointer to a boolean to flag if the string contains env var.
 * @param quotes Pointer to a boolean to flag if the string contains quotes.
 * @return int Returns 1 on success, -1 on failure.
 */
static int	prepare_string_for_processing(const char *content, t_ret *result,
		bool *envar, bool *quotes)
{
	size_t	str_len;
	char	*str_ret;

	str_len = count_len_set_bool(content, envar, quotes);
	str_ret = ft_calloc(str_len + 1, sizeof(char));
	if (!str_ret)
		return (-1);
	if (*quotes)
		remove_quotes(str_ret, content);
	else
		ft_strcpy(str_ret, content);
	result->ret = str_ret;
	result->status = 1;
	return (1);
}

/**
 * @brief Processes the string to expand environment variables if applicable.
 * @param result Pointer to the t_ret structure containing the string to
 *	process.
 * @param envar Boolean indicating if the string contains environment variables.
 * @return int Returns 1 on success, -1 on failure.
 */
static int	process_expansion(t_ret *result, bool envar)
{
	char	*expanded;

	if (envar)
	{
		expanded = ft_strdup(result->ret);
		if (!expanded)
			return (-1);
		if (expand_var(expanded) != EXPAND_VAR_SUCCESS)
		{
			free(expanded);
			return (-1);
		}
		free(result->ret);
		result->ret = expanded;
	}
	return (1);
}

/**
 *
 * @brief Processes a string to remove outer quotes and expand env variables.
 *
 * @param content Pointer to the input string.
 *
 * @return t_ret* Pointer to a t_ret struct containing the status and the
 *     processed string.
 */
t_ret	*ft_process_args(const char *content)
{
	t_ret	*result;
	bool	quotes;
	bool	envar;

	quotes = false;
	envar = false;
	result = ft_calloc(1, sizeof(t_ret));
	if (!result)
		return (NULL);
	if (prepare_string_for_processing(content, result, &envar, &quotes) == -1)
	{
		free(result);
		return (NULL);
	}
	if (process_expansion(result, envar) == -1)
	{
		free(result->ret);
		free(result);
		return (NULL);
	}
	return (result);
}

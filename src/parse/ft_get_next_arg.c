/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:48:55 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/26 09:55:06 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include <utils.h>

/**
 * Exists solely to bypass Norminette.
 * If we got some redirection argument, returns it's string duplicate.
 * @warning	To be used only by ft_get_next_arg().
 * @warning	Dynamic memory allocation is used.
 * @param	token	Token we'd like to get a redirection argument from.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0, then $ret is set to non-NULL value,
 * 				containing a string duplicate of
 * 				the current redirection argument.
 */
static t_ret	ft_get_next_arg_strdup_redir(char *token)
{
	t_ret	ret;

	ret.status = 0;
	if (ft_strncmp(token, "<<", sizeof("<<")) == 0)
		ret.ret = ft_strdup("<<");
	else if (ft_strncmp(token, "<", sizeof("<")) == 0)
		ret.ret = ft_strdup("<");
	else if (ft_strncmp(token, ">>", sizeof(">>")) == 0)
		ret.ret = ft_strdup(">>");
	else
		ret.ret = ft_strdup(">");
	if (ret.ret == NULL)
		ret.status = -1;
	return (ret);
}

/**
 * Exists solely to bypass Norminette.
 * If we got here, then entirey of *$saveptr should be just ft_strdup()'ed.
 * @warning	To be used only by ft_get_next_arg_proceed_as_usual().
 * @warning	Dynamic memory allocation is used.
 * @param	saveptr	Where we've left.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0, then $ret is set to non-NULL value,
 * 				containing a string duplicate of
 * 				the current redirection argument.
 */
static t_ret	ft_get_next_arg_just_strdup_remaining(char **saveptr)
{
	char	*ret;

	ret = ft_strdup(*saveptr);
	if (ret == NULL)
		return ((t_ret){(-1), NULL});
	*saveptr += ft_strlen(ret);
	return ((t_ret){0, ret});
}

/**
 * Exists solely to bypass Norminette.
 * Returns a string duplicate of the normal argument we currently have.
 * @warning	To be used only by ft_get_next_arg().
 * @warning	Dynamic memory allocation is used.
 * @param	saveptr	Where we've left.
 * @return	If malloc() failed somewhere, $status is set to (-1) and
 * 				$ret is set to NULL;
 * 			if $status is set to 0, then $ret is set to non-NULL value,
 * 				containing a string duplicate of
 * 				the current redirection argument.
 */
static t_ret	ft_get_next_arg_proceed_as_usual(char **saveptr)
{
	enum e_quotes_type	quotes;
	char				*ret;
	size_t				ret_str_len;

	quotes = no_quotes;
	ret_str_len = 0;
	while ((*saveptr)[ret_str_len] != '\0')
	{
		if (**saveptr == '\'' || **saveptr == '\"')
			ft_handle_quotes(**saveptr, &quotes);
		else if ((**saveptr == ' ' || **saveptr == '<' || **saveptr == '>')
			&& quotes == no_quotes)
		{
			ret = (char *)malloc(ret_str_len + 1);
			if (ret == NULL)
				return ((t_ret){(-1), NULL});
			(void)ft_strlcpy(ret, *saveptr, ret_str_len + 1);
			*saveptr += ret_str_len;
			return ((t_ret){0, ret});
		}
		ret_str_len++;
	}
	return (ft_get_next_arg_just_strdup_remaining(saveptr));
}

t_ret	ft_get_next_arg(char *token, char **saveptr)
{
	char				*ret;
	t_ret				strdup_redir_ret;

	if (token != NULL)
		*saveptr = token;
	ft_skip_spaces((const char **)saveptr);
	ret = *saveptr;
	if (*ret == '\0')
		return ((t_ret){0, NULL});
	else if (*ret == '<' || *ret == '>')
	{
		strdup_redir_ret = ft_get_next_arg_strdup_redir(ret);
		if (strdup_redir_ret.status == -1)
			return (strdup_redir_ret);
		*saveptr += ft_strlen((const char *)strdup_redir_ret.ret) - 1;
		*(*saveptr)++ = '\0';
		return (strdup_redir_ret);
	}
	return (ft_get_next_arg_proceed_as_usual(saveptr));
}

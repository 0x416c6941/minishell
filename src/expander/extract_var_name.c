/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:01:20 by root              #+#    #+#             */
/*   Updated: 2024/11/29 16:18:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

/**
 * @brief Duplicates the variable name for `$?`.
 *
 * @param var_name Pointer to store the duplicated variable name.
 * @return size_t Length of the variable name (1 for `$?`) or 0 on failure.
 */
static size_t	handle_special_var(char **var_name)
{
	*var_name = ft_strdup("?");
	if (!*var_name)
	{
		ft_print_error("Error: handle_special_var: strdup failed for '$?'\n");
		return (0);
	}
	return (1);
}

/**
 * @brief Validates and calculates the length of a standard variable name.
 *
 * @param read_ptr Pointer to the start of the variable name.
 * @return size_t Length of the variable name or 0 if invalid.
 */
static size_t	get_standard_var_len(const char *read_ptr)
{
	size_t	var_len;

	var_len = 0;
	while ((*read_ptr >= 'a' && *read_ptr <= 'z') || (*read_ptr >= 'A'
			&& *read_ptr <= 'Z') || (*read_ptr >= '0' && *read_ptr <= '9')
		|| (*read_ptr == '_'))
	{
		var_len++;
		read_ptr++;
	}
	return (var_len);
}

/**
 * @brief Allocates and copies the variable name into `var_name`.
 *
 * @param start Pointer to the start of the variable name.
 * @param var_len Length of the variable name.
 * @param var_name Pointer to store the allocated variable name.
 * @return int 1 on success, 0 on memory allocation failure.
 */
static int	allocate_var_name(const char *start, size_t var_len,
		char **var_name)
{
	*var_name = malloc(var_len + 1);
	if (!*var_name)
	{
		fprintf(stderr,
			"allocate_var_name: Mem alloc failed for variable name at '%s'\n",
			start);
		return (0);
	}
	ft_strncpy(*var_name, start, var_len);
	(*var_name)[var_len] = '\0';
	return (1);
}

/**
 * @brief Extracts the variable name starting at `read_ptr`.
 *
 * @param read_ptr Pointer to the variable name.
 * @param var_name Pointer to store the allocated variable name.
 * @return size_t Length of the variable name or 0 on failure.
 */
size_t	extract_var_name(const char *read_ptr, char **var_name)
{
	size_t		var_len;
	const char	*start = read_ptr;

	if (*read_ptr == '?')
		return (handle_special_var(var_name));
	var_len = get_standard_var_len(read_ptr);
	if (var_len == 0)
	{
		fprintf(stderr,
			"extract_var_name: Empty or invalid variable name at '%s'\n",
			start);
		*var_name = NULL;
		return (0);
	}
	if (!allocate_var_name(start, var_len, var_name))
		return (0);
	return (var_len);
}

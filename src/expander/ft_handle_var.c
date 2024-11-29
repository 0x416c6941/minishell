/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:13:50 by root              #+#    #+#             */
/*   Updated: 2024/11/29 16:30:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

/**
 * @brief Initializes the buffer and its related parameters.
 *
 * @param str The input string to be expanded.
 * @param buffer Pointer to store the allocated buffer.
 * @param buffer_size Pointer to store the size of the buffer.
 * @return int Returns 1 if initialization succeeds, -1 on error.
 */
static int	init_buffer(const char *str, char **buffer, size_t *buffer_size)
{
	*buffer_size = strlen(str) * 2;
	*buffer = malloc(*buffer_size);
	if (!*buffer)
	{
		ft_print_error("Error: init_buffer: Buffer allocation failed\n");
		return (EXPAND_VAR_ERROR);
	}
	return (EXPAND_VAR_SUCCESS);
}

/**
 * @brief Expands a variable found in the input string.
 *
 * @param read_ptr Pointer to the current read position in the string.
 * @param buffer Pointer to the output buffer.
 * @param write_offset Pointer to the current write position in the buffer.
 * @param buffer_size Pointer to the size of the buffer.
 *
 * @return char* Pointer to the updated read position after processing
 *				the variable, or NULL on error.
 */
static char	*process_variable(char *read_ptr, char **buffer,
		size_t *write_offset, size_t *buffer_size)
{
	char	*var_name;
	size_t	var_len;

	read_ptr++;
	var_len = extract_var_name(read_ptr, &var_name);
	if (!var_len || !var_name)
	{
		ft_print_error("Error: process_variable: Variable extraction failed\n");
		return (NULL);
	}
	if (!replace_var_with_value(var_name, buffer, write_offset, buffer_size))
	{
		ft_print_error("Error: process_variable: Failed to replace variable\n");
		free(var_name);
		return (NULL);
	}
	free(var_name);
	return (read_ptr + var_len);
}

/**
 * @brief Processes regular characters in the input string.
 *
 * @param buffer Pointer to the output buffer.
 * @param write_offset Pointer to the current write position in the buffer.
 * @param buffer_size Pointer to the size of the buffer.
 * @param read_ptr Pointer to the current read position in the input string.
 * @return int Returns 1 on success, -1 on failure.
 */
static int	process_reg_char(char **buffer, size_t *write_offset,
		size_t *buffer_size, char **read_ptr)
{
	char	*new_buffer;
	size_t	new_size;

	if (*write_offset + 1 >= *buffer_size)
	{
		new_size = *buffer_size * 2;
		new_buffer = realloc(*buffer, new_size);
		if (!new_buffer)
		{
			ft_print_error("Error: process_reg_char: Buffer resize failed\n");
			return (EXPAND_VAR_ERROR);
		}
		*buffer = new_buffer;
		*buffer_size = new_size;
	}
	(*buffer)[(*write_offset)++] = *(*read_ptr)++;
	return (EXPAND_VAR_SUCCESS);
}

/**
 * @brief Processes the input string and expands variables.
 *
 * @param read_ptr Pointer to the current read position in the string.
 * @param buffer Pointer to the dynamic buffer for the output.
 * @param write_offset Current write position in the buffer.
 * @param buffer_size Current size of the buffer.
 * @return char* Updated read pointer, or NULL on error.
 */
static char	*process_string(char *read_ptr, char **buffer, size_t *write_offset,
		size_t *buffer_size)
{
	while (*read_ptr)
	{
		if (*read_ptr == '$')
		{
			read_ptr = process_variable(read_ptr, buffer, write_offset,
					buffer_size);
			if (!read_ptr)
				return (NULL);
		}
		else
		{
			if (process_reg_char(buffer, write_offset, buffer_size,
					&read_ptr) == EXPAND_VAR_ERROR)
				return (NULL);
		}
	}
	return (read_ptr);
}

/**
 * @brief Expands variables in the given string.
 *
 * @param str The input string to be expanded. The result is written in place.
 * @return int Returns EXPAND_VAR_SUCCESS on success,
 *				EXPAND_VAR_ERROR on failure.
 */
int	expand_var(char *str)
{
	char	*buffer;
	size_t	buffer_size;
	size_t	write_offset;
	char	*read_ptr;

	if (!str)
		return (EXPAND_VAR_ERROR);
	if (init_buffer(str, &buffer, &buffer_size) == EXPAND_VAR_ERROR)
		return (EXPAND_VAR_ERROR);
	write_offset = 0;
	read_ptr = str;
	if (!process_string(read_ptr, &buffer, &write_offset, &buffer_size))
	{
		free(buffer);
		return (EXPAND_VAR_ERROR);
	}
	buffer[write_offset] = '\0';
	ft_strcpy(str, buffer);
	free(buffer);
	return (EXPAND_VAR_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_with_value.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:11:26 by root              #+#    #+#             */
/*   Updated: 2024/11/29 16:34:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

/**
 * @brief Retrieves the environment variable value.
 *
 * @param var_name The name of the variable.
 * @return char* The variable value or NULL if retrieval fails.
 */
static char	*retrieve_env_value(const char *var_name)
{
	char	*env_value;

	env_value = ft_getenv(var_name);
	if (!env_value)
	{
		ft_print_error("Error: retrieve_env_value: Failed to get value for ");
		ft_print_error(var_name);
	}
	return (env_value);
}

/**
 * @brief Resizes the output buffer if necessary.
 *
 * @param buffer Pointer to the buffer to be resized.
 * @param buffer_size Pointer to the current size of the buffer.
 * @param required_size The additional space needed in the buffer.
 * @return int Returns 1 if resizing succeeds, 0 otherwise.
 */
static int	resize_buffer(char **buffer, size_t *buffer_size,
		size_t required_size)
{
	char	*new_buffer;
	size_t	new_size;

	new_size = *buffer_size + required_size + (*buffer_size / 2);
	new_buffer = realloc(*buffer, new_size);
	if (!new_buffer)
	{
		ft_print_error("Error: resize_buffer: Buffer resizing failed");
		return (0);
	}
	*buffer = new_buffer;
	*buffer_size = new_size;
	return (1);
}

/**
 * @brief Appends a value to the buffer at the given offset.
 *
 * @param buffer Pointer to the buffer where data will be appended.
 * @param write_offset Pointer to the current write offset in the buffer.
 * @param value The value to append.
 * @param value_len The length of the value.
 */
static void	append_to_buffer(char **buffer, size_t *write_offset,
		const char *value, size_t value_len)
{
	memcpy(*buffer + *write_offset, value, value_len);
	*write_offset += value_len;
}

/**
 * @brief Replaces a variable with its value in the output buffer.
 *
 * @param var_name The name of the variable to replace.
 * @param buffer Pointer to the output buffer.
 * @param write_offset Pointer to the current write offset in the buffer.
 * @param buffer_size Pointer to the current size of the buffer.
 * @return size_t The length of the appended value or 0 on failure.
 */
size_t	replace_var_with_value(const char *var_name, char **buffer,
		size_t *write_offset, size_t *buffer_size)
{
	char	*env_value;
	size_t	env_value_len;

	env_value = retrieve_env_value(var_name);
	if (!env_value)
		return (0);
	env_value_len = strlen(env_value);
	if (*write_offset + env_value_len >= *buffer_size)
	{
		if (!resize_buffer(buffer, buffer_size, env_value_len))
		{
			free(env_value);
			return (0);
		}
	}
	append_to_buffer(buffer, write_offset, env_value, env_value_len);
	free(env_value);
	return (env_value_len);
}

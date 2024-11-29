/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:13:50 by root              #+#    #+#             */
/*   Updated: 2024/11/29 15:32:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <expander.h>
#include <expander.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXPAND_VAR_ERROR -1
#define EXPAND_VAR_SUCCESS 1
#define ERR_VAR_NAME "Error: extract_var_name: Memory allocation failed for '$?'\n"

// Global variable to store the last exit code
int				g_exit_code = 0;

// Retrieves the environment variable or special `$?`
char	*ft_getenv(const char *name)
{
	char	*res;
	char	*itoa_result;

	if (!name)
		return (ft_strdup(""));
	if (ft_strcmp(name, "?") == 0)
	{
		itoa_result = ft_itoa(g_exit_code);
		if (!itoa_result)
			return (NULL);
		res = ft_strdup(itoa_result); // Copy the result to a new buffer
		free(itoa_result);            // Free the original memory
		return (res);
	}
	res = getenv(name);
	return (ft_strdup(res ? res : ""));
}

// Extracts variable name from a string starting at `$`
static size_t	extract_var_name(const char *read_ptr, char **var_name)
{
	size_t		var_len;
	const char	*start;

	start = read_ptr;
	if (*read_ptr == '?')
	{
		*var_name = ft_strdup("?");
		if (!*var_name)
		{
			write(STDERR_FILENO, ERR_VAR_NAME, strlen(ERR_VAR_NAME));
			return (0);
		}
		return (1);
	}
	var_len = 0;
	// Extract a standard variable name (letters, digits, underscores)
	while ((*read_ptr >= 'a' && *read_ptr <= 'z') || (*read_ptr >= 'A'
			&& *read_ptr <= 'Z') || (*read_ptr >= '0' && *read_ptr <= '9')
		|| (*read_ptr == '_'))
	{
		var_len++;
		read_ptr++;
	}
	if (var_len == 0)
	{
		fprintf(stderr,
			"extract_var_name: Empty or invalid variable name at '%s'\n",
			start);
		*var_name = NULL;
		return (0);
	}
	*var_name = malloc(var_len + 1); // +1 for null terminator
	if (!*var_name)
	{
		fprintf(stderr,
			"extract_var_name: Memory allocation failed for variable name at '%s'\n",
			start);
		return (0);
	}
	ft_strncpy(*var_name, start, var_len);
	(*var_name)[var_len] = '\0';
	return (var_len);
}

// Replaces a variable with its value in the output buffer
static size_t	replace_var_with_value(const char *var_name, char **buffer,
		size_t *write_offset, size_t *buffer_size)
{
	char	*env_value;
	size_t	env_value_len;
	size_t	new_size;
	char	*new_buffer;

	// Retrieve the environment variable value
	env_value = ft_getenv(var_name);
	if (!env_value)
	{
		fprintf(stderr,
			"replace_var_with_value: Failed to retrieve value for variable '%s'\n",
			var_name);
		return (0);
	}
	env_value_len = strlen(env_value);
	// Resize buffer if necessary
	if (*write_offset + env_value_len >= *buffer_size)
	{
		new_size = *buffer_size + env_value_len + (*buffer_size / 2);
		new_buffer = realloc(*buffer, new_size);
		if (!new_buffer)
		{
			free(env_value);
			fprintf(stderr,
				"replace_var_with_value: Buffer resizing failed for variable '%s'\n",
				var_name);
			return (0);
		}
		*buffer = new_buffer;
		*buffer_size = new_size;
	}
	// Copy the environment value into the buffer
	memcpy(*buffer + *write_offset, env_value, env_value_len);
	*write_offset += env_value_len;
	// Free the dynamically allocated environment value
	free(env_value);
	return (env_value_len);
}

// Expands variables in the given string
int	expand_var(char *str)
{
	size_t	buffer_size;
	char	*buffer;
	size_t	write_offset;
	char	*read_ptr;
	char	*var_name;
	size_t	var_len;
	size_t	new_size;
	char	*new_buffer;

	if (!str)
		return (EXPAND_VAR_ERROR);
	buffer_size = strlen(str) * 2;
	buffer = malloc(buffer_size);
	if (!buffer)
	{
		fprintf(stderr, "expand_var: Initial buffer allocation failed\n");
		return (EXPAND_VAR_ERROR);
	}
	write_offset = 0;
	read_ptr = str;
	var_name = NULL;
	while (*read_ptr)
	{
		if (*read_ptr == '$')
		{
			if (*(read_ptr + 1) == '\0') // Handle trailing `$`
			{
				buffer[write_offset++] = *read_ptr++;
				continue ;
			}
			read_ptr++;
			var_len = extract_var_name(read_ptr, &var_name);
			if (!var_len || !var_name)
			{
				free(buffer);
				return (EXPAND_VAR_ERROR);
			}
			// Replace variable with value
			if (!replace_var_with_value(var_name, &buffer, &write_offset,
					&buffer_size))
			{
				fprintf(stderr, "expand_var: Failed to replace variable '%s'\n",
					var_name);
				free(var_name);
				free(buffer);
				return (EXPAND_VAR_ERROR);
			}
			free(var_name);
			read_ptr += var_len;
		}
		else
		{
			// Copy regular characters
			if (write_offset + 1 >= buffer_size)
			{
				new_size = buffer_size * 2;
				new_buffer = realloc(buffer, new_size);
				if (!new_buffer)
				{
					fprintf(stderr,
						"expand_var: Buffer resizing failed at offset %ld\n",
						write_offset);
					free(buffer);
					return (EXPAND_VAR_ERROR);
				}
				buffer = new_buffer;
				buffer_size = new_size;
			}
			buffer[write_offset++] = *read_ptr++;
		}
	}
	buffer[write_offset] = '\0';
	strcpy(str, buffer);
	free(buffer);
	return (EXPAND_VAR_SUCCESS);
}

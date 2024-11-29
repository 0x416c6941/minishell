/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:59:06 by root              #+#    #+#             */
/*   Updated: 2024/11/29 15:01:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

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

// Copies up to `n` characters, null-terminating the result
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
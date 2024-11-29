char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	if (!dest || !src)
		return (NULL);
	while ((*dest++ = *src++) != '\0')
		;
	return (dest_start);
}

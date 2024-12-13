/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:21:24 by root              #+#    #+#             */
/*   Updated: 2024/12/13 14:45:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#define DEC_BASE 10
#include <limits.h>

static int	ft_exit_error(const char *arg)
{
	ft_errmsg("exit: ");
	ft_errmsg(arg);
	ft_errmsg(": numeric argument required\n");
	return (2);
}

/**
 * @brief Parses the sign, skips whitespace,
	and returns a pointer to the number.
 *
 * @param nptr Pointer to the string to parse.
 * @param sign Pointer to an integer where the sign (+1 or -1) will be stored.

	* @return const char* Pointer to the remaining part of the string after parsing.
 */
static const char	*parse_sign_and_skip_whitespace(const char *nptr, int *sign)
{
	*sign = 1;
	if (!nptr)
		return (NULL);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			*sign = -1;
		nptr++;
	}
	return (nptr);
}

/**
 * @brief skip leading and trailing whitespaces. Check if there is any other
 * 			character than digits or +/- before the digits
 *
 * @param arg
 * @return true
 * @return false ("  - 123" "+-123" "123 123" "123a123" "    " "")
 */
static bool	validate_arg(const char *arg)
{
	if (!arg || !*arg)
		return (false);
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		arg++;
	if (!*arg || !ft_isdigit(*arg))
		return (false);
	while (ft_isdigit(*arg))
		arg++;
	while (ft_isspace(*arg))
		arg++;
	if (*arg)
		return (false);
	return (true);
}

/**
 * @brief Main function to extract the numeric value from a string.
 *
 * @param nptr Pointer to the input string.
 * @return long int Extracted long integer value or 2 in case of error.
 */
static long int	extract_arg(const char *nptr)
{
	const char	*original_arg = nptr;
	int			sign;
	long		ret;
	int			digit;

	nptr = parse_sign_and_skip_whitespace(nptr, &sign);
	ret = 0;
	if (!nptr)
		return (0);
	while (ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		if (ret > (LONG_MAX - digit) / DEC_BASE)
			return (ft_exit_error(original_arg));
		ret = ret * DEC_BASE + digit;
		nptr++;
	}
	return (ret * sign);
}

/**
 * @brief Validate all digits (first can be + or -)
 *
 * @param arg
 * @return int
 */
static int	extract_validate_arg(const char *arg)
{
	long int	res;

	if (!arg)
		return (false);
	if (!validate_arg(arg))
		return (ft_exit_error(arg));
	res = extract_arg(arg);
	if (res < 0)
		res = (res % 256) + 256;
	else
		res = res % 256;
	return ((int)res);
}

/**
 * @brief Exits the shell.
 * can handle long int if overvlow -> print error and set exit code to 2
 * last_exit_code modullo 256
 * if negative -> modullo 256 than +256
 * in case of exit:numeric argument required returns 2 as in bash
 */
int	exit_builtin(const char *args[], int *last_exit_code)
{
	if (!args || !last_exit_code)
		return (EXIT_FAILURE);
	printf("exit\n");
	if (args[0] != NULL && args[1] != NULL)
	{
		*last_exit_code = 1;
		ft_errmsg("exit: too many arguments\n");
		return (EXIT_SUCCESS);
	}
	if (args[0] == NULL)
	{
		*last_exit_code = 0;
		return (EXIT_SUCCESS);
	}
	*last_exit_code = extract_validate_arg(args[0]);
	return (EXIT_SUCCESS);
}

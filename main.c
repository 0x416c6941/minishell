/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:51:42 by hlyshchu          #+#    #+#             */
/*   Updated: 2024/11/25 19:04:08 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;
	char buffer[1024];

	// Determine the mode
	is_interactive = isatty(STDIN_FILENO);

	// Set up signal handling
	setup_signals();

	if (is_interactive)
	{
		printf("Interactive mode detected!\n");

		while (1)
		{
			input = readline("minishell> ");
			if (!input)
			{ // Handle Ctrl-D (EOF)
				write(STDOUT_FILENO, "exit\n", 5);
				break;
			}
			if (*input)
			{
				add_history(input); // Add non-empty input to history
			}
			printf("Command: %s\n", input); // Placeholder for command execution
			free(input);
		}
	}
	else
	{
		printf("Non-interactive mode detected!\n");

		while (fgets(buffer, sizeof(buffer), stdin))
		{
			// Trim newline and process the command
			buffer[strcspn(buffer, "\n")] = '\0';
			if (buffer[0] != '\0')
			{									   // Skip empty lines
				printf("Executing: %s\n", buffer); // Placeholder for command execution
			}
		}
	}

	return 0;
}

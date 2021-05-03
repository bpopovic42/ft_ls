/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:03:55 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:04:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		argument_is_a_flag(char *argument)
{
	if (argument[0] == '-' && ft_strlen(argument) > 1 && !g_flags.option_stop)
		return (1);
	return (0);
}

int		no_valid_file_arguments_provided(t_store *store)
{
	if (store->folders_queue->size == 0 &&
		store->invalid_folders->size == 0 &&
		store->cli_file_arguments_folder->files->size == 0)
		return (1);
	return (0);
}

int		parse_current_argument(t_store *store, char *argument)
{
	if (argument_is_a_flag(argument))
	{
		if (parse_flag_argument(store, &argument[0]) != EXIT_SUCCESS)
			return (handle_error(store, FT_LS_FATAL_ERROR));
	}
	else
	{
		if (parse_path_argument(store, argument, 1) != EXIT_SUCCESS)
			return (FT_LS_FATAL_ERROR);
		store->nbr_of_file_args += 1;
	}
	return (EXIT_SUCCESS);
}

int		parse_arguments(t_store *store, int arg_count, char **arguments)
{
	int i;

	i = 0;
	while (i < arg_count)
	{
		if (parse_current_argument(store, arguments[i]) != EXIT_SUCCESS)
			return (FT_LS_FATAL_ERROR);
		i++;
	}
	if (no_valid_file_arguments_provided(store))
	{
		if (parse_path_argument(store, ".", 0) != EXIT_SUCCESS)
			return (FT_LS_FATAL_ERROR);
	}
	return (EXIT_SUCCESS);
}

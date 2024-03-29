/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:03:04 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:03:42 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		handle_invalid_flag(struct s_store *store, char *argument)
{
	ft_dprintf(2, "%s: invalid option -- '%c'\n", store->program_name,
				*argument);
	ft_dprintf(2, "Try '%s --help' for more information.\n",
	store->program_name);
	return (handle_error(store, EINVAL));
}

int		handle_unrecognized_flag(struct s_store *store, char *argument)
{
	ft_dprintf(2, "%s: unrecognized option '%s'\n", store->program_name,
				argument);
	ft_dprintf(2, "Try '%s --help' for more information.\n",
				store->program_name);
	return (handle_error(store, EINVAL));
}

void	handle_flag(char flag)
{
	if (flag == 'a')
		g_flags.option_a = true;
	else if (flag == 'l')
		g_flags.option_l = true;
	else if (flag == 'r')
		g_flags.option_r = true;
	else if (flag == 'R')
		g_flags.option_upper_r = true;
	else if (flag == 't')
		g_flags.option_t = true;
}

int		parse_flag_argument(struct s_store *store, char *argument)
{
	int i;

	i = 1;
	if (!ft_strcmp(argument, "--"))
		g_flags.option_stop = true;
	else
	{
		while (argument[i])
		{
			if (argument[i] == '-' && i == 1)
				return (handle_unrecognized_flag(store, argument));
			else if (!ft_strchr(FT_LS_FLAGS_LIST, argument[i]))
				return (handle_invalid_flag(store, argument + i));
			else
				handle_flag(argument[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

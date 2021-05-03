/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:46:32 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:46:42 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Original ls doesn't exit in case of access failure
*/

int		handle_error(t_store *store, int err_type)
{
	store->error.type = err_type;
	if (err_type == EACCES)
		store->error.exit_code = FT_LS_ERROR;
	else
		store->error.exit_code = FT_LS_FATAL_ERROR;
	return (store->error.exit_code);
}

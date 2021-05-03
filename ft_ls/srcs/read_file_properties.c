/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:55:26 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 16:55:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		read_file_properties(t_file *file)
{
	struct stat file_stat;
	int			error_status;

	if (lstat(file->path, &file_stat) < 0)
		return (errno);
	get_file_mode(&file->mode, &file_stat);
	if ((error_status = get_file_properties(file, &file_stat)) != EXIT_SUCCESS)
		return (error_status);
	return (EXIT_SUCCESS);
}

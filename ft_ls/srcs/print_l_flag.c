/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:01:43 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:02:08 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_special_file(t_file *file, t_padding *padding)
{
	ft_printf("%s %*d %-*r %-*r %*d,%*d %s %r%s%r\n",
				&file->mode,
				padding->file_links,
				file->hard_links,
				padding->file_uid,
				file->properties->usr_owner,
				padding->file_gid,
				file->properties->grp_owner,
				padding->file_major_rdev,
				file->properties->major_rdev,
				padding->file_minor_rdev,
				file->properties->minor_rdev,
				file->properties->date,
				file->name,
				file->mode.type == 'l' ? " -> " : "",
				file->properties->link);
}

void	print_regular_file(t_file *file, t_padding *padding)
{
	ft_printf("%s %*d %-*r %-*r %*d %s %r%s%r\n",
				&file->mode,
				padding->file_links,
				file->hard_links,
				padding->file_uid,
				file->properties->usr_owner,
				padding->file_gid,
				file->properties->grp_owner,
				padding->file_size,
				file->properties->size,
				file->properties->date,
				file->name,
				file->mode.type == 'l' ? " -> " : "",
				file->properties->link);
}

void	print_file_l_flag(t_file *file, t_padding *padding)
{
	if (padding->file_major_rdev > 0)
	{
		padding->file_size += 1;
	}
	if (file->mode.type == 'c' || file->mode.type == 'b')
		print_special_file(file, padding);
	else
		print_regular_file(file, padding);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:09:00 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:09:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_special_bits(t_mode *mode, struct stat *file_stat)
{
	if (S_IXUSR & file_stat->st_mode)
		mode->usr_exec = (S_ISUID & file_stat->st_mode) ? 's' : 'x';
	else
		mode->usr_exec = (S_ISUID & file_stat->st_mode) ? 'S' : '-';
	if (S_IXGRP & file_stat->st_mode)
		mode->grp_exec = (S_ISGID & file_stat->st_mode) ? 's' : 'x';
	else
		mode->grp_exec = (S_ISGID & file_stat->st_mode) ? 'S' : '-';
	if (S_IXOTH & file_stat->st_mode)
		mode->oth_exec = (S_ISVTX & file_stat->st_mode) ? 't' : 'x';
	else
		mode->oth_exec = (S_ISVTX & file_stat->st_mode) ? 'T' : '-';
}

void	get_file_mode(t_mode *mode, struct stat *file_stat)
{
	if (S_ISBLK(file_stat->st_mode))
		mode->type = 'b';
	else if (S_ISCHR(file_stat->st_mode))
		mode->type = 'c';
	else if (S_ISDIR(file_stat->st_mode))
		mode->type = 'd';
	else if (S_ISLNK(file_stat->st_mode))
		mode->type = 'l';
	else if (S_ISFIFO(file_stat->st_mode))
		mode->type = 'p';
	else if (S_ISSOCK(file_stat->st_mode))
		mode->type = 's';
	mode->usr_read = (S_IRUSR & file_stat->st_mode ? 'r' : '-');
	mode->usr_write = (S_IWUSR & file_stat->st_mode ? 'w' : '-');
	mode->grp_read = (S_IRGRP & file_stat->st_mode ? 'r' : '-');
	mode->grp_write = (S_IWGRP & file_stat->st_mode ? 'w' : '-');
	mode->oth_read = (S_IROTH & file_stat->st_mode ? 'r' : '-');
	mode->oth_write = (S_IWOTH & file_stat->st_mode ? 'w' : '-');
	get_special_bits(mode, file_stat);
}

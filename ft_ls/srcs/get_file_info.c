/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:09:57 by bopopovi          #+#    #+#             */
/*   Updated: 2021/05/03 17:10:05 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_file_time(t_file *file, struct stat *file_stat)
{
	char		*date;
	t_uint64	current_time;

	current_time = time(0);
	date = ctime(&file_stat->st_mtime);
	file->properties->mtime = file_stat->st_mtim.tv_sec * 1000 +
								file_stat->st_mtim.tv_nsec / 1000000;
	ft_strncpy(file->properties->date, date + 4, 7);
	if ((current_time - file_stat->st_mtim.tv_sec) >
		(t_uint64)(SECONDS_IN_A_YEAR / 2))
		ft_strncpy(file->properties->date + 7, date + 19, 5);
	else
		ft_strncpy(file->properties->date + 7, date + 11, 5);
	return (EXIT_SUCCESS);
}

int		get_usr_name(struct stat *file_stat, char **usr_name)
{
	struct passwd *pwuid;

	pwuid = getpwuid(file_stat->st_uid);
	if (pwuid == NULL || pwuid->pw_name == NULL)
	{
		if (!(*usr_name = ft_itoa(file_stat->st_uid)))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!(*usr_name = ft_strdup(pwuid->pw_name)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		get_grp_name(struct stat *file_stat, char **grp_name)
{
	struct group *grgid;

	grgid = getgrgid(file_stat->st_gid);
	if (grgid == NULL || grgid->gr_name == NULL)
	{
		if (!(*grp_name = ft_itoa(file_stat->st_gid)))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!(*grp_name = ft_strdup(grgid->gr_name)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		get_usr_and_grp_info(struct stat *file_stat, char **usr_name, char
		**grp_name)
{
	if (get_usr_name(file_stat, usr_name) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (get_grp_name(file_stat, grp_name) != EXIT_SUCCESS)
	{
		ft_strdel(usr_name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

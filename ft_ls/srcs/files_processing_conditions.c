#include "ft_ls.h"

int should_process_file(t_file *file)
{
	return !(file->name[0] == '.' && g_flags[0] != 'a' &&
	!ft_strequ(file->name, file->path));
}

int should_add_subfolder(t_file *subfolder)
{
	return (g_flags[3] == 'R' && subfolder->mode.type == 'd'
	        && !ft_strequ(subfolder->name, ".")
	        && !ft_strequ(subfolder->name, ".."));
}

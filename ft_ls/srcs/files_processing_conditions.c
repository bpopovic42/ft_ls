#include "ft_ls.h"

int should_process_folder(t_file *file)
{
	return !(file->name[0] == '.' && !g_flags.option_a &&
	!ft_strequ(file->name, file->path));
}

int should_add_subfolder(t_file *subfolder)
{
	return (g_flags.option_R && subfolder->mode.type == 'd'
	        && !ft_strequ(subfolder->name, ".")
	        && !ft_strequ(subfolder->name, ".."));
}

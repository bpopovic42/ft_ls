#include "ft_ls.h"

int should_process_file(char flags[FT_LS_FLAGS], t_file *file)
{
	return (file->name[0] != '.' || flags[0] == 'a');
}

int should_add_subfolder(char flags[FT_LS_FLAGS], t_file *subfolder)
{
	return (flags[3] == 'R' && subfolder->mode.type == 'd'
	        && !ft_strequ(subfolder->name, ".")
	        && !ft_strequ(subfolder->name, ".."));
}

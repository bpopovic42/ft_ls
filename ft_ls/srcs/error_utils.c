#include "ft_ls.h"

/*
** Original ls doesn't exit in case of access failure
*/

int handle_error(t_store *store, int err_status)
{
	store->error_status = err_status;
	if (err_status > FT_LS_ERROR || (errno != EACCES && errno != ENOENT))
		return (FT_LS_FATAL_ERROR);
	else
		return (EXIT_SUCCESS);
}
#include "ft_ls.h"

/*
** Original ls doesn't exit in case of access failure
*/

int handle_error(t_store *store, int error_status)
{
	store->error_status = error_status;
	if (error_status != FT_LS_FATAL_ERROR && (errno == EACCES || errno ==
	ENOENT))
		return (EXIT_SUCCESS);
	return (error_status);
}
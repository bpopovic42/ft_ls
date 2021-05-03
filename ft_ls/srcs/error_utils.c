#include "ft_ls.h"

/*
** Original ls doesn't exit in case of access failure
*/

int handle_error(t_store *store, int err_type)
{
	store->error.type = err_type;
	if (err_type == EACCES)
		store->error.exit_code = FT_LS_ERROR;
	else
		store->error.exit_code = FT_LS_FATAL_ERROR;
	return (store->error.exit_code);
}
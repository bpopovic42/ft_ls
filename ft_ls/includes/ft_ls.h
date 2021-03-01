#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>

# define FT_LS_FLAGS 5

typedef struct s_store
{
	char flags[FT_LS_FLAGS];
	bool flags_end;
	int nbr_of_file_args;
	t_list *folders_queue;
} t_store;

typedef struct s_mode {
	char type;
	char usr_read;
	char usr_write;
	char usr_exec;
	char grp_read;
	char grp_write;
	char grp_exec;
	char oth_read;
	char oth_write;
	char oth_exec;
} t_mode;

typedef struct s_file
{
	char   *name;
	char   *path;
	int     timestamp;
	int    struct_size;
	t_mode mode;
	t_list *files;
	t_list *sub_folders;
} t_file;


/*
** FILES_UTILS
*/

int create_new_file(t_file **new_file, char *name, char *parent_path);

void del_file(t_file *file, size_t folder_size);

/*
** READ_FILE
*/

int read_file_properties(t_file *file);

/*
** STRUCTURES UTILS
*/

int init_store(t_store *store);

void clean_store(t_store *store);

/*
** PARSE_ARGUMENTS
*/

int parse_arguments(char **arguments, t_store *store);

/*
** SORTING
*/

void sort_files(t_store *store, t_list *files);

/*
** PRINTING
*/

void print_parent_folder(t_store *store, t_file *parent_folder);
void print_file(t_store *store, t_file *file, int is_last_file);

/*
** PROCESS FOLDERS
*/

int process_folders(t_store *store);

/*
** FILES PROCESSING CONDITIONS
*/

int should_process_file(char flags[FT_LS_FLAGS], t_file *file);

int should_add_subfolder(char flags[FT_LS_FLAGS], t_file *subfolder);

#endif

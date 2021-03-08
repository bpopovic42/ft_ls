#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

# define FT_LS_FLAGS 5

typedef struct s_store
{
	bool flags_end;
	int nbr_of_file_args;
	char *program_name;
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

typedef struct s_properties
{
	long     timestamp;
	char    *usr_owner;
	char    *grp_owner;
	char    *link;
	char    date[13];
	int     blocks;
	int     total_blocks;
	int     size;
	int    struct_size;
} t_properties;

typedef struct s_file
{
	char          *name;
	char          *path;
	int           struct_size;
	int           hard_links;
	int           error;
	char          *error_msg;
	struct s_file *parent_folder;
	t_properties  *properties;
	t_mode        mode;
	t_list        *files;
	t_list        *sub_folders;
} t_file;

char g_flags[FT_LS_FLAGS];

# define FT_LS_BLOCKSIZE 1024

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

int init_store(t_store *store, char *program_name);

void clean_store(t_store *store);

/*
** PARSE_ARGUMENTS
*/

int parse_arguments(char **arguments, t_store *store);

/*
** SORTING
*/

void sort_files(t_list *files);

/*
** PRINTING
*/

void print_parent_folder(t_store *store, t_file *parent_folder);
void print_file(t_file *file, int is_last_file);
void print_file_from_node(t_node *file_node);

/*
** PROCESS FOLDERS
*/

int process_folders(t_store *store);

/*
** GET FOLDER FILES
*/

int get_folder_files(struct s_file *folder);

/*
** PROCESS FOLDER FILES
*/

int process_folder_files(t_store *store, struct s_file *folder);

/*
** FILES PROCESSING CONDITIONS
*/

int should_process_file(t_file *file);

int should_add_subfolder(t_file *subfolder);

#endif

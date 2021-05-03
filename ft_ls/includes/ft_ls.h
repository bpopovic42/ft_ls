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
# include <stdint.h>

# define FT_LS_FLAGS 6
# define FT_LS_FLAGS_LIST "alrRt"
# define FT_LS_ERROR 1
# define FT_LS_FATAL_ERROR 2
# define SECONDS_IN_A_YEAR 31556952

typedef struct s_error
{
	int  type;
	char *message;
	int  exit_code;
} t_error;

typedef struct s_store
{
	int nbr_of_file_args;
	char *program_name;
	t_error error;
	struct s_file *cli_file_arguments_folder;
	t_list *folders_queue;
	t_list *invalid_folders;
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
	t_uint64 mtime;
	char     *usr_owner;
	char     *grp_owner;
	char     *link;
	t_mode   link_mode;
	char     date[13];
	int      blocks;
	int      total_blocks;
	int      size;
	int      major_rdev;
	int      minor_rdev;
	int      struct_size;
} t_properties;

typedef struct s_file
{
	char          *name;
	char          *path;
	int           struct_size;
	int           hard_links;
	int           is_cli_arg;
	int           error;
	char          *error_msg;
	struct s_file *parent_folder;
	t_properties  *properties;
	t_mode        mode;
	t_list        *files;
	t_list        *sub_folders;
} t_file;

typedef struct s_padding
{
	size_t file_uid;
	size_t file_gid;
	size_t file_links;
	size_t file_size;
	size_t file_major_rdev;
	size_t file_minor_rdev;
} t_padding;

typedef struct s_flags
{
	bool option_a;
	bool option_l;
	bool option_r;
	bool option_R;
	bool option_t;
	bool option_stop;
} t_flags;

t_flags g_flags;

/*
** FILES_UTILS
*/

int allocate_new_file(t_file **new_file, char *name, char *parent_path);

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

int parse_arguments(t_store *store, int arg_count, char **arguments);
int parse_path_argument(struct s_store *store, char *argument, int is_cli_arg);
int parse_flag_argument(struct s_store *store, char *argument);

/*
** SORTING
*/

void sort_files(t_list *files);
int ascii_compare(t_file *f1, t_file *f2);

/*
** PRINTING
*/

void print_parent_folder(t_store *store, t_file *parent_folder);
void print_file(t_file *file, int is_last_file);
void print_file_from_node(t_node *file_node);
void print_file_error(t_store *store, t_file *file);
void print_help();

/*
** PROCESS FOLDERS
*/

int process_folders_queue(t_store *store);

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

int should_process_folder(t_file *file);

int should_add_subfolder(t_file *subfolder);

/*
** ERROR UTILS
*/

int handle_error(t_store *store, int err_type);

#endif

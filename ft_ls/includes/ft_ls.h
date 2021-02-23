#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>

typedef struct s_store {
  t_list *folders_queue;
} t_store;

typedef struct s_file {
  char *name;
  char *path;
  int type;
  t_list *files;
  t_list *sub_folders;
} t_file;

/*
** STRUCTURES UTILS
*/

t_file *create_new_file(char *name, char *parent_path);
int init_store(t_store *store);
int clean_store(t_store *store);

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

void tmp_print_folder(t_node *node);

/*
** PROCESS FOLDERS
*/

int   process_folders(t_store *store);

#endif

NAME		=	ft_ls

############################## DIRS ############################################

LFTDIR		=	./libft

IDIR		=	./includes

SDIR		=	./srcs

ODIR		=	./objs

############################## SRCS ############################################

# **************************************************************************** #
# ft_ls :

LS_FILES	=	main.c process_folders.c sorting.c printing.c \
	parse_arguments.c structures_utils.c files_utils.c

# **************************************************************************** #
# Complete path :

LS_SRCS		=	$(addprefix $(SDIR)/, $(LS_FILES))

############################## OBJS ############################################

LS_OBJS		=	$(LS_FILES:.c=.o)

LS_OBJ		=	$(addprefix $(ODIR)/, $(LS_OBJS))

OBJ			=	$(LS_OBJ)

############################## INCS ############################################

LFT			=	$(addprefix $(LFTDIR)/, libft.a)

LFT_INC_DIR	=	$(addprefix $(LFTDIR)/, $(IDIR))

LFT_INC		=	$(addprefix $(LFTDIR)/, $(IDIR)/libft.h $(IDIR)/ft_printf.h)

LS_INC		=	$(addprefix $(IDIR)/, ft_ls.h)

HEADERS		=	$(LFT_INC) $(LS_INC)

INCS		=	$(addprefix -I,$(IDIR) $(LFT_INC_DIR))

############################## COMP ############################################

CC			=	clang-9

CFLAGS		=	$(DEBUG) $(if $(SILENT), , -Wall -Wextra -Werror)

############################## RULES ###########################################

all			:	$(NAME)

$(NAME)		:	$(LFT) $(LS_OBJ) $(LS_INC)
			@$(CC) $(CFLAGS) -o $(NAME) $(LS_OBJ) $(LFT) $(INCS)
			@$(IF_CMP)
			@echo $(BG)[$(BLB)FT_LS $(BG)COMPILED$(BG)]$(X)

$(ODIR)/%.o	:	$(SDIR)/%.c $(HEADERS)
			@$(CMP)
			@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
			@$(CLR)
			@echo -n $@

$(LS_OBJ) 	: | $(ODIR)

$(ODIR)		:
			@/bin/mkdir -p $(ODIR)

$(LFT)		:
	@$(IF_NO_LFT)
	@$(MAKE) DEBUG="$(DEBUG)" -C $(LFTDIR)

clean		:
	@$(MAKE) clean -C $(LFTDIR)
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(ODIR)
	@/bin/rm -rf $(DBGDIR)
	@echo $(BG)[$(BLB)LEM_IN $(BG)CLEANED$(BG)]$(X)

fclean		:	clean
	@/bin/rm -f $(LFT)
	@/bin/rm -f $(NAME)

re			:
	@$(MAKE) fclean
	@$(MAKE) all

############################## UTIL ############################################

DBGDIR		=	$(NAME).dSYM

CMP			=	if [ ! -e .cmp ]; then \
				echo $(BY)Compiling $(B)Project $(X)files...$(BY); \
				touch .cmp; fi

IF_CMP		=	if [ -e .cmp ]; then \
			$(CLR); \
			echo $(UP) $(CUT) $(UP); \
			/bin/rm -f .cmp; fi

IF_NO_LFT	=	if [ ! -e libft/ ]; then \
					git clone https://github.com/bpopovic42/libft; fi

############################## DISPLAY #########################################

BY			=	"\033[1;33m"
BR			=	"\033[1;31m"
BG			=	"\033[1;32m"
BLB			=	"\033[1;36m"
BP			=	"\033[1;35m"
Y			=	"\033[33m"
R			=	"\033[31m"
G			=	"\033[0;32m"
B			=	"\033[34m"
P			=	"\033[35m"
X			=	"\033[0m"
UP			=	"\033[A"
CUT			=	"\033[K"
CLR			=	printf "\r%40c\r" " "
CUT_UP		=	$(UP)$(CUT)$(UP)

############################## OTHER ###########################################

.PHONY		: all, clean, fclean, re

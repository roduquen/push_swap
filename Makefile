CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = checker
NAME2 = push_swap
SRCDIR = ./
INCLDIR = ./includes/
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a
LIBSDL = -L /Users/roduquen/.brew/lib/ -lSDL2-2.0.0 `sdl2-config --cflags --libs`
SRCS = checker.c checker_verify.c do_movement.c sort_list.c push_swap.c \
	   chose_right_move.c moves.c chose_rotation.c utils.c visual_utils.c \
	   visual.c commands.c sort_list_less_than_5.c create_renderer_rect.c
OBJC = checker.o \
	   checker_verify.o \
	   do_movement.o \
	   visual_utils.o \
	   visual.o \
	   utils.o \
	   commands.o \
	   create_renderer_rect.o
OBJP = push_swap.o \
		sort_list.o \
		do_movement.o \
		visual_utils.o \
		checker_verify.o \
		chose_right_move.o \
		chose_rotation.o \
		moves.o \
		utils.o \
		sort_list_less_than_5.o

all : $(NAME) $(NAME2)

$(NAME) : $(OBJC) $(LIB)
	@$(CC) $(CFLAGS) -I $(INCLDIR) $^ -o $@ -L $(LIBDIR) -lft $(LIBSDL)
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

$(NAME2) : $(OBJP) $(LIB)
	@$(CC) $(CFLAGS) -I $(INCLDIR) $^ -o $@ -L $(LIBDIR) -lft
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -I $(INCLDIR) -I /Users/roduquen/.brew/include/SDL2
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(LIB) :
	@echo "\n\033[36mLibs Compilation :\033[0m \033[33m$(LIBDIR)\033[0m\n"
	@make -C libft

clean :
	@rm -rf $(OBJP)
	@rm -rf $(OBJC)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAME2)
	@make -C libft/ fclean
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all clean fclean re

NAME = minirt

MAIN_ALL := main main2
MAIN := main2

FILES = \
	$(MAIN) \
	free_scene parser parser_utils parse_lighting parse_objects \
	parse_parameters get_next_line get_next_line_utils

HEADERS= \
	minirt input parser get_next_line

OFILES = $(FILES:%=src/%.o)
HFILES = $(HEADERS:%=inc/%.h)
OMAIN_ALL = $(MAIN_ALL:%=src/%.o)
CFLAGS = -Wall -Wextra -Werror
OPTIM = -O3
export OPTIM
INC = -I. -I./inc -I./mlx/include
LIBS= -lgf -lft -lmlx42 -ldl -lglfw -lm
LIBS_FILES = libft/libft.a libgf/libgf.a mlx/libmlx42.a
LIBS_DIRS = $(addprefix -L, $(dir $(LIBS_FILES)))

all: $(NAME)

$(NAME): $(OFILES) $(LIBS_FILES)
	gcc $(LIBS_DIRS) $(OFILES) $(LIBS) -o $@

$(OFILES): %.o: %.c $(HFILES)
	gcc $(CFLAGS) $(OPTIM) $(INC) -c $< -o $@

$(LIBS_FILES): FORCE
	make -C $(dir $@)

FORCE: ;

clean_:
	rm -f $(OFILES) $(OMAIN_ALL)

clean: clean_libs clean_

fclean_: clean_
	rm -f $(NAME)

fclean: fclean_ clean
	rm -f $(LIBS_FILES)

re_: fclean_ all

re: re_libs re_

clean_libs:
	make clean -C libft
	make clean -C libgf
	make clean -C mlx

re_libs:
	make re -C libft
	make re -C libgf
	make re -C mlx

.PHONY: all clean clean_ fclean fclean_ re re_ re_libs clean_libs FORCE

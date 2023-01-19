NAME = libgf.a

FILES = \
	gf_camera gf_color gf_color2 \
	gf_strtodouble gf_utils \
	gf_vector gf_vector2 gf_vector3 \
	cplx cplx2 cplx3 gf_img

OFILES = $(FILES:%=%.o)

CFLAGS = -Wall -Wextra -Werror

INC = -I. -I..

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $@ $?

$(OFILES): %.o: %.c
	gcc $(CFLAGS) $(OPTIM) $(INC) -c $< -o $@

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re

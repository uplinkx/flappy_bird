NAME = flappy_bird
NAMEW = index.html

FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/ -I includes/SDLX/
LIBRARIES = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="['png']"
SKELE_HTML = --shell-file srcs/skeleton.html

SDL_LIB = -L ~/.brew/lib -l SDL2 -l sdl2_image -l SDL2_ttf

PRELOAD_FILES =							\
	resources/


PRELOAD = --preload-file $(PRELOAD_FILES)

all: $(NAME)

SDLX_DIR = SDLX/
BIN_DIR = bin/

SDLX_NAMES = 			\
	SDLX_background		\
	SDLX_button_loop	\
	SDLX_button			\
	SDLX_collide		\
	SDLX_collisions		\
	SDLX_init			\
	SDLX_input			\
	SDLX_ticks			\
	SDLX_math			\
	SDLX_render_queue	\
	SDLX_render			\
	SDLX_utils			\
	SDLX_utilsX			\
	SDLX_xbox			\

FILE_NAMES =		\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))		\
	carve_texture	\
	game_input		\
	itow			\
	main			\
	pipe			\
	player			\
	render			\
	update			\



SRC_FILES = $(addsuffix .c, $(addprefix srcs/, $(FILE_NAMES)))

OBJS = $(addprefix $(BIN_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)


allw:
	emcc -Wall -Wextra -Werror -O0 $(INCLUDES) -D EMCC $(LIBRARIES) $(PRELOAD) $(SRC_FILES) $(SKELE_HTML) -o $(NAMEW)

$(NAME): $(BIN_DIR) $(OBJS)
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(SDL_LIB)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# These are the target object file names given by path ($(OBJS)).
# We will create the required directories with mkdir -p.
$(BIN_DIR)%.o: %.c
	@mkdir -p $(BIN_DIR)$(dir $<)
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

run:
	rm -f $(NAME)
	make -j all
	clear
	@echo "\033[1m\033[32m$(NAME)\033[0m"
	@./$(NAME)


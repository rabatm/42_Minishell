NAME = minishell

SRC_DIR = srcs

OBJS_DIR = objs

LIBFT_DIR = libft
LIBFT_NAME = libft.a

DEP_FILE = .depend

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

RM = rm -rf

MAKE = make

GREEN = echo "\033[32m$1\033[0m"
RED = echo "\033[31m$1\033[0m"

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

INCLUDES = -I includes -I $(LIBFT_DIR)/includes

LIBS = -L $(LIBFT_DIR) -lft -lreadline

.PHONY: all clean fclean re libft_fclean

all: $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT_NAME) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@$(call GREEN, "Compilation of $(NAME) done")

$(LIBFT_DIR)/$(LIBFT_NAME):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(call GREEN, "Compilation of $(LIBFT_NAME) done")

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@$(call GREEN, "Compilation of $@ done")

$(DEP_FILE): $(SRCS) $(INCLUDES)
	@$(CC) $(CFLAGS) -MM $^ > $@

clean:
	@$(RM) $(OBJS_DIR) $(DEP_FILE)
	@$(call RED, "Objects files deleted")

fclean: clean libft_fclean
	@$(RM) $(NAME)
	@$(call RED, "$(NAME) deleted")

re: fclean all

libft_fclean:
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(call RED, "$(LIBFT_NAME) deleted")
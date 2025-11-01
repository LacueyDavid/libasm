NAME = libasm.a
NASM = nasm
NASMFLAGS = -f elf64 -DPIC
AR = ar
ARFLAGS = rcs
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
RM = rm -f

ASM_DIR = src
ASM_SRCS = $(ASM_DIR)/ft_strlen.s \
					 $(ASM_DIR)/ft_strcpy.s \
					 $(ASM_DIR)/ft_strcmp.s \
					 $(ASM_DIR)/ft_write.s \
					 $(ASM_DIR)/ft_strdup.s \
					 $(ASM_DIR)/ft_read.s
ASM_OBJS = $(ASM_SRCS:.s=.o)

TEST_SRCS = main.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_BIN = tests

all: $(NAME)

$(NAME): $(ASM_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(ASM_DIR)/%.o: $(ASM_DIR)/%.s
	$(NASM) $(NASMFLAGS) $< -o $@

$(TEST_OBJS): $(TEST_SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. -l:$(NAME) -o $@

test: $(TEST_BIN)

run: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	$(RM) $(ASM_OBJS) $(TEST_OBJS) compile_commands.json testwr1.txt

fclean: clean
	$(RM) $(NAME) $(TEST_BIN)

re: fclean all

.PHONY: all clean fclean re run

NAME := tiny_file.exe
TEST_NAME = $(TEST_OUTPUT_DIR)/test_huffman
.DEFAULT_GOAL := all
CC := cc
AR := ar
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
INC_DIRS := . libft src include
SRC_DIRS := src libft libft/printf libft/get_next_line
TEST_OUTPUT_DIR := test_output

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS :=	src/main.c \
       	src/huffman/huffman_decode.c \
		src/huffman/huffman_tree.c \
		src/huffman/huffman.c \
       	src/rle/rle.c \
       	src/file_io/file_io.c \
       	src/utils/utils.c \

TEST_SRCS := tests/test_huffman.c
LIBFT_SRCS := libft/*.c libft/printf/*.c libft/get_next_line/get_next_line.c libft/get_next_line/get_next_line_utils.c
SRCS += $(LIBFT_SRCS)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
TEST_OBJS := $(addprefix $(OBJ_DIR)/, $(TEST_SRCS:%.c=%.o))
# BONUS_OBJS := $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:%.c=%.o))
# GNL_OBJS := $(addprefix $(OBJ_DIR)/, $(GNL_SRCS:%.c=%.o))
# GC_OBJS := $(addprefix $(OBJ_DIR)/, $(GC_SRCS:%.c=%.o))


LIBFT := libft/libft.a

################################################################################
########                         COMPILING                      ################
################################################################################

# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I$(INC_DIRS)
# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
CFLAGS := -g -MMD -MP $(addprefix -I, $(INC_DIRS))
# LDFLAGS := -Llibft -lft
# ARFLAGS := -rcs

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Rule to compile .o files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_NAME): $(TEST_OBJS) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) $(LIBFT) -o $(TEST_NAME)

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(OBJS) $(LIBFT)
	@mkdir -p $(TEST_OUTPUT_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) $(LIBFT) -o $(TEST_NAME)

test_clean:
	$(RM) $(TEST_OUTPUT_DIR)/*
	rm -f $(TEST_OBJS) $(TEST_NAME)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean submodule_update all

submodule_update:
	git submodule update --remote --merge

# bonus: all

re_sub: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

help:
	@echo "Makefile for $(NAME)"
	@echo "Usage:"
	@echo "	make						Build the project"
	@echo "	make test					Testing"
	@echo "	make clean					Remove object files in the main project"
	@echo "	make fclean					Remove all build files, including libft's objects"
	@echo "	make re						Clean and rebuild the project"
	@echo "	make submodule_update				Update all submodules to the latest commit"
	@echo "	make re_submodule				Fully reset and update submodules"
	@echo "	make submodule_rebuild				Reinitialize submodules from scratch"
	@echo "	make help					Display this help message"

-include $(OBJS:%.o=%.d)
# -include $(BONUS_OBJS:%.o=%.d)
# -include $(GNL_OBJS:%.o=%.d)

.PHONY: all clean fclean re re_sub submodule_rebuild submodule_update test test_clean help
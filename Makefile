NAME := tiny_file.exe
.DEFAULT_GOAL := all
CC := cc
AR := ar
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
INC_DIRS := . printf get_next_line
SRC_DIRS := src libft libft/printf libft/get_next_line

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS := main.c

LIBFT_SRCS := libft/*.c printf/*.c get_next_line/*.c

SRCS += $(LIBFT_SRCS)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
# BONUS_OBJS := $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:%.c=%.o))
# GNL_OBJS := $(addprefix $(OBJ_DIR)/, $(GNL_SRCS:%.c=%.o))
# GC_OBJS := $(addprefix $(OBJ_DIR)/, $(GC_SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I$(INC_DIRS)
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS :=
ARFLAGS := -rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean submodule_update all

submodule_update:
	git submodule update --remote --merge

# bonus: all

re_sub: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

-include $(OBJS:%.o=%.d)
# -include $(BONUS_OBJS:%.o=%.d)
# -include $(GNL_OBJS:%.o=%.d)

.PHONY: all clean fclean re re_sub submodule_rebuild
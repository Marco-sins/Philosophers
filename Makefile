CC := gcc
CFLAGS := -g -Wall -Werror -Wextra -Iincludes

RM := rm -fr

SOURCES :=	main.c \
			ft_init.c \
			free.c \
			monitor.c \
			philo_routine.c \
			utils.c

HEADERS := philo.h

OBJDIR	:= objs
OBJS	:= $(SOURCES:%.c=$(OBJDIR)/%.o)

NAME := philo

all: $(NAME)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJDIR)
		@echo 🔥 🔥 Deleting all .o Files 🗑️ 🗑️

fclean: clean
		$(RM) $(NAME)
		@echo  🔥 🔥 Deleting executables files 🗑️ 🗑️

re: fclean all

.PHONY: all clean fclean re
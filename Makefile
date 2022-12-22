NAME := monitoring

FILES := main.c init_and_parse.c destroy.c thread_util.c\
		 base_destroy.c base_init.c \
		 dns_init.c	dns_util.c dns_monitor.c\
		 http_init.c http_methods.c http_monitor.c http_util.c callback.c\
		 ping_init.c ping_util.c ping_monitor.c\
		 check_input.c checkers.c\
		 get_time.c statistic.c time_analyze.c\
		 simplify.c

CC := clang

FLAGS := -lcurl -lpthread -lcares

INCLUDE := -Iheaders

VPATH := dns_method http_method ping_method base \
		 input_check main simplify time_analyze

OBJ_FILES := $(FILES:c=o)
OBJ := $(addprefix obj/, $(OBJ_FILES))

.PHONY=all clean fclean

all: $(NAME)

re: fclean $(NAME)

obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -c $^ -o $@

$(NAME): $(OBJ)
	$(CC) $(INCLUDE) $(FLAGS) -o $@ $(OBJ)

clean:
	rm -rf obj

fclean: clean
	rm -rf monitoring

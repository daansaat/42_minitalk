GREEN = \033[0;32m
PURPLE = \033[0;35m
YELLOW = \033[0;33m
RESET = \033[0m

SRCS_SERVER = server.c
SRCS_CLIENT = client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
FLAGS = -Wall -Werror -Wextra
INC = -I ./libft
LIB = -L ./libft -l ft

all: libft/libft.a server client
	@make graphic

server: $(OBJS_SERVER)
	$(CC) $(FLAGS) $(INC) $(LIB) $(SRCS_SERVER) -o server

client: $(OBJS_CLIENT)
	$(CC) $(FLAGS) $(INC) $(LIB) $(SRCS_CLIENT) -o client

%.o: %.c
	@echo "$(PURPLE)compiling $@$(RESET)"
	$(CC) -c $(INC) $< -o $@

libft/libft.a:
	@echo "$(YELLOW)compiling $@$(RESET)"
	make -C ./libft

clean:
	make -C libft clean
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	make -C libft fclean
	rm -f server client

re: fclean all

graphic:
	@echo "\n"
	@echo "$(GREEN)███╗░░░███╗██╗███╗░░██╗██╗████████╗░█████╗░██╗░░░░░██╗░░██╗"
	@echo "$(GREEN)████╗░████║██║████╗░██║██║╚══██╔══╝██╔══██╗██║░░░░░██║░██╔╝"
	@echo "$(GREEN)██╔████╔██║██║██╔██╗██║██║░░░██║░░░███████║██║░░░░░█████═╝░"
	@echo "$(GREEN)██║╚██╔╝██║██║██║╚████║██║░░░██║░░░██╔══██║██║░░░░░██╔═██╗░"
	@echo "$(GREEN)██║░╚═╝░██║██║██║░╚███║██║░░░██║░░░██║░░██║███████╗██║░╚██╗"
	@echo "$(GREEN)╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝$(RESET)\n"

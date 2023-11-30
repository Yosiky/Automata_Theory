CC		=	g++
CFLAGS	=	--std=c++11 -g

INC_DIR =	include
INCS	=	-I include/

LIBS	=

SRC_DIR	=	src
SRCS	=	main.cpp				\
			dnf.cpp					\
			implicant.cpp			

OBJ_DIR =	obj
OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

NAME	=	lab2

.PHONY: all clean fclean re run


all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
	g++ $(CFLAGS) $(INCS) -c $< -o $@ $(LIBS) 

$(OBJ_DIR):
	mkdir $@

$(NAME): Makefile $(OBJS)
	$(CC) $(INCS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: all
	./$(NAME)

CC		=	g++
CFLAGS	=	--std=c++11

INC_DIR =	include
INCS	=	-I include/

LIBS	=

SRC_DIR	=	src
SRCS	=	main.cpp				\
			dnf.cpp					\
			implicant.cpp			\
			read_dnf_from_file.cpp	\
			write_dnf_in_file.cpp 

OBJ_DIR =	obj
OBJS	=	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

NAME	=	lab1

.PHONY: all clean fclean re


all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -c $? -o $@ $(LIBS) $(INCS)

$(OBJ_DIR):
	mkdir $@

$(NAME): $(OBJS)
	$(CC) $? -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

_END		=	\033[0;0m
_RED		=	\033[0;31m
_GREEN		=	\033[0;32m

NAME = twicyrc

CXX = clang++

CXXFLAGS = -std=c++11 -I ${INC_DIR} -pthread

INC_DIR = ./includes

SRCS = $(wildcard ./srcs/*.cpp)

OBJS = $(patsubst %.cpp, %.o, ${SRCS})

$(NAME) : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME) 

%.o : %.cpp
	$(CXX) -o $@ -c $^ $(CXXFLAGS)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

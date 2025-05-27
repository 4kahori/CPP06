NAME		= convert

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
RM			= rm -f

# source files
SRCS		= main.cpp			\
			  ScalarConverter.cpp	
			  
OBJS		= $(SRCS:.cpp=.o)

# colors
RESET		= \033[0m
GRAY		= \033[1;90m
RED			= \033[1;91m
GREEN		= \033[1;92m
YELLOW		= \033[1;93m
BLUE		= \033[1;94m
MAGENTA		= \033[1;95m
CYAN		= \033[1;96m

all: $(NAME)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $<

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "$(GREEN)  Conversion of scalar types ✅ $(RESET)"

clean:
	@$(RM) $(OBJS)

fclean:
	@make clean
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re buildCFLAGS -Wall -Wextra -Werror -std=c++98


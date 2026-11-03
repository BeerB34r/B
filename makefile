# project management
include srcfiles.mk
SRCDIR		= src/
INCDIR		= inc/
DEPDIR		= dep/
BINDIR		= bin/
DEP		= $(addprefix $(DEPDIR),$(SRC:.c=.d) $(BSRC:.c=.d))
BIN		= $(addprefix $(BINDIR),$(SRC:.c=.o))
BBIN		= $(addprefix $(BINDIR),$(BSRC:.c=.o))
INC		= -I$(INCDIR)

# programs
CC		= cc -c
CPP		= cc -E
LD		= cc # implicit libc :pensive:
AS		= as
RM		= rm -fr

# flags
CFLAGS		= -Wall -Wextra -Werror -std=c2x
CPPFLAGS	= $(INC)
LDFLAGS		=

# dependency management
DEPFLAG		= -M -MF $@ -MT $@ -MT $(BINDIR)$(notdir $(basename $<)).o

# makefile management
VPATH		= $(SRCDIR) $(INCDIR)
MAKEFLAGS	+= -r --no-print-directory -j
.EXTRA_PREREQS	= $(firstword $(MAKEFILE_LIST))
.DEFAULT_GOAL	= all
.PRECIOUS	: $(BINDIR) $(DEPDIR)
.PHONY		: clean fclean re all test bonus clangd
-include $(DEP)

NAME		= B
BONUS_NAME	= Bonus

test		: $(NAME)

all		: $(NAME)
$(NAME)		: $(BIN)
	$(LD) -o $@ $^
bonus		: $(BONUS_NAME)
$(BONUS_NAME)	: $(BIN) $(BBIN)
	$(LD) -o $@ $^

$(BINDIR)%.o	: %.c | $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<
$(DEPDIR)%.d	: %.c | $(DEPDIR)
	$(CPP) $(CPPFLAGS) $(DEPFLAG) $<

%/		:
	@mkdir -p $@
clean		:
	$(RM) $(BINDIR)
fclean		:
	$(RM) $(BINDIR) $(DEPDIR) $(NAME) $(BONUS_NAME)
re		:
	+$(MAKE) fclean
	+$(MAKE)
clangd		:
	intercept-build-15 $(MAKE) -B

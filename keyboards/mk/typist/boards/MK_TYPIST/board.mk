# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/MK_TYPIST/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/MK_TYPIST

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)

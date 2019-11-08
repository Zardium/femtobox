.RECIPEPREFIX=>

# Macros ========================================

ASSIGNMENTNAME=femtobox
SRC_EXT=.c

OUTPUT_DIR=./bin/
OBJECT_DIR=$(OUTPUT_DIR)obj/
SOURCE_DIR=./src/
INCLUDE=./include/

EXE=$(OUTPUT_DIR)$(ASSIGNMENTNAME)

CC=gcc
CXX=clang++
COMPILER=$(CC)
CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -g
LFLAGS=-lSDL2 -lm
FLAGS=

ERASE=rm

NUMBERS=0 1 2 3 4 5 6 7 8 9 10 11
NAMES=all add_front add_end remove1 remove2 insert_before1 insert_after1 find1 \
find2 find_stress1 find_stress2 test_a_lot

SRC=$(wildcard $(SOURCE_DIR)*$(SRC_EXT))
OBJ=$(patsubst $(SOURCE_DIR)%$(SRC_EXT),$(OBJECT_DIR)%.o, $(SRC))

ZIPPABLES=$(SRC) ./typescript ./latex/refman.pdf

# TARGETS ========================================

build : $(EXE)
	
$(EXE) : $(OBJ)
>$(COMPILER) $(CFLAGS) -I$(INCLUDE) $^ -o $@ $(LFLAGS) 

$(OBJECT_DIR)%.o : $(SOURCE_DIR)%$(SRC_EXT) | $(OBJECT_DIR)
>$(COMPILER) $(CFLAGS) -I$(INCLUDE) -c $^ -o $@

$(OBJECT_DIR) :
>mkdir -p $(OBJECT_DIR)

$(NUMBERS) :
>./$(EXE) $@ > student-output-$(word $(shell expr $@ + 1), $(NAMES))
>diff ./output-$(word $(shell expr $@ + 1), $(NAMES)).txt ./student-output-$(word $(shell expr $@ + 1), $(NAMES))

run :
>$(EXE) $(FLAGS)

clean :
>$(ERASE) $(OBJ) $(EXE)

rebuild: clean build

try : build run

script :
>script -c "bash -x ./$(ASSIGNMENTNAME)script.sh"

preprocess :
>$(COMPILER) $(CFLAGS) -I$(INCLUDE) -E $(SRC) -o preprocessed$(SRC_EXT)

zip :
>zip submission_$(ASSIGNMENTNAME).zip -xi $(ZIPPABLES)

# debug printing of variables at runtime
print-%  : ; @echo $*=$($*)
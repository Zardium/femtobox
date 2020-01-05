.RECIPEPREFIX=>

# Macros ========================================

PROJECT=femtobox
SRC_EXT=.c

OUT_DIR=bin
OBJ_DIR=$(OUT_DIR)/obj
SRC_DIR=src
DATA_DIR=data
INCLUDE=include

EXE=$(OUT_DIR)/$(PROJECT)

CC=clang
CXX=g++
COMPILER=$(CC)
LINKER=ld
CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -g -O0
LFLAGS=-lSDL2 -lm
FLAGS=

ERASE=rm -rf

NUMBERS=0 1 2 3 4 5 6 7 8 9 10 11
NAMES=all add_front add_end remove1 remove2 insert_before1 insert_after1 find1 \
find2 find_stress1 find_stress2 test_a_lot

SRC=$(wildcard $(SRC_DIR)/*$(SRC_EXT)) $(wildcard $(SRC_DIR)/**/*$(SRC_EXT))
DATA=$(wildcard $(DATA_DIR)/*) $(wildcard $(DATA_DIR)/**/*)
OBJ=$(patsubst $(SRC_DIR)/%$(SRC_EXT),$(OBJ_DIR)/%.o, $(SRC))
DATA_OBJ=$(patsubst %,$(OBJ_DIR)/%.o, $(DATA))

ZIPPABLES=$(SRC) typescript latex/refman.pdf



# TARGETS ========================================

build : $(EXE)
	
$(EXE) : $(OBJ) $(DATA_OBJ) | $(OUT_DIR)
>$(COMPILER) $(CFLAGS) -I$(INCLUDE) $^ -o $@ $(LFLAGS)

.SECONDEXPANSION:

$(OBJ_DIR)/%.o : $(SRC_DIR)/%$(SRC_EXT) | $$(dir $$@)
>$(COMPILER) $(CFLAGS) -I$(INCLUDE)/ -c $< -o $@

$(OBJ_DIR)/$(DATA_DIR)/%.o : $(DATA_DIR)/% | $$(dir $$@)
>$(LINKER) -r -b binary -o $@ $<
# --leading-underscore

.SECONDARY: ./**/

%/ :
>mkdir -p $@

$(NUMBERS) :
>./$(EXE) $@ > student-output-$(word $(shell expr $@ + 1), $(NAMES))
>diff ./output-$(word $(shell expr $@ + 1), $(NAMES)).txt ./student-output-$(word $(shell expr $@ + 1), $(NAMES))

run :
>$(EXE) $(FLAGS)

clean :
>$(ERASE) $(OBJ_DIR) $(OBJ) $(DATA_OBJ) $(EXE)

rebuild: clean build

try : build run

script :
>script -c "bash -x ./$(PROJECT)script.sh"

preprocess :
>$(COMPILER) $(CFLAGS) -I$(INCLUDE) -E $(SRC) -o preprocessed$(SRC_EXT)

zip : $(ZIPPABLES)
>zip submission_$(PROJECT).zip -xi $?

# debug printing of variables at runtime
print-%  : ; @echo $*=$($*)

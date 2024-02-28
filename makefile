# VC6 makefile

BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
RC_DIR = rc
SRC_DIR = src
DEF_DIR = def

RC_FILE = $(RC_DIR)\main.rc
CPP_FILES = $(SRC_DIR)\*.cpp
#COMMON_DEF = $(DEF_DIR)\Common.def

RES_FILE = $(OBJ_DIR)\main.RES
OBJ_FILES = $(OBJ_DIR)\*.obj
#COMMON_LIB = $(OBJ_DIR)\Common.lib

OUTPUT_FILE = $(BIN_DIR)\Cloak.dll

CXX_FLAGS = /c /GX /O2 /nologo /W3 /WX /LD /MD
LD_FLAGS = /DLL /FILEALIGN:512 /NOLOGO /RELEASE
LIB_FLAGS = /NOLOGO /MACHINE:IX86

$(OUTPUT_FILE): $(RES_FILE) $(OBJ_FILES) $(BIN_DIR)
    link $(OBJ_FILES) $(RES_FILE) $(LD_FLAGS) /OUT:$(OUTPUT_FILE)

{$(SRC_DIR)}.cpp{$(OBJ_DIR)}.obj::
    $(CPP) $(CXX_FLAGS) $< -I$(INCLUDE_DIR) /Fo./$(OBJ_DIR)/

$(RES_FILE): $(RC_FILE) $(OBJ_DIR)
    rc /fo $(RES_FILE) $(RC_FILE)

$(OBJ_DIR):
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(BIN_DIR):
    if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Dependencies
$(SRC_DIR)\main.cpp: $(INCLUDE_DIR)\utils.h $(INCLUDE_DIR)\cloak_key.h $(INCLUDE_DIR)\Freelancer.h
$(SRC_DIR)\utils.cpp: $(INCLUDE_DIR)\utils.h
$(SRC_DIR)\cloak_key.cpp: $(INCLUDE_DIR)\cloak_key.h $(INCLUDE_DIR)\Freelancer.h

clean:
	del $(BIN_DIR)\*.dll $(OBJ_DIR)\*.obj $(OBJ_DIR)\*.RES $(OBJ_DIR)\*.lib

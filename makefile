# VC6 makefile

BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
RC_DIR = rc
SRC_DIR = src
DEF_DIR = def

RC_FILE = $(RC_DIR)\main.rc
COMMON_DEF = $(DEF_DIR)\Common.def

RES_FILE = $(OBJ_DIR)\main.RES
OBJ_FILES = $(OBJ_DIR)\cloak_key.obj $(OBJ_DIR)\main.obj $(OBJ_DIR)\utils.obj $(OBJ_DIR)\config.obj
COMMON_LIB = $(OBJ_DIR)\Common.lib

OUTPUT_FILE = $(BIN_DIR)\Cloak.dll

CPP_FLAGS = /c /O2 /nologo /W3 /WX /LD /MD
LD_FLAGS = /DLL /NOLOGO /RELEASE
LIB_FLAGS = /NOLOGO /MACHINE:IX86

$(OUTPUT_FILE): $(RES_FILE) $(COMMON_LIB) $(OBJ_FILES) $(BIN_DIR)
    link $(OBJ_FILES) $(COMMON_LIB) $(RES_FILE) $(LD_FLAGS) /OUT:$(OUTPUT_FILE)

{$(SRC_DIR)}.cpp{$(OBJ_DIR)}.obj::
    $(CPP) $(CPP_FLAGS) $< -I$(INCLUDE_DIR) /Fo./$(OBJ_DIR)/

$(OBJ_FILES): makefile

$(OBJ_DIR)\cloak_key.obj: $(SRC_DIR)\cloak_key.cpp $(INCLUDE_DIR)\cloak_key.h $(INCLUDE_DIR)\Freelancer.h
$(OBJ_DIR)\main.obj: $(SRC_DIR)\main.cpp $(INCLUDE_DIR)\utils.h $(INCLUDE_DIR)\Freelancer.h $(INCLUDE_DIR)\cloak_key.h $(INCLUDE_DIR)\config.h
$(OBJ_DIR)\utils.obj: $(SRC_DIR)\utils.cpp $(INCLUDE_DIR)\utils.h
$(OBJ_DIR)\config.obj: $(SRC_DIR)\config.cpp $(INCLUDE_DIR)\config.h $(INCLUDE_DIR)\Common.h

$(RES_FILE): $(RC_FILE) $(OBJ_DIR) makefile
    rc /fo $(RES_FILE) $(RC_FILE)

$(COMMON_LIB): $(COMMON_DEF) makefile
    lib $(LIB_FLAGS) /def:$(COMMON_DEF) /name:COMMON /out:$(COMMON_LIB)

$(OBJ_DIR):
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(BIN_DIR):
    if not exist $(BIN_DIR) mkdir $(BIN_DIR)

clean:
    del $(BIN_DIR)\*.dll $(OBJ_DIR)\*.obj $(OBJ_DIR)\*.RES $(OBJ_DIR)\*.lib

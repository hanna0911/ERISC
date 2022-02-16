# Project: ERISC大作业 DEV项目

CPP      = g++
CC       = gcc
OBJ      = "ERISC\ FINAL/main.o" "ERISC\ FINAL/pro_control.o" "ERISC\ FINAL/pro_draw.o" "ERISC\ FINAL/pro_header.o" "ERISC\ FINAL/pro_initialize.o" "ERISC\ FINAL/pro_input.o" "ERISC\ FINAL/pro_memory.o" "ERISC\ FINAL/pro_output.o" "ERISC\ FINAL/pro_recognize.o" "ERISC\ FINAL/pro_register.o" "ERISC\ FINAL/pro_stack.o"
LINKOBJ  = "ERISC FINAL/main.o" "ERISC FINAL/pro_control.o" "ERISC FINAL/pro_draw.o" "ERISC FINAL/pro_header.o" "ERISC FINAL/pro_initialize.o" "ERISC FINAL/pro_input.o" "ERISC FINAL/pro_memory.o" "ERISC FINAL/pro_output.o" "ERISC FINAL/pro_recognize.o" "ERISC FINAL/pro_register.o" "ERISC FINAL/pro_stack.o"
BIN      = "ERISC_executable"
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN)

"ERISC\ FINAL/main.o": ERISC\ FINAL/main.cpp
	$(CPP) -c "ERISC FINAL/main.cpp" -o "ERISC FINAL/main.o"

"ERISC\ FINAL/pro_control.o": ERISC\ FINAL/pro_control.cpp
	$(CPP) -c "ERISC FINAL/pro_control.cpp" -o "ERISC FINAL/pro_control.o"

"ERISC\ FINAL/pro_draw.o": ERISC\ FINAL/pro_draw.cpp
	$(CPP) -c "ERISC FINAL/pro_draw.cpp" -o "ERISC FINAL/pro_draw.o"

"ERISC\ FINAL/pro_header.o": ERISC\ FINAL/pro_header.cpp
	$(CPP) -c "ERISC FINAL/pro_header.cpp" -o "ERISC FINAL/pro_header.o"

"ERISC\ FINAL/pro_initialize.o": ERISC\ FINAL/pro_initialize.cpp
	$(CPP) -c "ERISC FINAL/pro_initialize.cpp" -o "ERISC FINAL/pro_initialize.o"

"ERISC\ FINAL/pro_input.o": ERISC\ FINAL/pro_input.cpp
	$(CPP) -c "ERISC FINAL/pro_input.cpp" -o "ERISC FINAL/pro_input.o"

"ERISC\ FINAL/pro_memory.o": ERISC\ FINAL/pro_memory.cpp
	$(CPP) -c "ERISC FINAL/pro_memory.cpp" -o "ERISC FINAL/pro_memory.o"

"ERISC\ FINAL/pro_output.o": ERISC\ FINAL/pro_output.cpp
	$(CPP) -c "ERISC FINAL/pro_output.cpp" -o "ERISC FINAL/pro_output.o"

"ERISC\ FINAL/pro_recognize.o": ERISC\ FINAL/pro_recognize.cpp
	$(CPP) -c "ERISC FINAL/pro_recognize.cpp" -o "ERISC FINAL/pro_recognize.o"

"ERISC\ FINAL/pro_register.o": ERISC\ FINAL/pro_register.cpp
	$(CPP) -c "ERISC FINAL/pro_register.cpp" -o "ERISC FINAL/pro_register.o"

"ERISC\ FINAL/pro_stack.o": ERISC\ FINAL/pro_stack.cpp
	$(CPP) -c "ERISC FINAL/pro_stack.cpp" -o "ERISC FINAL/pro_stack.o"

#
# Makefile
# , 2020-03-01 22:30
#

GXX=g++
FLAGS= -g -std=c++11
LIBS= -lboost_system -lpthead

BUILD_LIB=$(GXX) $(FLAGS) -I . -L lib/ -c -Wall -Werror -fpic $(DEPENDENCY_FILES) -o $(TARGET_NAME).out $(LIB_LOAD) && $(GXX) -L lib/ -shared -o lib/lib$(TARGET_NAME).so $(TARGET_NAME).out $(LIB_LOAD)

build_lib: 
	$(BUILD_LIB)

PatternCapture : CommonUtils.cpp Dependencies.cpp  PatternCapture.cpp
	$(GXX) $(FLAGS) -I . -L lib/ -Wall -Werror $^ -o bin/$@ -lboost_system -lboost_filesystem -lcapturesource


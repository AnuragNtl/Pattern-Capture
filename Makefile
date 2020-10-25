#
# Makefile
# , 2020-03-01 22:30
#

GXX=g++
FLAGS= -g -std=c++11
LIBS= -lboost_system -lpthead
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(shell dirname $(mkfile_path))/


BUILD_LIB=$(GXX) $(FLAGS) -I . -L lib/ -c -Wall -Werror -fpic $(DEPENDENCY_FILES) -o $(TARGET_NAME).out $(LIB_LOAD) && $(GXX) -L lib/ -shared -o lib/lib$(TARGET_NAME).so $(TARGET_NAME).out -Wl,-z,defs $(LIB_LOAD)

build_library=$(GXX) $(FLAGS) $(4) -I $(current_dir) -L $(current_dir)lib/ -c -Wall -Werror -fpic $(1) -o $(current_dir)$(2).out $(3) && $(GXX) -L $(current_dir)lib/ -shared -o $(current_dir)lib/lib$(2).so $(current_dir)$(2).out -Wl,-z,defs $(3)

all: PatternCapture Captures Transforms HookLib Hooks ApiClientLib Api

build_lib: 
	$(BUILD_LIB)

HookLib:
	$(MAKE) build_lib DEPENDENCY_FILES=core/engine/hooks/Hooks.cpp TARGET_NAME=Hooks


PatternCapture : CommonUtils.cpp Dependencies.cpp  PatternCapture.cpp core/engine/graphparser/GraphParser.cpp core/engine/graphparser/JsonGraphParser/JsonGraphParser.cpp core/scheduler/Scheduler.cpp core/engine/graphparser/GraphParserFactory.cpp core/engine/hooks/Hooks.cpp
	$(GXX) $(FLAGS) -I . -L lib/ -Wall -Werror $^ -o bin/$@ -lboost_system -lboost_filesystem -ldl -lpthread


crawl_and_build=@for i in $$(ls $(1)); do if [ -d "$(1)/$$i" ]; then if [ -e "$(1)/$$i/Makefile" ]; then echo "Makefile exists " && make -C $(1)/$$i/ $$i ; else make -C . build_lib  DEPENDENCY_FILES=$$(ls -d $$(pwd)/$(1)/$$i/*.cpp) TARGET_NAME=$$i LIB_LOAD=$(2) ; fi; fi; done;

Captures:
	$(call crawl_and_build,Capture)

Transforms:
	$(call crawl_and_build,transform)

Hooks:
	$(call crawl_and_build,hooks)

ApiClientLib:
	$(MAKE) build_lib "DEPENDENCY_FILES=api/ApiClient.cpp" TARGET_NAME=ApiClient

Api:
	$(call crawl_and_build,api,-lApiClient)

Common:
	$(call crawl_and_build,common)




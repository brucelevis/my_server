CUR_DIR:=$(shell pwd)
OUTPUT_DIR:=$(CUR_DIR)/debug
BUILD_DIR:=$(CUR_DIR)/build

CXX:=ccache g++
#DEFINE:=-DLOCAL_DEBUG
CXXFLAGS:=-g -Wall -std=c++11 -Woverloaded-virtual $(DEFINE)
LDFLAGS+=-lpthread -lprotobuf
LIBS:=
MKDIR:=mkdir -p
RM:=rm -f
RMDIR:=rm -rf
CLI_TARGET:=$(OUTPUT_DIR)/my_client
SRV_TARGET:=$(OUTPUT_DIR)/my_server
AOI_TEST_TARGET:=$(OUTPUT_DIR)/aoi_test
RANK_TEST_TARGET:=$(OUTPUT_DIR)/rank_test

# pre header help make faster
PCH_H:=$(CUR_DIR)/src/Pre_Header.h
PCH:=$(CUR_DIR)/src/Pre_Header.h.gch

CLIENT:=$(CUR_DIR)/src/client
SERVER:=$(CUR_DIR)/src/server
AOI_TEST:=$(CUR_DIR)/src/aoi_test
RANK_TEST:=$(CUR_DIR)/src/rank_test

DIRS:=$(shell find $(CUR_DIR)/src -type d)
HEADERS:=$(foreach dir_var,$(DIRS),$(wildcard $(dir_var)/*.h))
HEADER_DIRS:=$(sort $(dir $(HEADERS)))
SRCS:=$(foreach dir_var,$(DIRS),$(wildcard $(dir_var)/*.cc))
SRC_DIRS:=$(sort $(dir $(SRCS)))
OBJS:=$(patsubst %.cc,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))
DEPS:=$(patsubst %.o,%.d,$(OBJS))
INCLUDES:=$(foreach dir_var,$(DIRS), -I $(dir_var))

export

vpath %.h $(HEADER_DIRS)
vpath %.cc $(SRC_DIRS)

.PHONY : all $(CLIENT) $(SERVER) $(AOI_TEST) $(RANK_TEST) clean clean_pch clean_all test_var
all: $(CLIENT) $(SERVER) $(AOI_TEST) $(RANK_TEST)

# depend rule clean don't need it
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), clean_pch)
ifneq ($(MAKECMDGOALS), clean_all)
-include $(DEPS)
endif
endif
endif
	
# dir create rule
$(OUTPUT_DIR) $(BUILD_DIR):
	$(MKDIR) $@

# pre header create rule
$(PCH): $(PCH_H)
	$(CXX) $(CXXFLAGS) $> $^

# object file create rule
$(BUILD_DIR)/%.o: %.cc $(PCH)
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

# depend file depend on build dir
$(DEPS): | $(BUILD_DIR)

# depend file create rule
$(BUILD_DIR)/%.d: %.cc
	@echo "making $@"
	@set -e; \
	$(RM) $@.tmp; \
	$(CXX) -E -MM $(CXXFLAGS) $(INCLUDES) $(filter %.cc,$^) > $@.tmp; \
	sed 's,\(.*\)\.o[:]*,$(BUILD_DIR)/\1.o $@:,g'<$@.tmp > $@; \
	$(RM) $@.tmp

$(CLIENT) $(SERVER) $(AOI_TEST) $(RANK_TEST) : $(OBJS) $(OUTPUT_DIR)
	$(MAKE) --directory=$@
	
# clean
clean:
	$(RMDIR) $(OUTPUT_DIR)
	$(RMDIR) $(BUILD_DIR)

# clean pre header
clean_pch:
	$(RM) $(PCH)
	
# clean all
clean_all: clean clean_pch
	
# show var for makefile test
test_var:
	@echo "headers:";echo $(HEADERS);echo -e "\nheader_dirs:";echo $(HEADER_DIRS); \
	echo -e "\nsrcs:"; echo $(SRCS);echo -e "\nsrc dirs:";echo $(SRC_DIRS); \
	echo -e "\nobjs:";echo $(OBJS);echo -e "\ndeps:";echo $(DEPS)
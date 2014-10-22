TARGET=$(OUTPUT_DIR)/my_aoi_test
CLI_DIRS=$(shell find ./ -type d) $(shell find ../define -type d) $(shell find ../utility -type d)
CLI_SRCS=$(foreach dir_var,$(CLI_DIRS),$(wildcard $(dir_var)/*.cc))
CLI_OBJS=$(patsubst %.cc,$(BUILD_DIR)/%.o,$(notdir $(CLI_SRCS)))

.PHONY : all
all: $(CLI_OBJS)
	$(CXX) -o $(TARGET) $(CLI_OBJS) $(LIBS) $(LDFLAGS)
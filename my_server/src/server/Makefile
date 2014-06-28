TARGET=$(OUTPUT_DIR)/my_server
SRV_DIRS=$(shell find ./ -type d) $(shell find ../define -type d) $(shell find ../utility -type d) $(shell find ../proto -type d)
SRV_SRCS=$(foreach dir_var,$(SRV_DIRS),$(wildcard $(dir_var)/*.cc))
SRV_OBJS=$(patsubst %.cc,$(BUILD_DIR)/%.o,$(notdir $(SRV_SRCS)))

.PHONY : all
all: $(SRV_OBJS)
	$(CXX) -o $(TARGET) $(SRV_OBJS) $(LIBS) $(LDFLAGS)
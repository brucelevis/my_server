TARGET=$(OUTPUT_DIR)/rank_test
DIRS=./ ../utility
SRCS=$(foreach dir_var,$(DIRS),$(wildcard $(dir_var)/*.cc))
OBJS=$(patsubst %.cc,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

.PHONY : all
all: $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(LDFLAGS)
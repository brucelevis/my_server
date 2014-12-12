TARGET=$(OUTPUT_DIR)/rank_test
OBJS=rank_test.o Log.o
OBJS_WITH_PATH=$(addprefix $(BUILD_DIR)/, $(OBJS))

.PHONY : all
all: $(OBJS_WITH_PATH)
	$(CXX) -o $(TARGET) $(OBJS_WITH_PATH) $(LIBS) $(LDFLAGS)
	

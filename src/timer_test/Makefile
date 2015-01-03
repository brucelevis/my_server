TARGET=$(OUTPUT_DIR)/timer_test
OBJS=timer_test_main.o Log.o Timer.o Time_Value.o Date_Time.o
OBJS_WITH_PATH=$(addprefix $(BUILD_DIR)/, $(OBJS))

.PHONY : all
all: $(OBJS_WITH_PATH)
	$(CXX) -o $(TARGET) $(OBJS_WITH_PATH) $(LIBS) $(LDFLAGS)
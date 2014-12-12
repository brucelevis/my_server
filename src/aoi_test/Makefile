TARGET=$(OUTPUT_DIR)/aoi_test
OBJS=aoi_test_main.o Log.o Aoi.o Object.o
OBJS_WITH_PATH=$(addprefix $(BUILD_DIR)/, $(OBJS))

.PHONY : all
all: $(OBJS_WITH_PATH)
	$(CXX) -o $(TARGET) $(OBJS_WITH_PATH) $(LIBS) $(LDFLAGS)
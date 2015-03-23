TARGET=$(OUTPUT_DIR)/proto_benchmark
OBJS=proto_benchmark_main.o google_speed.pb.o google_size.pb.o
OBJS_WITH_PATH=$(addprefix $(BUILD_DIR)/, $(OBJS))

.PHONY : all
all: $(OBJS_WITH_PATH)
	$(CXX) -o $(TARGET) $(OBJS_WITH_PATH) $(LIBS) $(LDFLAGS)
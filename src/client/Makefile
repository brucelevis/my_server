TARGET=$(OUTPUT_DIR)/my_client
OBJS=cli_main.o Log.o Client.o Tcp_Client.o Tcp_Connection.o Reactor.o Sock_Connector.o IPC_SAP.o Event.o Sock_IO.o Sock.o Msg_Block.o reg.pb.o login.pb.o
OBJS_WITH_PATH=$(addprefix $(BUILD_DIR)/, $(OBJS))

.PHONY : all
all: $(OBJS_WITH_PATH)
	$(CXX) -o $(TARGET) $(OBJS_WITH_PATH) $(LIBS) $(LDFLAGS)
	

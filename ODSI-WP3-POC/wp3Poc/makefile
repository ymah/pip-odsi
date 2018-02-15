NW_TARGET="WIN32"##Network target is either Scenario or WIN32

CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g

FREERTOS_INCLUDE = -IFreeRTOS/include -IFreeRTOS -IFreeRTOS/portable/MSVC-MingW
FREERTOS_TRACE_INCLUDE = -IFreeRTOSPlusTrace/include -IFreeRTOSPlusTrace/
UTILS_INCLUDE = -Iutils/include

NW_INCLUDE = -INWManager/include

TOKEN_SIMPLE_INCLUDE = -ITokenSimple/include
CLIENT_SIMPLE_INCLUDE = -IClient_Simple/include
CONFIG_SIMPLE_INCLUDE = -IConfig_Simple/include
KEY_SIMPLE_INCLUDE = -IKeyVault_Simple/include
COM_SIMPLE_INCLUDE = -ICommunicate_Simple/include

CLIENT_OBJ = obj/Client_SimpleAdaptor.o
CONFIG_OBJ = obj/Config_SimpleAdaptor.o
KEY_OBJ = obj/Key_SimpleAdaptor.o
TOKEN_OBJ = obj/Token_SimpleAdaptor.o
INTCOM_OBJ = obj/InternalCommunication_SimpleAdaptor.o
#NW_OBJ = obj/manageNW.o

APP_OBJ= obj/main.o obj/main_myapp.o obj/Run-time-stats-utils.o $(CORE_OBJ) $(CLIENT_OBJ) $(CONFIG_OBJ) $(KEY_OBJ) $(TOKEN_OBJ) $(INTCOM_OBJ)
APP_LIB= lib/libfreertos.a lib/libfreertos_trace.a lib/libutils.a lib/libtoken_simple.a lib/libclient_simple.a lib/libconfig_simple.a lib/libkey_simple.a lib/libmanageNW.a lib/libcom_simple.a
APP_LLIB=  -lfreertos -lfreertos_trace -lutils -ltoken_simple -lclient_simple -lconfig_simple -lkey_simple -lmanageNW -lcom_simple -lwinmm -lws2_32 -Llib 

CORE_INCLUDE = -Isrc/include
CORE_OBJ = obj/AdminManager.o obj/ConfigManager.o obj/KeyManager.o obj/InternalCommunication.o obj/TokenValidator.o

####ALL
all: bin/wp3app_freertos
	#rm -f lib/*

####CLEAN
clean:
	cd FreeRTOS && make clean
	cd FreeRTOSPlusTrace && make clean
	cd TokenSimple && make clean
	cd utils && make clean
	cd NWManager && make clean
	cd Client_Simple && make clean
	cd Config_Simple && make clean
	cd KeyVault_Simple && make clean
	cd Communicate_Simple && make clean
	rm -f lib/* obj/* bin/* 
	

####### My APP

bin/wp3app_freertos: $(APP_OBJ) $(APP_LIB)
	$(CC) -o bin/wp3app_freertos $(APP_OBJ) $(APP_LLIB)

obj/main.o: src/main_freertos.c
	$(CC) $(CFLAGS) -c src/main_freertos.c -o obj/main.o $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)

obj/main_myapp.o: src/main_myapp.c
	$(CC) $(CFLAGS) -c src/main_myapp.c -o obj/main_myapp.o $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(SIMPLE_INCLUDE) $(CORE_INCLUDE) $(UTILS_INCLUDE) $(NW_INCLUDE)

obj/Run-time-stats-utils.o: src/Run-time-stats-utils.c
	$(CC) $(CFLAGS) -c src/Run-time-stats-utils.c -o obj/Run-time-stats-utils.o $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)

####### FREERTOS

lib/libfreertos.a:
	cd FreeRTOS && $(MAKE) install

######## FreeRTOS Plus Trace

lib/libfreertos_trace.a:
	cd FreeRTOSPlusTrace && $(MAKE) install

######## Utils

lib/libutils.a:
	cd utils && $(MAKE) install
	
######## Simple Token validator

lib/libtoken_simple.a:
	cd TokenSimple && $(MAKE) install
	
####### Simple Client	
lib/libclient_simple.a:
	cd Client_Simple && $(MAKE) install

####### Simple Config Manager	

lib/libconfig_simple.a:
	cd Config_Simple && $(MAKE) install

####### Simple Key Vault	

lib/libkey_simple.a:
	cd KeyVault_Simple && $(MAKE) install
	
####### Internal Compunication

lib/libcom_simple.a:
	cd Communicate_Simple && $(MAKE) install
	
####### NW Manager

lib/libmanageNW.a:
	cd NWManager && $(MAKE) install TARGET=$(NW_TARGET)


######SimpleAdaptors
obj/Key_SimpleAdaptor.o: src/adaptor/Simple/ManageKey_SimpleAdaptor.c
	$(CC) $(CFLAGS) -c src/adaptor/Simple/ManageKey_SimpleAdaptor.c -o obj/Key_SimpleAdaptor.o $(KEY_SIMPLE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(CORE_INCLUDE) $(UTILS_INCLUDE)

obj/Config_SimpleAdaptor.o: src/adaptor/Simple/ManageDomain_SimpleAdaptor.c
	$(CC) $(CFLAGS) -c src/adaptor/Simple/ManageDomain_SimpleAdaptor.c -o obj/Config_SimpleAdaptor.o $(CONFIG_SIMPLE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(CORE_INCLUDE) $(UTILS_INCLUDE)

obj/Client_SimpleAdaptor.o: src/adaptor/Simple/routeCommand_SimpleAdaptor.c
	$(CC) $(CFLAGS) -c src/adaptor/Simple/routeCommand_SimpleAdaptor.c -o obj/Client_SimpleAdaptor.o $(CLIENT_SIMPLE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(CORE_INCLUDE) $(UTILS_INCLUDE)
	
obj/Token_SimpleAdaptor.o: src/adaptor/Simple/validateToken_SimpleAdaptor.c
	$(CC) $(CFLAGS) -c src/adaptor/Simple/validateToken_SimpleAdaptor.c -o obj/Token_SimpleAdaptor.o $(TOKEN_SIMPLE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(CORE_INCLUDE) $(UTILS_INCLUDE)

obj/InternalCommunication_SimpleAdaptor.o: src/adaptor/Simple/Communicate_SimpleAdaptor.c
	$(CC) $(CFLAGS) -c src/adaptor/Simple/Communicate_SimpleAdaptor.c -o obj/InternalCommunication_SimpleAdaptor.o $(COM_SIMPLE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(CORE_INCLUDE) $(UTILS_INCLUDE)

######Core
obj/AdminManager.o: src/core/AdminManager.c
	$(CC) $(CFLAGS) -c src/core/AdminManager.c -o obj/AdminManager.o $(CORE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE) 
obj/ConfigManager.o: src/core/ConfigManager.c
	$(CC) $(CFLAGS) -c src/core/ConfigManager.c -o obj/ConfigManager.o $(CORE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)
obj/KeyManager.o: src/core/KeyManager.c
	$(CC) $(CFLAGS) -c src/core/KeyManager.c -o obj/KeyManager.o $(CORE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)
obj/InternalCommunication.o: src/core/InternalCommunication.c
	$(CC) $(CFLAGS) -c src/core/InternalCommunication.c -o obj/InternalCommunication.o $(CORE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE) $(NW_INCLUDE)
obj/TokenValidator.o: src/core/TokenValidator.c
	$(CC) $(CFLAGS) -c src/core/TokenValidator.c -o obj/TokenValidator.o $(CORE_INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)
	

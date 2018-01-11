
When porting, pay attention to these points:
1) FreeRTOS/portable should contain the target of porting
2) change the heap if necessary
3) Change the SELECTED_PORT to the target in the file trcConfig.h

For WIN32 PORT:
Add -lwinmm for building the app
example : bin/wp3app_freertos: obj/main.o obj/main_blinky.o obj/Run-time-stats-utils.o lib/libfreertos.a lib/libfreertos_trace.a
	$(CC) -o bin/wp3app_freertos obj/main.o obj/main_blinky.o obj/Run-time-stats-utils.o -lfreertos -lfreertos_trace -lwinmm -Llib 


For advice on TRACE:
https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_Trace/RTOS_Trace_Instructions.shtml
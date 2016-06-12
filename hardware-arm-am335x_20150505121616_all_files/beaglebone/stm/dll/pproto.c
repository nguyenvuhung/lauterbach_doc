#include <stdio.h>
#include <windows.h>
#include "pipeproto.h"

/*
   Type definitions for STP data
*/
#define DECSTP_TYPE_OVF        2

#define DECSTP_TYPE_D8         4
#define DECSTP_TYPE_D16        5
#define DECSTP_TYPE_D32        6
#define DECSTP_TYPE_D64        7

#define DECSTP_TYPE_WITHTS  0x10
#define DECSTP_TYPE_ERROR   0xFF

#define TS_SIZE 8


typedef struct localData
{
	unsigned char ts[TS_SIZE];
	char myStr[1024];
	int  myStrLen;

} localDataT, *localDataP;

/*********************/
/* Private functions */
/*********************/

void init_localDataT_struct(localDataP data)
{
	memset(data,0,sizeof(localDataT));
}


/* Processing function
 *
 * The following function will be called, each time a STP message is decoded
 *
 * Parameters
 *  info   : Structure for calling functions inside T32 software.
 *  data   : Pointer to structure which holds local data for this DLL.
 *  buffer : Pointer to byte buffer which holds STP message.
 *           [7:0]   = timestamp from CombiProbe
 *           [8]     = STP packet type
 *           [9]     = channel
 *           [10]    = master
 *           [11:19] = data
 *  len    : Length of byte buffer which holds STP message.
 */
static void process(SPipeProtoInfo *info, localDataP data, unsigned char *buffer, int len)
{
	uint8_t channel, type;

	if (!buffer)
		return;

	type = buffer[8];
	channel = buffer[9];

	/* Simple byte based print function for channel 0 */
	if (channel==0 && (type==DECSTP_TYPE_D8 || type==(DECSTP_TYPE_D8|DECSTP_TYPE_WITHTS))) {
		int c;
		if ( data->myStrLen == 0 ) {
			memcpy(data->ts, buffer, TS_SIZE); /* remember timestamp */
		}
		c = buffer[11];
		if (c>31 && c<127) {
			data->myStr[data->myStrLen] = c;
			data->myStrLen++;
		}
		if ((type & DECSTP_TYPE_WITHTS) || (c == 0x0a) || (c == 0x0d)) {
			data->myStr[data->myStrLen] = 0;

			/* Write string immediately to an AREA window named "myPrint"
			 *   Create such a AREA in TRACE32 with "AREA.Create myPrint"
			 *   View the AREA window with "AREA.view myPrint"
			 * Data printed to an AREA window will be also shown while the CPU is running. */
			PIPE_PrintfArea(info, "myPrint", "%s", data->myStr);

			/* Generate a string entry for customized Trace.List window
			 * Open such a window with SystemTrace.CustomTrace.<name>.List
			 *   with <name> is the name used with command SystemTrace.CustomTraceLoad
			 * E.g.:
			 *   SystemTrace.CustomTraceLoad "myPrint" "~~~~/dll/pproto64.dll"
			 *   SystemTrace.CustomTrace.MYPRINT.List                            */
			PIPE_LogCustom(info, data->ts, PIPE_LOG_TYPE_STRING, (unsigned char *)(data->myStr), data->myStrLen);

			data->myStrLen = 0;
		}
	}

	/* Customized display of 32-bit values from channel 2*/
	if (channel==2 && (type==DECSTP_TYPE_D32 || type==(DECSTP_TYPE_D32|DECSTP_TYPE_WITHTS))) {
		uint32_t loop = buffer[11]|((uint32_t)buffer[12]<<8)|((uint32_t)buffer[13]<<16)|((uint32_t)buffer[14]<<24);
		uint8_t mydata[8];

		mydata[0] = 2;
		*((uint32_t*)(mydata+4)) = loop;

		/* Write a string immediately to an AREA window named "myPrint"
		 *   Create such a AREA in TRACE32 with "AREA.Create myPrint"
		 *   View the AREA window with "AREA.view myPrint"
		 * Data printed to an AREA window will be also shown while the CPU is running. */
		PIPE_PrintfArea(info, "myPrint", "Count %u", loop);

		/* Store value, to get it displayed later in a customized Trace.List window
		 * Open such a window with SystemTrace.CustomTrace.<name>.List
		 *   with <name> is the name used with command SystemTrace.CustomTraceLoad
		 * E.g.:
		 *   SystemTrace.CustomTraceLoad "myPrint" "~~~~/dll/pproto64.dll"
		 *   SystemTrace.CustomTrace.MYPRINT.List
		 * Here we store only the 32-bit value. Because of PIPE_LOG_TYPE_CUSTOMSTRING the
		 * creation of the string which should be displayed is done later with the display()
		 * function.
		 * Because of PIPE_LOG_TYPE_DISPLAY the message is also shown in the
		 * global SystemTrace.PipePROTO.LOG window.*/
		PIPE_LogCustom(info, buffer, PIPE_LOG_TYPE_CUSTOMSTRING|PIPE_LOG_TYPE_DISPLAY, mydata, sizeof(mydata));
	}
}


static void display(SPipeProtoInfo *info, localDataP data, const unsigned char *buffer, int len, SPipeProtoCustomInfo *out)
{
	if ((out->type == PIPE_LOG_TYPE_CUSTOMSTRING)  &&  (buffer[0] == 2)){
		uint32_t loop = *((uint32_t*)(buffer+4));

		out->type = PIPE_LOG_TYPE_STRING;
		sprintf(out->content.str.buf, "%u times we sayed hello to the world", loop );
		out->content.str.len = strlen(out->content.str.buf);
	}
}


/* called when DLL is unloaded
 * Parameters
 *  info   : Structure for calling functions inside T32
 *  data   : Pointer to structure which holds local data for this DLL.
 */
static void exitDll(SPipeProtoInfo *info,localDataP localdata)
{
	/* Free data, which was allocated in "PIPE_Init" */
	free(localdata);
}

/* called when DLL is loaded
 *
 * Parameters
 *  info   : Structure for calling functions inside T32
 *  argc   : numbers of parameters stored in "argv"
 *  argv   : array of pointers to "NULL" terminated command line parameters
 *
 * Return Value:
 *  == 0 indicates success.
 *  != 0 indicates error. DLL will be unloaded.
 *
 * This function should allocate space to store local configuration data
 * for one DLL load.
 * It additionally should do all initialization which is necessary.
 */
int PIPE_Init(SPipeProtoInfo *info,int argc, char **argv)
{
	localDataP localdata = (localDataP)malloc(sizeof(localDataT));
	init_localDataT_struct(localdata);

	/*
	 * Parameters for PIPE_RegisterCallback:
	 *  info     : Pointer to "SPipeProtoInfo" structure
	 *  type     : Type of function to register
	 *  callback : Pointer to function which will be called.
	 *  flags    : optional flags (currently always 0).
	 */
	PIPE_RegisterCallback(info, PIPE_PROCESS_CALLBACK, process, localdata, 0);
	PIPE_RegisterCallback(info, PIPE_DISPLAYCUSTOM_CALLBACK, display, localdata, 0);
	PIPE_RegisterCallback(info, PIPE_EXIT_CALLBACK   , exitDll, localdata, 0);

	return 0;
}

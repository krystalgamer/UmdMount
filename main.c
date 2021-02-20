#include <pspkernel.h>
#include <psputility.h>
#include <pspctrl.h>
#include <string.h>
#include <stdio.h>
#include <pspumd.h>
#include "systemctrl.h"
#include "systemctrl_se.h"

PSP_MODULE_INFO("UmdMount", 0x1000, 1, 0);
PSP_NO_CREATE_MAIN_THREAD();


void writeLog(char *str){

	int fd = sceIoOpen("ms0:/log.txt", PSP_O_CREAT | PSP_O_WRONLY | PSP_O_APPEND, 0777);

	sceIoWrite(fd, str, strlen(str));
	sceIoWrite(fd, "\n", 1);
	sceIoClose(fd);
}



int mount_thread(SceSize args, void *argp){

	sceKernelChangeThreadPriority(0, 16);
	SceCtrlData pad;


	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	while(1){
		sceKernelDelayThread(4000);
		sceCtrlPeekBufferPositive(&pad, 1); 
		if (pad.Buttons != 0){
			if (pad.Buttons & PSP_CTRL_NOTE){
				char *curUmd = sctrlSEGetUmdFile();
				if(curUmd[0] == '\0'){
					sctrlSESetUmdFile("ms0:/ISO/updater.iso");
					sctrlSESetBootConfFileIndex(MODE_VSHUMD);
					sctrlSESetDiscType(0x10);
					sctrlKernelExitVSH(NULL);
					sceKernelStopUnloadSelfModule(0, NULL, NULL, NULL);
				}
			}
		}
	}


	return sceKernelExitDeleteThread(0);


}

int module_start(int argc, char *argv[]){

	int thid = sceKernelCreateThread("UmdMountThread", mount_thread, 16, 0x1000, 0, 0 );
	if(thid >= 0)
		sceKernelStartThread(thid, 0, 0);

	return 0;
}

int module_stop(int argc, char *argv[])
{
	return 0;
}


#include "WorkPlace.h"

WorkPlace::WorkPlace()
{
	timeWork = 1;
	isWork = true;
}

void WorkPlace::doWork()
{

	while (true) {
		if (timeWork++ % 50==0) {
			/*Сообщение деталь обработана*/
			//MessageBox(hWnd, "Detal Obrabotana", NULL, MB_OK);
			break;
		}
	}
	//ResumeThread(workThread);
}



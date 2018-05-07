#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#define DR 0
#define DG 255
#define DB 255

int main(int argc, char const *argv[])
{
	if(argc!=4)
		return 1;

	int words = argv[1];
	char* input1 = argv[2];
	int timeZone = argv[3];
	if (words != 2)
	{
		sysPrintString("Wrong parameters: setTimeZone timezone\n", CB, CG, CR);
		return 1;
	}
	if (toInt(input1) > 12 || toInt(input1) < -11)
	{
		sysPrintString("Timezone values must be between -11 and +12\n", CB, CG, CR);
		return 1;
	}

	timeZone = toInt(input1);

	return 0;
}
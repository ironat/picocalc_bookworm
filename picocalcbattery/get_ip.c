#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LabelSize 36

char * get_host(char *buffer, int mode)
{
	//  Returns hostame if mode == 0 (default, else IP Address)
	// Setup our pipe for reading and execute our command.
	FILE *pf = mode ? popen("hostname -I","r") : popen("hostname","r");
	// Get the buffer from the process execution
	if(pf)	fgets(buffer, 36 , pf);
	pclose(pf);
	return buffer;
}

#define CONFIGFILE "/.config/hostname"	// saved Host option
int read_saved_mode(void)
{
	// return saved mode (or default)
	FILE *fp;
	int dmode = 0;
	char *homedir = strcat(getenv("HOME"), CONFIGFILE);
	if((fp = fopen(homedir, "r")))
	{
		fscanf(fp, "%d", &dmode);
	}
	return dmode;
}

int main()
{
	char buff[LabelSize+1];
	printf("%s\n", get_host(buff, read_saved_mode()));
}

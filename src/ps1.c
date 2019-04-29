#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>
#include <ctype.h>


int getField(char* fileName1, char* str)
{
	int val = 0,i,n;
	
	char temp[10000];
	int flag = 0;
	strcpy(temp, fileName1);
	char* new_str = strstr(temp, str);
	//printf("new_str: %s\n", new_str);
	if(new_str != NULL){
		for(i=val=0,n=strlen(new_str);i<n;i++){
		
			if(!isdigit(new_str[i]))
				if(flag == 1)
					break;	
				else
					continue;
			if( new_str[i] >= '0' && new_str[i] <= '9' ){ 
			// you can use if ( !(isdigit(string[i])) )
				val = val*10 + new_str[i] - '0';
				flag = 1;
			}
			else 
				flag = 0;			
		}
	}
	return val;
}

int main(){
	
	char path[6] = "/proc";
	char fileName[10000];
	char fileName1[10000], fileName2[10000], fileName3[10000];
	char current_path[256];
	char pid[10], uid[10], uname[20];
	long int vmsize = 0, rss = 0, memtotal = 0;
	char uid_str1[6] = "Uid";
	char vmsize_str2[10] = "VmSize";
	char vmrss_str3[6] = "VmRSS";
	char memtotal_str4[15] = "MemTotal"; //the name of this field should match that in /proc/meminfo file. to check type in command prompt "cat /proc/meminfo"
	int UID =  12;
	long int vmsize1 = 0;

	uid_t id = 0;
        struct passwd *pwd;

        printf("PID\tUSER\tVSZ\tRSS\tTTY");
	DIR* dirPtr = opendir(path);//TOCHAGNE
	if(dirPtr != NULL){
		//printf("Hi! directory opened successfully\n");
	
		struct dirent* current;
		current = readdir(dirPtr); //open works on current dir based on where your executable is, so need to concatanate onto path you are at now and pass that going forward.//readdir: works in whatever dir you opened(ex: ./dirIn)
		if(current != NULL){
			//strcpy(fileName, path);
			if(current->d_type == DT_DIR){ //readdir -> d_name == DTIR

				char* dirName = current->d_name;
			}
			do{
			   	current = readdir(dirPtr);
				if(current ==NULL){
					return 1;
			     	}
				if((current->d_type == DT_DIR)&&(atoi(current->d_name))) { 
					//char filename[256];
					strcpy(fileName, path); //filename = "/proc"
					strcat(fileName, "/"); //filename = "/proc/"
					strcat(fileName, current->d_name);	// filename = "/proc/PID"
 					//printf("%s\n", current->d_name);
					
					strcpy(pid, current->d_name);
					printf("\n%s\t", pid);
					strcat(fileName, "/status"); //filename = "/proc/PID/status"
					
					int fd = open(fileName, O_RDONLY);
					if(fd != -1){
						if(0 != read(fd, fileName1, 10000)){
							
							UID = getField(fileName1, uid_str1);
							
							pwd = getpwuid(UID); //map to u4824sername
							if(pwd != NULL){
								printf("%s\t", pwd->pw_name);
								//return 0;
							}

							vmsize1 = getField(fileName1, vmsize_str2);
							printf("%d\t", vmsize1);

							rss = getField(fileName1, vmrss_str3);
							printf("%d\t", rss);
							printf("?");
						} 
					}
					//else
					//	printf("Problem in opening file.\n");



					//MemTotal code can be here
					// path2 = /proc/meminfo
					//int fd2 = open(path2, O_RDONLY);
					//if(fd != -1){
					//	if(0 != read(fd, fileName1, 10000)){
					//
					//		strcpy(fileName2, fileName1);
					//		
					//		memtotal = getField(fileName2, memtotal_str4); calculate Mem usage percentage


				}
			}while(dirPtr !=NULL);
			

		}
	}
	else	{
		printf("Error!");
		return 1;
	}
	
	return 0;
}



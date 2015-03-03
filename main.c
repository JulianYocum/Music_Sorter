#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


//function heads
const char *get_ext(const char *filename);
int move(char* Music_File, char* path);
int clean(char* newdir);


//main function
int main (int argc, char* argv[])
{	
	//if not run from terminal or arguments not given
	if(argc != 2)
	{
		printf("Directory not chosen. \nDefaulting to standard directory...\n");
		argv[1] = ".";
	}
	
	//opens chosen directory as pdir
	DIR *pdir = NULL;
    pdir = opendir (argv[1]);
    struct dirent *pent = NULL;
	//if directory can't be opened: Error
    if (pdir == NULL)
    {
        printf ("Error: Could not read direcotry\n");
        return -1;
    }
	
	//creates directory "Clean" in chosen directory
	char newdir[strlen(argv[1]) + 7];
	char* temp = argv[1];
	strcpy(newdir, temp);
	strcat(newdir, "/Clean");
	
	printf("%s\n", newdir);
	
	mkdir(newdir, 0777);



	//loops through dir entries
   while ((pent = readdir (pdir)))
    {
		//file_count++;
        if (pent == NULL)
        {
            printf ("ERROR! pent could not be initialised correctly\n");
            return -1;
        }
		
		char* filename = pent->d_name;
		//if d_type == file acess file innards(coined)
		
		char* filepos = malloc(strlen(argv[1]) + 7 + strlen(filename) + 1);
		strcpy(filepos, argv[1]);
		strcat(filepos,"/Clean/");
		
        strcat(filepos, filename);
		
		
		if(get_ext(filename) == NULL)
			continue;
		else if(strcmp(get_ext(filename),".mp3") == 0 || strcmp(get_ext(filename),".m4a") == 0)
			move(filename, filepos);
    }
	
	clean(newdir);
	
	closedir(pdir);
	
    return(0);
}


//gets file extension
const char *get_ext(const char *filename)
{
	char *dot = strrchr(filename, '.');
	if(!dot || dot == filename)
		return NULL;
	return dot;
}


//copies file into "Clean" directory
int move(char* Music_File, char* path)
{   
   FILE *old = NULL;
   FILE *new = NULL;
   
	printf("%s\n", path);
   
   //strcat(filePath, Music_File);
   char temporary[strlen(Music_File) + 4];
   strcpy(temporary, Music_File);
   strcat(temporary, "(1)");
	
   char c;
   
   old = fopen(Music_File, "rb");
   new = fopen(temporary, "wb");
   
   if( old == NULL || new == NULL) 
   {
      perror ("Error opening file\n");
      return -1;
   }
 
	while(1)
	{
		c = fgetc(old);
		
		if (feof(old))
			break;
		
		fputc(c, new);
	}
	
	printf("temporary.mp3 to %s\n",path);
	int ret = rename(temporary, path);
	
	if(ret != 0)
		return -1;

	fclose(old);
	fclose(new);
	
    return 0;
}


//cleans the "Clean" directory :)
int clean(char* newdir)
{
	int check = chdir(newdir);
	
	if(check != 0)
		return -1;
	/*
	//implement file reader
	char* file_names[file_count];
	char* file_artists[file_count];
	char* file_albums[file_count];
	*/
}

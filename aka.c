#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define EQ(s, t) (strcmp(s, t) == 0)

char* find_name(char* dirName, char* guessName);

int how_good(const char *s, const char *t);


int main()
{
  char buffer[128];
  gets(buffer);
  char* guess;
  char* dirName;

  if (buffer == '.*') {
    guess = buffer;
    dirName = find_name('./', guess); 
    if (dirName != NULL) {
      return printf(dirName);
      exit(0);
    } else {
      printf("No match found");
      exit(1);
    }
  } else if (buffer == '/*') {
    guess = buffer;
    chdir('/');
    dirName = find_name('/', guess)
    if (dirName != NULL) {
      return printf(dirName);
      exit(0);
    } else {
      printf("No match found");
      exit(1);
    }
  }
 
}



char* find_name(char* dirName, char* guessName)
{
  int match;
  struct dirent *aDirent;
  DIR *aDir;
  char* matchDir;

  aDir = opendir(dirName);

  while ((aDirent = readdir(aDir)) != NULL) {
    match = how_good(aDirent, guessName);
    if (match >= 1) {
      matchDir = aDirent;
      closedir(aDir);
      return matchDir;
    } else {
      return NULL;
    }
}  

int how_good(const char *s, const char *t)
{
  if(EQ(s,t)) {
      return 0;/* exact match*/
  }

  while(*s++ == *t++);   /* move to discrepancy*/
   
  if (*--s) {

    if (*--t) {

      if (s[1] && t[1] && *s == t[1] && *t == s[1] && EQ(s+2,t+2))
	return 1;/*two characters transposed*/

      if (EQ(s+1, t+1))
	return 2;/* one character mismatch */
         
      if (EQ(s+1, t))
	return 3;/*extra character in the middle of one string*/
      
      if (EQ(s, t+1))
	return 4;/*character missing in the string*/
    }

    if (EQ(s+1,t))
      return 3;/*extra character at end of string*/
  }

  if (*--t && EQ(s, t+1))
    return 4;/*missing character at end of string*/

  return -1;/* no match found */
}

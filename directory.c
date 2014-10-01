#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

#define EQ(s, t) (strcmp(s, t) == 0)

char* find_name(char* dirname, char* guessname);

int how_good(const char *s, const char *t);

int main(int argc, char *argv[])
{
  printf("arg count %i\n", argc);

  //  int i;
  //  for (i = 0; i < argc; i++) {
  //    puts(argv[i]);
  //    printf("args %s", argv[i]);
  //  }

  if (*argv[2] == '/') {
    chdir('/');
  }

  if (*argv[2] == '.') {
    char* dir = find_name(argv[1], argv[2]);
    if (dir != NULL) {
      printf("correct pathname %s", dir);
      return 0;
    } else {
      printf("No match found");
      return 1;
    }
  }
  // printf("test %s\n", dir);


}



char* find_name(char* dirname, char* guessname)
{
  DIR *dip;
  struct dirent *dit;

  int i = 0;

  if (guessname == "tmp") {
    printf("You typed 'tmp'\n");
  }

  if (*dirname == '/') {
    printf("You typed '/'\n");
  }

  
  //  if (argc < 2) {
  //    printf("Usage: %s <directory>\n", argv[0]);
  //    return 0;
  //  }
    
  if ((dip = opendir(dirname)) == NULL) {
    perror("opendir");
    return dirname;
  }

  printf("Directory stream is now open\n");

  int matchNumber;

  while ((dit = readdir(dip)) != NULL) {
    i++;
    matchNumber = how_good(dit->d_name, guessname);
    if (matchNumber >= 0) {
      closedir(dip);
      return dit->d_name;
    } else {
      closedir(dip);
      return NULL;
    }
    printf("\n%s", dit->d_name);
  }

  printf("\n\nreaddir() found a total of %i files\n", i);

  //    if (closedir(dip) == -1) {
  //     perror("closedir");
  //    return dirname;
  //   }

  printf("\nDirectory stream is now closed\n");
  //  return dirname;
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

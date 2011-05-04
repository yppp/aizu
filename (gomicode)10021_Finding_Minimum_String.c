#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFSIZE 4096
struct Lines
{
  int length;
  char **line;
};
struct Lines *readstdin();
int main ()
{
  int i;

  struct Lines *lines = readstdin();
  int nyuryokusu = atoi(lines->line[0]);
  char *minstr = lines->line[1];
  for (i = 1; i < nyuryokusu+1; i++)
    {
      if(strcmp (minstr, lines->line[i]) == 1)
	{
	  minstr = lines->line[i];
	}
    }
  printf("%s", minstr);
  return 0;
}

struct Lines* readstdin()
{
  int i,j;
  int resize, strlength;
  char buf[BUFSIZE];
  char *str = NULL;
  char *tmp = NULL;
  struct Lines *lines = (struct Lines*)malloc (sizeof (struct Lines));
  lines->length = 0;
  lines->line = NULL;
  strlength = 0;
  for (i = 0; fgets (buf, BUFSIZE, stdin) != NULL; i++)
    {
      resize = 0;
      tmp = str;
      for (j = 0; j < BUFSIZE; j++)
	{
	  if (j == BUFSIZE - 1)
	    {
	      resize = BUFSIZE;
	    }
	  else if (buf[j] == '\n')
	    {
	      resize = j + 1; /*NULL文字までコピーしないように*/
	      break;
	    }
	  else if (buf[j] == '\0')
	    {
	      resize = j;
	      break;
	    }
	  else
	    {}
	}
      strlength += resize;
      tmp = (char*)realloc (str, sizeof(char) * strlength);
      str = strncat(tmp, buf, resize);
      if (buf[j] == '\n')
	{
	  strlength = 0;
	  lines->line = (char**)realloc (lines->line, sizeof(char*) * (lines->length + 1));
	  lines->line[lines->length] = str;
	  str = NULL;
	  lines->length += 1;
	}
    }
  return lines;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lines
{
  unsigned int length;
  char **line;
};

enum
  {
    INIT = 4096,
    GROW = 2
  };

char* fileGetLine(FILE*);
static int endofline(FILE*, int);

int main()
{
  int i, j;
  char *line = NULL;
  char *left = NULL;
  char *right = NULL;
  char *aword = NULL;
  char **shufflewords = NULL;
  int readlines;
  int irekaenum;
  struct Lines lines;
  lines.length = 0;
  lines.line = NULL;
  for (i = 0; (line = fileGetLine(stdin)) != NULL; i++)
    {
      lines.length += 1;
      lines.line = (char**)realloc (lines.line, sizeof(char*) * lines.length);
      lines.line[i] =  line;
    }
  i = 0;
  while (strcmp("-", lines.line[i]) != 0)
    {
      aword = (char*)malloc (sizeof(char) * (strlen(lines.line[i]) + 1));
      strcpy(aword, lines.line[i]);
      i++;
      readlines = atoi (lines.line[i]);
      i++;
      for (j = 0; j < readlines; j++)
	{
	  irekaenum = atoi(lines.line[i+j]);
	  right = (char*)malloc (sizeof(char) * (strlen(aword) + 1));
	  left = (char*)malloc (sizeof(char) * (strlen(aword) + 1));
	  strcpy(right, "");
	  strcpy(left, "");
	  strncpy(left, aword, irekaenum);
	  left[irekaenum] = '\0';
	  strcpy(right, aword + irekaenum);
	  strcat(right, left);
	  strcpy(aword, right);
	  free(left);
	  free(right);
	}
      i += j;
      printf("%s\n",aword);
      free(aword);
    }

  for(i = 0; i < lines.length; i++)
    {
      free(lines.line[i]);
    }

  free(lines.line);
  return 0;
}

char* fileGetLine(FILE *fin)
{
  int i, c;
  int maxline = INIT;
  char *line = (char*)malloc (sizeof(char) * maxline);

  for (i = 0;(c = getc(fin)) != EOF && !(endofline(fin, c)); i++)
    {
      if (i >= maxline - 1)
	{
	  maxline *= GROW;
	  line = (char*) realloc(line, sizeof(char) * maxline);
	}
      line[i] = (char)c;
    }

  return (c == EOF && i == 0) ? NULL : line;
}

static int endofline(FILE *fin, int c)
{
  int eol;
  eol = (c == '\r' || c == '\n');

  if (c == '\r')
    {
      c = getc(fin);
      if (c != '\n' && c != EOF)
	{
	  ungetc(c, fin);
	}
    }
  return eol;
}

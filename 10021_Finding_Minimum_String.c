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
  int i;
  char *line = NULL;
  struct Lines lines;
  lines.length = 0;
  lines.line = NULL;
  for (i = 0; (line = fileGetLine(stdin)) != NULL; i++)
    {
      lines.length += 1;
      lines.line = (char**)realloc (lines.line, sizeof(char*) * lines.length);
      lines.line[i] = line;
    }

  int toi = atoi(lines.line[0]);
  char *minstr = lines.line[1];
  for(i = 2; i < toi; i++)
    {
      if(strcmp(minstr, lines.line[i]) == 1)
	{
	  minstr = lines.line[i];
	}
    }

  printf("%s\n",minstr);
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

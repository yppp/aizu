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
void printlinestoiandsorttop3(struct Lines*);
int int_comp(const void*, const void*);
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
      lines.line[i] =  line;
    }

  printlinestoiandsorttop3(&lines);

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

void printlinestoiandsorttop3(struct Lines *lines)
{
    int *hill = NULL;
    int i;
    hill = (int*)malloc (sizeof(int) * lines->length);
    for(i = 0; i < lines->length; i++)
      {
	hill[i] = atoi(lines->line[i]);
      }
    qsort(hill, lines->length, sizeof(int), int_comp);
    
    for(i = 1; i < 4; i++)
      {
	printf("%d\n", hill[lines->length -i]);
      }
}
int int_comp(const void *_a, const void *_b)
{
  int a = *(int *)_a;
  int b = *(int *)_b;
  
  if (a < b) {
    return -1;
  } else if (a > b) {
    return 1;
  } else {
    return 0;
  }
}

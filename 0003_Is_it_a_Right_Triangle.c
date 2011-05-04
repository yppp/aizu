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
int char_comp(const void*, const void*);
char** split(struct Lines*);

int main()
{
  int i;
  char *line = NULL;
  char **words = NULL;
  struct Lines lines;
  lines.length = 0;
  lines.line = NULL;
  int f;
  int s;
  int right;

  for (i = 0; (line = fileGetLine(stdin)) != NULL; i++)
    {
      lines.length += 1;
      lines.line = (char**)realloc (lines.line, sizeof(char*) * lines.length);
      lines.line[i] =  line;
    }

  words = split(&lines);

  for(i = 0; i < atoi(words[0]); i++)
    {
      qsort(words + (i*3) + 1, 3, sizeof(char*), char_comp);
      f = atoi(words[(i*3) + 1]);
      s = atoi(words[(i*3) + 2]);
      right = atoi(words[(i*3) + 3]);
      if((f*f + s*s) == (right*right))
	{
	  printf("YES\n");
	}
      else
	{
	  printf("NO\n");
	}
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

char** split(struct Lines* lines)
{
  char **words;
  words = (char**)malloc(sizeof(char*) * INIT);
  int i;
  int j = 0;
  int wordslen = INIT;
  int sep;
  int readed;

  for(i = 0; i < lines->length; i++)
    {
      if(i >= wordslen - 1)
	{
	  wordslen *= GROW;
	  words = (char**)realloc (words, sizeof(char*) * wordslen);
	}

      readed = 0;
      while((strlen(lines->line[i]) - readed) != -1)
	{
	  sep = strcspn(lines->line[i] + readed, " ");
	  words[j] = (char*)malloc (sizeof(char) * (sep + 1));
	  strncpy(words[j], lines->line[i] + readed, sep + 1);
	  if(words[j][sep] == ' ')
	    {
	      words[j][sep] = '\0';
	    }
	  readed += sep + 1;
	  j++;
	}
    }
  return words;
}

int char_comp(const void *_a, const void *_b)
{
  int a = atoi(*(char**)_a);
  int b = atoi(*(char**)_b);

  if (a < b)
    {
      return -1;
    }
  else if(a > b)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Lines
{
  unsigned int length;
  char **line;
};
struct Words
{
  int num;
  char *word;
};

enum
  {
    INIT = 4096,
    GROW = 2
  };

char* fileGetLine(FILE*);
static int endofline(FILE*, int);
void lower(char**);
char** split(struct Lines*);

int main()
{
  int i;
  char *line = NULL;
  char **words;
  char *fastword;
  int jufukuword = 0;
  struct Lines lines;
  lines.length = 0;
  lines.line = NULL;

  for (i = 0; (line = fileGetLine(stdin)) != NULL; i++)
    {
      lines.length += 1;
      lines.line = (char**)realloc (lines.line, sizeof(char*) * lines.length);
      lines.line[i] =  line;
    }

  words = split(&lines);
  lower(words);

  fastword = words[0];
  for (i = 1; strcmp("END_OF_TEXT", words[i]) != 0; i++)
    {
      if(strcmp(fastword, words[i]) == 0)
	{
	  jufukuword++;
	}
    }

  printf("%d\n", jufukuword);
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

void lower(char** words)
{
  int i, j;
  for(i = 0; strcmp("END_OF_TEXT", words[i]) != 0; i++)
    {
      for (j = 0; j < strlen(words[i]); j++)
	{
	  words[i][j] = tolower(words[i][j]);
	}
    }

}

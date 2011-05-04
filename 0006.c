#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int i;
  int c;
  int len = 1;
  int slen;
  char *str = NULL;
  while((c = getc(stdin)) != EOF)
    {
      str = (char*)realloc(str, sizeof(char) * (len+1));
      if(c != '\n')
	{
	  str[len-1] = (char)c;
	  str[len] = '\0';
	}
      else
	{
	  str[len-1] = '\0';
	}
      len++;
    }
  slen = strlen(str);
  for(i = 0; i < slen; i++)
    {
      printf("%c", str[slen-1-i]);
    }
  puts("");
  return 0;
}

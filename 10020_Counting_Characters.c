#include<stdio.h>
#include<stdlib.h>
#define NELEMS(array) (sizeof(array) / sizeof(array[0]))
int main()
{
  int i,c;
  int moji[26] = {0};
  while ((c = getc (stdin)) != EOF)
    {
      if(c >= 97 && c <= 122)
	{
	  moji[c-97] += 1;
	}
      else if(c >= 65 && c <=90)
	{
	  moji[c-65] += 1;
	}
      else
	{
	}
    }
  for (i = 0; i < NELEMS(moji); i++)
    {
      printf("%c : %d\n", i+97, moji[i]);
    }
  return 0;
}

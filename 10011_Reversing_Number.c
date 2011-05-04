#include<stdio.h>
#include<stdlib.h>

struct nums
{
  int length;
  int *num;
};
int getProgressionLength(FILE *in)
{
  int i,c;
  char ch[20];
  for (i = 0; ((c = getc (in)) != '\n'); i++)
    {
      ch[i] = (char)c;
      ch[i+1] = '\0';
    }
  return atoi(ch);
}

void getProgressionLine(int v[100],FILE *in)
{
  int i,j;
  int c;
  char ch[20];
  i = 0;
  j = 0;
  while ((c = getc (in)) != '\n')
    {
      switch(c)
	{
	case ' ':
	  v[j] = atoi(ch);
	  j++;
	  i = 0;
	  break;
	default:
	  ch[i] = (char)c;
	  ch[i+1] = '\0';
	  i++;
	}
    }
  v[j] = atoi(ch);
}

struct nums *setlines(int n, int v[100])
{
  int i;
  struct nums *allo = (struct nums*)malloc (sizeof(struct nums));
  allo->num = (int*)malloc (sizeof(int) * n);
  allo->length = n;

  for(i = 0; i < n; i++)
    {
      allo->num[i] = v[i];
    }
  
  return allo;
}
int main ()
{
  int i,j,n;
  int v[100];
  struct nums *numnum[100];
  int nyuryokusu;

  for (i = 0; (n = getProgressionLength(stdin)) != 0; i++)
    {
      getProgressionLine(v, stdin);
      numnum[i] = setlines(n, v);
      nyuryokusu = i + 1;
    }
  for(j = 0; j < nyuryokusu; j++)
    {
      for(i = 0; i < numnum[j]->length; i++)
	{
	  if(i != 0)
	    {
	      printf(" ");
	    }
	  printf("%d", numnum[j]->num[(numnum[j]->length) - 1 - i]);
	}
      puts("");
    }
  return 0;
}


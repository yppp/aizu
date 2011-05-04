#include<stdio.h>

int main()
{
  int a,b;
  int i, j;
  while(1)
    {
      scanf("%d %d", &a, &b);
      if(a == 0 && b == 0)
	{
	  break;
	}
      for(i = 0; i < a; i++)
	{
	  for(j = 0; j < b; j++)
	    {
	      if(i == 0 || j == 0 || i == a-1 || j == b-1)
		{
		  printf("#");
		}
	      else
		{
		  printf(".");
		}
	    }
	  puts("");
	}
      puts("");
    }
  return 0;
}


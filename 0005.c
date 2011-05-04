#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a,b;
  int m,n;
  int temp;

  while(scanf("%d%d", &a, &b) != EOF)
    {
      getc(stdin);
      if(a < b)
	{
	  a = a ^ b;
	  b = a ^ b;
	  a = a ^ b;
	}

      m = a;
      n = b;

      while(a % b != 0)
	{
	  temp = b;
	  b = a % b;
	  a = temp;
	}
      printf("%d %d\n", b ,(m / b) * n);
    }
  return 0;
}

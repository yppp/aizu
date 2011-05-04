#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i, j, k;
  double n;
  double tmp[2][3];
  double matrix[2][3];
  double a[1000][2];

  for (i = 0; scanf("%lf%lf%lf%lf%lf%lf",&matrix[0][0], &matrix[0][1], &matrix[0][2], &matrix[1][0], &matrix[1][1], &matrix[1][2]) != EOF; i++)
    {
      if(matrix[0][0] == 0)
	{
	  for(j = 0; j < 2; j++)
	    {
	      for(k = 0; k < 3; k++)
		{
		  tmp[j][k] = matrix[j][k];
		}
	    }
	  
	  for(j = 0; j < 3; j++)
	    {
	      matrix[0][j] = tmp[1][j];
	    }
	  for(j = 0; j < 3; j++)
	    {
	      matrix[1][j] = tmp[0][j];
	    }
	}

	  n = matrix[0][0];
	  matrix[0][0] /= n;
	  matrix[0][1] /= n;
	  matrix[0][2] /= n;


      if(matrix[1][0] != 0)
	{
	  n = matrix[1][0];

	  matrix[1][0] += (matrix[0][0] * (n * -1));
	  matrix[1][1] += (matrix[0][1] * (n * -1));
	  matrix[1][2] += (matrix[0][2] * (n * -1));
      	}

      n =  matrix[1][1];
      matrix[1][1] /= n;
      matrix[1][2] /= n;
      
      n = matrix[0][1];
      matrix[0][1] += (n * -1);
      matrix[0][2] += matrix[1][2] * (n * -1);

      a[i][0] = matrix[0][2];
      a[i][1] = matrix[1][2];
    }
  n = i;
  for(i = 0; i < n; i++)
    {
      printf("%.3lf %.3lf\n",a[i][0] ,a[i][1]);
    }

  return 0;
}

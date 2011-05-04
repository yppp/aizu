#include<stdio.h>

void flaggingcards(int*);

int main()
{
  int cards[4][13] = {{0}};
  int c;
  int i,j;

  while(getc(stdin) != '\n')
    {}
  while((c = getc(stdin)) != EOF)
    {
      switch(c)
	{
	case 'S':
	  flaggingcards(cards[0]);
	  break;
	case 'H':
	  flaggingcards(cards[1]);
	  break;
	case 'C':
	  flaggingcards(cards[2]);
	  break;
	case 'D':
	  flaggingcards(cards[3]);
	  break;
	}
    }

  for(i = 0; i < 4; i++)
    {
      for(j = 0; j < 13; j++)
	{
	    if(cards[i][j] == 0)
	    {
	      switch(i)
		{
		case 0:
		  printf("S %d\n",j+1);
		  break;
		case 1:
		  printf("H %d\n",j+1);
		  break;
		case 2:
		  printf("C %d\n",j+1);
		  break;
		case 3:
		  printf("D %d\n",j+1);
		  break;
		}
	    }
	}
    }
  return 0;
}

void flaggingcards(int *cards)
{
  int cardnum;
  scanf(" %d", &cardnum);
  cards[cardnum-1] = 1;
}


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
int N, cpt=0;

int **creertours(int N, int c)
{ int i,**p;
  p = (int **)malloc(sizeof(int *) * N);
  for (i=0 ; i<N ; i++)
    p[i] = (int *)malloc(sizeof(int) * c);
   return(p);
}

int **liretour(int N)
{ int **p;
  int i, j;
  p=creertours(N,3);

  for (i=0 ; i<N ; i++)
    {
            for (j=0 ; j<3 ; j++)
            {
                 if (j) p[i][j] = 0;
                 else  p[i][j] = i+1;
            }
    }
return p;
}


void affichetour(int **p, int N)
{ int i, j;
  printf("\n\n       " );
  for (i=0 ; i<N ; i++)
      {
             for (j=0 ; j<3 ; j++)
              {
                        if (p[i][j] == 0) printf("0 \t" );
                        else
                          printf("%d\t", p[i][j]);
               }
                        printf("\n       " );
              }
              printf("A        B       C ");
              printf("\n       *******************" );
}

void traiter(int **p, int A, int C, int n)
    {
      int i=0, v;
      while ( (i<n) && (p[i][A] == 0) )
                  i++;

      if (i<n)
       {
                  v = p[i][A];
                  p[i][A] = 0;
       }
      i=n-1;
      while ( (i>=0)    && (p[i][C] != 0) )
                  i--;
      if (i>=0)
                  p[i][C] = v;
                  cpt++;
                  affichetour(p, N);
      }


    int hanoi(int **p, int n, int A, int B, int C)
    {
          if (n == 0 )
              return 0;

          hanoi(p, n-1,A,C, B);

          traiter(p, A, C, N);

          hanoi(p, n-1,B, A, C);
          return 1;
    }





    int main()
    {  int **p;
       int A=0,B=1,C=2;

        printf("       *********** Les Tours de Hanoi  ************\n\n");
        printf("       *****  Developper par:  AYMEN BEN MHAMED & OMAR SAAD  ******\n\n");
        printf("       *************  Amphi:B ************ \n\n");
        printf("       *************  groupe:3 & 2 ************\n\n");
        printf("       Donner le nombre des anneuax ? : " );
        scanf("%d", &N);

        p = liretour(N);
        printf("\n\n" );
        affichetour(p, N);

        hanoi(p, N, A,B,C);

        printf("\n\n     le nombre d'operation est egale a: %d \n\n", cpt);
        system("pause");
        return 0;

    }

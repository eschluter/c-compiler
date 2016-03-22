
/* Eratosthene */

#define N 100
#define SN 10		/* sqrt(n) */

#ifdef GCC /* VERSION C */

#include <stdio.h>

int tab[100];

int main() {
  int i,j;
  tab[0] = 0;
  for ( i = 1 ; i < N ; i++ )
    tab[i] = 1;
  for ( i = 2 ; i < SN ; i = i+1 )
    for ( j = i+i; j < N ; j += i ) 
      tab[j] = 0;

  for ( i = 0 ; i < N ; i++ )
    if ( tab[i] == 1 )
      printf( "%d ", i );
  printf("\n");
  return 0;
}

#else /* COMPILER VERSION */

#include "../lib/lib.h"

string tab;

int main() {
  int i,j;
  tab = "0";
  for ( i = 1 ; i < N ; i = i+1 )
    tab = tab + '1';
  for ( i = 2 ; i < SN ; i = i+1 )
    for ( j = i+i; j < N ; j = j+i ) 
      put_char_at( tab, j, '0' );
  
  for ( i = 0 ; i < N ; i = i+1 )
    if ( get_char_at( tab, i ) == '1' ) {
      printd(i);
      printf(" ");
    }
  printf("\n");
  return 0;
}

#endif

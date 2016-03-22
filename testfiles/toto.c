
int sleep( int t );

int main() {
  int i;
  for ( i = 0; i < 1000; i = i+1 ) {
    printd(i);
    printf("\n");
    sleep(1);
    printf( 27+"M" );
  }
  return 0;
}
C
#include <string.h> 
#include "../lib/lib.h"

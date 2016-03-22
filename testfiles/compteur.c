#include "../lib/lib.h"
int sleep( int t );

int main() {
  int i;
  for ( i = 0; i < 10; i = i+1 ) {
    printd(i);
    printf("\n");
    sleep(1);
    printf( 27+"M" );
  }
  return 0;
}

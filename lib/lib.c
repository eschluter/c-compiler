
/*  LIBRARY langage CSTR to be compied with GCC */

#include <stdio.h>

int printd( int d ) {
  return printf( "%d", d );
}
int get_char_at( char *s, int i ) {
  return s[i];
}
int put_char_at( char *s, int i, int c ) {
  s[i] = c;
  return c;
}

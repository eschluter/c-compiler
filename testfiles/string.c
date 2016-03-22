
#ifdef GCC /* GCC code */

#define STRING_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

string cat( string s, string t ) {
  char *p;
  p = (char *) malloc(STRING_SIZE);
  strncpy( p, s , STRING_SIZE-1 );
  strncat( p, t , STRING_SIZE-1-strlen(p));
  return p;
}

string int2string( int a ) {
  char s[2] = " ";
  *s = a;
  return strdup(s);
}

#else /* compiler code */

#define cat(x,y) x+y
#define int2string(x) x

extern int printf( string s );

#endif

string u;

int main() {
  string s;
  string t;

  s = "hello";
  t = " world\n";
  u = "bye";
  printf("hello");
  printf(cat("hello","world\n"));
  printf(cat(s,"world\n"));
  printf(cat("hello",t));
  printf(cat(s,t));
  printf(cat((cat(s,u)),t));
  printf(cat(s,(cat(u,t))));
  printf(cat((cat(s,s)),(cat(t,t))));
  printf(cat(cat(s,u),t));
  return 0;
}

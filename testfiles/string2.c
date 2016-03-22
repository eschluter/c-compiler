#ifdef GCC /* GCC code */

#define STRING_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

#define printd(x) printf("%d",x)

char * cat( char *s, char *t ) {
  char *p;
  p = (char *) malloc(STRING_SIZE);
  strncpy( p, s , STRING_SIZE );
  strncat( p, t , STRING_SIZE );
  return p;
}

#define eq(x,y) ( strcmp(x,y) == 0 )
#define ne(x,y) ( strcmp(x,y) != 0 )

#else /* compiler code */

#define cat(x,y) x+y

extern int printd( int a );

#define eq(x,y) x==y
#define ne(x,y) x!=y

#endif

string u;

int main() {
  string s;
  string t;

  s = "hello";
  t = "helll";
  u = "hellp";

  if (eq(s,t)) printd(1); else printd(0);
  if (eq("abc","abc")) printd(1); else printd(0);
  if (eq(t,s)) printd(1); else printd(0);
  if (eq(cat(t,"abc"),cat(u,"ab"))) printd(1); else printd(0);
  if (eq(cat(s,cat(t,u)),cat(s,cat(t,u)))) printd(1); else printd(0);
 
  if (ne(s,t)) printd(1); else printd(0);
  if (ne("abc","abc")) printd(1); else printd(0);
  if (ne(t,s)) printd(1); else printd(0);
  if (ne(cat(t,"abc"),cat(u,"ab"))) printd(1); else printd(0);
  if (ne(cat(s,cat(t,u)),cat(s,cat(t,u)))) printd(1); else printd(0);

  return 0;
}

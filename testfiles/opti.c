/* optimization tests */

int main() {
  int a;
  string b;

  if ( 0 == 0*100 )
    a = 11+1*4;
  else
    a = 12+2;

  if ( "a" + "aa" != "aa" + 'a' )
    b = "abc" + "def";

  for ( a = a; 0 > 1; b = b+'1' )
    a = a+1;

  return a;
}

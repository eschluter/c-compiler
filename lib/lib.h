#ifndef _CSTR_LIB
#define _CSTR_LIB

/* langage CSTR library */

/* display 's' on stdout */
extern int printf( string s );

/* display integer 'a' on stdout : */
extern int printd( int a );

/* return i-th char on 's' : */
extern int get_char_at( string s, int i );

/* replace i-th char of s by c et return c */
extern int put_char_at( string s, int i, int c );

/* return length s */
extern int strlen( string s );

#endif /* _CSTR_LIB */

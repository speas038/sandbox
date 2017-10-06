#include <glib.h>
#include <stdio.h>

int main()
{

  int one = 1;
  int two = 2;
  
  GList *list = NULL;
  GList *res = NULL;

  res = g_list_append( list, &two );
  res = g_list_append( res, &one );
  
  
  printf( "HELLO\n" );
  return 0;

}

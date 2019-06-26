/* sprintf example */
#include <stdio.h>


int main () {
    char buffer [50];
    int n, a=5, b=3, c=1, d=5;

    //conta quantos caracteres irah possuir a string buffer!!
    n=sprintf(buffer, "%d plus %d is %d and %d plus %d is %d", a, b, a+b,c,d,c+d);
    //imrpime a string buffer carregada, e quantos caracteres possui!!
    printf ("[%s] is a string %d chars long\n ",buffer,n);

    return 0;

}

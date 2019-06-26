#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("%d %s\n\n",argc, *argv);

    char carac[50]= "BELISSIMO TOPISSIMO AULISSIMA";
    char s1[10], s2[10], s3[10];

    sscanf(carac,"%s %s %s", s1, s2, s3);
    printf("\n%s\n%s\n%s\n",s1,s2,s3);

    //printf("%d ---- %s",argc, argv);
    return 0;
}

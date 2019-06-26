#include <stdio.h>
#include <stdlib.h>

struct time{
    int h;//horas
    int m;//minutos
    int s;//segundos

};


int main()
{
    struct time tempo[2];
    int hour, min, secon, a=0;

    do{
        printf("HORAS: ");
        scanf("%d",&hour);
        printf("\nMINUTOS: ");
        scanf("%d",&min);
        printf("\nSEGUNDOS: ");
        scanf("%d",&secon);
        if (min<0 || hour<0 || secon<0)
        {
            printf("\nALGUM DADO ESTÁ INCORRETO!\n");
        }
        else
        {
            tempo[a].h = hour;
            tempo[a].m = min;
            tempo[a].s = secon;
            a++;
        }
    }while((min<0 || hour<0 || secon<0) || a<2);
    for (a=0;a<2;a++){
        printf("%d - %d:%d:%d\n",a+1,tempo[a].h,tempo[a].m,tempo[a].s);
    }

    return 0;
}

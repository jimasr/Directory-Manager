#include <stdio.h>

int main()
{
    int nb;
    printf("Rentrez un nombre : ");
    scanf("%d",&nb);
    for (int i = 0; i < nb; i++)
        printf("Salut mec!\n");
    return 0; 
}

//Character stuffing 

#include<stdio.h>
#include<string.h>
void main()
{
char a[30], fs[50]="", t[3], sd, ed, x[3], s[3], d[3], [3];
int i, j, p = 0 q = 0
printf("Enter characters to be stuffed:");
scanf("%s", a);
printf("\nEnter a character that represents starting delimiter:");
scanf("%c", &sd);
printf("\nEnter a character that represents ending delirniter:");
scanf("%c", &ed);
x[O] = s[O] = s[1] = sd
x[1] = s[2] = 10
y[O] = d[O] = d[1] = ed
d[2] = y[1] ='/0' ;
strcat(fs, x);
for(i=0; i < strlen(a); i++) {
t[O] = a[i];
t[1] = '/0';
if( t[0] ==sd)
strcat(fs, s);
else if(t[0]==e d)
strcat(fs, d);
else
strcat(fs, t);
}
strcat(fs, y);
printf("\n After stuffing:%s", fs);
}
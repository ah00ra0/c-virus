#include <stdio.h>
#include "sds.h"
#define cat sdscat
#define ss sds
#define strnew sdsnew
int main() {
    // ساخت رشته جدید
    // sds myString = sdsnew("Hello");
    // sds a =sdsnew("");
    // // // الحاق رشته
    // // myString = sdscat(myString, " World");
    // a=cat(a,"ahoora");
    // // چاپ رشته و طول آن
    // // printf("%s\n", myString);
    // // printf("Length: %d\n", (int)sdslen(myString));
    // // printf("%s\n",a);
    // // آزادسازی حافظه
    // // sdsfree(myString);
    // // sdsfree(a);




    // ss a =strnew("");
    // scanf("%s",a);
    // ss b=strnew("");
    // scanf("%s",b);
    // a=cat(a,b);
    // printf("%s",a);
    // sdsfree(a);
    // sdsfree(b);
    sds mystring = sdsempty();
    mystring= cat(mystring,"hi");
    sds a= strnew("hi");
    if(sdscmp(mystring, a) == 0)
        printf("%s","yes");    
    
    sdsfree(mystring);

    
    

    return 0;
}

//gcc -o myprogram file.c sds.c


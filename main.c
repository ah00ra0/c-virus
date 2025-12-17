#include "winhttpclientc.h"
#include <stdio.h>
// #include <string.h>
#include <wchar.h>
#include <windows.h>

/*
 char *a;
    char *aa=" ahora ";
    strcpy(a,"hi");//all delite and then write 
    //strcat(a,aa);//and end txt
    //strstr();//serch otput int 
    printf("%d",strstr(a,"hi"));
    return 0;
*/
int main (){
    //get
    // wchar_t *url =L"http://httpbin.org/get";
    // char man[1024];
    // WinHttpInit();
    // SendHttpRequest(L"GET",url,NULL,0,man,FALSE);
    // printf("%s",man);




    //post




//     wchar_t *url = L"http://httpbin.org/post";

//     char *data  = "username=ultra&password=1234";

//     char response[1024];

//     int responselen;

//     WinHttpInit();
    

//   responselen=   SendHttpRequest(L"POST",url, (UCHAR*)data , strlen(data)+1, response , FALSE );

   
 

//     for( int i =0;  i < responselen ; i++ ){
        
//              printf("%c", response[i]);

//     }

//try

   
//     wchar_t *url = L"http://127.0.0.1:8000/c2.php?update";

//     char *data  = "cmd=hiahoora";

//     char response[1024];

//     int responselen;

//     WinHttpInit();
    

//   responselen=   SendHttpRequest(L"POST",url, (UCHAR*)data , strlen(data)+1, response , FALSE );

   
 

//     for( int i =0;  i < responselen ; i++ ){
        
//              printf("%c", response[i]);

   
//     }

     wchar_t *url =L"https://wicked-areas-show.loca.lt/index.php?read=1";
    char man[10000];
    WinHttpInit();
    SendHttpRequest(L"GET",url,NULL,0,man,FALSE);
    printf("%s",man);
    return 0;
   
}
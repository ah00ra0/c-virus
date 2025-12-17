#include "winhttpclientc.h"
#include <stdio.h>
// #include <string.h>
#include <wchar.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

typedef int(__cdecl *function_nircmd)(char *);

/*
 char *a;
    char *aa=" ahora ";
    strcpy(a,"hi");//all delite and then write 
    //strcat(a,aa);//and end txt
    //strstr();//serch otput int 
    printf("%d",strstr(a,"hi"));
    return 0;
*/
void speak(char name[]){
     HINSTANCE hinstLib;
    function_nircmd nircmd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibrary(TEXT("nircmd.dll"));

    if (hinstLib != NULL)
    {
        nircmd = (function_nircmd)GetProcAddress(hinstLib, "DoNirCmd");

        if (NULL != nircmd)
        {
            fRunTimeLinkSuccess = TRUE;
            // FreeConsole();
                char cmd[512];
                snprintf(cmd, sizeof(cmd),
             "speak text \"%s\"",
             name);
            (nircmd)(cmd);
            printf("%d",0);
        }

        fFreeResult = FreeLibrary(hinstLib);
    }

    if (!fRunTimeLinkSuccess)
        printf("Error!!!!!!");
}
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

    //  wchar_t *url =L"https://wicked-areas-show.loca.lt/index.php?read=1";
    // char man[10000];
    // WinHttpInit();
    // SendHttpRequest(L"GET",url,NULL,0,man,FALSE);
    // printf("%s",man);


//asli
     wchar_t *url =L"https://ahoorair.loca.lt/index.php?read=1";
    char man[10000];
    WinHttpInit();
    SendHttpRequest(L"GET",url,NULL,0,man,FALSE);
    man[strcspn(man, "\r\n")] = 0;
    if (strcmp(man, "001")==0)
   {
        speak("hack");
        // printf("%s",man);
   }else
   {
         printf("%s","wrong");
   }
   
    
    
    return 0;
   
}
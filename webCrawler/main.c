#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HYPERLINKS 100

typedef struct _url {
    char name[30];
    char *hyperLink[HYPERLINKS];
    int cnt;
} Url;

void insertHyperLink(Url *url, char *str) {
    url->hyperLink[url->cnt] = str;
    url->cnt++;
};

void printUrl(Url *url) {
    printf("URL: %s [%d]\n", url->name, url->cnt);
    for (int i = 0; i < url->cnt; i++) {
        printf("\t %s\n", url->hyperLink[i]);
    }

}

int main()
{
    Url link;
    strcpy(link.name, "Raja");
    link.cnt = 0;

    insertHyperLink(&link,"google");
    insertHyperLink(&link, "facebook");
    insertHyperLink(&link, "twitter");

    printUrl(&link);
    return 0;
}

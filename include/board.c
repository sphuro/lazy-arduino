#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

int get_boards(Board boards[], int max) {
    FILE *fp = popen("arduino-cli board list --format json", "r");
    if (!fp) return -1;

    char buf[8192];
    fread(buf, 1, sizeof(buf), fp);
    pclose(fp);

    int count = 0;
    char *ptr = buf;

    while ((ptr = strstr(ptr, "\"address\"")) && count < max) {
        char *addr_start = strchr(ptr, ':');
        if (!addr_start) break;
        addr_start = strchr(addr_start, '"') + 1;
        char *addr_end = strchr(addr_start, '"');
        strncpy(boards[count].port, addr_start, addr_end - addr_start);
        boards[count].port[addr_end - addr_start] = '\0';

        ptr = strstr(ptr, "\"boardName\"");
        if (!ptr) break;
        char *name_start = strchr(ptr, ':');
        name_start = strchr(name_start, '"') + 1;
        char *name_end = strchr(name_start, '"');
        strncpy(boards[count].boardName, name_start, name_end - name_start);
        boards[count].boardName[name_end - name_start] = '\0';

        ptr = name_end;
        count++;
    }

    return count;
}


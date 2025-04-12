#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_debugger_present() {
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) {
        perror("fopen");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "TracerPid:", 10) == 0) {
            int tracer_pid = atoi(line + 10);
            fclose(f);
            return tracer_pid != 0;
        }
    }

    fclose(f);
    return 0;
}

int main() {
    printf("Spouštím monitorování...\n");

    while (1) {
        if (is_debugger_present()) {
            system("clear");
            printf("Debugger detekován!\n");
            // Zde můžete přidat kód, který se vykoná při detekci debuggeru
        } else {
            system("clear");
            printf("Debugger není přítomen.\n");
        }

        usleep(100000);
    }

    return 0;
}

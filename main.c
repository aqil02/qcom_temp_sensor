#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

struct tempSensor {
    char sysfsName[16];
    char realName[128];
    int value;
};


int main(void) {
    struct dirent *entry;
    char sysfsBase[] = "/sys/devices/virtual/thermal/";
    DIR *folder = opendir(sysfsBase);

    if (folder == NULL)
    {
        puts("Directory doesn't exist!");
        return(1);
    }
    while ((entry=readdir(folder)))
    {
        //printf("%s\n", entry->d_name);
        int checkForThermals = strcmp("thermal_zone", entry->d_name);
        if (checkForThermals < 0)
        {
            char sysfsConfigName[128];
            char sysfsValueName[128];
            char sensorName[128];
            char sensorValue[16];

            strcpy(sysfsConfigName, sysfsBase);
            strcat(sysfsConfigName, entry->d_name);
            strcpy(sysfsValueName, sysfsConfigName);
            strcat(sysfsConfigName, "/config");
            strcat(sysfsValueName, "/temp");

            FILE *sysfsptr = fopen(sysfsConfigName, "r");
            if (sysfsptr == NULL) {
                printf("Sensor doesn't exist!");
            }

            FILE *valuesysfsptr = fopen(sysfsValueName, "r");
            if (valuesysfsptr == NULL) {
                printf("Temp for sensor doesn't exist!");
            }

            //Read config into memory
            while (fgets(sensorName, sizeof(sensorName), sysfsptr)) {
                int sensorLine = strcmp("sensor", sensorName);
                if (sensorLine < 0) {
                    *sensorName = sensorLine;
                    break;
                }
            }
            fclose(sysfsptr);

            fgets(sensorValue, sizeof(sensorValue), valuesysfsptr);
            fclose(valuesysfsptr);
            long sensorValueInt = atoi(sensorValue);
            sensorValueInt = sensorValueInt / 1000.0;

            printf("%s\n Contents: %s Value: %ld\n", entry->d_name, sensorName, sensorValueInt);
        }
    }
    closedir(folder);
    return 0;
}

#include <stdio.h>
#include <windows.h>

int main() {
    DWORD sectorsPerCluster, bytesPerSector, freeClusters, totalClusters;

    if(GetDiskFreeSpaceA("C:\\",&sectorsPerCluster,&bytesPerSector,&freeClusters,&totalClusters)) {
        unsigned long long total = (unsigned long long)sectorsPerCluster*bytesPerSector*totalClusters;
        unsigned long long free = (unsigned long long)sectorsPerCluster*bytesPerSector*freeClusters;
        printf("Drive C:\\ Total: %llu MB Free: %llu MB\n", total/1024/1024, free/1024/1024);
    }
    return 0;
}

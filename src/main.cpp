#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>

void* AllocateAlignedBelow2GB(size_t size, size_t alignment)
{
    MEM_ADDRESS_REQUIREMENTS addressReqs = {0};
    MEM_EXTENDED_PARAMETER param = {0};

    addressReqs.Alignment = alignment;
    addressReqs.HighestEndingAddress = (PVOID)(ULONG_PTR) 0x7fffffff;

    param.Type = MemExtendedParameterAddressRequirements;
    param.Pointer = &addressReqs;

    return VirtualAlloc2 (
        nullptr, nullptr,
        size,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE,
        &param, 1);
}

int main() {

    WSADATA wsaData;
    int iResult;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        return -1;
    }

    WSACleanup();

    AllocateAlignedBelow2GB(1024 * 1024, 1024);
    
    return 0;
}

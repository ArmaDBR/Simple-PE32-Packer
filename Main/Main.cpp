#include <stdio.h>
#include <Windows.h>
#pragma comment (lib, ".\\DLLs\\packer.lib")

__declspec(dllimport) BOOL Pack(LPCSTR strSrcPath, LPCSTR strDstPath);
__declspec(dllimport) BOOL Unpack(LPCSTR strSrcPath, LPCSTR strDstPath);

int main(int argc, char * argv[])
{
	if (argc < 3)
		printf("Usage : Uchiha_Packer.exe [-d] SrcPath DstPath\n");

	if (!strcmp(argv[1], "-d"))
	{
		if (Unpack(argv[2], argv[3]))
		{
			printf("The file has been successfully unpacked.");
		}
	}
	else
	{
		if (Pack(argv[1], argv[2]))
		{

			HANDLE hSrcFile = CreateFileA(argv[1], GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
			HANDLE hDstFile = CreateFileA(argv[2], GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);

			DWORD dwSrcSize = GetFileSize(hSrcFile, NULL);
			DWORD dwDstSize = GetFileSize(hDstFile, NULL);

			DWORD dwPercentage = (((double)dwSrcSize - (double)dwDstSize) / (double)dwSrcSize) * 100.0;

			printf("Original Size : %d Bytes\nPacked Size : %d Bytes\nPercentage : %d%%\n", dwSrcSize, dwDstSize, dwPercentage);
		}
	}

    return 0;
}
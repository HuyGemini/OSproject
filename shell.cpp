#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <strings.h>
#include <conio.h>
BOOL GetProcessList( );
void killProcessByName();
void killProcessByID();
void help();
int main()
{
  char command[5];
  system("cls");
  printf("\n\nWelcome to F5Shell\n\n");
  printf("\n\tF5Shell support the following command:");
  printf("\n\t1. List the running Process");
  printf("\n\t2. Kill the running Process by name");
  printf("\n\t3. Kill the running Process by ID");
   printf("\n\t4. Help");
  printf("\n\t10. Clear screen");
  printf("\n\t11. Exit F5Shell\n\n");
  do{
    printf("\nF5Shell>");
    fflush(stdin);
    gets(command);
    if(strcmp(command,"1")==0) GetProcessList();
    else if(strcmp(command,"2")==0) killProcessByName();
    else if(strcmp(command,"3")==0) killProcessByID();
    else if(strcmp(command,"4")==0) help();
    else if(strcmp(command,"10")==0) system("cls");
    else if(strcmp(command,"11")==0) break;
    else {
      printf("Nhap ngu vc");
    }
  }while (1);
  return 0;
}



BOOL GetProcessList( )
{
  int count=0;
  HANDLE hProcessSnap;
  PROCESSENTRY32 pe32;
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
  {
    printf("CreateToolhelp32Snapshot (of processes)\n" );
    return( FALSE );
  }

  // Set the size of the structure before using it.
  pe32.dwSize = sizeof( PROCESSENTRY32 );

  // Retrieve information about the first process,
  // and exit if unsuccessful
  if( !Process32First( hProcessSnap, &pe32 ) )
  {
    printf("Process32First\n" ); // show cause of failure
    CloseHandle( hProcessSnap );          // clean the snapshot object
    return( FALSE );
  }

  // Now walk the snapshot of processes, and

  printf("\n\n=====================================================\n");
  printf("|STT |                 PROCESS NAME                     |Process ID|       Thread count|Parent process ID\n");
  do
    {
      printf("|%4d|%-50s|%6d|%7d%|%6d|\n",count,pe32.szExeFile,pe32.th32ProcessID,pe32.cntThreads,pe32.th32ParentProcessID);
      count++;
    }   while( Process32Next( hProcessSnap, &pe32 ) );

  printf("\n-------------------------------------------------------");
  CloseHandle( hProcessSnap );
  return( TRUE );
}


void killProcessByName()
{
    char filename[50];
    printf("\nNhap ten tien trinh: ");
    fflush(stdin);
    gets(filename);
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

void killProcessByID()
{
  int pid;
  printf("\nNhap ID cua tien trinh: ");
  scanf("%d",pid);
  HANDLE handy;
  handy =OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE, TRUE,pid);
  TerminateProcess(handy,0);
}

void help(){
  printf("\n\tF5Shell support the following command:");
  printf("\n\t1. List the running Process");
  printf("\n\t2. Kill the running Process by name");
  printf("\n\t3. Kill the running Process by ID");
  printf("\n\t10. Clear screen");
  printf("\n\t11. Exit F5Shell\n\n");

}

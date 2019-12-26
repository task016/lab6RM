// Zadaci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zad910.h"
#include <io.h>
#include <stdio.h>
#include <fcntl.h>
#include<math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

void parse(char *s)
{
	printf("Content-Type: text/html\n\n");
	CString pom(s);
	int len=pom.GetLength();
	int cena=500;

	if(pom.Find(_T("dvd"))<=len && pom.Find(_T("dvd"))>0)
		cena=cena+30;
	if(pom.Find(_T("TV_tuner"))<=len && pom.Find(_T("TV_tuner"))>0)
		cena=cena+40;
	if(pom.Find(_T("stampac"))<=len && pom.Find(_T("stampac"))>0)
		cena=cena+50;
	
	printf("<html><p>Cena je: %d  E</html>",cena);
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		char* reqmethod = getenv("REQUEST_METHOD");	//cita request method GET ili POST
		char* q_string = getenv("QUERY_STRING");

		CString s_get("GET");
		CString s_post("POST");
		if(s_get.CompareNoCase(CString(reqmethod)) == 0)
		{
			if(q_string != NULL)
			parse(q_string);
		}
		else
			if(s_post.CompareNoCase(CString(reqmethod)) == 0)
			{
				int br_byte = atoi(getenv("CONTENT_LENGTH"));
				if(br_byte > 0)
				{
					char* postInput = new char[br_byte];
					scanf("%s", postInput);
				
					parse(postInput);
				}
				else
					AfxMessageBox(_T("Nema podataka"));
			}
	}
	return nRetCode;
}





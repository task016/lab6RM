// Zadaci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zad1234.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <afx.h>
#include<math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

void SendFile(CString outName)
{
	CFile f;
    	if(!f.Open(outName, CFile::modeRead))
	{
		AfxMessageBox(_T("Fajl nije pronadjen!"));
		exit(-1);
	}
	DWORD len = f.GetLength(); //32bitni unsgined integer
	printf("Content-Type: image/jpeg\r\n");
	printf("Content-Length: %d\r\n\r\n", len);

	int result;
	result = _setmode(_fileno(stdout), _O_BINARY);
	if(result == -1)
	{
		AfxMessageBox(_T("Ne moze se postaviti binarni mod!"));
		exit(-1);
	}
	else
	{
		for(long i=0; i<len; i++)
		{
			BYTE buf;
			f.Read(&buf, 1);
			printf("%c", buf);
		}

		fflush(stdout); //ipraznjivanje bafera stdout
		result = _setmode(_fileno(stdout), _O_TEXT);
		if(result == -1)
		{
			AfxMessageBox(_T("Ne moze da vrati tekstualni mod!"));
		}
	}
	f.Close();

}

void parse(char* string) 
{
	CString izbor(string);
	int poc = izbor.Find(_T("Slika=")) + 6; 
	int kraj = izbor.GetLength();
	CString slika;
	for(int i=poc; i<kraj; i++)
		slika.AppendChar(izbor[i]);

	SendFile(slika);
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
			if(q_string != NULL) parse(q_string);
		}
		else if(s_post.CompareNoCase(CString(reqmethod)) == 0)
		{
			int br_byte = atoi(getenv("CONTENT_LENGTH"));
			if(br_byte > 0)
			{
				char* postInput = new char[br_byte];
				scanf("%s", postInput);
					
				parse(postInput);
			}
			else AfxMessageBox(_T("Nema podataka"));
		}
	}
	return nRetCode;
}


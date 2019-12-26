// Zadaci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zad56.h"
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


void parse(char *s)
{
	CString str(s);
	int  broj=0;

	CString pr;
	int p=str.Find(_T("prva="))+5;
	for(int i=p;str[i]!='&';i++)
		pr.AppendChar(str[i]);
	broj+=_wtoi(pr);

	CString dr;
	 p=str.Find(_T("druga="))+6;
	for(int i=p;str[i]!='&';i++)
		dr.AppendChar(str[i]);
	broj+=_wtoi(dr);

	CString tr;
	p=str.Find(_T("treca="))+6; 
	for(int i=p;str[i]!='&';i++)
		tr.AppendChar(str[i]);
	broj+=_wtoi(tr);

	CString ce;
	p=str.Find(_T("cetvrta="))+8; 
	for(int i=p;str[i]!='&';i++)
		ce.AppendChar(str[i]);
	broj+=_wtoi(ce);

	CString pe;
	p=str.Find(_T("peta="))+5;
	int k=str.GetLength();
	for(int i=p;i<k;i++)
		pe.AppendChar(str[i]);
	broj+=_wtoi(pe);

   	float srednja=(float)broj/5;
	
	printf("Content-Type: text/html\n\n");
	printf("<html><p>Srednja ocena je: %.2f </html>",srednja);
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


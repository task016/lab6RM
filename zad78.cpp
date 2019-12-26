// Zadaci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zad78.h"
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

void parse(char* string)
{
	CString str(string);

	int ProcesorPoc = str.Find(_T("Procesor=")) + 9;
	int ProcesorKraj = str.Find(_T("&"));

	CString procesor;
	for(int i=ProcesorPoc; i<ProcesorKraj; i++)
		procesor.AppendChar(str[i]);

	int MaticnaPoc = str.Find(_T("MaticnaPloca=")) + 13;
	int MaticnaKraj = str.GetLength();

	CString maticna;
	for(int i=MaticnaPoc; i<MaticnaKraj; i++)
		maticna.AppendChar(str[i]);

	double cena = 0.0;
	if(procesor.CompareNoCase(_T("Inteli3")) == 0)
		cena += 10348;
	else
		if(procesor.CompareNoCase(_T("AMDAthlon")) == 0)
			cena += 8746;
		else
			if(procesor.CompareNoCase(_T("AMDPhenom")) == 0)
				cena += 9678;

	if(maticna.CompareNoCase(_T("ASUS")) == 0)
		cena += 8563;
	else
		if(maticna.CompareNoCase(_T("ASUSExtreme")) == 0)
			cena += 24365;
		else
			if(maticna.CompareNoCase(_T("GIGABYTE")) == 0)
				cena += 7834;

        printf("Content-Type: text/html\n\n");
	printf("<html><p>%.2f RSD</html>", cena);
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
		//char* POST_INPUT;
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

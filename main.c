/*
 * Programa de instalacion que va dentro de los Máster de Fabricante.
 * 
 * Sustituye el InstalaciuonATM,exe de NCR.
*/ 

// *** http://www.winprog.org/tutorial/ ***

#include <windows.h>
#include <CommCtrl.h>
#include <stdio.h>

#include "string.h"
#include "ventano.h"


#define MAXCDMS 100
#define CMDLEN  2048



FILE *pLog;
#define Log(...) fprintf (pLog, __VA_ARGS__)

DWORD ejecuta(char *strCmd);


DWORD nScreenX=800;
DWORD nScreenY=600;


const char strTituloVersion[] = "InstalacionATM - Unicaja - V. 1.00\n";


// Step 4: the Window Procedure
LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UINT nIdxBoton = LOWORD(wParam);
	UINT nCmdBoton = HIWORD(wParam);
	
    switch(msg)
    {
        case WM_CLOSE://Para la ventana
            DestroyWindow(hwnd);
			break;
        case WM_DESTROY://Para la ventana
            PostQuitMessage(0);
			break;
        
        case WM_COMMAND://Para los botones
			
			switch(nIdxBoton)
			{
				case 1:
					if(nCmdBoton == BN_CLICKED)
					{
						/* Action here */
						//MessageBox(NULL, "Hola Mundo!!!!", "Error!", MB_ICONEXCLAMATION | MB_OK);
						break;
					}
					else
						return DefWindowProc(hwnd, msg, wParam, lParam);

				default:
					return DefWindowProc(hwnd, msg, wParam, lParam);
			}
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    VENTANO obVentana;
    LABEL obLblTitulo;
    LABEL obLblTextoLeyenda;
    PROGRESSBAR obProgress;
    BUTTON obButton;
    TEXTFIELD obTextField;
    RICHTEXTAREA obTextArea;
    
    //HWND hwndBtnReconstruirDisco;
    MSG Msg;
	FILE *pF;
	UINT nExexRet;
	
	pLog=fopen("c:\\instala\\InstalacionATM.log", "w+");
	
	Log(strTituloVersion);
	Log("Numero Maximo de comandos a procesar: %d\n", MAXCDMS);
	Log("Longitud maxima de cada comando: %d\n", CMDLEN);
	

	newVENTANO(&obVentana, "Mi Titulo", hInstance, nCmdShow, WindowCallBack, 800, 600, 50, 50);


	//Obtener resolucion de pantalla
	nScreenX=GetSystemMetrics(SM_CXSCREEN);
	nScreenY=GetSystemMetrics(SM_CYSCREEN);

	newRICHTEXTAREA(&obTextArea, &obVentana, "Hola Mundo", 200, 200, 300, 300);
	newBUTTON(&obButton, &obVentana, "Prueba", 1, 100, 40, 20, 20);
	newTEXTFIELD(&obTextField, &obVentana, "Texto por defecto", 300, 15, 155, 20);
	
	newLABEL(&obLblTitulo, &obVentana, strTituloVersion, nScreenX - 200, 30, 100, 100);
	setLABELFont(&obLblTitulo, "Arial", 30, 1, 0, 0);
	newPROGRESSBAR(&obProgress, &obVentana, nScreenX - 200, 75, 100, 400);
	newLABEL(&obLblTextoLeyenda, &obVentana, "", 800, 30, 0, 550);


	showVENTANO(&obVentana, nCmdShow);


	pF=fopen("c:\\instala\\InstalacionATM.cfg", "r");
	if (pF == NULL){
		Log("ERROR. No encuentro c:\\instala\\InstalacionATM.cfg\n");
        return 10; 
	}

	int nComandos=0;
	char strComandos[MAXCDMS][CMDLEN];
	char strLinea[CMDLEN]={0};
	
	//while(fgets(strComandos[nComandos], CMDLEN, pF)!=NULL){
	while(fgets(strLinea, CMDLEN, pF)!=NULL){
		//Log("Comando leido -> %s", strComandos[nComandos]);
		Log("Comando leido -> %s", strLinea);
		trim(strLinea);
		if(strLinea[0]!='#'){
			strncpy(strComandos[nComandos], trim(strLinea), CMDLEN);
			nComandos++;
			memset(strLinea, 0, CMDLEN);
		}
	}
	fclose(pF);
	
	Log("Numero de comandos-> %d", nComandos);
	setPROGRESSBARRange(&obProgress, 0, nComandos-1);
	definePROGRESSBARStep(&obProgress, 1);
	setPROGRESSBARPossition(&obProgress, 0);
	

	
	int nCmd=0;
	for(nCmd=0; nCmd<nComandos; nCmd++){
		if(nCmd < MAXCDMS){
			Log("Ejecutando comando-> %s", strComandos[nCmd]);
			
			//Mostrar comando que se ejecuta ...
			setLABELText(&obLblTextoLeyenda, strComandos[nCmd]);
			
			//nExexRet=WinExec(strComandos[nCmd], SW_HIDE);
			nExexRet=ejecuta(strComandos[nCmd]);
			
			//Avanzar la progressBar
			incrementaPROGRESSBAR(&obProgress);
			
			//if(nExexRet<32){ //Para WinExec
			if(nExexRet!=0){ //Para ejecuta
				Log("[ERROR]. Ejecutando comando. Ret=%d\n", nExexRet);
			}else{
				Log("[OK]. Ejecutando comando. Ret=%d\n", nExexRet);
			}
		} else {
			Log("[ERROR]. Maximo numero de comandos alcanzado. %d\n", MAXCDMS);
		}
	}
	
	fclose(pLog);
	
    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    
    return Msg.wParam;
}

DWORD ejecuta(char *strCmd)
{
	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi = { 0 };
	DWORD exitCode=1;
	
	BOOL success = CreateProcess(
      NULL /*L"C:\\Windows\\system32\\notepad.exe"*/,  // Path to executable
      strCmd,                                   // Command line arguments
      NULL,                                   // Process attributes
      NULL,                                   // Thread attributes
      FALSE,                                  // Inherit handles
      CREATE_NO_WINDOW,                       // Creation flags
      NULL,                                   // Environment
      NULL,                                   // Working directory
      &si,                                    // Startup info
      &pi);                                   // Process information

	if (success)
	{
		// Esperar el Exit del proceso
		WaitForSingleObject(pi.hProcess, INFINITE);

		//Obtener el exit code del proceso
		GetExitCodeProcess(pi.hProcess, &exitCode);

		// Cerrar los handlers
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	
	return exitCode;
}



#include "ventano.h"


char *windowCallBackEjemplo="\
LRESULT CALLBACK WindowCallBack(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)\n\
{\n\
	UINT nIdxBoton = LOWORD(wParam);\n\
	UINT nCmdBoton = HIWORD(wParam);\n\
	\n\
    switch(msg)\n\
    {\n\
        case WM_CLOSE://Para la ventana\n\
            DestroyWindow(hwnd);\n\
			break;\n\
        case WM_DESTROY://Para la ventana\n\
            PostQuitMessage(0);\n\
			break;\n\
        \n\
        case WM_COMMAND://Para los botones\n\
			\n\
			switch(nIdxBoton)\n\
			{\n\
				case 1:\n\
					if(nCmdBoton == BN_CLICKED)\n\
					{\n\
						/* Action here */\n\
						//MessageBox(NULL, \"Hola Mundo!!!!\", \"Error!\", MB_ICONEXCLAMATION | MB_OK);\n\
						break;\n\
					}\n\
					else\n\
						return DefWindowProc(hwnd, msg, wParam, lParam);\n\
\n\
				default:\n\
					return DefWindowProc(hwnd, msg, wParam, lParam);\n\
			}\n\
        \n\
        default:\n\
            return DefWindowProc(hwnd, msg, wParam, lParam);\n\
    }\n\
    return 0;\n\
}\n\
";


VENTANO *newVENTANO(VENTANO *obVentana, const char *strTitulo, HINSTANCE hAppInstance, int nCmdShow, void *fnCallback, int nAncho, int nAlto, int nX, int nY){
	
	obVentana->hAppInstance=hAppInstance;
	obVentana->nCmdShow=nCmdShow;
	
    //Step 1: Registering the Window Class
    obVentana->wc.cbSize        = sizeof(WNDCLASSEX);
    obVentana->wc.style         = 0;
    obVentana->wc.lpfnWndProc   = fnCallback;
    obVentana->wc.cbClsExtra    = 0;
    obVentana->wc.cbWndExtra    = 0;
    obVentana->wc.hInstance     = hAppInstance;
    obVentana->wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    obVentana->wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    obVentana->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    obVentana->wc.lpszMenuName  = NULL;
    obVentana->wc.lpszClassName = strTitulo;
    obVentana->wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);	
    
    if(!RegisterClassEx(&obVentana->wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }
	
	// Step 2: Creating the Window
    obVentana->hwnd = CreateWindowEx(
        0 /*WS_EX_CLIENTEDGE*/,
        strTitulo,
        strTitulo,
        WS_OVERLAPPEDWINDOW |/* WS_MAXIMIZE | WS_POPUP | */WS_VISIBLE, // Sin caption y maximizada
        nX, nY, nAncho, nAlto,
        NULL, NULL, hAppInstance, NULL);

    if(obVentana->hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    
    
    return obVentana;
}

void showVENTANO(VENTANO *obVentana, int nCmdShow){
	ShowWindow(obVentana->hwnd, nCmdShow);
    UpdateWindow(obVentana->hwnd);
}

char *getVENTANOCallbackEjemplo(void){
	return windowCallBackEjemplo;
}


LABEL *newLABEL(LABEL *obLabel, VENTANO *obVentana, const char *strTexto, int nAncho, int nAlto, int nX, int nY){
	
		obLabel->hwndLabel = CreateWindowEx(
			0, 
			"STATIC", 
			strTexto, 
			WS_CHILD | WS_VISIBLE /*| SS_CENTER*/, 
			nX, 
			nY, 
			nAncho, 
			nAlto, 
			obVentana->hwnd, 
			(HMENU) 0, 
			obVentana->hAppInstance, 
			NULL);
	
	return obLabel;
}

void setLABELText(LABEL *obLabel, const char *strTexto){
	SendMessage(obLabel->hwndLabel, WM_SETTEXT, 0, (LPARAM)strTexto);
}

void setLABELFont(LABEL *obLabel, const char *strFuente, int nTamanio, unsigned char swBold, unsigned char swItalic, unsigned char swSunrayado){
        /*
         HFONT CreateFontA(int cHeight, int cWidth, int cEscapement, int cOrientation,
			int cWeight, DWORD bItalic, DWORD bUnderline, DWORD bStrikeOut, DWORD iCharSet,
			DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily,
			LPCSTR pszFaceName);
		*/
	HFONT hFont=CreateFont (30, 0, 0, 0, (swBold==1)?FW_BOLD:FW_NORMAL, (swItalic==1)?TRUE:FALSE, (swSunrayado==1)?TRUE:FALSE, 
		FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, strFuente);
	SendMessage (obLabel->hwndLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
}









PROGRESSBAR *newPROGRESSBAR(PROGRESSBAR *obProgress, VENTANO *obVentana, int nAncho, int nAlto, int nX, int nY){
	
	obProgress->hwndProgressBar = CreateWindowEx(
		0, 
		PROGRESS_CLASS, 
		(LPTSTR) NULL, 
        WS_CHILD | WS_VISIBLE | PBS_MARQUEE, 
        nX, 
        nY, 
        nAncho, 
        nAlto, 
        obVentana->hwnd, 
        (HMENU) 0, 
        obVentana->hAppInstance, 
        NULL);
        
        return 	obProgress;
}

void setPROGRESSBARRange(PROGRESSBAR *obProgress, int nInicio, int nFin){
	SendMessage(obProgress->hwndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(nInicio, nFin));
}

void definePROGRESSBARStep(PROGRESSBAR *obProgress, int nStep){
	SendMessage(obProgress->hwndProgressBar, PBM_SETSTEP, nStep, 0); 
}

void setPROGRESSBARPossition(PROGRESSBAR *obProgress, int nPossition){
	SendMessage(obProgress->hwndProgressBar, PBM_SETPOS, nPossition, 0);
}

void incrementaPROGRESSBAR(PROGRESSBAR *obProgress){
	SendMessage(obProgress->hwndProgressBar, PBM_DELTAPOS, 1, 0);
}






BUTTON *newBUTTON(BUTTON *obButton, VENTANO *obVentana, const char *strText, int nButtonIndex, int nAncho, int nAlto, int nX, int nY){
	
    obButton->hwndButton = CreateWindowEx(
        0, 
        "BUTTON", 	// Predefined class; Unicode assumed 
        strText, // Button text
        WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON, // Styles 
        nX, // x position
        nY, 			// y position
        nAncho, 			// Button width
        nAlto, 			// Button height
        obVentana->hwnd, 			// Parent window
        (HMENU)nButtonIndex, 		// Menu Index 1.
        obVentana->hAppInstance, 
        NULL);			// Pointer not needed.

	
	return obButton;
}





TEXTFIELD *newTEXTFIELD(TEXTFIELD *obTextField, VENTANO *obVentana, const char *strDefText, int nAncho, int nAlto, int nX, int nY){
	obTextField->hwndTextField=CreateWindowEx(
        0, 
        "EDIT", 	// Predefined class; Unicode assumed 
        strDefText, // Button text
        WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER, // Styles 
        nX, // x position
        nY, 			// y position
        nAncho, 			// Button width
        nAlto, 			// Button height
        obVentana->hwnd, 			// Parent window
        (HMENU)0, 		// Menu Index 1.
        obVentana->hAppInstance, 
        NULL);			// Pointer not needed.
	
	obTextField->txtBuff=NULL;
	
	return obTextField;
}

void setTEXTFIELDText(TEXTFIELD *obTextField, const char *strText){
	SetWindowText(obTextField->hwndTextField, strText);
}

char *getTEXTFIELDText(TEXTFIELD *obTextField, char *strRet){
	//https://stackoverflow.com/questions/35213529/winapi-retrieving-text-from-edit-control
	
	int len;
	
	if(obTextField->txtBuff!=NULL)
		free(obTextField->txtBuff);

	len=(GetWindowTextLength(obTextField->hwndTextField)+1)*sizeof(char);
	
	if((obTextField->txtBuff=malloc(len))!=NULL)
		GetWindowText(obTextField->hwndTextField, obTextField->txtBuff, len);
	
	strRet=obTextField->txtBuff;
	
	return strRet;
}






RICHTEXTAREA *newRICHTEXTAREA(RICHTEXTAREA *obTextArea, VENTANO *obVentana, const char *strDefText, int nAncho, int nAlto, int nX, int nY){
	LoadLibrary(TEXT("Msftedit.dll"));
    
    obTextArea->hwndTextArea= CreateWindowEx(
		0, 
		"RICHEDIT50W" /*MSFTEDIT_CLASS*/, 
		strDefText,
        ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 
        nX, 
        nY, 
        nAncho, 
        nAlto, 
        obVentana->hwnd, 
        NULL, 
        obVentana->hAppInstance, 
        NULL);	
	
	obTextArea->txtBuff=NULL;
	
	return obTextArea;
}

void setRICHTEXTAREAText(RICHTEXTAREA *obTextArea, const char *strText){
	SetWindowText(obTextArea->hwndTextArea, strText);
}

char *getRICHTEXTAREAText(RICHTEXTAREA *obTextArea, char *strRet){
	
	int len;
	
	if(obTextArea->txtBuff!=NULL)
		free(obTextArea->txtBuff);

	len=(GetWindowTextLength(obTextArea->hwndTextArea)+1)*sizeof(char);
	
	if((obTextArea->txtBuff=malloc(len))!=NULL)
		GetWindowText(obTextArea->hwndTextArea, obTextArea->txtBuff, len);
	
	strRet=obTextArea->txtBuff;
	
	return strRet;
}

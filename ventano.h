#include <windows.h>
#include <CommCtrl.h>

#ifndef ventano_h

#define ventano_h

typedef struct{
	WNDCLASSEX wc;
	HWND hwnd;
	HINSTANCE hAppInstance;
	int nCmdShow;
	void *fnCallback;
}VENTANO;
VENTANO *newVENTANO(VENTANO *obVentana, const char *strTitulo, HINSTANCE hAppInstance, int nCmdShow, void *fnCallback, int nAncho, int nAlto, int nX, int nY);
void showVENTANO(VENTANO *obVentana, int nCmdShow);
char *getVENTANOCallbackEjemplo(void);

typedef struct{
	HWND hwndLabel;
}LABEL;
LABEL *newLABEL(LABEL *obLabel, VENTANO *obVentana, const char *strTexto, int nAncho, int nAlto, int nX, int nY);
void setLABELText(LABEL *obLabel, const char *strTexto);
void setLABELFont(LABEL *obLabel, const char *strFuente, int nTamanio, unsigned char swBold, unsigned char swItalic, unsigned char swSunrayado);


typedef struct{
	HWND hwndProgressBar;
}PROGRESSBAR;
#define PBS_MARQUEE  0x08 
#define PBM_SETMARQUEE WM_USER + 10 
PROGRESSBAR *newPROGRESSBAR(PROGRESSBAR *obProgress, VENTANO *obVentana, int nAncho, int nAlto, int nX, int nY);
void setPROGRESSBARRange(PROGRESSBAR *obProgress, int nInicio, int nFin);
void definePROGRESSBARStep(PROGRESSBAR *obProgress, int nStep);
void setPROGRESSBARPossition(PROGRESSBAR *obProgress, int nPossition);
void incrementaPROGRESSBAR(PROGRESSBAR *obProgress);



typedef struct{
	HWND hwndButton;
}BUTTON;
BUTTON *newBUTTON(BUTTON *obButton, VENTANO *obVentana, const char *strText, int nButtonIndex, int nAncho, int nAlto, int nX, int nY);

typedef struct{
	HWND hwndTextField;
	char *txtBuff;
}TEXTFIELD;
TEXTFIELD *newTEXTFIELD(TEXTFIELD *obTextField, VENTANO *obVentana, const char *strDefText, int nAncho, int nAlto, int nX, int nY);
void setTEXTFIELDText(TEXTFIELD *obTextField, const char *strText);
char *getTEXTFIELDText(TEXTFIELD *obTextField, char *strRet);


typedef struct{
	HWND hwndTextArea;
	char *txtBuff;
}RICHTEXTAREA;
#define MSFTEDIT_CLASS "RICHEDIT50W"
RICHTEXTAREA *newRICHTEXTAREA(RICHTEXTAREA *obTextArea, VENTANO *obVentana, const char *strDefText, int nAncho, int nAlto, int nX, int nY);
void setRICHTEXTAREAText(RICHTEXTAREA *obTextArea, const char *strText);
char *getRICHTEXTAREAText(RICHTEXTAREA *obTextArea, char *strRet);



#endif

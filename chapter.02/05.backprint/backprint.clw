; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBackprintDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "backprint.h"

ClassCount=3
Class1=CBackprintApp
Class2=CBackprintDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_BACKPRINT_DIALOG
Resource4=IDR_MENU_MAIN

[CLS:CBackprintApp]
Type=0
HeaderFile=backprint.h
ImplementationFile=backprint.cpp
Filter=N

[CLS:CBackprintDlg]
Type=0
HeaderFile=backprintDlg.h
ImplementationFile=backprintDlg.cpp
Filter=D
LastObject=CBackprintDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=backprintDlg.h
ImplementationFile=backprintDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BACKPRINT_DIALOG]
Type=1
Class=CBackprintDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_TEXT,edit,1350631552
Control3=IDC_BTN_DISPLAY,button,1342242817
Control4=IDC_BTN_PRINT,button,1342242816
Control5=IDC_OUTPUT,button,1342177287

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=IDC_FILE_EXIT
Command2=IDC_FILE_ABOUT
CommandCount=2


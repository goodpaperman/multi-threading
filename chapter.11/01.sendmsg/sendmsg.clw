; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSendmsgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sendmsg.h"

ClassCount=3
Class1=CSendmsgApp
Class2=CSendmsgDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SENDMSG_DIALOG

[CLS:CSendmsgApp]
Type=0
HeaderFile=sendmsg.h
ImplementationFile=sendmsg.cpp
Filter=N

[CLS:CSendmsgDlg]
Type=0
HeaderFile=sendmsgDlg.h
ImplementationFile=sendmsgDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_BTN_SEND

[CLS:CAboutDlg]
Type=0
HeaderFile=sendmsgDlg.h
ImplementationFile=sendmsgDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SENDMSG_DIALOG]
Type=1
Class=CSendmsgDlg
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_ID,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=ID_BTN_SEND,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_MSG,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_RET,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_RADIO_THREAD,button,1342373897
Control12=IDC_RADIO_WND,button,1342177289


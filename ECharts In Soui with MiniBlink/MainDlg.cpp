// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "controls/SMiniBlink.h"
	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	// 加载本地文件
	SOUI::SWkeWebkit *pWkeWebkit = FindChildByName2<SOUI::SWkeWebkit>(L"wke_test");
	if (pWkeWebkit != NULL) {
		/*pWkeWebkit->GetWebView()->loadFile("E:\\myproject\\[4] Just for Fun\\ECharts In Soui\\ECharts In Soui with MiniBlink\\echarts\\Demo1.htm");*/
		wkeLoadFile(pWkeWebkit->GetWebView(), "E:\\myproject\\[4] Just for Fun\\ECharts In Soui\\ECharts In Soui with MiniBlink\\echarts\\Demo1.htm");
		const char *js = "                                                  \
			var myChart = echarts.init(document.getElementById(\'main\'));  \
				var option = {												\
				title: {													\
				text: \'ECharts 入门示例\'									\
		},																	\
				tooltip : {},												\
				legend : {													\
				data:[\'销量\']												\
		},																	\
				xAxis : {													\
				data: [\"衬衫\",\"羊毛衫\",\"雪纺衫\",\"裤子\",\"高跟鞋\",\"袜子\"]\
            },																\
            yAxis: {},														\
            series: [{														\
                name: \'销量\',												\
                type: \'bar\',												\
                data: [5, 20, 36, 10, 10, 20]								\
            }]																\
        };																	\
        myChart.setOption(option);";
		wkeRunJS(pWkeWebkit->GetWebView(), js);
	}

	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}


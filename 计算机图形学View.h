// 计算机图形学View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__5DE45190_856C_4F6D_B30F_F4AB959FDD0F__INCLUDED_)
#define AFX_VIEW_H__5DE45190_856C_4F6D_B30F_F4AB959FDD0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "Matrix.h"
//#include "Matrix2.h"
#include <math.h>

typedef struct{ unsigned all;
				unsigned left,right,top,bottom;
}OutCode;

typedef struct{ 
	double x, y;
}DCPoint;

class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();
	CColorDialog CColor;
	int COLOR;  //颜色
	bool up;   //鼠弹起
	bool sym;  //覆盖标记
	int flag; //操作标记
	int xx1,xx2,yy1,yy2,xxx2,yyy2; //记录鼠标坐标
	int save[10000][3],count; 
	DCPoint a, b, c, d;
	int cc;
	int vpoint;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnUpdateDda(CCmdUI* pCmdUI);
	afx_msg void OnDda();
	afx_msg void OnCircle();
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void Onellipse();
	afx_msg void OnUpdateellipse(CCmdUI* pCmdUI);
	bool isinside(int,int);
	void ddaline (int,int,int,int,int);
	void midcircle (int,int,int,int);
	void midellispse (int,int,int,int,int);
	void draw (int,int,int,int,int);
	void draw_point (int, int, int);
	void seed_edge(int,int,int,int);
	void edge_scan();
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void Onsseed();
	afx_msg void OnUpdatesseed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateoedge(CCmdUI* pCmdUI);
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 计算机图形学View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__5DE45190_856C_4F6D_B30F_F4AB959FDD0F__INCLUDED_)

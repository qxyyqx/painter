// 计算机图形学View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "计算机图形学.h"

#include "计算机图形学Doc.h"
#include "计算机图形学View.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const double PI=3.1415926535897932384626;

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_s_seed, Onsseed)
	ON_UPDATE_COMMAND_UI(ID_s_seed, OnUpdatesseed)
	ON_UPDATE_COMMAND_UI(ID_o_edge, OnUpdateoedge)
	ON_COMMAND(ID_COLOR, OnColor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_DDA, OnUpdateDda)
	ON_COMMAND(ID_DDA, OnDda)
	ON_COMMAND(ID_CIRCLE, OnCircle)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, OnUpdateCircle)
	ON_COMMAND(ID_ellipse, Onellipse)
	ON_UPDATE_COMMAND_UI(ID_ellipse, OnUpdateellipse)

END_MESSAGE_MAP()

CMyView::CMyView()
{
	CColorDialog CColor( 1000,  0,  NULL );
	COLOR=CColor.GetColor( );
	flag=0;	
	up=false;
	sym=true;
	count=0;
	cc=0;
	vpoint = 500;
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

void CMyView::OnDda() 
{
	flag=0;

}

void CMyView::OnUpdateDda(CCmdUI* pCmdUI) 
{

	pCmdUI->SetCheck(flag==0);
	
}

void CMyView::OnCircle() 
{
	flag=3;
	
}

void CMyView::OnUpdateCircle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(flag==3);
}

void CMyView::Onellipse() 
{
	flag=4;
	
}

void CMyView::OnUpdateellipse(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(flag==4);
}
void CMyView::OnUpdateoedge(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(flag==5);
}
void CMyView::Onsseed() 
{
	flag=7;
}

void CMyView::OnUpdatesseed(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(flag==7);
}

void CMyView::ddaline (int x0,int y0,int x1,int y1,int color){
	double dx, dy, x, y, m;
	dx = x1 - x0;
	dy = y1 - y0;

	if (sym)
		count=0;

	if (dx == 0){
		for (int i = min(y0,y1), j = abs(y0-y1); j >=0; j-- )
			draw_point (x0, i+j, color);
	}
	else{
		if (dx < 0){
			int xBuf, yBuf;
			xBuf = x0; x0 = x1; x1 = xBuf;
			yBuf = y0; y0 = y1; y1 = yBuf;
			dx = -dx; dy = -dy;
		}

		if (dx >= (dy>0?dy:-dy)){
			m = dy / dx;
			y = y0;
			for (x = x0; x <= x1; x++){
				draw_point((int)x, (int)(y+0.5), color );
				y += m;
			}
		}
		else{
			m = dx / dy;
			if (m < 0)
				m = -m;
			x = x0;
			if (dy > 0){
				for (y = y0; y <= y1; y++){
					draw_point( (int)(x+0.5), (int)y, color);
					x += m;
				}
			}
			else{
				for (y = y0; y >= y1; y--){
				draw_point( (int)(x+0.5), (int)y, color);
					x += m;
				}
			}
		}
	}
}


void CMyView::draw_point (int x,int y,int color){
	CDC* pDC=GetDC();
	int cc=pDC->GetPixel(x,y),white=RGB(255,255,255);
	if (cc!=white&&sym){//暂时保存点信息,以备刷新时恢复
		save[count][0]=(int)(x+0.5);
		save[count][1]=(int)y;
		save[count][2]=cc;
		count++;
	}
	pDC->SetPixel( x, y, color);
	ReleaseDC(pDC);
}

void CMyView::draw (int x,int y,int xx,int yy,int c){
	CDC* pDC=GetDC();
	int cc,white=RGB(255,255,255);
	cc=pDC->GetPixel(x+xx,y+yy);
	if(cc!=white&&sym){ //暂时保存点信息,以备刷新时恢复
			save[count][0]=x+xx;
			save[count][1]=y+yy;
			save[count][2]=cc;
			count++;
	}
	pDC->SetPixel (x+xx,y+yy,c);

	cc=pDC->GetPixel(x+xx,-y+yy);
	if(cc!=white&&sym){
			save[count][0]=x+xx;
			save[count][1]=-y+yy;
			save[count][2]=cc;
			count++;
	}
	pDC->SetPixel (x+xx,-y+yy,c);

	cc=pDC->GetPixel(-x+xx,y+yy);
	if(cc!=white&&sym){
		save[count][0]=-x+xx;
		save[count][1]=y+yy;
		save[count][2]=cc;
		count++;
	}
	pDC->SetPixel (-x+xx,y+yy,c);

	cc=pDC->GetPixel(-x+xx,-y+yy);
	if(cc!=white&&sym){
		save[count][0]=-x+xx;
		save[count][1]=-y+yy;
		save[count][2]=cc;
		count++;
	}
	pDC->SetPixel (-x+xx,-y+yy,c);
	ReleaseDC(pDC);

}

void CMyView::midcircle (int xx, int yy ,int r,int color){
	int x=0,y=r;     
	float d;
	int add=0;//控制终止条件
	if (up)
		add=2;
	d=5.0/4-r;
	if(sym)
		count=0;
	if (!up){
		draw (x,y,xx,yy,color);
		draw (y,x,xx,yy,color);
	}
	while (y>x+add){
		if (d<=0)
			d+=2.0*x+3;
		else{
			d+=2.0*(x-y)+5;
			y--;
		}
		x++;
		draw (x,y,xx,yy,color);
		draw (y,x,xx,yy,color);

	}
}



void CMyView::midellispse (int xx,int yy, int r1,int r2 ,int color){
	int a=r1,b=r2,x,y,d,xp,yp,sa,sb;
	sa=a*a;
	sb=b*b;
	xp=(int)(0.5+(float)sa/sqrt((float)(sa+sb)));
	yp=(int)(0.5+(float)sb/sqrt((float)(sa+sb)));
	x=0;
	y=b;
	d=4*(sb-sa*b)+sa;
	
	int add=0;//控制终止条件
	if (up)
		add=2;
	if(sym)
		count=0;
	if (!up){
		draw (x,y,xx,yy,color);
	}
	while(x<=xp-add)
	{
		if(d<=0)
			d+=4*sb*(2*x+3);
		else
		{
			d+=4*sb*(2*x+3)-8*sa*(y-1);
			y--;
		}
		x++;
		draw (x,y,xx,yy,color);
	}
	x=a;
	y=0;
	d=4*(sa-a*sb)+sb;
	if (!up){
		draw (x,y,xx,yy,color);
	}
	while(y<yp-add)
	{
		if(d<=0)
			d+=4*sa*(2*y+3);
		else
		{
			d+=4*sa*(2*y+3)-8*sb*(x-1);
			x--;
		}
		y++;
		draw (x,y,xx,yy,color);

	}

}


void CMyView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	xx1=point.x;
	yy1=point.y;
	xx2=xx1;
	yy2=yy1;
	up=true;

	if (flag==7){
		int a=IDYES;
	
		if (!isinside(xx1,yy1))
			a=AfxMessageBox ("种子为外部点或填充区域较大,确认填充?",MB_YESNO);
		if (a==IDYES){
			CDC *pDC=GetDC();
			int oldcolor, newcolor=COLOR;
			oldcolor=pDC->GetPixel (xx1,yy1);
			seed_edge ( xx1, yy1,oldcolor,newcolor);
			ReleaseDC(pDC);
		}
	}


	CView::OnLButtonDown(nFlags, point);
}

void CMyView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	up=false;
	count=0;
	if (flag==3){
		int x=(xx1+xx2)/2;
		int	y=(yy1+yy2)/2;
		int	r=pow((xx1-xx2)*(xx1-xx2)+(yy1-yy2)*(yy1-yy2),0.5);
		int color=COLOR;
		sym=false;
		midcircle (xx1,yy1,r,color);
		sym=true;
	}
	else if (flag==4){
		int	r1= abs ( xx1-xx2 )/2,r2=abs (yy1-yy2)/2,xx=(xx1+xx2)/2,yy=(yy1+yy2)/2;	
		int	color=COLOR;
		sym=false;
		midellispse (xx,yy,r1,r2,color);
		sym=true;
	
	}

	CView::OnLButtonUp(nFlags, point);
}

void CMyView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(up){
		xxx2=xx2;
		xx2=point.x;
		yyy2=yy2;
		yy2=point.y;
		int color;
		if(flag==0){
			color=RGB(255,255,255);
			sym=false;
			ddaline (xx1,yy1,xxx2,yyy2,color);
			sym=true;
			CDC* pDC=GetDC();
			while (count>0){
				count--;
				pDC->SetPixel(save[count][0],save[count][1],save[count][2]);
			}
			color=COLOR;
			ddaline (xx1,yy1,xx2,yy2,color);

		}
			
		else if(flag==3){
			int	x=(xx1+xxx2)/2;
			int y=(yy1+yyy2)/2;
			int	r=pow((xx1-xxx2)*(xx1-xxx2)+(yy1-yyy2)*(yy1-yyy2),0.5);
			color=RGB(255,255,255);
			sym=false;
			midcircle (xx1,yy1,r,color);
			sym=true;
			CDC* pDC=GetDC();
			while (count>0){
				count--;
				pDC->SetPixel(save[count][0],save[count][1],save[count][2]);

			}
			ReleaseDC(pDC);	
			x=(xx1+xx2)/2;
			y=(yy1+yy2)/2;
			r=pow((xx1-xx2)*(xx1-xx2)+(yy1-yy2)*(yy1-yy2),0.5);
			color=COLOR;
			midcircle (xx1,yy1,r,color);
		}
		else if (flag==4) { 
			int r1= abs ( xx1-xxx2 )/2,r2=abs (yy1-yyy2)/2,xx=(xx1+xxx2)/2,yy=(yy1+yyy2)/2;
			color=RGB(255,255,255);
			sym=false;
			midellispse (xx,yy,r1,r2,color);
			sym=true;
			CDC* pDC=GetDC();
			while (count>0){
				count--;
				pDC->SetPixel(save[count][0],save[count][1],save[count][2]);

			}
			ReleaseDC(pDC);	
			r1= abs ( xx1-xx2 )/2,r2=abs (yy1-yy2)/2,xx=(xx1+xx2)/2,yy=(yy1+yy2)/2;
			color=COLOR;
			midellispse (xx,yy,r1,r2,color);
		}
		else if (flag==10){

			
		}
		
	}

	CView::OnMouseMove(nFlags, point);
}


void CMyView::seed_edge (int x,int y, int oldcolor,int newcolor){ //扫描线种子填充算法
	int ss[2][3],t,i;  
	CDC *pDC=GetDC();

	i=x;
	while (pDC->GetPixel(i,y)==oldcolor){
		pDC->SetPixel(i,y,newcolor);
		i++;
	}
	ss[0][0]=i-1;
	ss[1][0]=i-1;

	i=x-1;
	while (pDC->GetPixel(i,y)==oldcolor){
		pDC->SetPixel(i,y,newcolor);
		i--;
	}
	ss[0][1]=i+1;
	ss[0][2]=y+1;
	ss[1][1]=i+1;
	ss[1][2]=y-1;

	while (pDC->GetPixel(int (ss[0][1]+ss[0][0])/2,ss[0][2])==oldcolor){
		i=int (ss[0][1]+ss[0][0])/2;
		while (pDC->GetPixel(i,ss[0][2])==oldcolor){
			pDC->SetPixel(i,ss[0][2],newcolor);
			i++;
		}
		t=i-1;
		i=int (ss[0][1]+ss[0][0])/2-1;
		while (pDC->GetPixel(i,ss[0][2])==oldcolor){
			pDC->SetPixel(i,ss[0][2],newcolor);
			i--;
		}
		ss[0][0]=t;
		ss[0][1]=i+1;
		ss[0][2]+=1;
		::Sleep(3);
	}
	while (pDC->GetPixel(int (ss[1][1]+ss[1][0])/2,ss[1][2])==oldcolor){
		i=int (ss[1][1]+ss[1][0])/2;
		while (pDC->GetPixel(i,ss[1][2])==oldcolor){
			pDC->SetPixel(i,ss[1][2],newcolor);
			i++;
		}
		t=i-1;
		i=int (ss[1][1]+ss[1][0])/2-1;
		while (pDC->GetPixel(i,ss[1][2])==oldcolor){
			pDC->SetPixel(i,ss[1][2],newcolor);
			i--;
		}
		ss[1][0]=t;
		ss[1][1]=i+1;
		ss[1][2]-=1;
		::Sleep(3);
	}
	ReleaseDC(pDC);
}

void CMyView::edge_scan(){
	typedef struct edge {           //建立边的分类表
		int bottom,x;
		float deltax;
		edge * nextedge;
	};
	edge *list[501],*temp;
	edge *a=new edge,*b=new edge,*c=new edge,*d=new edge;
	(*a).bottom=350, (*a).x=400, (*a).deltax=1.0;
	(*b).bottom=100, (*b).x=600, (*b).deltax=0.0;
	(*c).bottom=200, (*c).x=500, (*c).deltax=3.0;
	(*d).bottom=100, (*d).x=500, (*d).deltax=-(2.0/7.0);
	for(int r=0;r<551;r++)
		list[r]=NULL;
	list[550]=a;
	(*a).nextedge=b;
	(*a).nextedge=NULL;
	list[450]=c;
	(*c).nextedge=d;
	(*d).nextedge=NULL;
	float t=0.0;
	int y=550;
	int color=COLOR;
	while(y>450){
		ddaline((a->x),y,(b->x),y,color);
		(a->x)=(a->x)-(a->deltax);
		(b->x)=(b->x)-(b->deltax);
		y--;
		::Sleep(5);
	}
	while(y>350){
		ddaline((a->x),y,(c->x),y,color);
		(a->x)=(a->x)-(a->deltax);
		(c->x)=(c->x)-(c->deltax);
		ddaline((b->x),y,(d->x),y,color);
		t+=d->deltax;
		(b->x)=(b->x)-(b->deltax);
		(d->x)=(d->x)-int(t);
		t=t-int (t);
		y--;
		::Sleep(5);
	}
	while (y>=100){
		ddaline((b->x),y,(d->x),y,color);
		t+=d->deltax;
		(b->x)=(b->x)-(b->deltax);
		(d->x)=(d->x)-int(t);
		t=t-int (t);
		y--;
		::Sleep(5);
	}
}

const int vpoint=150;
bool CMyView::isinside (int x,int y){ //判断是不是为内部点
	int i,j,a=1,color;
	CDC* pDC=GetDC();
	color=pDC->GetPixel(x,y);
	for (i=x+1;i<x+vpoint;i++)
		if (color!=pDC->GetPixel(i,y))
			break;
	if (i==x+vpoint){
		ReleaseDC (pDC);
		return false;
	}

	for (i=y+1;i<y+vpoint;i++)
		if (color!=pDC->GetPixel(x,i))
			break;
	if (i==y+vpoint){
		ReleaseDC (pDC);
		return false;
	}
	
	for (i=x+1;i>x-vpoint;i--)
		if (color!=pDC->GetPixel(i,y))
			break;
	if (i==x-vpoint){
		ReleaseDC (pDC);
		return false;
	}

	for (i=y+1;i>y-vpoint;i--)
		if (color!=pDC->GetPixel(x,i))
			break;
	if (i==y-vpoint){
		ReleaseDC (pDC);
		return false;
	}
	ReleaseDC (pDC);
	return true;	

}

void CMyView::OnColor() //颜色对话框
{
	CColor.DoModal();
	COLOR=CColor.GetColor( );
}

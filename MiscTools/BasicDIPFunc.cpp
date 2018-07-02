#include "StdAfx.h"
#include "BasicDIPFunc.h"
#include <atlimage.h>

CBasicDIPFunc::CBasicDIPFunc(void)
{
}


CBasicDIPFunc::~CBasicDIPFunc(void)
{
}


int CBasicDIPFunc::SnapImgWnd(CWnd * pWnd, LPCTSTR pImgFileName)
{
	CRect rectClient ;
	pWnd->GetClientRect(rectClient) ;
	CDC *pWndDC = pWnd->GetDC() ;
	CDC memDC ;
	memDC.CreateCompatibleDC(pWndDC) ;
	CBitmap	memBMP ;
	memBMP.CreateCompatibleBitmap(pWndDC, rectClient.Width(), rectClient.Height()) ;
	CBitmap	*pOldBMP = memDC.SelectObject(&memBMP) ;
	memDC.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), pWndDC, 0, 0, SRCCOPY) ;
	CImage ImgObj ;
	ImgObj.Attach(memBMP) ;
	ImgObj.Save(pImgFileName) ;
	ImgObj.Detach() ;
	memDC.SelectObject(pOldBMP) ;
	memDC.DeleteDC() ;

	pWnd->ReleaseDC(pWndDC) ;
	////------->
 //   CBitmap*  m_pBitmap;                                                     // �������Ա
 //   CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // ��ý�ͼ���ڵ�ָ�룬Ĭ��Ϊ�����ڣ����Ը���Ϊ�����Ĵ��ڡ�
 //   CPaintDC   dc(pMainFrame); 
 //    
 //   m_pBitmap=new   CBitmap;   
 //   m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   
 //
 //   CDC   memDC;  
 //   memDC.CreateCompatibleDC(&dc); 
 //   CBitmap memBitmap, *oldmemBitmap;                                        // ��������Ļ���ݵ�bitmap
 //    
 //   memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
 //    
 //   oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC
 //   memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,left, top, SRCCOPY);  // ����߶ȿ��
 //   BITMAP bmp;
 //   memBitmap.GetBitmap(&bmp);                                               // ���λͼ��Ϣ 
 //    
 //   FILE *fp = fopen(name, "w+b");
 //    
 //   BITMAPINFOHEADER bih = {0};                                              // λͼ��Ϣͷ
 //   bih.biBitCount = bmp.bmBitsPixel;                                        // ÿ�������ֽڴ�С
 //   bih.biCompression = BI_RGB;
 //   bih.biHeight = bmp.bmHeight;                                             // �߶�
 //   bih.biPlanes = 1;
 //   bih.biSize = sizeof(BITMAPINFOHEADER);
 //   bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // ͼ�����ݴ�С
 //   bih.biWidth = bmp.bmWidth;                                               // ���
 //    
 //   BITMAPFILEHEADER bfh = {0};                                              // λͼ�ļ�ͷ
 //   bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // ��λͼ���ݵ�ƫ����
 //   bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // �ļ��ܵĴ�С
 //   bfh.bfType = (WORD)0x4d42;
 //    
 //   fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //д��λͼ�ļ�ͷ
 //    
 //   fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                           //д��λͼ��Ϣͷ
 //    
 //   byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                    //�����ڴ汣��λͼ����
 //    
 //   GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
 //   (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                    //��ȡλͼ����
 //    
 //   fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                       //д��λͼ����
 //   delete [] p;    
 //   fclose(fp);
 //   memDC.SelectObject(oldmemBitmap);
 //   memDC.DeleteDC();

	return 0;
}

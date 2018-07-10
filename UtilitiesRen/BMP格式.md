# BMP图像格式

[TOC]

## 1.数据结构

### 1.1. BITMAPINFO Structure

​	BITMAPINFO结构体中定义了Windows设备无关位图（DIB）中的维度和颜色信息。

```C++
typedef struct tagBITMAPINFO {
   BITMAPINFOHEADER bmiHeader;
   RGBQUAD bmiColors[1];
} BITMAPINFO;
```

#### a. 参数

- bmiHeader

   定义了一个BITMAPINFOHEADER 结构体，该结构体包含了Windows设备无关位图（DIB）中的维度和颜色格式信息。

- bmiColors

   指定了一个RGBQUAD或DWORD类型的数组来定义bitmap中的颜色。虽然该参数定义为 RGBQUAD bmiColors[1]，数组的大小指定为1，但实际上，变量bmiColors可以存储一个数组的地址，如果分配给其足够的地址空间，可以访问更多的地址空间。

### 1.2. BITMAPINFOHEADER Structure

​	BITMAPINFOHEADER结构包含：设备无关位图（DIB）的尺寸和颜色格式的信息。

```C++
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER;
```

#### a. 参数

+ biSize

  指定结构所需的字节数。则该值不包括颜色表的大小或颜色掩码的大小，如果这些值附加到结构的末尾。

+ biWidth

  指定位图的宽度（以像素为单位）。

+ biHeight

  指定位图的高度（以像素为单位）。

  对于未压缩的RGB位图，如果biHeight为正，则位图是自底向上的DIB，其原点位于左下角。如果biHeight为负数，则位图是自上而下的DIB，其原点位于左上角。
  对于YUV位图，无论biHeight的符号如何，位图始终是自上而下的。解码器应提供具有正向biHeight的YUV格式，但为了向后兼容，它们应接受具有正或负biHeight的YUV格式。
  对于压缩格式，无论图像方向如何，biHeight都必须为正。

+ biPlanes 

  指定目标设备的平面数。该值必须设置为1

+ biBitCount

  指定每像素的位数（bpp）。对于未压缩格式，此值是每个像素的平均位数。对于压缩格式，此值是解码图像后未压缩图像的隐含位深度。

+ biCompression

  对于压缩视频和YUV格式，此成员是FOURCC代码，以little-endian顺序指定为DWORD。例如，YUYV视频具有FOURCC'VYUY'或0x56595559。有关更多信息，请参阅FOURCC代码。

  对于未压缩的RGB格式，可以使用以下值：

  ​	BI_RGB未压缩的RGB。

  ​	BI_BITFIELDS带有彩色遮罩的未压缩RGB。适用于16-bpp和32-bpp位图。

  对于16-bpp位图，如果biCompression等于BI_RGB，则格式始终为RGB 555.如果biCompression等于BI_BITFIELDS，则格式为RGB 555或RGB 565.使用AM_MEDIA_TYPE结构中的子类型GUID来确定特定的RGB类型。

+ biSizeImage

  指定图像的大小（以字节为单位）。双字对齐，即4字节。对于未压缩的RGB位图，可以将其设置为0。

+ biXPelsPerMeter

  指定位图的目标设备的水平分辨率（以每米像素为单位）。

+ biYPelsPerMeter

  指定位图的目标设备的垂直分辨率（以每米像素为单位）。

+ biClrUsed

  指定颜色表中位图实际使用的颜色索引数。有关更多信息，请参阅备注。

+ biClrImportant

  指定对于显示位图而言重要的颜色索引的数量。如果此值为零，则所有颜色都很重要。

### 1.3 RGBQUAD structure

### 1.4 BITMAP structure

​	BITMAP 结构体定义了高、宽、颜色格式、以及逻辑bitmap的bit值。

```C++
typedef struct tagBITMAP {  /* bm */ 
   int bmType; 
   int bmWidth; 
   int bmHeight; 
   int bmWidthBytes; 
   BYTE bmPlanes; 
   BYTE bmBitsPixel; 
   LPVOID bmBits; 
} BITMAP;
```

#### a. 参数

- bmType  

  ​	指定Bitmap类型，对于逻辑Bitmap，该成员始终为0

- bmWidth

  ​	指定Bitmap像素宽度，该值必须大于0

- bmHeight  

  ​	指定Bitmap光栅行数，即像素高度，该值必须大于0

- bmWidthBytes  

  指定每个光栅行的字节数。该值必须是一个偶数，因为GDI假设组成Bitmap的Bit值是一个整数（2个字节）数组。 换句话说，bmWidthBytes * 8必须是16的下一个倍数，大于或等于bmWidth成员乘以bmBitsPixel成员时获得的值。

- bmPlanes  

  指定bitmap的颜色平面。

- bmBitsPixel  

  指定每个平面上定义一个像素的相邻的颜色位的数目。

- bmBits  

  指向Bitmap的bit值的地址，该值是一个long型的，指向单字节数组的指针。

#### b.注意

目前使用的位图格式是单色和彩色。 单色位图使用1位1平面格式。 每次扫描是16位的倍数。

对于高度为n的单色位图，扫描的组织如下：

扫描0

扫描1

...

扫描n-2

扫描n-1

​	单色设备上的像素为黑色或白色。 如果位图中的相应位为1，则打开像素（白色）。 如果位图中的相应位为0，则关闭像素（黑色）。

​	所有支持bitmap的设备在CDC::GetDeviceCaps函数中的RASTERCAPS索引中都有RC_BITBLT 位。

​	每个设备都有自己独特的颜色格式。 要将位图从一个设备传输到另一个设备，请使用GetDIBits和SetDIBits Windows函数。

## 2.函数

### 2.1. GetObject function

​	该函数接收特定图形对象的信息。

```C++
int GetObject(
  _In_  HGDIOBJ hgdiobj,
  _In_  int     cbBuffer,
  _Out_ LPVOID  lpvObject
);
```

#### a. 参数

- hgdiobj [in]  

  感兴趣图形对象的句柄，可以是：a logical bitmap, a brush, a font, a palette, a pen, or  由CreateDIBSection函数创建的一个device  independent bitmap（DIB）。 

- cbBuffer [in]  

   写入Buffer中的字节数

- lpvObject [out]  

   接收图形对象信息的buffer指针。对于不同的图形对象，将有对应的信息写入缓冲。如当HGDIOBJ为HBITMAP，写入buffer的数据为BITMAP，当HGDIOBJ为CreateDIBSection函数创建的HBITMAP，写入缓冲的数据由cbBuffer决定，当cbBuffer为 sizeof (DIBSECTION),或sizeof (BITMAP).，分别写入DIBSECTION，以及BITMAP。

#### b.返回值

​	如果函数成功，并且lpvObject是有效指针，则返回值是存储在缓冲区中的字节数。 

​	如果lpvObject参数为NULL，则函数返回值是写入缓冲区所需的字节数。 lpvObject的地址必须在4字节边界上; 否则，GetObject失败。

​	如果函数失败，则返回值为零。

### 2.2 GetDIBits function

​	GetDIBits函数检索指定的兼容位图的位，并使用指定的格式将它们作为DIB复制到缓冲区中。

```C++
int GetDIBits(
  _In_    HDC          hdc,
  _In_    HBITMAP      hbmp,
  _In_    UINT         uStartScan,
  _In_    UINT         cScanLines,
  _Out_   LPVOID       lpvBits,
  _Inout_ LPBITMAPINFO lpbi,
  _In_    UINT         uUsage
);
```

#### a.参数

+ hdc [in]

  设备上下文的句柄。

+ hbmp [in]

  位图的句柄。 这必须是兼容的位图（DDB）。

+ uStartScan [in]

  要检索的第一条扫描线。

+ cScanLines [in]

  要检索的扫描行数。

+ lpvBits [out]

  指向缓冲区以指示接收位图数据的指针。 如果此参数为NULL，则该函数将位图的维度和格式传递给lpbi参数指向的BITMAPINFO结构。

+ lpbi [in，out]

  指向BITMAPINFO结构的指针，指定DIB数据的所需格式。

+ uUsage [in]

  BITMAPINFO结构的成员bmiColors的格式。 它必须是以下值之一。

  DIB_PAL_COLORS：颜色表应包含当前逻辑调色板中的16位索引数组。

  DIB_RGB_COLORS：颜色表应直接包含红色，绿色，蓝色（RGB）值。

## 3.  示例

​	许多应用程序将图像永久存储为文件。例如，绘图应用程序存储图片，电子表格应用程序存储图表，CAD应用程序存储图纸等。

​	如果您正在编写将位图图像存储在文件中的应用程序，则应使用位图文件格式。 要以此格式存储位图，必须使用BITMAPINFOHEADER，BITMAPV4HEADER或BITMAPV5HEADER结构以及RGBQUAD结构数组以及调色板索引数组。

​	以下示例代码定义了一个函数，该函数使用BITMAPINFO结构并为BITMAPINFOHEADER结构中的成员分配内存并对其进行初始化。 请注意，BITMAPINFO结构不能与BITMAPV4HEADER或BITMAPV5HEADER结构一起使用。

```C++
PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 

    // Retrieve the bitmap color format, width, and height.  
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
        errhandler("GetObject", hwnd); 

    // Convert the color format to a count of bits.  
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 

    // Allocate memory for the BITMAPINFO structure. (This structure  
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
    // data structures.)  

     if (cClrBits < 24) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (1<< cClrBits)); 

     // There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

     else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 

    // Initialize the fields in the BITMAPINFO structure.  

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

    // If the bitmap is not compressed, set the BI_RGB flag.  
    pbmi->bmiHeader.biCompression = BI_RGB; 

    // Compute the number of bytes in the array of color  
    // indices and store the result in biSizeImage.  
    // The width must be DWORD aligned unless the bitmap is RLE 
    // compressed. 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the  
    // device colors are important.  
     pbmi->bmiHeader.biClrImportant = 0; 
     return pbmi; 
 }
```

以下示例代码定义了一个函数，该函数初始化其余结构，检索调色板索引数组，打开文件，复制数据以及关闭文件。

```C++
void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC)
{
	HANDLE hFile;                 // file handle  
	BITMAPFILEHEADER bmFileHeader;       // bitmap file-header  
	PBITMAPINFOHEADER pbmInfoHeader;     // bitmap info-header  
	
	LPBYTE lpBits;              // 指向BMP图像像素数据的指针
	DWORD dwTmp;

	// 为像素指针分配内存
	pbmInfoHeader = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbmInfoHeader->biSizeImage);
	if (!lpBits)
		errhandler("GlobalAlloc", hwnd);

	// Retrieve the color table (RGBQUAD array) and the bits  
	// (array of palette indices) from the DIB.  
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbmInfoHeader->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		errhandler("GetDIBits", hwnd);
	}

	// 创建bmp文件
	hFile = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		errhandler("CreateFile", hwnd);
	bmFileHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
								// Compute the size of the entire file.  
	bmFileHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbmInfoHeader->biSize + pbmInfoHeader->biClrUsed
		* sizeof(RGBQUAD) + pbmInfoHeader->biSizeImage);
	bmFileHeader.bfReserved1 = 0;
	bmFileHeader.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	bmFileHeader.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbmInfoHeader->biSize + pbmInfoHeader->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	if (!WriteFile(hFile, (LPVOID)&bmFileHeader, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		errhandler("WriteFile", hwnd);
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hFile, (LPVOID)pbmInfoHeader, sizeof(BITMAPINFOHEADER)
		+ pbmInfoHeader->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		errhandler("WriteFile", hwnd);

	// Copy the array of color indices into the .BMP file.  
	if (!WriteFile(hFile, (LPSTR)lpBits, (int)(pbmInfoHeader->biSizeImage), (LPDWORD)&dwTmp, NULL))
		errhandler("WriteFile", hwnd);

	// Close the .BMP file.  
	if (!CloseHandle(hFile))
		errhandler("CloseHandle", hwnd);

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}
```


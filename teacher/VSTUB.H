
#ifndef __VSTUB_H_INCLUDED__
#define __VSTUB_H_INCLUDED__

#include <windows.h>
#include <strstream>

namespace std{

#ifdef __DEFINE_VSTUB_CONSTS__
#undef __DEFINE_VSTUB_CONSTS__
#define DECLAR(t,n,v) extern const t vstub##n = v
#else
#define DECLAR(t,n,v) extern const t vstub##n
#endif

DECLAR (int, Height, 400);
DECLAR (int, WidthC, 400);
DECLAR (int, WidthG, 400);
DECLAR (int, CellH, 13);
DECLAR (COLORREF, TextColor, RGB(0,192,0));
DECLAR (COLORREF, GraphColor, RGB(255,255,0));

DECLAR (int, HeightC, vstubHeight);
DECLAR (int, HeightG, vstubHeight);
DECLAR (int, Width, vstubWidthC+vstubWidthG);

#undef DECLAR

class vcstreambuf: public strstreambuf
{
  public:
    virtual int sync ();
};

class vcstreambuf;
extern vcstreambuf vcsb;
extern ostream vc;

int main (void);

int vgetchar (void);

void drawgrid (void);
void setcolor (unsigned char r, unsigned char g, unsigned char b);
void putpixel (int x, int y);
void drawpixel (int x, int y);
void putline (int x1, int y1, int x2, int y2);
void drawline (int x1, int y1, int x2, int y2);
void putarc (int x, int y, int radius, float StartAngle, float SweepAngle);
void drawarc (int x, int y, int radius, float StartAngle, float SweepAngle);

void TFlush(void);
void GFlush(void);

#define D2R(x) ((float)(x*3.141592654/180.0))
#define R2D(x) ((float)(x*180.0/3.141592654))

}
#endif

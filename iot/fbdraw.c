#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

#define FBDEVICE "/dev/fb0"
typedef unsigned char ubyte;

unsigned short makepixel(unsigned char r, unsigned char g, unsigned char b)
{
    return (unsigned short)(((r>>3)<<11)|((g>>2)<<5)|(b>>3));
}

static int DrawPoint(int fd, int x, int y, unsigned short color)
{
    struct fb_var_screeninfo vinfo;

    ioctl(fd,FBIOGET_VSCREENINFO,&vinfo);

    int offset = (x + y*vinfo.xres)*2;
    lseek(fd, offset, SEEK_SET);
    write(fd,&color,2);
    return 0;
}

static int DrawCircle(int fd, int center_x, int center_y, int radius, unsigned short color)
{
    int x = radius, y =0;
    int radiusError = 1-x;

    while(x>=y)
    {
        DrawPoint(fd, x+center_x,y+center_y,color);
        DrawPoint(fd, y+center_x,x+center_y,color);
        DrawPoint(fd, -x+center_x,y+center_y,color);
        DrawPoint(fd, -y+center_x,x+center_y,color);
        DrawPoint(fd, -x+center_x,-y+center_y,color);
        DrawPoint(fd, -y+center_x,-x+center_y,color);
        DrawPoint(fd, x+center_x,-y+center_y,color);
        DrawPoint(fd, y+center_x,-x+center_y,color);

        y++;
        
        if(radiusError<0)
            radiusError +=2*y+1;
        else
        {
            x--;
            radiusError +=2*(y-x+1);
        }
    }
}


static int DrawFace(int fd, int start_x, int start_y, int end_x, int end_y, unsigned short color)
{
    int x,y,offset;
    struct fb_var_screeninfo vinfo;

    ioctl(fd,FBIOGET_VSCREENINFO,&vinfo);

    
    if(end_x==0) end_x=vinfo.xres;
    if(end_y==0) end_y=vinfo.yres;

    for(x=start_x;x<end_x;x++)
    {
        for(y=start_y;y<end_y;y++)
        {
            offset = (x + y*vinfo.xres)*2;
            lseek(fd,offset,SEEK_SET);
            write(fd,&color,2);
        }
    }
    return 0;
}

static int DrawFaceMMAP(int fd, int start_x, int start_y, int end_x, int end_y, unsigned short color)
{
    int x,y,offset;
    struct fb_var_screeninfo vinfo;
    unsigned short *pfb;

    ioctl(fd,FBIOGET_VSCREENINFO,&vinfo);

    
    if(end_x==0) end_x=vinfo.xres;
    if(end_y==0) end_y=vinfo.yres;
    
    pfb=(unsigned short *)mmap(0,vinfo.xres*vinfo.yres*2,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    for(x=start_x;x<end_x;x++)
    {
        for(y=start_y;y<end_y;y++)
        {
            *(pfb+x+y*vinfo.xres)=color;
        }
    }
    munmap(pfb,vinfo.xres*vinfo.yres*2);
    return 0;
}

int main(int argc, char **argv)
{
    int fbfd,status,offet;
    unsigned short pixel;

    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    fbfd = open(FBDEVICE,O_RDWR);
    printf("The framebuffer device was opened successfully.\n");

    ioctl(fbfd,FBIOGET_FSCREENINFO, &finfo);

    ioctl(fbfd,FBIOGET_VSCREENINFO, &vinfo);

    printf("Resolution : %dx%d, %dbpp\n",vinfo.xres,vinfo.yres,vinfo.bits_per_pixel);
    printf("Virtual Resolution : %dx%d\n", vinfo.xres_virtual, vinfo.yres_virtual);
    printf("Length of frame buffer memory : %d\n", finfo.smem_len);

    //vinfo.xres=800;
    //vinfo.yres=600;
    vinfo.bits_per_pixel = 16;

    ioctl(fbfd,FBIOPUT_VSCREENINFO,&vinfo);
    
    printf("Resolution : %dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    DrawPoint(fbfd,250,250,makepixel(255,0,0));
    DrawPoint(fbfd,100,100,makepixel(0,255,0));
    DrawPoint(fbfd, 150,150,makepixel(0,0,255));
    
    //DrawCircle(fbfd,200,200,100,makepixel(250,0,255));
    //DrawFace(fbfd,0,0,0,0,makepixel(255,255,0));
    DrawFaceMMAP(fbfd,0,0,0,0,makepixel(0,0,255));
    close(fbfd);

    return 0;
    
}

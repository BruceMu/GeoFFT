#include "vol_math_ImageVolume.h"
#include "vol_math_filter_Interface.h"
#include "vol_math_RawImage.h"
int main(){
    int wid = 281,hei=481,dep =301;
    int len = wid*hei*dep;
    RawImage rawtest;
    unsigned char * indata = new unsigned char[len];
  //  unsigned char * outdata = new unsigned char[len];
    rawtest.readImage(indata,"/home/mu/mig.raw",len*sizeof(unsigned char));
    ImageVolume * src = new ImageVolume(wid,hei,dep,1,indata);
    ImageVolume * ret = new ImageVolume(wid,hei,dep,1,true);
    lowPassI p(100);
    dolowPassI(src,ret,p);
    delete [] indata;
    delete src;
    rawtest.writeImagesesmicarray(ret->Data,wid,hei,dep);
    delete ret;

}
/*
int main()
{
    testFftinterface();
    return 0;
}
*/

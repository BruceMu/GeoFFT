#include "vol_math_RawImage.h"
#include <cassert>

//#include"vol_math_Raw3D_Independt.h"
/*
RawImage is to change the all the three data types to double or float
*/
//=====================================================================================================
char* double2char(float *buf, long length)
{
	int i=0;
	char *imgf=new char[length];
	while(i < length)
	{
		imgf[i]= (char)buf[i++];
	}
	return imgf;
}

RawImage::RawImage(int length,int height,int width)
{
	this->height=height;
	this->length=length;
	this->width=width;
	int length1=this->getlength();
	this->buf=new PIXTYPE[length1];
}
RawImage::RawImage()
{
	this->height=0;
	this->length=0;
	this->width=0;
	this->buf=NULL;

}
void RawImage::readImage(unsigned char * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	fseek(op,281*481*1300L,SEEK_SET);
	fread(buf,sizeof(unsigned char),size,op);

	fclose(op);
	printf("read is ok\n");
}
void RawImage::readImage2(float * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	fseek(op,281*481*500L,SEEK_SET);
	fread(buf,sizeof(float),size,op);

	fclose(op);
	printf("read is ok\n");
}
void RawImage::readStream(short* buf,char const *filename,int size)
{
	int lx=0,ly=0,lz=0;
	ifstream file;
	file.open(filename, ios::out | ios::app | ios::binary);
	if (!file.is_open()) {
		cout<< "The file open failed, Please check it and try again"<< endl;
		exit(0);
	}
	file.read(reinterpret_cast<char *>(&lx),sizeof(int));
	file.read(reinterpret_cast<char *>(&ly),sizeof(int));
	file.read(reinterpret_cast<char *>(&lz),sizeof(int));
	//cout<<sizeof(int)<<endl;
	//cout<<sizeof(short)<<endl;
	//cout<<"lx="<<lx<<",ly="<<ly<<",lz="<<lz<<endl;
	//file.seekg(24L+512*512*345*sizeof(short),ios::beg);//+512*512*345*sizeof(short)
	file.read((char *)buf,size);
	file.close();


}
void RawImage::readImagesi(short  * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	fseek(op,24L+43253760L,SEEK_SET);
	fread((char *)buf,sizeof(signed int ),size,op);

	fclose(op);
	printf("read is ok\n");
}
void RawImage::writeImagecolon(Raw &destImg)
{
	FILE *p=fopen("F:\\3Dlevel.raw","wb");
	//char* data = double2char(destImg.getdata(), destImg.size());
	PIXTYPE *data=destImg.getdata();
	//for (int i=0;i<destImg.getXsize()*destImg.getYsize()*destImg.getZsize();i++)
	//{

	//	if (data[i]<1)
	//	{
	//		data[i]=data[i];
	//	}
	//	else data[i]=0;

	//}
	for (int i=0;i<destImg.getZsize();i++)
	{
		for (int j=0;j<destImg.getYsize();j++)
		{
			for (int k=0;k<destImg.getXsize();k++)
			{
				PIXTYPE *val=&data[i*destImg.getXsize()*destImg.getYsize()+j*destImg.getXsize()+k];
				if(k<451 &&k> 45 && j>162 &&j <391)
				{
					if (*val>1)
					{
						*val=0;

					}
					else *val=100;
				}
				else *val=0;
			}
		}
	}
	fwrite(data, sizeof(float), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
void RawImage::writeImage(Raw &destImg)
{
	FILE *p=fopen("F:\\3Dlevel.raw","wb");
	PIXTYPE *data=(PIXTYPE *)destImg.getdata();
	fwrite(data, sizeof(PIXTYPE), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
void RawImage::writeImagesesmic(Raw &destImg)
{
	FILE *p;
	if((p=fopen("/home/mutest219.raw","wb"))==NULL)
	{
		printf("cant open the file");
		exit(0);
	}

	PIXTYPE *data=(PIXTYPE *)destImg.getdata();

	fwrite(data, sizeof(PIXTYPE), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
void RawImage::writeImagesesmicarray(void * src, int l ,int m, int n)
{
	FILE *p;
	if((p=fopen("/home/mu/test301_100.raw","wb"))==NULL)  //"ab+"append
	{
		printf("cant open the file");
		exit(0);
	}
	//= new unsigned char [l *m*n];
	//unsigned char *  data =(unsigned char *) src;
	fwrite(src, sizeof(unsigned char), l*m*n, p);
	fclose(p);
	fflush(stdout);

	//delete[] data;
	printf("write is ok");
}
float* RawImage::buf2float(unsigned char *buf)
{
	unsigned char *p;
	p=buf;
	int i=0;
	long length=this->getlength();
	float *imgf=new float[length];
	while(p)
	{
		imgf[i]= (float)p[i] ;
		imgf+=i;
		p++;i++;
	}
	return imgf;
}

RawImage::~RawImage(void)
{
	delete[] buf;
}


void RawImage::readImagerecursive( unsigned char * buf,char const *file ,int l,int m,int i )
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	fseek(op,l*m*i*3L,SEEK_SET);
	fread(buf,sizeof(unsigned char),l*m*3,op);

	fclose(op);
	printf("read is ok\n");
}

void RawImage:: writeImageSesmicRecursive(void * src, int l ,int m, int n)
{

	FILE *p;
	if((p=fopen("F:\\sesmic.raw","a+"))==NULL)  //"ab+"append
	{
		printf("cant open the file");
		exit(0);
	}
	//= new unsigned char [l *m*n];
	//unsigned char *  data =(unsigned char *) src;
	fwrite(src, sizeof(unsigned char), l*m*n, p);
	fclose(p);
	fflush(stdout);

	//delete[] data;
	printf("write is ok");
}

//=====================================================================================================
Raw::Raw(ImageVolume &src)
{
	this->xsize=src.Width;
	this->ysize=src.Height;
	this->zsize=src.Depth;
	this->data=new PIXTYPE[size()];
	memcpy(this->data,(PIXTYPE*)src.Data,sizeof(PIXTYPE)*size());

}
Raw::Raw(void)
{
	xsize=0;
	ysize=0;
	zsize=0;
	is_shared = false;
	data=NULL;
}
Raw::Raw(int xsize,int ysize,int zsize,PIXTYPE *y,bool share)
{
	//float i=0.0f;
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	this->is_shared = share;
	//data=new PIXTYPE[size()];
		if (is_shared == true) {
		this->data = y;
	} else
	{
		this->data=new PIXTYPE[size()];
		memcpy(this->data,y,sizeof(PIXTYPE)*size());
	}
}
Raw::Raw(int xsize,int ysize,int zsize)
{
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	//this->is_shared = _is_shared;
	this->data=new PIXTYPE[size()];
}

Raw::Raw(const Raw & src, bool _is_shared)
{
	this->xsize=src.xsize;
	this->ysize=src.ysize;
	this->zsize=src.zsize;
	this->is_shared = _is_shared;

	if (this->is_shared == true) {
		this->data = src.data;
	} else {
		this->data=new PIXTYPE[size()];
		memcpy(this->data,src.data,sizeof(PIXTYPE)*size());
	}
}

Raw::~Raw(void)
{
	if(this->is_shared == false && this->data!=NULL) {
		delete [] this->data;
		data=NULL;
	}
}

Raw& Raw::set_shared(bool _is_shared)
{
	this->is_shared = _is_shared;
	return *this;
}

void Raw::sizer(int ixsize, int iysize,int izsize) {
	if(data!=NULL)
		delete [] this->data;
	data=NULL;
	this->data = new PIXTYPE[ixsize*iysize*izsize];	// & allocate memory.
	xsize = ixsize;				// set new RawImage size,
	ysize = iysize;
	zsize=izsize;
}

void Raw::sizer(Raw* src) {
	int ix, iy,iz;

	ix = src->getXsize();
	iy = src->getYsize();
	iz = src->getZsize();
	sizer(ix,iy,iz);
}

int Raw::wipecopy(Raw* src) {
	int out=1;
	int i,imax;

	if(getYsize() != src->getYsize() || getXsize()!=src->getXsize()) { // resize to fit 'src'.
		sizer(src);
		out=0;
	}
	imax = getXsize()*getYsize();
	for(i=0; i<imax; i++) {
		putXYZ(i,src->getXYZ(i));
	}

	return(out);
}

Raw operator /(const PIXTYPE val, const Raw &volume)
{
	Raw res(volume);

	for (int i = 0; i < res.size(); i ++ )
	{
		res.data[i]= val/volume.data[i];
	}


	return res.set_shared(true);
}

//=====================================================================================================
RawArray::RawArray(int rawNum,Raw *src)
{
	this->rawNum=rawNum;
	this->z=src;
}
RawArray::RawArray(void)
{
	z=0;
}
RawArray::~RawArray(void)
{
	if(this->z!=NULL)
		delete [] this->z;
	z=NULL;
	//cout<<"RawArray is deconstruct"<<endl;
}
void RawArray::sizer(int ixsize, int iysize, int izsize,int rawNum) {
	int ii;
	if(z!=NULL)
		delete[]this->z;
	z = new Raw[rawNum];			// make room for the 2D objects,
	this->rawNum = 0;   //rawNum

	for(ii=0; ii< rawNum; ii++)
		z[ii].sizer(ixsize,iysize,izsize);	// use the Raw sizer.
}
void RawArray::sizer(RawArray* src)
{
	z=src->z;
	rawNum=src->rawNum;

}
void RawArray::wipecopy(RawArray& src) {
	int k,kmax;

	if(&src==NULL)return;
	if(src.rawNum==0) return;		// ignore empty inputs.
	if(src.getrawNum()!=rawNum || src.getZsize() != z[0].getZsize() || src.getYsize() != z[0].getYsize() ||
		src.getXsize() != getXsize()) {
			sizer(&src);
	}
	kmax = getrawNum();
	for(k=0; k< kmax; k++) {		// copy each field;
		z[k].wipecopy(&(src.z[k]));
	}
}
//================================================//
void *  ImageVolume2Raw(ImageVolume &src)
{
	PIXTYPE *data= new PIXTYPE[src.GetLength()];
	if (src.PixelType==1)
	{
		unsigned char* datSrc = (unsigned char*)(src.Data);
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.GetLength();i++)
		{
			data[i]=(PIXTYPE)datSrc[i];
		}
	}
	else if (src.PixelType == 2)
	{

		unsigned short * datSrc = (unsigned short *)(src.Data);
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.GetLength();i++)
		{
			data[i]=(PIXTYPE)datSrc[i];
		}

	}
	else if (src.PixelType == 3 )
	{


		float* datSrc = (float*)(src.Data);

		for (int i=0;i<src.GetLength();i++)
		{
			data[i]=(PIXTYPE)datSrc[i];
		}

	}


	//src.Data=data;
	Raw *ret=new Raw(src.Width,src.Height,src.Depth,data);
	return ret;

}
void *  ImageVolume2Raw(ImageVolume *src)
{
	PIXTYPE *data= new PIXTYPE[src->GetLength()];
	if (src->PixelType==1)
	{
		unsigned char* datSrc = (unsigned char*)(src->Data);
		//PIXTYPE *data= new PIXTYPE[src->GetLength()];
		for (int i=0;i<src->GetLength();i++)
		{
			data[i]=(PIXTYPE)datSrc[i];
		}
	}
	else if (src->PixelType == 2)
	{

		unsigned short * datSrc = (unsigned short *)(src->Data);
		//PIXTYPE *data= new PIXTYPE[src->GetLength()];
		for (int i=0;i<src->GetLength();i++)
		{
			data[i]=(PIXTYPE)datSrc[i];
		}

	}
	else if (src->PixelType == 3 )
	{


		float* datSrc = (float*)(src->Data);

		for (int i=0;i<src->GetLength();i++)
		{
			data[i]=(PIXTYPE)datSrc[i];
		}

	}


	//src->Data=data;
	Raw *ret=new Raw(src->Width,src->Height,src->Depth,data);
	return ret;

}
void *  Raw2ImageVolume(Raw  &src,int type)
{
	PIXTYPE *datSrc = (PIXTYPE *)(src.getdata());

	if (type == 1)
	{
		unsigned char *data= new unsigned char[src.size()];

		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i = 0; i < src.size();i++)
		{
			data[i] =(unsigned char) datSrc[i];
		}
		void * ret=(void *)data;
		ImageVolume * res = new ImageVolume(src.getXsize(),src.getYsize(),src.getZsize());
		res->Data = ret;
		return res;
	}
	else if (type == 2 )
	{
		unsigned short *data =new unsigned short[src.size()];
		PIXTYPE  * datSrc = (src.getdata());
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.size();i++)
		{
			data[i]=datSrc[i];
		}
		void * ret= (void *)data;
		return ret;
	}
	else return (void *)src.getdata();

}
Raw2D Image2D2Raw2D(Image2D &src)
{
	PIXTYPE *data= new PIXTYPE[src.GetLength()];
	if (src.PixelType==1)
	{
		unsigned char* datSrc = (unsigned char*)(src.data);
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.GetLength();i++)
		{
			data[i]=datSrc[i];
		}
	}
	else if (src.PixelType == 2)
	{

		unsigned short * datSrc = (unsigned short *)(src.data);
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.GetLength();i++)
		{
			data[i]=datSrc[i];
		}

	}
	else if (src.PixelType == 3 )
	{


		short* datSrc = (short*)(src.data);

		for (int i=0;i<src.GetLength();i++)
		{
			data[i]=datSrc[i];
		}

	}


	//src.Data=data;
	Raw2D *ret=new Raw2D(src.width,src.height,data);
	return *ret;
}
void * Raw2D2Image2D(Raw2D &src,int type)
{
	PIXTYPE *data= new PIXTYPE[src.size()];
	if (type==1)
	{
		unsigned char* datSrc = new unsigned char [src.size()];//(unsigned char*)(src.data);
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.size();i++)
		{
			datSrc[i]=(unsigned char)src.getXY(i);
		}
		void * ret= (void *)datSrc;
		return datSrc;
	}
	else if (type == 2)
	{

		unsigned short * datSrc = new unsigned short [src.size()];//(unsigned short *)(src.data);
		//PIXTYPE *data= new PIXTYPE[src.GetLength()];
		for (int i=0;i<src.size();i++)
		{
			datSrc[i]=src.getXY(i);
		}
		void * ret=(void *)datSrc;
		return datSrc;
	}
	else if (type == 3 )
	{


		float* datSrc = new float [src.size()]; //(short*)(src.data);

		for (int i=0;i<src.size();i++)
		{
			datSrc[i]=src.getXY(i);
		}
		void *ret =(void *)datSrc;
		return datSrc;

	}


	//src.Data=data;

	//return *ret;
}




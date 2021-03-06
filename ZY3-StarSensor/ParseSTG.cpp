#include "ParseSTG.h"

//////////////////////////////////////////////////////////////////////////
//功能：解析STG文件中的四元数等信息
//输入：STGpath，STG文件路径
//输出：ZY3_02STGdata，各姿态相关数据组成的结构体
//注意：该星敏为APS星敏数据
//日期：2016.07.01
//////////////////////////////////////////////////////////////////////////
void ParseSTG::ParseZY302_STG(string STGpath, vector<STGData> &ZY3_02STGdata)
{
	ifstream in;
	in.open(STGpath.c_str(), ios::binary);

	in.seekg(0, ios::end);
	ios::pos_type ss = in.tellg();
	int nSize = (int)ss;
	nSize = nSize / 120;
	in.seekg(0, ios::beg);

	int i;
	double ta, tb, tc;
	int ka = 0, kb = 0, kc = 0;
	STGData *ZY_3Data = new STGData[nSize];
	memset(ZY_3Data, 0, 4096);
	for (i = 0; i < nSize; i++)
	{
		in.seekg(4, ios::cur);
		unsigned char a[8];
		in.read((char*)&a, 8);
		ta = mBase.RevDouble(a);
		ZY_3Data[i].StarA.UTC = ta;
		//为解决资三STG数据问题加的判断
		if (ka == 0) { ZY_3Data[i].StarA.UTC = ta; ka++; }
		else if (ta - ZY_3Data[i - 1].StarA.UTC < -0.3) { ZY_3Data[i].StarA.UTC = ta + 1; }
		else if (ta - ZY_3Data[i - 1].StarA.UTC > 0.3) { ZY_3Data[i].StarA.UTC = ta - 1; }
		else { ZY_3Data[i].StarA.UTC = ta; }
		in.seekg(1, ios::cur);
		long Q1temp, Q2temp, Q3temp;
		in.read((char*)&Q1temp, 4);
		ZY_3Data[i].StarA.Q1 = mBase.ReverseQ(Q1temp);
		in.read((char*)&Q2temp, 4);
		ZY_3Data[i].StarA.Q2 = mBase.ReverseQ(Q2temp);
		in.read((char*)&Q3temp, 4);
		ZY_3Data[i].StarA.Q3 = mBase.ReverseQ(Q3temp);
		ZY_3Data[i].StarA.Q0 = sqrt(1 - ZY_3Data[i].StarA.Q1*ZY_3Data[i].StarA.Q1 - ZY_3Data[i].StarA.Q2*ZY_3Data[i].StarA.Q2 - ZY_3Data[i].StarA.Q3*ZY_3Data[i].StarA.Q3);

		in.read((char*)&a, 8);
		tb = mBase.RevDouble(a);
		ZY_3Data[i].StarB.UTC = tb;
		//为解决资三STG数据问题加的判断
		if (kb == 0) { ZY_3Data[i].StarB.UTC = tb; kb++; }
		else if (tb - ZY_3Data[i - 1].StarB.UTC < -0.3) { ZY_3Data[i].StarB.UTC = tb + 1; }
		else if (tb - ZY_3Data[i - 1].StarB.UTC > 0.3) { ZY_3Data[i].StarB.UTC = tb - 1; }
		else { ZY_3Data[i].StarB.UTC = tb; }
		in.seekg(1, ios::cur);
		in.read((char*)&Q1temp, 4);
		ZY_3Data[i].StarB.Q1 = mBase.ReverseQ(Q1temp);
		in.read((char*)&Q2temp, 4);
		ZY_3Data[i].StarB.Q2 = mBase.ReverseQ(Q2temp);
		in.read((char*)&Q3temp, 4);
		ZY_3Data[i].StarB.Q3 = mBase.ReverseQ(Q3temp);
		ZY_3Data[i].StarB.Q0 = sqrt(1 - ZY_3Data[i].StarB.Q1*ZY_3Data[i].StarB.Q1 - ZY_3Data[i].StarB.Q2*ZY_3Data[i].StarB.Q2 - ZY_3Data[i].StarB.Q3*ZY_3Data[i].StarB.Q3);

		in.read((char*)&a, 8);
		tc = mBase.RevDouble(a);
		ZY_3Data[i].StarC.UTC = tc;
		//为解决资三STG数据问题加的判断
		if (kc == 0) { ZY_3Data[i].StarC.UTC = tc; kc++; }
		else if (tc - ZY_3Data[i - 1].StarC.UTC < -0.3) { ZY_3Data[i].StarC.UTC = tc + 1; }
		else if (tc - ZY_3Data[i - 1].StarC.UTC > 0.3) { ZY_3Data[i].StarC.UTC = tc - 1; }
		else { ZY_3Data[i].StarC.UTC = tc; }
		in.seekg(1, ios::cur);
		in.read((char*)&Q1temp, 4);
		ZY_3Data[i].StarC.Q1 = mBase.ReverseQ(Q1temp);
		in.read((char*)&Q2temp, 4);
		ZY_3Data[i].StarC.Q2 = mBase.ReverseQ(Q2temp);
		in.read((char*)&Q3temp, 4);
		ZY_3Data[i].StarC.Q3 = mBase.ReverseQ(Q3temp);
		ZY_3Data[i].StarC.Q0 = sqrt(1 - ZY_3Data[i].StarC.Q1*ZY_3Data[i].StarC.Q1 - ZY_3Data[i].StarC.Q2*ZY_3Data[i].StarC.Q2 - ZY_3Data[i].StarC.Q3*ZY_3Data[i].StarC.Q3);

		in.read((char*)&a, 8);
		ZY_3Data[i].utgyro = mBase.RevDouble(a);
		short gy;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g1 = gy*0.000022 / 0.25;
		//ZY_3Data[i].g1=gy*0.000022/0.25*1.115454545;//ZY3-01星陀螺的比例系数
		in.read((char*)&gy, 2);
		ZY_3Data[i].g2 = gy*0.000022 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g3 = gy*0.000022 / 0.25;
		//ZY_3Data[i].g3=gy*0.000022/0.25*1.073181818;//ZY3-01星陀螺的比例系数
		in.read((char*)&gy, 2);
		ZY_3Data[i].g4 = gy*0.000022 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g5 = gy*0.000022 / 0.25;
		//ZY_3Data[i].g5=gy*0.000022/0.25*1.103181818;//ZY3-01星陀螺的比例系数
		in.read((char*)&gy, 2);
		ZY_3Data[i].g6 = gy*0.000022 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g7 = gy*0.00005 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g8 = gy*0.00005 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g9 = gy*0.00005 / 0.25;

		long bsx, bsy, bsz;
		in.read((char*)&bsx, 4);
		in.read((char*)&bsy, 4);
		in.read((char*)&bsz, 4);
		ZY_3Data[i].bx = mBase.Reverse2(bsx);
		ZY_3Data[i].by = mBase.Reverse2(bsy);
		ZY_3Data[i].bz = mBase.Reverse2(bsz);

		in.seekg(3, ios::cur);
		in.read((char*)&gy, 2);
		ZY_3Data[i].g10 = gy*0.000025 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g11 = gy*0.000025 / 0.25;
		in.read((char*)&gy, 2);
		ZY_3Data[i].g12 = gy*0.000025 / 0.25;

		char sign;
		in.read((char*)&sign, 1);
		//判断星敏B和C的符号
		if (sign == 0)
		{
		}
		else if (sign == 1)
		{
			ZY_3Data[i].StarB.Q0 = -ZY_3Data[i].StarB.Q0;
		}
		else if (sign == 2)
		{
			ZY_3Data[i].StarC.Q0 = -ZY_3Data[i].StarC.Q0;
		}
		else if (sign == 3)
		{
			ZY_3Data[i].StarB.Q0 = -ZY_3Data[i].StarB.Q0;
			ZY_3Data[i].StarC.Q0 = -ZY_3Data[i].StarC.Q0;
		}
		ZY3_02STGdata.push_back(ZY_3Data[i]);
		in.seekg(5, ios::cur);
	}

	string path = string(STGpath);
	path = path.substr(0, path.rfind('.'));
	string strpath = path + "_STG_parse.txt";
	FILE *fpres = fopen(strpath.c_str(), "w");
	fprintf(fpres,"%d\n",nSize);
	for (i = 0; i < nSize; i++)
	{
		fprintf(fpres, "%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t", ZY_3Data[i].StarA.UTC, ZY_3Data[i].StarA.Q0, ZY_3Data[i].StarA.Q1, ZY_3Data[i].StarA.Q2, ZY_3Data[i].StarA.Q3);
		fprintf(fpres, "%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t", ZY_3Data[i].StarB.UTC, ZY_3Data[i].StarB.Q0, ZY_3Data[i].StarB.Q1, ZY_3Data[i].StarB.Q2, ZY_3Data[i].StarB.Q3);
		fprintf(fpres, "%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t", ZY_3Data[i].StarC.UTC, ZY_3Data[i].StarC.Q0, ZY_3Data[i].StarC.Q1, ZY_3Data[i].StarC.Q2, ZY_3Data[i].StarC.Q3);
		fprintf(fpres, "%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\n", ZY_3Data[i].utgyro, ZY_3Data[i].g1,
			ZY_3Data[i].g2, ZY_3Data[i].g3, ZY_3Data[i].g4, ZY_3Data[i].g5, ZY_3Data[i].g6, ZY_3Data[i].g7, ZY_3Data[i].g8, ZY_3Data[i].g9, ZY_3Data[i].g10,
			ZY_3Data[i].g11, ZY_3Data[i].g12, ZY_3Data[i].bx, ZY_3Data[i].by, ZY_3Data[i].bz);
	}
	fcloseall;

}

//////////////////////////////////////////////////////////////////////////
//功能：解析STI文件中的星图
//输入：STIpath，STI文件路径
//输出：输出到星敏目录
//注意：该星敏为APS星敏数据
//日期：2017.01.08
//////////////////////////////////////////////////////////////////////////
bool ParseSTG::ParseZY302_STI(string STIpath)
{
	FILE *fp = fopen(STIpath.c_str(), "rb");
	if (!fp)
	{
		printf("Failed to open the RAW File(%s)\n", STIpath.c_str());
		return false;
	}
	//一次将文件全部读入内存pData
	_fseeki64(fp, 0, SEEK_END);
	__int64 nSize = _ftelli64(fp);
	_fseeki64(fp, 0, SEEK_SET);
	byte *pData = new byte[nSize];
	if (fread(pData, sizeof(byte), nSize, fp) != nSize)
	{
		fclose(fp);
		return false;
	}
	fclose(fp);	fp = NULL;
	long width = 1024, height = 1024;// 影像的宽度和高度
	unsigned short *pFred = new unsigned short[width * height];	     //像素值
	int nSizeFred = nSize / 1310736;   //帧数
	
	//创建星图文件夹
	workpath = STIpath.substr(0, STIpath.rfind('\\'));
	string imgtmp = workpath + "\\Bouguet";
	char * imgpath = (char *)imgtmp.data();
	if (_mkdir(imgpath) == 0);
	string imgtxt = workpath + "\\Bouguet\\像面坐标.txt";
	// 累计秒从2009年1月1日0时开始计数
	double jd0, refMJD;
	Cal2JD(2009, 1, 1, 0, &jd0, &refMJD);
	string outpath = workpath + "\\星时.txt";
	FILE *ftime = fopen(outpath.c_str(), "w");
	if (!ftime)
	{
		printf("Failed to open the RAW File(%s)\n", outpath);
		return false;
	}
	fprintf(ftime, "帧号\t 星时1(累计秒，与姿态轨道文件对应)\t星时2（YYYY:MM:DD）\n");	
	char chr[41], c[10];
	bitset<8> bit8;
	string str;
	unsigned int tmp, tmps = 0, tmpms = 0;
	double  second;
	double *UT = new double[nSizeFred];
	int year, month, day, hour, minute;
	//输出影像格式
	string outdriver = "GTiff";	    //也可以存为bmp
	GeoReadImage m_out;
	for (int i = 0; i < nSizeFred; )
	{
		//星时
		//整秒
		memcpy(&bit8, pData + i * 1310736 + 4, sizeof(byte));
		tmps = pow(2, 24)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 5, sizeof(byte));
		tmps += pow(2, 16)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 6, sizeof(byte));
		tmps += pow(2, 8)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 7, sizeof(byte));
		tmps += pow(2, 0)* bit8.to_ulong();
		//微妙
		memcpy(&bit8, pData + i * 1310736 + 8, sizeof(byte));
		tmpms = pow(2, 16)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 9, sizeof(byte));
		tmpms += pow(2, 8)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 10, sizeof(byte));
		tmpms += pow(2, 0)* bit8.to_ulong();
		//累计秒
		UT[i] = tmps + tmpms / 1000000.0;
		//历书时
		FromSecondtoYMD(refMJD, UT[i], year, month, day, hour, minute, second);
		fprintf(ftime, "%3d\t%16.6lf\n", i + 1, UT[i]);
		//fprintf(ftime, "%04d:%02d:%02d:%02d:%02d:%06.3lf\n", year, month, day, hour, minute, second);

		//重新组织一帧数据
		for (int j = 0; j < 262144; j++)
		{
			//每次从内存取5B转换为4个像素值，存入pFred
			for (int k = 0; k < 5; k++)
			{
				memcpy(&bit8, pData + i * 1310736 + 15 + j * 5 + k, sizeof(byte));
				str = bit8.to_string();
				strcpy(chr + k * 8, str.c_str());
			}
			for (int k = 0; k < 4; k++)
			{
				memcpy(c, &chr[10 * k], sizeof(char) * 10);
				pFred[j * 4 + k] = (c[0] - 48) * 512 + (c[1] - 48) * 256 + (c[2] - 48) * 128 + (c[3] - 48) * 64 + (c[4] - 48) * 32
					+ (c[5] - 48) * 16 + (c[6] - 48) * 8 + (c[7] - 48) * 4 + (c[8] - 48) * 2 + (c[9] - 48) * 1;
			}
		}
		//创建影像
		char tempath[100];
		sprintf_s(tempath, "\\Bouguet\\星图%d.tiff", i/5 + 1);
		string imgpath = workpath +  tempath;
		m_out.New(imgpath, outdriver, GDT_Byte, width, height, 1);

		//更新方式打开影像
		m_out.Open(imgpath, GA_Update);
		if (m_out.m_isopen == true)
			printf("\rUpdate Img (%s)", imgpath.c_str());
		else
		{
			printf("\rUpdate Img (%s) Failed", imgpath.c_str());
			return 0;
		}
		//建立out数据区
		m_out.SetBuffer(0, 0, width, height, m_out.pBuffer[0]);
		double gray;
		for (long y = 0; y < height; y++)       //y坐标
		{
			for (long x = 0; x < width; x++)   //x坐标
			{
				//读入数据
				gray = pFred[y*width + x];
				if (gray > 255)gray = 255;
				//输出图像坐标系顺时针90度转为星敏像平面坐标系
				m_out.SetDataValue(x, y, gray, 0);    //赋值
			}
		}
		//写入数据
		bool iswrite = true;
		iswrite *= m_out.WriteBlock(0, 0, width, height, 0, m_out.pBuffer[0]);
		//关闭影像
		m_out.Destroy();
			
		int rate = 100 * (i+1) / nSizeFred;
		printf("\r已处理行数：%d;  Process:%d%%", i+1, rate);               //进度输出
		i = i + 5;//每五景输出一次
	}
	if (pFred != NULL)		delete[]pFred;       pFred = NULL;
	if (pData != NULL)		delete[]pData;		 pData = NULL;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//功能：解析STI文件中的星图
//输入：STIpath，STI文件路径
//输出：输出到星敏目录
//注意：该星敏为APS星敏数据
//作者：GZC
//日期：2017.02.21
//////////////////////////////////////////////////////////////////////////
bool ParseSTG::ParseZY302_STI_10B(string STIpath)
{
	FILE *fp = fopen(STIpath.c_str(), "rb");
	if (!fp)
	{
		printf("Failed to open the RAW File(%s)\n", STIpath.c_str());
		return false;
	}

	long width = 1024, height = 1024;// 影像的宽度和高度
	unsigned short *pFred = new unsigned short[width * height];	     //像素值	
	//一次将文件全部读入内存pData
	_fseeki64(fp, 0, SEEK_END);
	__int64 nSize = _ftelli64(fp);
	_fseeki64(fp, 0, SEEK_SET);
	byte *pData = new byte[nSize];
	if (fread(pData, sizeof(byte), nSize, fp) != nSize)
	{
		fclose(fp);
		return false;
	}
	fclose(fp);	fp = NULL;
	int nSizeFred = nSize / 1310736;   //帧数
		
	 // 累计秒从2009年1月1日0时开始计数
	double jd0, refMJD;
	Cal2JD(2009, 1, 1, 0, &jd0, &refMJD);
	string outpath = workpath + "星时.txt";
	FILE *ftime = fopen(outpath.c_str(), "w");
	if (!ftime)
	{
		printf("Failed to open the RAW File(%s)\n", outpath);
		return false;
	}
	fprintf(ftime, "帧号\t 星时1(累计秒，与姿态轨道文件对应)\t星时2（YYYY:MM:DD）\n");
	char chr[41], c[10];
	
	string str;
	unsigned int tmp, tmps = 0, tmpms = 0;
	double  second;
	double *UT = new double[nSizeFred];
	int year, month, day, hour, minute;
	GeoReadImage m_out;
	bitset<8>bit8;
	bitset<10>bit10;
	bitset<40>bit40;
	bitset<40>bit401;

	for (int i = 0; i < nSizeFred; i++)
	{
		//星时
		//整秒
		memcpy(&bit8, pData + i * 1310736 + 4, sizeof(byte));
		tmps = pow(2, 24)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 5, sizeof(byte));
		tmps += pow(2, 16)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 6, sizeof(byte));
		tmps += pow(2, 8)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 7, sizeof(byte));
		tmps += pow(2, 0)* bit8.to_ulong();
		//微妙
		memcpy(&bit8, pData + i * 1310736 + 8, sizeof(byte));
		tmpms = pow(2, 16)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 9, sizeof(byte));
		tmpms += pow(2, 8)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 10, sizeof(byte));
		tmpms += pow(2, 0)* bit8.to_ulong();
		//累计秒
		UT[i] = tmps + tmpms / 1000000.0;
		//历书时
		FromSecondtoYMD(refMJD, UT[i], year, month, day, hour, minute, second);
		fprintf(ftime, "%3d\t%16.6lf\n", i + 1, UT[i]);
		//fprintf(ftime, "%04d:%02d:%02d:%02d:%02d:%06.3lf\n", year, month, day, hour, minute, second);
				
		//重新组织一帧数据
		for (int j = 0; j < 262144; j++)
		{
			//每次从内存取5B转换为4个像素值，存入pFred
			for (int k = 0; k < 5; k++)
			{
				memcpy(&bit8, pData + i * 1310736 + 15 + j * 5 + k, sizeof(byte));
				str = bit8.to_string();
				strcpy(chr + k * 8, str.c_str());
			}
			for (int k = 0; k < 4; k++)
			{
				memcpy(c, &chr[10 * k], sizeof(char) * 10);
				pFred[j * 4 + k] = (c[0] - 48) * 512 + (c[1] - 48) * 256 + (c[2] - 48) * 128 + (c[3] - 48) * 64 + (c[4] - 48) * 32
					+ (c[5] - 48) * 16 + (c[6] - 48) * 8 + (c[7] - 48) * 4 + (c[8] - 48) * 2 + (c[9] - 48) * 1;
			}
		}
		//创建影像
		char tempath[100];
		sprintf_s(tempath, "星图 (%d).tiff", i + 1);
		string imgpath = workpath + tempath;
		m_out.New(imgpath, "GTiff", GDT_Byte, width, height, 1);

		//更新方式打开影像
		m_out.Open(imgpath, GA_Update);
		if (m_out.m_isopen == true)
			printf("\rUpdate Img (%s)", imgpath.c_str());
		else
		{
			printf("\rUpdate Img (%s) Failed", imgpath.c_str());
			return 0;
		}
		//建立out数据区
		m_out.SetBuffer(0, 0, width, height, m_out.pBuffer[0]);
		double gray;
		for (long y = 0; y < height; y++)       //y坐标
		{
			for (long x = 0; x < width; x++)   //x坐标
			{
				//读入数据
				gray = pFred[y*width + x];
				if (gray > 255)gray = 255;
				//输出图像坐标系顺时针90度转为星敏像平面坐标系
				m_out.SetDataValue(x, y, gray, 0);    //赋值
			}
		}
		//写入数据
		bool iswrite = true;
		iswrite *= m_out.WriteBlock(0, 0, width, height, 0, m_out.pBuffer[0]);
		//关闭影像
		m_out.Destroy();

		int rate = 100 * (i + 1) / nSizeFred;
		printf("\r已处理行数：%d;  Process:%d%%", i + 1, rate);               //进度输出
	}
	if (pFred != NULL)		delete[]pFred;       pFred = NULL;
	if (pData != NULL)		delete[]pData;		 pData = NULL;
	return true;
}

//////////////////////////////////////////////////////////////////////////
//功能：解析STI用到的，将5字节40bit转为4个10bit的arr
//输入：5个字节的p
//输出：4个unsigned short的arr
//注意：该星敏为APS星敏数据
//作者：jianwen0529，http://bbs.csdn.net/topics/392089574
//日期：2017.02.23
//////////////////////////////////////////////////////////////////////////
void ParseSTG::Get4_10Bit(const unsigned char *p, unsigned short(&arr)[4])
{
	const unsigned short bit_mask = 0x00ff; // 0000 0011 1111 1111
	arr[0] = (unsigned short)(p[0] | (p[1] << 8)) & bit_mask;
	arr[1] = ((unsigned short)(p[1] | (p[2] << 8)) >> 2) & bit_mask;
	arr[2] = ((unsigned short)(p[2] | (p[3] << 8)) >> 4) & bit_mask;
	arr[3] = ((unsigned short)(p[3] | (p[4] << 8)) >> 6) & bit_mask;
}
//////////////////////////////////////////////////////////////////////////
//功能：解析STI文件中的星图
//输入：STIpath，STI文件路径
//输出：输出到星敏目录
//注意：该星敏为APS星敏数据
//日期：2017.01.08
//////////////////////////////////////////////////////////////////////////
bool ParseSTG::ParseZY302_STItime(string STIpath)
{
	FILE *fp = fopen(STIpath.c_str(), "rb");
	if (!fp)
	{
		printf("Failed to open the RAW File(%s)\n", STIpath.c_str());
		return false;
	}

	//一次将文件全部读入内存pData
	_fseeki64(fp, 0, SEEK_END);
	__int64 nSize = _ftelli64(fp);
	_fseeki64(fp, 0, SEEK_SET);
	byte *pData = new byte[nSize];
	if (fread(pData, sizeof(byte), nSize, fp) != nSize)
	{
		fclose(fp);
		return false;
	}
	fclose(fp);	fp = NULL;

	int nSizeFred = nSize / 1310736;   //帧数
	// 累计秒从2009年1月1日0时开始计数
	double jd0, refMJD;
	Cal2JD(2009, 1, 1, 0, &jd0, &refMJD);
	string outpath = workpath + "星时.txt";
	FILE *ftime = fopen(outpath.c_str(), "w");
	if (!ftime)
	{
		printf("Failed to open the RAW File(%s)\n", outpath);
		return false;
	}
	fprintf(ftime, "帧号\t 星时1(累计秒，与姿态轨道文件对应)\t星时2（YYYY:MM:DD）\n");
	bitset<8> bit8;
	string str;
	unsigned int tmp, tmps = 0, tmpms = 0;
	double  second;
	double *UT = new double[nSizeFred];
	int year, month, day, hour, minute;
	for (int i = 0; i < nSizeFred; i++)
	{
		//星时
		//整秒
		memcpy(&bit8, pData + i * 1310736 + 4, sizeof(byte));
		tmps = pow(2, 24)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 5, sizeof(byte));
		tmps += pow(2, 16)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 6, sizeof(byte));
		tmps += pow(2, 8)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 7, sizeof(byte));
		tmps += pow(2, 0)* bit8.to_ulong();
		//微妙
		memcpy(&bit8, pData + i * 1310736 + 8, sizeof(byte));
		tmpms = pow(2, 16)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 9, sizeof(byte));
		tmpms += pow(2, 8)* bit8.to_ulong();
		memcpy(&bit8, pData + i * 1310736 + 10, sizeof(byte));
		tmpms += pow(2, 0)* bit8.to_ulong();
		//累计秒
		UT[i] = tmps + tmpms / 1000000.0;
		//历书时
		FromSecondtoYMD(refMJD, UT[i], year, month, day, hour, minute, second);
		fprintf(ftime, "%3d\t%16.6lf\n", i + 1, UT[i]);
		//fprintf(ftime, "%04d:%02d:%02d:%02d:%02d:%06.3lf\n", year, month, day, hour, minute, second);		
	}
	fclose(ftime);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//功能：读取资三软件解析出的星点文件
//输入：StarDataPath，星点文件路径
//输出：星点控制点
//注意：该星敏为APS星敏数据
//日期：2017.11.29
//////////////////////////////////////////////////////////////////////////
bool ParseSTG::ParseZY302_SoftStarData(string StarDataPath, vector<vector<StarGCP>>&StarData)
{
	FILE *fp = fopen(StarDataPath.c_str(), "r");
	StarGCP StarTmp;	vector<StarGCP > StarTmp2;
	fscanf(fp, "%lf\t%lf\t%lf\t%*f\t%*f\t%*f\t%*f\t%lf\t%lf\t%lf\n", &StarTmp.UTC
		, &StarTmp.x, &StarTmp.y, &StarTmp.V[0], &StarTmp.V[1], &StarTmp.V[2]);
	StarTmp2.push_back(StarTmp);
	double utIndex;	
	while (!feof(fp))
	{
		utIndex = StarTmp.UTC;
		fscanf(fp, "%lf\t%lf\t%lf\t%*f\t%*f\t%*f\t%*f\t%lf\t%lf\t%lf\n", &StarTmp.UTC
		, &StarTmp.x, &StarTmp.y, &StarTmp.V[0], &StarTmp.V[1], &StarTmp.V[2]);
		if (StarTmp.UTC == utIndex)
		{
			StarTmp2.push_back(StarTmp);
		}
		else
		{
			StarData.push_back(StarTmp2);
			StarTmp2.clear();
			StarTmp2.push_back(StarTmp);
		}
	}
	fcloseall();
	return false;
}

//////////////////////////////////////////////////////////////////////////
//功能：读取资三02星轨道txt数据
//输入：sOrb，ZY3-02轨道数据
//输出：轨道vector
//注意：这个是星上GPS数据
//日期：2017.04.25
//////////////////////////////////////////////////////////////////////////
bool  ParseSTG::ReadZY302OrbTXT2(string sOrb, vector<Orbit_Ep> &arr_Orb)
{
	if (sOrb.empty())
		return false;
	FILE *fp = fopen(sOrb.c_str(), "r");
	if (!fp)
		return false;
	arr_Orb.clear();

	int num;
	Orbit_Ep Orb;
	char ss[1024];
	fgets(ss, 1024, fp);
	fgets(ss, 1024, fp);
	fscanf(fp, "%d\n", &num);//跳过前两行读取第三行
	for (size_t i = 0; i < num; i++)
	{
		fscanf(fp, "%*s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
			&Orb.UTC, &Orb.X, &Orb.Y, &Orb.Z, &Orb.Xv, &Orb.Yv, &Orb.Zv);
		arr_Orb.push_back(Orb);
	}

	fclose(fp);
	return true;
}

//////////////////////////////////////////////////////////////////////////
//功能：读取星时文件
//输入：STItimepath，STI星时文件
//输出：星时指针
//注意：该星敏为APS星敏数据
//日期：2017.01.08
//////////////////////////////////////////////////////////////////////////
void ParseSTG::ReadZY302_STItime(double *UTC)
{
	string STItimepath = workpath + "星时.txt";
	FILE *fp = fopen(STItimepath.c_str(), "r");
	int num,index;
	fscanf(fp, "%d", num);
	for (int a = 0; a < num; a++)
	{
		fscanf(fp, "%d\t%f\n", index, UTC[a]);
	}
}

//////////////////////////////////////////////////////////////////////////
//功能：根据恒星赤经赤纬及星敏姿态，计算星敏像面坐标
//输入：starCatlog，单颗恒星参数，包括J2000系下的单位矢量V[3]
//		R，星敏坐标系与J2000系的旋转关系，Crj
//输出：x,y，像面坐标
//注意：该星敏为APS星敏数据
//日期：2016.11.01
//////////////////////////////////////////////////////////////////////////
void ParseSTG::FromLL2XY(Star starCatlog, double *R, double &x, double &y)
{
	double V[3], W[3];
	V[0] = starCatlog.V[0]; V[1] = starCatlog.V[1]; V[2] = starCatlog.V[2];
	mBase.Multi(R, V, W, 3, 3, 1);
	//x0=y0=512,f=43.3mm,像元大小0.015mm
	if (W[2] > 0)
	{
		x = (512 - W[0] / W[2] * 43.3/0.015) ;
		y = (512 - W[1] / W[2] * 43.3/0.015) ;
	}
	//if (W[2] > 0)
	//{
	//	x = (W[0] / W[2] * 43.3 + 512 * 0.015) / 0.015;//X-X0;
	//	y = (W[1] / W[2] * 43.3 + 512 * 0.015) / 0.015;//Y-Y0;
	//}
	else
	{
		//x = -1, y = -1;
		x = -513, y = -513;
	}//这个是用来判断是否和星敏指向的半球方向一致
}

//////////////////////////////////////////////////////////////////////////
//功能：根据恒星赤经赤纬及星敏姿态，计算星敏像面坐标
//输入：getGCP，单颗恒星参数，J2000系下的单位矢量V[3]
//		Param，定标结果参数
//		R，星敏坐标系与J2000系的旋转关系，Crj
//输出：x,y，像面坐标
//注意：与上面函数名相同，用到了函数重载
//日期：2017.03.07
//////////////////////////////////////////////////////////////////////////
void ParseSTG::FromLL2XY(double *W, StarCaliParam Param, double *x, double *y)
{	
	//没有畸变的情况
	x[0] = Param.x0 - W[0] / W[2] * Param.f;
	y[0] = Param.y0 - W[1] / W[2] * Param.f;

	//有畸变的情况
	double r2 = (x[0] - Param.x0)*(x[0] - Param.x0) + (y[0] - Param.y0)*(y[0] - Param.y0);
	x[1] = Param.x0 - W[0] / W[2] * Param.f * (1 - Param.k1 * r2 - Param.k2 * r2*r2);
	y[1] = Param.y0 - W[1] / W[2] * Param.f * (1 - Param.k1 * r2 - Param.k2 * r2*r2);
	
}

//////////////////////////////////////////////////////////////////////////
//功能：根据星敏像面坐标及星敏感器参数，得到真实星点坐标矢量
//输入：x,y，像面坐标，Param，星敏参数
//输出：V，恒星在惯性系下坐标
//注意：要在这一步加入畸变
//作者：GZC
//日期：2017.03.02
//////////////////////////////////////////////////////////////////////////
void ParseSTG::FromXY2LL(double x, double y, StarCaliParam Param, double * V)
{
	/*double p1 = 1e-7, p2 = 1e-7;
	double xp = x - Param.x0;
	double yp = y - Param.y0;
	double r2 = (x - Param.x0)*(x - Param.x0) + (y - Param.y0)*(y - Param.y0);
	double xreal = -(x - Param.x0)*(1 - Param.k1 * r2) -
		p1*(3 * xp*xp + yp*yp) - 2 * p2*xp*yp;
	double yreal = -(y - Param.y0)*(1 - Param.k1 * r2) -
		p2*(3 * yp*yp + xp*xp) - 2 * p1*xp*yp;
	double freal = Param.f;
	double sum = sqrt(xreal*xreal + yreal*yreal + freal*freal);
	V[0] = xreal / sum;
	V[1] = yreal / sum;
	V[2] = freal / sum;*/

	double r2 = (x - Param.x0)*(x - Param.x0) + (y - Param.y0)*(y - Param.y0);
	double xreal = -(x - Param.x0)*(1 - Param.k1 * r2 - Param.k2 * r2*r2);
	double yreal = -(y - Param.y0)*(1 - Param.k1 * r2 - Param.k2 * r2*r2);
	double freal = Param.f;
	double sum = sqrt(xreal*xreal + yreal*yreal + freal*freal);
	V[0] = xreal / sum;
	V[1] = yreal / sum;
	V[2] = freal / sum;
}

//////////////////////////////////////////////////////////////////////////
//功能：根据恒星亮度等级，计算仿真星图的亮度DN值
//输入：Mag:恒星星等；
//输出：DN值
//注意：定义星等3为255亮度，小于星等3的也为255
//日期：2016.12.08
//////////////////////////////////////////////////////////////////////////
int ParseSTG::Mag2DN(double Mag)
{
	int DN = 166 * pow(100, (3 - Mag) / 5)+65;
	return DN;
}

//////////////////////////////////////////////////////////////////////////
//功能：根据资三APS星敏四元数构建星图
//输入：ZY3_02STGdata：STG解析出的姿态数据
//输出：四元数对应星图
//注意：星敏A为APS星敏数据
//日期：2016.10.31
//////////////////////////////////////////////////////////////////////////
void ParseSTG::StarMap(vector<STGData> ZY3_02STGdata)
{
	//打开星表文件
	string starCatlogpath = "D:\\2_ImageData\\ZY3-02\\星图处理\\星表\\导航星表矢量.txt";
	FILE *fp;
	fp = fopen(starCatlogpath.c_str(), "r");
	if (fp == NULL)
	{
		printf("打开%s文件失败,请确认文件路径是否正确!\n", starCatlogpath.c_str());
		return;
	}
	int i, n;
	fscanf(fp, "%d", &n);//读取星表数据
	Star *starCatlog = new Star[n];
	for (i = 0; i < n; i++)
	{
		fscanf(fp, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", &starCatlog[i].ID, &starCatlog[i].phiX,
			&starCatlog[i].phiY, &starCatlog[i].mag, &starCatlog[i].V[0], &starCatlog[i].V[1], &starCatlog[i].V[2]);
	}
	fclose(fp);

	int j, m = ZY3_02STGdata.size();
	double R[9], za[3] = { 0,0,1 }, zc[3];
	double px, py, x, y;
	// 影像的宽度和高度
	long width = 1024, height = 1024;
	//创建像平面像素值数组
	byte *UnitData = new byte[1024 * 1024];
		
	string imgtmp = workpath + "星图";
	char * imgpath = (char *)imgtmp.data();
	_mkdir(imgpath);//创建星图文件夹
	imgtmp = workpath + "星图\\星图仿真\\";
	imgpath = (char *)imgtmp.data();
	_mkdir(imgpath);//创建星图仿真文件夹
	string imgtxt = workpath + "星图\\像面坐标.txt";
	FILE *fptxt = fopen(imgtxt.c_str(), "w");

	//给出第一帧的星像点坐标和亮度	
	//int aa = 2;
	//mBase.quat2matrix(ZY3_02STGdata[aa].StarA.Q1, ZY3_02STGdata[aa].StarA.Q2,
	//	ZY3_02STGdata[aa].StarA.Q3, ZY3_02STGdata[aa].StarA.Q0, R);//Crj
	//for (j = 0; j < n; j++)
	//{
	//	FromLL2XY(starCatlog[j], R, x, y);//对星表每颗星遍历，计算像面坐标
	//	if (x > 0 && x < 1024 && y>0 && y < 1024)		
	//	{
	//		int xPixel = int(y + 0.5);			
	//		int yPixel = 1024 - int(x + 0.5);	
	//		/*int xPixel = 512 - int(y + 0.5);
	//		int yPixel = 512 + int(x + 0.5);*/
	//		UnitData[yPixel*width + xPixel] = starCatlog[j].DN;
	//		fprintf(fptxt, "%d\t%d\t%.1f\n", xPixel, yPixel, starCatlog[j].mag);
	//	}
	//}
	//fclose(fptxt);

	//根据姿态仿出星图
	m = 40;
	for (i=0;i<m;i++)
	//for (i = 900; i < 1100; i++)
	{
		memset(UnitData, 0, sizeof(byte) * 1024 * 1024);//影像像素值置为0
		//星敏A即APS星敏仿真
		mBase.quat2matrix(ZY3_02STGdata[i].StarA.Q1,ZY3_02STGdata[i].StarA.Q2,
			ZY3_02STGdata[i].StarA.Q3,ZY3_02STGdata[i].StarA.Q0,R);//Crj
		//星敏B仿真
		//mBase.quat2matrix(ZY3_02STGdata[i].StarB.Q1, ZY3_02STGdata[i].StarB.Q2,
		//	ZY3_02STGdata[i].StarB.Q3, ZY3_02STGdata[i].StarB.Q0, R);//Crj
		for (j = 0; j < n; j++)
		{
			FromLL2XY(starCatlog[j], R, x, y);//对星表每颗星遍历，计算像面坐标
			if (x > 4 && x < 1020 && y>4 && y < 1020)
			//if (x > -510 && x < 510 && y>-510 && y < 510)
			{
				for (int ii = 0; ii < 5; ii++)//生成5个像素大小的星图
				{
					for (int jj = 0; jj < 5; jj++)
					{
						//UnitData[yPixel*width + xPixel] = starCatlog[j].DN;
						//将 X↓Y→ 转换为 X→Y↑
						int xTrans = int(y+0.5);
						int yTrans = 1024-int(x+0.5);
						int DN = Mag2DN(starCatlog[j].mag);
						if (DN > 255) DN = 255;
						UnitData[yTrans*width + xTrans] = DN;
						//UnitData[yTrans*width + xTrans] = starCatlog[j].mag*10;
						x++;
					}
					x -= 5;
					y++;
				}
			}
		}
		//创建影像
		char tempath[100];
		// 输出影像参数
		string outdriver = "GTiff";
		//投影
		string tarProject = "PROJCS[\"UTM_Zone_50N\", GEOGCS[\"GCS_WGS_1984\", DATUM[\"WGS_1984\", SPHEROID[\"WGS_1984\", 6378137.0, 298.2572235630016],TOWGS84[0,0,0,0,0,0,0]], PRIMEM[\"Greenwich\", 0.0], UNIT[\"Degree\", 0.0174532925199433]], PROJECTION[\"Transverse_Mercator\"], PARAMETER[\"False_Easting\", 500000.0], PARAMETER[\"False_Northing\", 0.0], PARAMETER[\"Central_Meridian\", 117.0], PARAMETER[\"Scale_Factor\", 0.9996], PARAMETER[\"Latitude_Of_Origin\", 0.0], UNIT[\"Meter\", 1.0]]";
		//仿射变换
		double minx = 0, maxy = 1024, resolution = 1;
		double adfGeoTransform[6] = { minx, resolution, 0, maxy, 0, -resolution };
		sprintf_s(tempath, "星图 (%d) APS仿.tiff", i+1);
		//sprintf_s(tempath, "星敏B仿真 (%d).tiff", i + 1, ZY3_02STGdata[i].StarB.UTC);
		string imgpath = workpath + "星图\\星图仿真\\" + tempath;
		GeoReadImage m_out;
		m_out.New(imgpath, outdriver, GDT_Byte, width, height, 1);
		m_out.poDataset->SetProjection(tarProject.c_str());
		m_out.poDataset->SetGeoTransform(adfGeoTransform);
		//更新方式打开影像
		m_out.Open(imgpath, GA_Update);
		if (m_out.m_isopen == true)
			printf("\rUpdate Img (%s)", imgpath.c_str());
		else
		{
			printf("\rUpdate Img (%s) Failed", imgpath.c_str());
			return;
		}
		//建立out数据区
		m_out.SetBuffer(0, 0, width, height, m_out.pBuffer[0]);
		double gray;
		for (int yPixel = 0; yPixel < height; yPixel++)       //y坐标
		{
			for (int xPixel = 0; xPixel < width; xPixel++)   //x坐标
			{
				//读入数据
				gray = UnitData[yPixel*width + xPixel];
				//gray = 0;
				m_out.SetDataValue(xPixel, yPixel, gray, 0);    //赋值
			}
		}
		//写入数据
		bool iswrite = true;
		iswrite *= m_out.WriteBlock(0, 0, width, height, 0, m_out.pBuffer[0]);
		//关闭影像
		m_out.Destroy();
	}
}

//////////////////////////////////////////////////////////////////////////
//功能：资三APS星图识别结果与星上下传STG数据对比
//输入：ZY3_02STGdata：STG解析出的姿态数据
//      IDpath：星图识别得到的APS星敏四元数
//输出：同目录下对比结果
//注意：星敏A为APS星敏数据
//日期：2016.11.02
//////////////////////////////////////////////////////////////////////////
//void ParseSTG::StarIDComp(vector<STGData> ZY3_02STGdata,string IDpath)
//{
//	FILE *fp;
//	fp = fopen(IDpath.c_str(),"r");
//	int i,m,n;
//	fscanf(fp,"%d",&m);//星图识别四元数个数 2Hz
//	n = ZY3_02STGdata.size();//STG解析出的四元数个数 4Hz
//	Quat *Qid = new Quat[m];
//	Quat *Qidint = new Quat[n];
//	double *UT = new double[n];
//	for (i=0;i<m;i++)
//	{
//		fscanf(fp,"%lf\t%lf\t%lf\t%lf\t%lf\t%*lf\t%*lf\n",&Qid[i].UTC,&Qid[i].Q0,&Qid[i].Q1,&Qid[i].Q2,&Qid[i].Q3);
//	}
//	for (i=0;i<n;i++)
//	{
//		UT[i] = ZY3_02STGdata[i].StarA.UTC;
//	}
//	QuatInterpolation(Qid,m,UT,n,Qidint);//姿态内插
//	
//	string resPath = workpath + "StarId_Compare.txt";
//	FILE *fpres;
//	fpres = fopen(resPath.c_str(),"w");
//	//然后进行比较输出
//	double qL[4],qR[4],dQ[4];
//	SateEuler *EulerArray = new SateEuler[n];
//	for (i=0;i<n;i++)
//	{
//		qL[0]=ZY3_02STGdata[i].StarA.Q0,qL[1]=ZY3_02STGdata[i].StarA.Q1,
//		qL[2]=ZY3_02STGdata[i].StarA.Q2,qL[3]=ZY3_02STGdata[i].StarA.Q3;
//		qR[0]=-Qidint[i].Q0,qR[1]=Qidint[i].Q1,qR[2]=Qidint[i].Q2,qR[3]=Qidint[i].Q3;
//		quatmult(qL,qR,dQ);
//		dQ[1]=2*dQ[1]/PI*180*3600;dQ[2]=2*dQ[2]/PI*180*3600;dQ[3]=2*dQ[3]/PI*180*3600;
//		fprintf(fpres,"%.9lf\t%.9lf\t%.9lf\n",dQ[1],dQ[2],dQ[3]);
//		EulerArray[i].R = dQ[1];	
//		EulerArray[i].P = dQ[2];	
//		EulerArray[i].Y = dQ[3];
//		EulerArray[i].UTC = UT[i]-97499271;
//	}
//	Sim.MatPlotDetQ(EulerArray,n);
//}

//////////////////////////////////////////////////////////////////////////
//功能：APS星图识别结果四元数与星敏B、星敏C三者之间的夹角关系
//输入：ZY3_02STGdata：STG解析出的姿态数据
//      IDpath：星图识别得到的APS星敏四元数
//      StarTag：int值，12表示星敏A和B
//输出：同目录下，三组夹角对比结果
//注意：星敏A为APS星敏数据
//日期：2016.11.02
//////////////////////////////////////////////////////////////////////////
void ParseSTG::StarAngleAPS_B_C(vector<STGData> ZY3_02STGdata, int StarTag)
{
	int i,m,n;
	m=ZY3_02STGdata.size();	
	//string IDpath = workpath + "0830_STG_parse.txt";
	//FILE *fp = fopen(IDpath.c_str(),"r");
	/*fscanf(fp,"%d\n",&n);*/
	Quat *StarA = new Quat[m];
	Quat *StarB = new Quat[m];
	Quat *StarC = new Quat[m];
	Quat *StarAi = new Quat[m];
	Quat *StarCi = new Quat[m];
	double *UT = new double[m];
	/*for (i=0;i<n;i++)
	{
		fscanf(fp,"%lf\t%lf\t%lf\t%lf\t%lf\t%*lf\t%*lf\n",&StarA[i].UTC,&StarA[i].Q0,&StarA[i].Q1,&StarA[i].Q2,&StarA[i].Q3);
	}*/
	double mz[3]={0,0,1},RA[9],RB[9],za[3],zb[3],Angle;
	string strpath;
	if (StarTag==23)
	{
		for (i=0;i<m;i++)//星敏B和C数据，以B为时间基准
		{
			UT[i]=ZY3_02STGdata.at(i).StarB.UTC;
			StarB[i].Q1=ZY3_02STGdata.at(i).StarB.Q1;StarB[i].Q2=ZY3_02STGdata.at(i).StarB.Q2;
			StarB[i].Q3=ZY3_02STGdata.at(i).StarB.Q3,StarB[i].Q0=ZY3_02STGdata.at(i).StarB.Q0;
			StarC[i].UTC=ZY3_02STGdata.at(i).StarC.UTC;
			StarC[i].Q1=ZY3_02STGdata.at(i).StarC.Q1;StarC[i].Q2=ZY3_02STGdata.at(i).StarC.Q2;
			StarC[i].Q3=ZY3_02STGdata.at(i).StarC.Q3,StarC[i].Q0=ZY3_02STGdata.at(i).StarC.Q0;
		}
		mBase.QuatInterpolation(StarC, m, UT, m,StarCi);
		strpath = workpath+"Star23Angle.txt";	
		FILE *fpres=fopen(strpath.c_str(),"w");
		for(int i=0;i<m;i++)
		{
			mBase.quat2matrix(StarB[i].Q1,StarB[i].Q2,StarB[i].Q3,StarB[i].Q0,RA);
			mBase.quat2matrix(StarCi[i].Q1,StarCi[i].Q2,StarCi[i].Q3,StarCi[i].Q0,RB);//Crj
			mBase.invers_matrix(RA,3);
			mBase.invers_matrix(RB,3);//Cjr
			mBase.Multi(RA,mz,za,3,3,1);
			mBase.Multi(RB,mz,zb,3,3,1);//星敏光轴在惯性系中的坐标值
			Angle=acos((za[0]*zb[0]+za[1]*zb[1]+za[2]*zb[2])/sqrt(za[0]*za[0]+za[1]*za[1]+za[2]*za[2])/sqrt(zb[0]*zb[0]+zb[1]*zb[1]+zb[2]*zb[2]))/PI*180;
			fprintf(fpres,"%.9f\t%.9f\n",UT[i],Angle);
		}
	} 
	else if(StarTag==12)
	{
		for (i=0;i<m;i++)//星敏A和B数据，以B为时间基准
		{
			UT[i]=ZY3_02STGdata.at(i).StarB.UTC;
			StarB[i].Q1=ZY3_02STGdata.at(i).StarB.Q1;StarB[i].Q2=ZY3_02STGdata.at(i).StarB.Q2;
			StarB[i].Q3=ZY3_02STGdata.at(i).StarB.Q3,StarB[i].Q0=ZY3_02STGdata.at(i).StarB.Q0;
		}
		mBase.QuatInterpolation(StarA, m, UT, m, StarAi);
		strpath =workpath+"Star12Angle.txt";
		FILE *fpres=fopen(strpath.c_str(),"w");
		for(int i=0;i<m;i++)
		{
			mBase.quat2matrix(StarAi[i].Q1,StarAi[i].Q2,StarAi[i].Q3,StarAi[i].Q0,RA);
			mBase.quat2matrix(StarB[i].Q1,StarB[i].Q2,StarB[i].Q3,StarB[i].Q0,RB);//Crj
			mBase.invers_matrix(RA,3);
			mBase.invers_matrix(RB,3);//Cjr
			mBase.Multi(RA,mz,za,3,3,1);
			mBase.Multi(RB,mz,zb,3,3,1);//星敏光轴在惯性系中的坐标值
			Angle=acos((za[0]*zb[0]+za[1]*zb[1]+za[2]*zb[2])/sqrt(za[0]*za[0]+za[1]*za[1]+za[2]*za[2])/sqrt(zb[0]*zb[0]+zb[1]*zb[1]+zb[2]*zb[2]))/PI*180;
			fprintf(fpres,"%.9f\t%.9f\n",UT[i],Angle);
		}
	} 
	else if(StarTag==13)
	{
		for (i=0;i<m;i++)//星敏A和C数据，以C为时间基准
		{
			UT[i]=ZY3_02STGdata.at(i).StarC.UTC;
			StarC[i].Q1=ZY3_02STGdata.at(i).StarC.Q1;StarC[i].Q2=ZY3_02STGdata.at(i).StarC.Q2;
			StarC[i].Q3=ZY3_02STGdata.at(i).StarC.Q3,StarC[i].Q0=ZY3_02STGdata.at(i).StarC.Q0;
		}
		mBase.QuatInterpolation(StarA, m, UT, m, StarAi);
		strpath =workpath+"Star13Angle.txt";
		FILE *fpres=fopen(strpath.c_str(),"w");
		for(int i=0;i<m;i++)
		{
			mBase.quat2matrix(StarAi[i].Q1,StarAi[i].Q2,StarAi[i].Q3,StarAi[i].Q0,RA);
			mBase.quat2matrix(StarC[i].Q1,StarC[i].Q2,StarC[i].Q3,StarC[i].Q0,RB);//Crj
			mBase.invers_matrix(RA,3);
			mBase.invers_matrix(RB,3);//Cjr
			mBase.Multi(RA,mz,za,3,3,1);
			mBase.Multi(RB,mz,zb,3,3,1);//星敏光轴在惯性系中的坐标值
			Angle=acos((za[0]*zb[0]+za[1]*zb[1]+za[2]*zb[2])/sqrt(za[0]*za[0]+za[1]*za[1]+za[2]*za[2])/sqrt(zb[0]*zb[0]+zb[1]*zb[1]+zb[2]*zb[2]))/PI*180;
			fprintf(fpres,"%.9f\t%.9f\n",UT[i],Angle);
		}
	} 	
}

//////////////////////////////////////////////////////////////////////////
//功能：STG解析数据，APS与星敏B、星敏C三者之间的夹角关系
//输入：ZY3_02STGdata：STG解析出的姿态数据
//          StarTag：int值，12表示星敏A和B
//输出：同目录下，三组夹角对比结果
//注意：星敏A为APS星敏数据
//日期：2016.11.02--2017.01.09
//////////////////////////////////////////////////////////////////////////
void ParseSTG::StarAngle(vector<STGData> StarDat, int StarTag)
{
	int m, n;
	m = StarDat.size();
	Quat *StarX = new Quat[m];
	Quat *StarY = new Quat[m];
	Quat *StarYi = new Quat[m];
	double *UTC = new double[m];
	string strpath;

	if (StarTag == 23)
	{
		for (int i = 0; i<m; i++)//星敏2和3数据
		{
			UTC[i] = StarDat.at(i).StarB.UTC;
			StarX[i].Q1 = StarDat.at(i).StarB.Q1; StarX[i].Q2 = StarDat.at(i).StarB.Q2; StarX[i].Q3 = StarDat.at(i).StarB.Q3, StarX[i].Q0 = StarDat.at(i).StarB.Q0;
			StarY[i].UTC = StarDat.at(i).StarC.UTC;
			StarY[i].Q1 = StarDat.at(i).StarC.Q1; StarY[i].Q2 = StarDat.at(i).StarC.Q2; StarY[i].Q3 = StarDat.at(i).StarC.Q3, StarY[i].Q0 = StarDat.at(i).StarC.Q0;
		}
		mBase.QuatInterpolation(StarY, m, UTC, m, StarYi);
		strpath = workpath + "Star23Angle.txt";
	}
	else if (StarTag == 12)
	{
		for (int i = 0; i<m; i++)//星敏1和2数据
		{
			UTC[i] = StarDat.at(i).StarA.UTC;
			StarX[i].Q1 = StarDat.at(i).StarA.Q1; StarX[i].Q2 = StarDat.at(i).StarA.Q2; StarX[i].Q3 = StarDat.at(i).StarA.Q3, StarX[i].Q0 = StarDat.at(i).StarA.Q0;
			StarY[i].UTC = StarDat.at(i).StarB.UTC;
			StarY[i].Q1 = StarDat.at(i).StarB.Q1; StarY[i].Q2 = StarDat.at(i).StarB.Q2; StarY[i].Q3 = StarDat.at(i).StarB.Q3, StarY[i].Q0 = StarDat.at(i).StarB.Q0;
		}
		mBase.QuatInterpolation(StarY, m, UTC, m, StarYi);
		strpath = workpath + "Star12Angle.txt";
	}
	else if (StarTag == 13)
	{
		for (int i = 0; i<m; i++)//星敏1和3数据
		{
			UTC[i] = StarDat.at(i).StarA.UTC;
			StarX[i].Q1 = StarDat.at(i).StarA.Q1; StarX[i].Q2 = StarDat.at(i).StarA.Q2; StarX[i].Q3 = StarDat.at(i).StarA.Q3, StarX[i].Q0 = StarDat.at(i).StarA.Q0;
			StarY[i].UTC = StarDat.at(i).StarC.UTC;
			StarY[i].Q1 = StarDat.at(i).StarC.Q1; StarY[i].Q2 = StarDat.at(i).StarC.Q2; StarY[i].Q3 = StarDat.at(i).StarC.Q3, StarY[i].Q0 = StarDat.at(i).StarC.Q0;
		}
		mBase.QuatInterpolation(StarY, m, UTC, m, StarYi);
		strpath = workpath + "Star13Angle.txt";
	}

	FILE *fpres = fopen(strpath.c_str(), "w");
	fprintf(fpres, "星敏%d定姿\n", StarTag);
	double mz[3] = { 0,0,1 }, RA[9], RB[9], za[3], zb[3], Angle;
	for (int i = 0; i<m; i++)
	{
		mBase.quat2matrix(StarX[i].Q1, StarX[i].Q2, StarX[i].Q3, StarX[i].Q0, RA);
		mBase.quat2matrix(StarYi[i].Q1, StarYi[i].Q2, StarYi[i].Q3, StarYi[i].Q0, RB);//Crj
		mBase.invers_matrix(RA, 3);
		mBase.invers_matrix(RB, 3);//Cjr
		mBase.Multi(RA, mz, za, 3, 3, 1);
		mBase.Multi(RB, mz, zb, 3, 3, 1);//星敏光轴在惯性系中的坐标值
		Angle = acos((za[0] * zb[0] + za[1] * zb[1] + za[2] * zb[2]) / sqrt(za[0] * za[0] + za[1] * za[1] + za[2] * za[2]) / sqrt(zb[0] * zb[0] + zb[1] * zb[1] + zb[2] * zb[2])) / PI * 180;
		fprintf(fpres, "%.9f\t%.9f\n", UTC[i], Angle);
	}
}

//////////////////////////////////////////////////////////////////////////
//功能：读取APS星敏星图识别结果
//输入：IDpath：识别结果文件路径
//输出：APS对应四元数
//注意：只用到了星敏A
//日期：2016.12.05
//////////////////////////////////////////////////////////////////////////
void ParseSTG::ReadStarID(string IDpath, vector<STGData>&APSQ)
{
	FILE *fp;
	fp = fopen(IDpath.c_str(), "r");
	int i, m;
	fscanf(fp, "%d", &m);//星图识别四元数个数 2Hz
	STGData APStemp;
	for (i = 0; i < m; i++)
	{
		fscanf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\t%*lf\t%*lf\n", &APStemp.StarA.UTC, &APStemp.StarA.Q0,
			&APStemp.StarA.Q1, &APStemp.StarA.Q2, &APStemp.StarA.Q3);
		APSQ.push_back(APStemp);
	}
}

//////////////////////////////////////////////////////////////////////////
//功能：读取STG提取出的姿态数据STA
//输入：STA数据路径
//输出：读取的STA数据容器
//注意：
//日期：2016.12.08
//////////////////////////////////////////////////////////////////////////
void ParseSTG::ReadSTAtxt(string STApath, vector<STGData>&STAdat)
{
	FILE *fp;
	fp = fopen(STApath.c_str(), "r");
	int i, m;
	STGData STAtemp, STAtemp2;
	//fscanf(fp,"%*s\t%*s\t\n%*s\t%*s\t\n%d\n",&m);//跳过前两行读取第三行
	fscanf(fp, "%*s\t%*s\t\n%*s\t%*s\t\n%d\n%*s\n", &m);//跳过前两行读取第三行，顺便跳过第四行
	fscanf(fp, "%*s\t%lf\t%*d\t%lf\t%lf\t%lf\t%lf\t%*d\t%lf\t%lf\t%lf\t%*d\t%lf\t%*d\t%lf\t%lf\t%lf\t%*d\n",
		&STAtemp2.StarA.UTC, &STAtemp2.StarA.Q1, &STAtemp2.StarA.Q2, &STAtemp2.StarA.Q3,
		&STAtemp2.StarB.UTC, &STAtemp2.StarB.Q1, &STAtemp2.StarB.Q2, &STAtemp2.StarB.Q3,
		&STAtemp2.StarC.UTC, &STAtemp2.StarC.Q1, &STAtemp2.StarC.Q2, &STAtemp2.StarC.Q3);
	for (i = 0; i < m; i++)
	{
		fscanf(fp, "%*s\t%lf\t%*d\t%lf\t%lf\t%lf\t%lf\t%*d\t%lf\t%lf\t%lf\t%*d\t%lf\t%*d\t%lf\t%lf\t%lf\t%*d\n",
			&STAtemp.StarA.UTC, &STAtemp.StarA.Q1, &STAtemp.StarA.Q2, &STAtemp.StarA.Q3,
			&STAtemp.StarB.UTC, &STAtemp.StarB.Q1, &STAtemp.StarB.Q2, &STAtemp.StarB.Q3,
			&STAtemp.StarC.UTC, &STAtemp.StarC.Q1, &STAtemp.StarC.Q2, &STAtemp.StarC.Q3);
		if (STAtemp.StarA.UTC < STAtemp2.StarA.UTC)
		{
			STAtemp.StarA.UTC += 1;
		}
		STAtemp2.StarA.UTC = STAtemp.StarA.UTC;
		if (STAtemp.StarB.UTC < STAtemp2.StarB.UTC)
		{
			STAtemp.StarB.UTC -= 1;
		}
		STAtemp2.StarB.UTC = STAtemp.StarB.UTC;
		if (STAtemp.StarC.UTC < STAtemp2.StarC.UTC)
		{
			STAtemp.StarC.UTC -= 1;
		}
		STAtemp2.StarC.UTC = STAtemp.StarC.UTC;
		STAtemp.StarA.Q0 = sqrt(1 - pow(STAtemp.StarA.Q1, 2) - pow(STAtemp.StarA.Q2, 2) - pow(STAtemp.StarA.Q3, 2));
		STAtemp.StarB.Q0 = sqrt(1 - pow(STAtemp.StarB.Q1, 2) - pow(STAtemp.StarB.Q2, 2) - pow(STAtemp.StarB.Q3, 2));
		STAtemp.StarC.Q0 = sqrt(1 - pow(STAtemp.StarC.Q1, 2) - pow(STAtemp.StarC.Q2, 2) - pow(STAtemp.StarC.Q3, 2));
		STAdat.push_back(STAtemp);
	}
}


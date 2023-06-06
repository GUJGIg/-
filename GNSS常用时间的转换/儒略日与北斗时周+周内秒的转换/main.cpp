#include <iostream>
#include <math.h>
using namespace std;
typedef struct tagTOD
{
	long sn;  //��������������
	double tos;//������С������
}TOD;
typedef TOD *PTOD;
typedef struct
{
	long day; //��������
	TOD tod;  //һ���ڵ�����
}JULIANDAY;//������
typedef JULIANDAY *PJULIANDAY;
typedef struct tagTOW
{
	long sn;//����������
	double tos;//��С������
}TOW;
typedef TOW *PTOW;
typedef struct tagBDSTIME
{
	int wn; //����
	TOW second;
}BDSTIME;//GPSʱ
typedef BDSTIME *PBDSTIME;
void JulianDayToBDSTime(PJULIANDAY pjd, PBDSTIME pbt)//�����յ�GPSʱ��ת��
{
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	pbt->wn = int((x - 2453736.5) / 7);
	pbt->second.sn = int(((pjd->day - 2453736) % 7 + (pjd->tod.sn / (60.0*60.0 * 24) - 0.5)) * 86400);
	pbt->second.tos = pjd->tod.tos;
	if(pbt->second.sn<0)
    {
        pbt->second.sn=pbt->second.sn+1;
    }
}
void BDSTimeToJulianDay(PBDSTIME pbt, PJULIANDAY pjd)//GPSʱ�������յ�ת��
{
	pjd->day = int(pbt->wn * 7 + double(pbt->second.sn) / 86400.0 + 2453736.5);
	pjd->tod.sn = (pbt->second.sn + 43200) % 86400;
	pjd->tod.tos = pbt->second.tos;
	cout << "BDSʱ�������յ�ת��:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
}
int main()
{
	PJULIANDAY pjd = new JULIANDAY;
	PBDSTIME pbt = new BDSTIME;
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	if(x >= 2453736.5)
    {
        JulianDayToBDSTime(pjd, pbt);//������->GPSʱ��ת��
	cout << "��������BDSʱ��ת��:";
	cout << pbt->wn << " �� " << pbt->second.sn << " ������ " << pbt->second.tos << "С����" << endl;
	cout << endl;
	BDSTimeToJulianDay(pbt, pjd);//GPSʱ->�����յ�ת��
    }
	else
    {
        printf("���������2453736.5��������");
    }
}

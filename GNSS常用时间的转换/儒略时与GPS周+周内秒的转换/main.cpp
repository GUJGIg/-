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
typedef struct tagGPSTIME
{
	int wn; //����
	TOW second;
}GPSTIME;//GPSʱ
typedef GPSTIME *PGPSTIME;
void JulianDayToGPSTime(PJULIANDAY pjd, PGPSTIME pgt)//�����յ�GPSʱ��ת��
{
	long double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	pgt->wn = int((x - 2444244.5) / 7);
	pgt->second.sn = int(((pjd->day - 2444244) % 7 + (pjd->tod.sn / (60.0*60.0 * 24) - 0.5)) * 86400);
	pgt->second.tos = pjd->tod.tos;
}
void GPSTimeToJulianDay(PGPSTIME pgt, PJULIANDAY pjd)//GPSʱ�������յ�ת��
{
	pjd->day = int(pgt->wn * 7 + double(pgt->second.sn) / 86400.0 + 2444244.5);
	pjd->tod.sn = (pgt->second.sn + 43200) % 86400;
	pjd->tod.tos = pgt->second.tos;
	cout << "GPSʱ�������յ�ת��:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
}
int main()
{
	PJULIANDAY pjd = new JULIANDAY;
	PGPSTIME pgt = new GPSTIME;
	printf("������������������+��������������+������С������\n");
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	if(x >= 2444244.5)
    {
        JulianDayToGPSTime(pjd, pgt);//������->GPSʱ��ת��
	cout << "��������GPSʱ��ת��:";
	cout << pgt->wn << " �� " << pgt->second.sn << " ������ " << pgt->second.tos << "С����" << endl;
	cout << endl;
	GPSTimeToJulianDay(pgt, pjd);//GPSʱ->�����յ�ת��
    }
	else
    {
        printf("���������2444244.5��������");
    }
}

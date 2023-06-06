#include <iostream>
#include <string>
#include <math.h>
using namespace std;
typedef struct tagGregorian
{
	int   year;
	int   month;
	int   day;
	int   hour;
	int   minute;
	double   second;
}Gregorian;//���������
typedef Gregorian *PGregorian;
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
void GregorianToJulianDay(PGregorian pct, PJULIANDAY pjd) //����������������յ�ת��
{
	double ut = pct->hour + pct->minute / 60.0 + pct->second / 3600.0;
	if (pct->month <= 2)
	{
		pct->year -= 1;
		pct->month += 12;
	}
	pjd->day = int(365.25*pct->year) + int(30.6001*(pct->month + 1)) + pct->day + int(ut / 24 + 1720981.5);
	pjd->tod.sn = ((pct->hour + 12) % 24) * 3600 + pct->minute * 60 + (int)pct->second;//�����������
	pjd->tod.tos = pct->second - (int)pct->second;//���С������
}
void JulianDayToGregorian(PJULIANDAY pjd, PGregorian pct)//�����յ������������ת��
{
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	int a = int(x + 0.5);
	int b = int(4 * (a + 68569) / 146097);
	int c = a + 68569 - int((b * 146097 + 3) / 4);
	int d = int(4000 * (c + 1) / 1461001);
	int e = c - int(1461 * d / 4) + 31;
	double f = int(80 * e / 2447);
	int g = int(f / 11);
	double h = (x + 0.5 - a) * 24 - 24*int((x + 0.5 - a) * 24 / 24);
	pct->hour = int(h);
	double j = (h - pct->hour)*60;
	pct->day = e - int(2447 * f / 80);
	pct->month = f + 2 - 12*g;
	pct->year = int(100 * (b - 49) + d + g);
	pct->minute = int(j);
	pct->second = (j - pct->minute)*60;
}
int main()
{
	PGregorian pct = new Gregorian;
	PJULIANDAY pjd = new JULIANDAY;
	printf("��������������ʱ��\n");
	cin>>pct->year>>pct->month>>pct->day>>pct->hour>>pct->minute>>pct->second;
	cout << "ת��֮ǰ�ĸ����������";
	cout << pct->year << "��" << pct->month << "��" << pct->day << "��" << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
	cout << endl;
	GregorianToJulianDay(pct, pjd);//����������������յ�ת��
	cout << "����������������յ�ת��:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
	JulianDayToGregorian(pjd, pct);//������������������ת��
	cout << "������������������ת��:";
	cout << pct->year << "��" << pct->month << "��" << pct->day << "��" << pct->hour << ":" << pct->minute << ":" << round(pct->second)<< endl;
	cout << endl;
}

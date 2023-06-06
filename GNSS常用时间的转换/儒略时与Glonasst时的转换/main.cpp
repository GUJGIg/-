#include <iostream>
using namespace std;
typedef struct tagTOD
{
	long sn;  //��������������
	double tos;//������С������
}TOD;
typedef TOD *PTOD;
typedef struct tagTOW
{
	long sn;//����������
	double tos;//��С������
}TOW;
typedef TOW *PTOW;
typedef struct tagGLONASSTTIME
{
	int   N4;
	int   NT;
	int   h;
	int   m;
	double   s;
}GLONASSTTIME;//GLONASSTʱ
typedef GLONASSTTIME *PGLONASSTTIME;
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
	int b = a + 1537;
	int c = int((b - 122.1) / 365.25);
	int d = int(365.25*c);
	int e = int((b - d) / 30.6001);
	pct->day = b - d - int(30.6001*e);
	pct->month = e - 1 - 12 * int(e / 14);
	pct->year = c - 4715 - int((7 + pct->month) / 10);
	pct->hour = (pjd->tod.sn / 3600 + 12) % 24;
	pct->minute = (pjd->tod.sn % 3600) / 60;
	pct->second = pjd->tod.sn % 60 + pjd->tod.tos;
}
void GLONASSTTIMETOJULIANDAY(PGLONASSTTIME pgnt, PJULIANDAY pjd)
{
    PGregorian pgro = new Gregorian;
    pgro->year = 1996 + 4*(pgnt->N4 - 1);
	pgro->month = 1;
	pgro->day = 1;
	pgro->hour = 0;
	pgro->minute = 0;
	pgro->second = 0;
	PJULIANDAY pjdo = new JULIANDAY;
    GregorianToJulianDay(pgro, pjdo);
    PJULIANDAY PJD = new JULIANDAY;
    PJD->day = pjdo->day + pgnt->NT - 1;
    PJD->tod.sn = ((pgnt->h + 12) % 24) * 3600 + pgnt->m * 60 + (int)pgnt->s;//�����������
	PJD->tod.tos = pgnt->s - (int)pgnt->s;//���С������
	cout << PJD->day << " �� " << PJD->tod.sn << " ������ " << PJD->tod.tos << "С����" << endl;
	cout << endl;
}
void JulianDayToGLONASSTTime(PJULIANDAY pjd, PGLONASSTTIME pgnt)//�����յ�GLONASSTʱ��ת��
{
    PGregorian pgro = new Gregorian;
	JulianDayToGregorian(pjd, pgro);
	pgnt->N4 = int((pgro->year - 1996)/4) + 1;
	PGregorian pGR = new Gregorian;
	PJULIANDAY pjdo = new JULIANDAY;
	pGR->year = 1996 + 4*(pgnt->N4 - 1);
	pGR->month = 1;
	pGR->day = 1;
	pGR->hour = 0;
	pGR->minute = 0;
	pGR->second = 0;
	GregorianToJulianDay(pGR, pjdo);
	pgnt->NT = pjd->day - pjdo->day + 1;
	pgnt->h = pgro->hour;
	pgnt->m = pgro->minute;
	pgnt->s = pgro->second;
	cout << pgnt->N4 << " : " << pgnt->NT << " : " << pgnt->h << " : " << pgnt->m << " : " << pgnt->s <<endl;
	cout << endl;
}
int main()
{
    PGLONASSTTIME pgnt = new GLONASSTTIME;
	PJULIANDAY pjd = new JULIANDAY;
	printf("������������������+��������������+������С������\n");
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	JulianDayToGLONASSTTime(pjd, pgnt);
	GLONASSTTIMETOJULIANDAY(pgnt, pjd);
}

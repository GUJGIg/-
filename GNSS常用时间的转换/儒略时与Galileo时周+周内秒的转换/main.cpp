#include <iostream>
using namespace std;
typedef struct tagTOW
{
	long sn;//����������
	double tos;//��С������
}TOW;
typedef TOW *PTOW;
typedef struct tagGLSTIME
{
	int wn; //����
	TOW second;//һ���ڵ�����
}GLSTIME;//GPSʱ
typedef GLSTIME *PGLSTIME;
typedef struct tagTOD
{
	long sn;  //��������������
	double tos;//������С������
}TOD;
typedef struct
{
	long day; //��������
	TOD tod;  //һ���ڵ�����
}JULIANDAY;//������
typedef JULIANDAY *PJULIANDAY;
void GLSTimeToJulianDay(PGLSTIME glt, PJULIANDAY pjd)
{
	pjd->day = int(glt->wn * 7 + double(glt->second.sn) / 86400.0 + 2451512.5);
	pjd->tod.sn = (glt->second.sn + 43200) % 86400;
	pjd->tod.tos = glt->second.tos;
	cout << "Galileoʱ�������յ�ת��:";
	cout << pjd->day << "  " << pjd->tod.sn << "  " << pjd->tod.tos << endl;
	cout << endl;
}
void JulianDayToGLSTime(PJULIANDAY pjd, PGLSTIME glt)
{
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	glt->wn = int((x - 2451512.5) / 7);
	glt->second.sn = int(((pjd->day - 2451512) % 7 + (pjd->tod.sn / (60.0*60.0 * 24) - 0.5)) * 86400);
	glt->second.tos = pjd->tod.tos;
	if(glt->second.sn<0)
    {
        glt->second.sn=glt->second.sn+604800;
    }
}
int main()
{
	PJULIANDAY pjd = new JULIANDAY;
	PGLSTIME glt = new GLSTIME;
	printf("������������������+��������������+������С������\n");
	cin>>pjd->day>>pjd->tod.sn>>pjd->tod.tos;
	double x = pjd->day + (pjd->tod.sn + pjd->tod.tos) / (60.0*60.0 * 24);
	if(x >= 2451512.5)
    {
        JulianDayToGLSTime(pjd, glt);//������->GPSʱ��ת��
	cout << "��������Galileoʱ��ת��:";
	cout << glt->wn << " �� " << glt->second.sn << " ������ " << glt->second.tos << "С����" << endl;
	cout << endl;
	GLSTimeToJulianDay(glt, pjd);
    }
	else
    {
        printf("���������2451512.5��������");
    }
}

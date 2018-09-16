#include <QStringList>
#include<QDebug>

typedef quint32 doubleword;
typedef quint8 byte;

#define pf(in) QString("0x%1").arg(in,0,16,QLatin1Char(' '))  //定义pf为输出16进制
#define LLO(x)  ((byte) ((doubleword)(x) & 255)) //最低8位
#define HLO(x)  ((byte) ((doubleword)(x) >> 8)) //次低8位
#define LHI(x)  ((byte) ((doubleword)(x) >> 16)) //次高8位
#define HHI(x)  ((byte) ((doubleword)(x) >> 24)) //最高8位

#define MAX(a,b) (((a)>(b))?(a):(b)) //求最大值
#define MIN(a,b) (((a)<(b))?(a):(b)) //求最小值

int main()
{
    int number=0x12345678;
    qint32 i;
    QList <byte> values;
    values.append(HHI(number));
    values.append(LHI(number));
    values.append(HLO(number));
    values.append(LLO(number));
    qDebug()<<"初始值为："<<pf(number)<<"=="<<number<<endl;
        qDebug()<< pf(HHI(number)) <<"=="<<dec<<HHI(number); //输出高16位中高8位，转换为10进制
        qDebug()<< pf(LHI(number)) <<"=="<<dec<<LHI(number); //输出高16位中低8位，转换为10进制
        qDebug()<< pf(HLO(number)) <<"=="<<dec<<HLO(number); //输出低16位中高8位，转换为10进制
        qDebug()<< pf(LLO(number)) <<"=="<<dec<<LLO(number)<<endl; //输出低16位中低8位，转换为10进制

        qDebug()<<"最高8位和次高8位最大值:"<<MAX(pf(HHI(number)) , pf(LHI(number)))<<"=="<<MAX(HHI(number) , LHI(number));
            qDebug()<<"次低8位和最低8位最小值:"<<MIN(pf(HLO(number)) , pf(LLO(number)))<<"=="<<MIN(HLO(number) , LLO(number))<<endl;

        i = (HHI(number) << 16)|LHI(number)|(HLO(number) << 24)|(LLO(number) << 8);

        qDebug() <<"重新组合后数值:"<<pf(i)<<"=="<<i<<endl;
        qDebug() <<"排序前:"<<values;

        std::sort(values.begin() , values.end() , std::greater<qint8>()); //从大到小排序
        qDebug() <<"排序后:"<<values;
        return 0;


}

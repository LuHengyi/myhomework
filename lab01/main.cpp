#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QString>

class student
{
public:
    int number;
    QString name;
    int sub1;
    int sub2;
};//定义一个学生信息的类

bool paixuname(const student& s1, const student & s2)
{
    return s1.name > s2.name;
}
bool paixusub1(const student& s1, const student & s2)
{
    return s1.sub1 > s2.sub1;
}

bool paixusub2(const student& s1, const student & s2)
{
    return s1.sub2 > s2.sub2;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    student st1;
    st1.number=1403130209;
    st1.name="鲁智深";
    st1.sub1=80;
    st1.sub2=72;
    student st2;
    st2.number=1403140101;
    st2.name="林冲";
    st2.sub1=82;
    st2.sub2=76;
    student st3;
    st3.number=1403140102;
    st3.name="宋江";
    st3.sub1=76;
    st3.sub2=85;
    student st4;
    st4.number=1403140103;
    st4.name="武松";
    st4.sub1=88;
    st4.sub2=80;
    //填写4个学生的信息
    QList <student> data;
    data<<st1<<st2<<st3<<st4;
    //定义一个QList，名称为data
    qDebug()<<"排序前：";
    qDebug()<<"学号\t\t"<<"姓名\t\t"<<"课程1"<<"  课程2";
    for(int i=0;i<4;i++)
    {
        qDebug()<<data.at(i).number<<"\t"<<data.at(i).name<<"\t"<<data.at(i).sub1<<"\t"<<data.at(i).sub2;
    }
    qDebug()<<endl;
    //输出原始的学生信息
    std::sort(data.begin(),data.end(),paixuname);
    qDebug()<<"按姓名排序：";
    qDebug()<<"学号\t\t"<<"姓名\t\t"<<"课程1"<<"  课程2";
    for(int i=0;i<4;i++)
    {
        qDebug()<<data.at(i).number<<"\t"<<data.at(i).name<<"\t"<<data.at(i).sub1<<"\t"<<data.at(i).sub2;
    }
    qDebug()<<endl;
    //比较学生姓名的大小并按从大到小顺序排序
    std::sort(data.begin(),data.end(),paixusub1);
    qDebug()<<"按课程一排序：";
    qDebug()<<"学号\t\t"<<"姓名\t\t"<<"课程1"<<"  课程2";
    for(int i=0;i<4;i++)
    {
        qDebug()<<data.at(i).number<<"\t"<<data.at(i).name<<"\t"<<data.at(i).sub1<<"\t"<<data.at(i).sub2;
    }
     qDebug()<<endl;
    //比较学生课程一成绩的大小并按从大到小顺序输出
    std::sort(data.begin(),data.end(),paixusub2);
    qDebug()<<"按课程二排序：";
    qDebug()<<"学号\t\t"<<"姓名\t\t"<<"课程1"<<"  课程2";
    for(int i=0;i<4;i++)
    {
        qDebug()<<data.at(i).number<<"\t"<<data.at(i).name<<"\t"<<data.at(i).sub1<<"\t"<<data.at(i).sub2;
    }

    //比较学生课程二成绩的大小并按从大到小顺序输出

    return a.exec();
}

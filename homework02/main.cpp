#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
//信息存储结构体,只用一个QStringList
typedef struct{
    QStringList stud;
} studData;
//重载 " << "符号,屏幕输出studData
QDebug operator << (QDebug d, const studData &data) {
    for(int i=0;i<data.stud.size();i++)
        d.noquote().nospace()<<QString(data.stud.at(i))<<"\t" ;
    return d;
}
// std::sort 比较规则 函数类,需传参,当前比较列位置
class myCmp {
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator() (const studData& d1,const studData& d2) const;
private:
    int currentColumn;
};
//重载比较规则,switch 从enum中匹配
bool myCmp::operator()(const studData &d1,const  studData &d2) const
{
    return d1.stud.at(currentColumn+1)>d2.stud.at(currentColumn+1);
}
//排序执行类
class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();//读文本
    void doSort();//文本内容排序
private:
    QString Filepath;
    QList<studData > data;
    studData listtitle;
    void printfile(quint8 lie);
};
//scoresorter构造函数
ScoreSorter::ScoreSorter(QString dataFile)
{
    this->Filepath=dataFile;
}
void ScoreSorter::readFile()
{
    QFile file(this->Filepath);   //只读方式打开文件
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    //读取表头并按空格 split '  '.
    QString titile(file.readLine());
    this->listtitle.stud = titile.split(" ", QString::SkipEmptyParts);
    // 除去末尾的'\n'
    if((this->listtitle.stud).last() == "\n") this->listtitle.stud.removeLast();
    // 按行读取
    studData perdata;
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        perdata.stud = str.split(" ", QString::SkipEmptyParts);
        //去末尾'\n'  如果是空 qlist()  则摒弃,否则添加到 data
        if((perdata.stud).last() == "\n") perdata.stud.removeLast();
        if(perdata.stud.size()==0) continue;
        this->data.append(perdata);
    }
    file.close();
}
//排序函数
void ScoreSorter::doSort()
{
    for(int i=1;i<this->listtitle.stud.size();i++)
    {
        //https://blog.csdn.net/maverick1990/article/details/37738601   声明比较规则类
        myCmp thiscmp(i-1);    //初始化排序规则对象
        std::sort(this->data.begin() , this->data.end() , thiscmp );  //排序
        qDebug()<<"排序后输出，当前排序第 "<<i+1 <<" 列：";
        qDebug() << '\t'<< (this->listtitle);    //qDebug重载输出
        for(int i=0;i<this->data.size();i++)  qDebug() << this->data.at(i);
        qDebug()<<"-----------------------------------------------------------------------\n";
        this->printfile(i+1);   //当前排序规则下的data 输出到文件
    }
}
//输出到文件
void ScoreSorter::printfile(quint8 lie)
{
    // 输出信息至文件中（读写、追加形式）
    QFile file("sorted_"+this->Filepath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);

    stream.setCodec("UTF-8");  //编码方式
    stream<<QString("排序后输出，当前排序第 ")<<lie <<QString(" 列：")<<"\r\n";
    stream<<"\t";  //输出表头
    for(int n=0;n<this->listtitle.stud.size();n++)
        stream<<this->listtitle.stud.at(n)<<"\t";
    stream<<"\r\n";
    for(int i=0;i<this->data.size();i++)
    {   //输出内容
        for(int n=0;n<this->listtitle.stud.size();n++)
            stream<<this->data.at(i).stud.at(n)<<"\t";
        stream<<"\r\n";
    }
    stream<<"----------------------------------------------------------------------------------------"<<"\r\n\r\n";
    file.close();
}


void printmymessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 输出信息至文件中（读写、追加形式）
    QFile file("Sorter_data.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    stream <<msg << endl;
    file.flush();
    file.close();
    QTextStream ts (stdout);
    ts << msg << endl;
    file.flush();
    file.close();

    // 自定义qDebug
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    qInstallMessageHandler(printmymessage);
    QString datafile = "data.txt";// 默认路径 .../Debug
    //  如果sorted_data.txt 已经存在  删除
    QFile f("sorted_"+datafile);
    if (f.exists())  f.remove();
    ScoreSorter s(datafile);   //read datafile
    s.readFile();     //读取data
    s.doSort();       //排序和导出
    return 0;
}

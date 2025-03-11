#include "QStrSvr.h"
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QCoreApplication>


extern "C" {
int showmsg(char *format,...) {Q_UNUSED(format); return 0;}
}

extern void settspan(gtime_t, gtime_t) {}
extern void settime(gtime_t) {}
QStrSvr::QStrSvr()
{

}

QStrSvr::~QStrSvr()
{
    int i=0;
    for (i=0;i<m_strsvr.nstr;i++) strclose(m_strsvr.stream+i);
    for (i=0;i<m_strsvr.nstr;i++) strclose(m_strsvr.strlog+i);
    m_strsvr.npb=0;
    if (m_strsvr.buff!=NULL) {
        free(m_strsvr.buff); m_strsvr.buff=NULL;
    }
    if (m_strsvr.pbuf!=NULL) {
        free(m_strsvr.pbuf); m_strsvr.pbuf=NULL;
    }
    printf("Release malloc memory.\n");
}

void QStrSvr::initVar(){
    QStringList fileTempList;
    QString stringTemp;
    QString fileAbs="";
    QString file=QCoreApplication::applicationFilePath();
    QFileInfo fi(file);
    m_IniFile = "";
    fileAbs = fi.absolutePath();
    fileTempList=fileAbs.split('/');
    for(int i = 0;i<(fileTempList.length()-1);i++){
        stringTemp = fileTempList.at(i);
        if(stringTemp.isEmpty())
            continue;
        m_IniFile = m_IniFile+"/"+stringTemp;
    }
    m_IniFile=m_IniFile+"/config"+"/strsvr.ini";


    //m_IniFile="/home/david/Documents/rtklib_b34_my/rtkStrSvrApli/strsvr.ini";
    m_StartTime.sec=m_StartTime.time=m_EndTime.sec=m_EndTime.time=0;
    m_Timer1.setInterval(5000);
    //m_Timer2.setInterval(100);
    FormCreate();
    /*QObject::connect(&m_Timer1,&QTimer::timeout,[=](){
        gtime_t time;
        double ep[6]={0};
        time=utc2gpst(timeget());
        time2epoch(time,ep);
        //qDebug()<<QString::number(ep[5]);
        if(ep[3]==23&&ep[4]==59&&ep[5]>55){
            strsvrstop(&m_strsvr,cmd);
            if (m_TraceLevel>0) traceclose();

            sleepms(10000);
            SvrStart();
        }

    });
    m_Timer1.start();*/

    //QTimer::singleShot(100,this,SLOT(FormCreate()));
}
//void QStrSvr::Timer1Timer(){


//}
/*void QStrSvr::Timer2Timer()
{
    unsigned char *msg=0;
    int len;

    lock(&m_strsvr.lock);

    len=m_strsvr.npb;
    if (len>0&&(msg=(unsigned char *)malloc(len))) {
        memcpy(msg,m_strsvr.pbuf,len);
        m_strsvr.npb=0;
    }
    unlock(&m_strsvr.lock);

    if (len<=0||!msg) return;


    free(msg);
}*/
void QStrSvr::FormCreate(){
    strsvrinit(&m_strsvr,3);
    LoadOpt();
    //m_Timer1.start();
    //m_Timer2.start();
    SvrStart();
    return ;

}
void QStrSvr::SvrStart(){
    strconv_t *conv[3]={0};
    static char str1[4][1024], str2[4][1024], str3[4][1024], str4[4][1024];
    //static char str1[MAXSTR][1024],str2[MAXSTR][1024];
    int itype[]={
        STR_SERIAL,STR_TCPCLI,STR_TCPSVR,STR_NTRIPCLI,STR_NTRIPCAS,STR_FILE,STR_FTP,STR_HTTP
    };
    int otype[]={
        STR_NONE,STR_SERIAL,STR_TCPCLI,STR_TCPSVR,STR_NTRIPSVR,STR_NTRIPCAS,STR_FILE,
    };
    int ip[]={0,1,1,1,1,2,3,3},strs[4]={0},opt[8]={0},n;
    //char *paths[4],filepath[1024],buff[1024];
    char buff[1024];
    //static char ccmds_periodic[4][1024]={0};
    char *paths[4], *logs[4] , *cmd[4], *cmds_periodic[4];
    //char cmd[1024];
    char *ant[3]={0},*rcv[3]={0},*p;

    for (int i=0;i<4;i++) {
        paths[i]=str1[i];
        logs [i]=str2[i];
        cmd[i] = str3[i];
        cmds_periodic[i]=str4[i];
    }

    if (m_TraceLevel>0) {
        QByteArray traceChar = m_traceFile.toLatin1();
        traceopen(traceChar.data());
        tracelevel(m_TraceLevel);
    }
    //for (int i=0;i<4;i++) paths[i]=str[i];

    strs[0]=itype[m_Input];
    strs[1]=otype[m_Output1];
    strs[2]=otype[m_Output2];
    strs[3]=otype[m_Output3];

    strcpy(paths[0],qPrintable(m_Paths[0][ip[m_Input]]));
    strcpy(paths[1],!m_Output1?"":qPrintable(m_Paths[1][ip[m_Output1-1]]));
    strcpy(paths[2],!m_Output2?"":qPrintable(m_Paths[2][ip[m_Output2-1]]));
    strcpy(paths[3],!m_Output3?"":qPrintable(m_Paths[3][ip[m_Output3-1]]));

    if (m_Input==0) {
        if (m_CmdEna[0]) strncpy(cmd[0],qPrintable(m_Cmds[0]),1024);
    }
    else if (m_Input==1||m_Input==3) {
        if (m_CmdEnaTcp[0]) strncpy(cmd[0],qPrintable(m_CmdsTcp[0]),1024);
    }
    for (int i=0;i<5;i++) {
        opt[i]=m_SvrOpt[i];
    }
    opt[5]=m_NmeaReq?m_SvrOpt[5]:0;
    opt[6]=m_FileSwapMargin;

//    for (int i=1;i<4;i++) {
//        if (strs[i]!=STR_FILE) continue;
//        strcpy(logs[0],paths[i]);
//        if (strstr(logs[0],"::A")) continue;
//        if ((p=strstr(logs[0],"::"))) *p='\0';
//        if (!(fp=fopen(logs[0],"r"))) continue;
//        fclose(fp);
//        if (QMessageBox::question(this,tr("Overwrite"),tr("File %1 exists. \nDo you want to overwrite?").arg(logs[0]))!=QMessageBox::Yes) return;
//    }
    strsetdir(qPrintable(m_LocalDirectory));
    strsetproxy(qPrintable(m_ProxyAddress));

    for (int i=0;i<3;i++) {
        if (!m_ConvEna[i]) continue;
        if (!(conv[i]=strconvnew(m_ConvInp[i],m_ConvOut[i],qPrintable(m_ConvMsg[i]),
                                 m_StaId,m_StaSel,qPrintable(m_ConvOpt[i])))) continue;
        strcpy(buff,qPrintable(m_AntType));
        for (p=strtok(buff,","),n=0;p&&n<3;p=strtok(NULL,",")) ant[n++]=p;
        strcpy(conv[i]->out.sta.antdes,ant[0]);
        strcpy(conv[i]->out.sta.antsno,ant[1]);
        conv[i]->out.sta.antsetup=atoi(ant[2]);
        strcpy(buff,qPrintable(m_RcvType));
        for (p=strtok(buff,","),n=0;p&&n<3;p=strtok(NULL,",")) rcv[n++]=p;
        strcpy(conv[i]->out.sta.rectype,rcv[0]);
        strcpy(conv[i]->out.sta.recver ,rcv[1]);
        strcpy(conv[i]->out.sta.recsno ,rcv[2]);
        matcpy(conv[i]->out.sta.pos,m_AntPos,3,1);
        matcpy(conv[i]->out.sta.del,m_AntOff,3,1);
    }
    // stream server start
    if (!strsvrstart(&m_strsvr,opt,strs,paths,logs,conv,cmd,cmds_periodic,m_AntPos)) return;

    m_StartTime=utc2gpst(timeget());


}
void QStrSvr::LoadOpt(void)
{
    QSettings settings(m_IniFile,QSettings::IniFormat);
    int optdef[]={10000,10000,1000,32768,10,0};

    m_Input  =settings.value("set/input",       0).toInt();
    m_Output1=settings.value("set/output1",     0).toInt();
    m_Output2=settings.value("set/output2",     0).toInt();
    m_Output3=settings.value("set/output3",     0).toInt();
    m_TraceLevel        =settings.value("set/tracelevel",  0).toInt();
    //m_TraceLevel        =5;
    m_NmeaReq           =settings.value("set/nmeareq",     0).toInt();
    m_FileSwapMargin    =settings.value("set/fswapmargin",30).toInt();
    m_StaId             =settings.value("set/staid"       ,0).toInt();
    m_StaSel            =settings.value("set/stasel"      ,0).toInt();
    m_AntType           =settings.value("set/anttype",    "").toString();
    m_RcvType           =settings.value("set/rcvtype",    "").toString();

    for (int i=0;i<6;i++) {
        m_SvrOpt[i]=settings.value(QString("set/svropt_%1").arg(i),optdef[i]).toInt();
    }
    for (int i=0;i<3;i++) {
        m_AntPos[i]=settings.value(QString("set/antpos_%1").arg(i),0.0).toDouble();
        m_AntOff[i]=settings.value(QString("set/antoff_%1").arg(i),0.0).toDouble();
    }
    for (int i=0;i<3;i++) {
        m_ConvEna[i]=settings.value(QString("conv/ena_%1").arg(i), 0).toInt();
        m_ConvInp[i]=settings.value(QString("conv/inp_%1").arg(i), 0).toInt();
        m_ConvOut[i]=settings.value(QString("conv/out_%1").arg(i), 0).toInt();
        m_ConvMsg[i]=settings.value(QString("conv/msg_%1").arg(i),"").toString();
        m_ConvOpt[i]=settings.value(QString("conv/opt_%1").arg(i),"").toString();
    }
    for (int i=0;i<2;i++) {
        m_CmdEna   [i]=settings.value(QString("serial/cmdena_%1").arg(i),1).toInt();
        m_CmdEnaTcp[i]=settings.value(QString("tcpip/cmdena_%1").arg(i),1).toInt();
    }
    for (int i=0;i<4;i++) for (int j=0;j<4;j++) {
        m_Paths[i][j]=settings.value(QString("path/path_%1_%2").arg(i).arg(j),"").toString();
    }
    for (int i=0;i<2;i++) {
        m_Cmds[i]=settings.value(QString("serial/cmd_%1").arg(i),"").toString();
        m_Cmds[i]=m_Cmds[i].replace("@@","\n");
    }
    for (int i=0;i<2;i++) {
        m_CmdsTcp[i]=settings.value(QString("tcpip/cmd_%1").arg(i),"").toString();
        m_CmdsTcp[i]=m_CmdsTcp[i].replace("@@","\n");
    }
//    for (int i=0;i<MAXHIST;i++) {
//        m_TcpHistory[i]=settings.value(QString("tcpopt/history%1").arg(i),"").toString();
//    }
//    for (int i=0;i<MAXHIST;i++) {
//        m_TcpMntpHist[i]=settings.value(QString("tcpopt/mntphist%1").arg(i),"").toString();
//    }
//    m_StaPosFile    =settings.value("stapos/staposfile",    "").toString();
//    m_ExeDirectory  =settings.value("dirs/exedirectory",  "").toString();
    m_LocalDirectory=settings.value("dirs/localdirectory","").toString();
    m_ProxyAddress  =settings.value("dirs/proxyaddress",  "").toString();
    m_traceFile     =settings.value("set/tracefile","").toString();

}

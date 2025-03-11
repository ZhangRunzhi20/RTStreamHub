#ifndef QSTRSVR_H
#define QSTRSVR_H
#include "rtklib.h"
#include <QTimer>
#include <QSettings>


#define MAXHIST		10
//#define TRACEFILE   "/home/david/Documents/rtklib_b34_my/rtkStrSvrApli/strsvr.trace"

class QStrSvr:public QObject
{

public:
    QStrSvr();
    ~QStrSvr();
private:
    QString m_IniFile;
    QString m_Paths[4][4],m_Cmds[2],m_CmdsTcp[2];
    QString m_TcpHistory[MAXHIST],m_TcpMntpHist[MAXHIST];
    QString m_StaPosFile,m_ExeDirectory,m_LocalDirectory,m_SwapInterval;
    QString m_ProxyAddress;
    QString m_ConvMsg[3], m_ConvOpt[3],m_AntType,m_RcvType;
    int m_ConvEna[3],m_ConvInp[3],m_ConvOut[3],m_StaId,m_StaSel;
    int m_TraceLevel,m_SvrOpt[6],m_CmdEna[2],m_CmdEnaTcp[2],m_NmeaReq,m_FileSwapMargin;
    double m_AntPos[3],m_AntOff[3];
    gtime_t m_StartTime,m_EndTime;

    QTimer m_Timer1,m_Timer2;

    strsvr_t m_strsvr;
    int m_Input,m_Output1,m_Output2,m_Output3;
    QString m_traceFile;
public:
    void initVar();
private:

    void LoadOpt(void);
    void SvrStart();
public slots:
    void FormCreate();
    //void Timer2Timer();
    void Timer1Timer();
};

#endif // QSTRSVR_H

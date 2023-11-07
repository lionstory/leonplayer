﻿/*
 * @file 	globalhelper.h
 * @date 	2023/08/21
 *
 * @author 	leon
 * @contact https://github.com/lionstory
 *
 * @brief 	公共接口
 * @note
 */
#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#pragma execution_character_set("utf-8")

#define MYLOG() \
    do { \
        if (true) qDebug() <<"File:"<< __FILE__ <<"    :"<< __LINE__  \
<< " Func: "<< __func__;} while(0)

#define LOGSTR(str) \
do { \
        if (true) qDebug() <<"File:"<< __FILE__ <<"    :"<< __LINE__  \
<< " Func: "<< __func__ << " " << str;} while(0)


enum ERROR_CODE
{
    NoError = 0,
    ErrorFileInvalid
};



#include <QString>
#include <QPushButton>
#include <QDebug>
#include <QStringList>

class GlobalHelper      // 工具类
{
public:
    GlobalHelper();
	/**
	 * 获取样式表
	 * 
	 * @param	strQssPath 样式表文件路径
	 * @return	样式表
	 * @note 	
	 */
    static QString GetQssStr(QString strQssPath);

	/**
	 * 为按钮设置显示图标
	 * 
	 * @param	btn 按钮指针
	 * @param	iconSize 图标大小
	 * @param	icon 图标字符
	 */
    static void SetIcon(QPushButton* btn, int iconSize, QChar icon);


    static void SavePlaylist(QStringList& playList);    // 保存播放列表
    static void GetPlaylist(QStringList& playList);     // 获取播放列表
    static void SavePlayVolume(double& nVolume);        // 保存音量
    static void GetPlayVolume(double& nVolume);         // 获取音量

    static QString GetAppVersion();
};

//必须加以下内容,否则编译不能通过,为了兼容C和C99标准
#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif

extern "C"{
#include "libavutil/avstring.h"
#include "libavutil/eval.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/dict.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/avassert.h"
#include "libavutil/frame.h"
#include "libavutil/time.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavcodec/avfft.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "SDL.h"
}




#define MAX_SLIDER_VALUE 65536



#endif // GLOBALHELPER_H

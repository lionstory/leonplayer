/*
 * @file 	customthread.h
 * @date 	2023/08/21
 *
 * @author 	leon
 * @contact https://github.com/lionstory
 *
 * @brief 	自定义线程抽象类
 * @note
 */


#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>

class CustomThread : public QThread
{
public:
    CustomThread();
    ~CustomThread();

	/**
	 * @brief	线程运行入口（纯虚函数）
	 */
    virtual void run() = 0;

	/**
	 * @brief	启动线程
	 * 
	 * @return	true 成功 false 失败
	 */
    bool StartThread();

	 /**
	 * @brief	停止线程
	 *
	 * @return	true 成功 false 失败
	 */
    bool StopThread();

protected:
    bool m_bRunning;    ///< 线程运行标志位
};

#endif // CUSTOMTHREAD_H

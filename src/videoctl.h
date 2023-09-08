﻿
#ifndef VIDEOCTL_H
#define VIDEOCTL_H

#include <QObject>
#include <QThread>
#include <QString>

#include "globalhelper.h"
#include "datactl.h"
#include "sonic.h"

#define FFP_PROP_FLOAT_PLAYBACK_RATE                    10003       // 设置播放速率
#define FFP_PROP_FLOAT_PLAYBACK_VOLUME                  10006

#define PLAYBACK_RATE_MIN           0.25     // 最慢
#define PLAYBACK_RATE_MAX           3.0     // 最快
#define PLAYBACK_RATE_SCALE         0.25    // 变速刻度
//单例模式
class VideoCtl : public QObject
{
    Q_OBJECT

public:
    //explicit VideoCtl(QObject *parent = nullptr);

    static VideoCtl* GetInstance();
    ~VideoCtl();
    /**
    * @brief	开始播放
    *
    * @param	strFileName 文件完整路径
    * @param	widPlayWid 播放窗口id
    * @return	true 成功 false 失败
    * @note
    */
    bool StartPlay(QString strFileName, WId widPlayWid);
    int audio_decode_frame(VideoState *is);
    void update_sample_display(VideoState *is, short *samples, int samples_size);
    void set_clock_at(Clock *c, double pts, int serial, double time);
    void sync_clock_to_slave(Clock *c, Clock *slave);

    float     ffp_get_property_float(int id, float default_value);
    void      ffp_set_property_float(int id, float value);
//    int64_t   ffp_get_property_int64(int id, int64_t default_value);
//    void      ffp_set_property_int64(int id, int64_t value);
signals:
    void SigSpeed(float speed);
    void SigPlayMsg(QString strMsg);//< 错误信息
    void SigFrameDimensionsChanged(int nFrameWidth, int nFrameHeight); //<视频宽高发生变化

    void SigVideoTotalSeconds(int nSeconds);
    void SigVideoPlaySeconds(int nSeconds);

    void SigVideoVolume(double dPercent);
    void SigPauseStat(bool bPaused);

    void SigStop();

    void SigStopFinished();//停止播放完成

    void SigStartPlay(QString strFileName);
public:
    void OnSpeed();
    void OnPlaySeek(double dPercent);
    void OnPlayVolume(double dPercent);
    void OnSeekForward();
    void OnSeekBack();
    void OnAddVolume();
    void OnSubVolume();
    void OnPause();
    void OnStop();

private:
    explicit VideoCtl(QObject *parent = nullptr);
    /**
     * @brief	初始化
     *
     * @return	true 成功 false 失败
     * @note
     */
    bool Init();

    /**
     * @brief	连接信号槽
     *
     * @return	true 成功 false 失败
     * @note
     */
    bool ConnectSignalSlots();

    int get_video_frame(VideoState *is, AVFrame *frame);
    int audio_thread(void *arg);
    int video_thread(void *arg);
    int subtitle_thread(void *arg);

    int synchronize_audio(VideoState *is, int nb_samples);

    int audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, struct AudioParams *audio_hw_params);
    int stream_component_open(VideoState *is, int stream_index);
    int stream_has_enough_packets(AVStream *st, int stream_id, PacketQueue *queue);
    int is_realtime(AVFormatContext *s);
    void ReadThread(VideoState *CurStream);
    void LoopThread(VideoState *CurStream);
    VideoState *stream_open(const char *filename);

    void stream_cycle_channel(VideoState *is, int codec_type);
    void refresh_loop_wait_event(VideoState *is, SDL_Event *event);
    void seek_chapter(VideoState *is, int incr);
    void video_refresh(void *opaque, double *remaining_time);
    int queue_picture(VideoState *is, AVFrame *src_frame, double pts, double duration, int64_t pos, int serial);
    //更新音量
    void UpdateVolume(int sign, double step);

    void video_display(VideoState *is);
    int video_open(VideoState *is);
    void do_exit(VideoState* &is);

    int realloc_texture(SDL_Texture **texture, Uint32 new_format, int new_width, int new_height, SDL_BlendMode blendmode, int init_texture);
    void calculate_display_rect(SDL_Rect *rect, int scr_xleft, int scr_ytop, int scr_width, int scr_height, int pic_width, int pic_height, AVRational pic_sar);
    int upload_texture(SDL_Texture *tex, AVFrame *frame, struct SwsContext **img_convert_ctx);
    void video_image_display(VideoState *is);
    void stream_component_close(VideoState *is, int stream_index);
    void stream_close(VideoState *is);
    double get_clock(Clock *c);

    void set_clock(Clock *c, double pts, int serial);
    void set_clock_speed(Clock *c, double speed);
    void init_clock(Clock *c, int *queue_serial);
    
    int get_master_sync_type(VideoState *is);
    double get_master_clock(VideoState *is);
    void check_external_clock_speed(VideoState *is);
    void stream_seek(VideoState *is, int64_t pos, int64_t rel);
    void stream_toggle_pause(VideoState *is);
    void toggle_pause(VideoState *is);
    void step_to_next_frame(VideoState *is);
    double compute_target_delay(double delay, VideoState *is);
    double vp_duration(VideoState *is, Frame *vp, Frame *nextvp);
    void update_video_pts(VideoState *is, double pts, int64_t pos, int serial);



public:

    void ffp_set_playback_rate(float rate);
    float ffp_get_playback_rate();

    int ffp_get_playback_rate_change();
    void ffp_set_playback_rate_change(int change);

    int64_t get_target_frequency();
    int     get_target_channels();
    int   is_normal_playback_rate();
private:

    static VideoCtl* m_pInstance; //< 单例指针

    bool m_bInited;	//< 初始化标志
    bool m_bPlayLoop; //刷新循环标志

    VideoState* m_CurStream;

    SDL_Window *window;
    SDL_Renderer *renderer;
    WId play_wid;//播放窗口


    /* options specified by the user */
    int screen_width;
    int screen_height;
    int startup_volume;

    //播放刷新循环线程
    std::thread m_tPlayLoopThread;

    int m_nFrameW;
    int m_nFrameH;



    float       pf_playback_rate;           // 播放速率
    int         pf_playback_rate_changed;   // 播放速率改变
public:
    // 变速相关
    sonicStreamStruct *audio_speed_convert;
};

#endif // VIDEOCTL_H

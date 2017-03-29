#ifndef __COM_VIDEO_IN_H__
#define __COM_VIDEO_IN_H__

#include "drv_tvd.h"

__s32 video_dev_init(__s32 video_source, __s32 tvd_channel,  __s32 enable_3d,__drv_TVD_system system);
//ev_index:0 for csi, 1 for tv in
//tvd_channel: tv0/tv1
__s32 com_video_in_open(__s32 dev_index, __s32 tvd_channel, __s32 enable_3d,__drv_TVD_system system);

__s32 com_video_in_close(void);

//tvd_channel: tv0/tv1
__s32 com_video_in_set_sel(__s32 tvd_channel);

///flag: 0: ȡ��������������ź�Ҳ����������  1:ֱ�����������������źţ� 2:���ź���������ʾ�����ź���ʾ����
__s32 com_video_set_blue_flag(__s32 flag);

///ץһ�����ݵ�U��
__s32 com_video_grap_data(void);


//0<=val<=255 Ĭ��128
__s32 com_video_set_contrast(__s32 val);

//0<=val<=255 Ĭ��32
__s32 com_video_set_bright(__s32 val);

//0<=val<=255 Ĭ��0
__s32 com_video_set_saturation(__s32 val);

//0<=val<=255 Ĭ��128
__s32 com_video_set_hue(__s32 val);

void com_video_set_smooth(__disp_video_smooth_t mode);

//����1�������źţ�����0�������ź�
__s32 com_video_get_status(void);

//����1����P�ƣ�����0����N��
__s32 com_video_get_format(void);

#endif//__COM_VIDEO_IN_H__

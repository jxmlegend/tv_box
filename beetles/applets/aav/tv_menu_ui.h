
#ifndef __tv_meun_UIPARA_H_
#define  __tv_meun_UIPARA_H_

#include "beetles_app.h"

//#define MOVIE_BRIGHT_MAX_ICON_RES_NUM 2

typedef struct  
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 res_id;	
	__s32 res_id1;
}tv_menu_rect_t;


typedef struct  
{
	__s32 res_id;
	__s32 res_id1;
	__s32 res_id2;	
	__s32 res_id3;	
}tv_menubg_rect_t;


typedef enum
{	
	tv_menu_icon_right=0,
	tv_menu_icon_contrast,
	tv_menu_icon_color,
	tv_menu_icon_input,
	tv_menu_icon_standard,
	tv_menu_icon_channel,
	tv_menu_icon_auto,
	tv_menu_icon_manual,	
	tv_menu_icon_fine_tuning,
	tv_menu_icon_num,
}tv_menu_icon_t;

typedef struct  
{	
	__s32 pipe;
	tv_menu_rect_t uipara_lyr;
	tv_menu_rect_t uipara_frm;
	tv_menu_rect_t uipara_bar[4];
	tv_menubg_rect_t uipara_menu_bg;			//  合作一张背景图
	tv_menu_rect_t uipara_Selet_item[4];		// 4 个小三角形
	tv_menu_rect_t uipara_page_icon[6];		// 两个page的图标
	tv_menu_rect_t uipara_bar_icon[4];
	tv_menu_rect_t uipara_icon[tv_menu_icon_num];	// 各小项的小图标
	tv_menu_rect_t uipara_bright_text[tv_menu_icon_num]; //  文字
	tv_menu_rect_t uipara_ch_text[3]; //  文字
	tv_menu_rect_t uipara_page_text[3]; //  文字
}tv_menu_uipara_t;

/*
extern __u32	tv_Pre_channel_id;
extern __u32	tv_channel_id;
extern __u32	tv_total_channel;
extern __u32	tv_bright;
extern __u32	tv_sourceInput;
extern __u32	tv_video_sys;
*/

/*
typedef struct  
{
	__s32 res_id[6];

}tv_menu_tvsys_t;

typedef struct  
{
	__s32 res_id[2];

}tv_menu_tvinput_t;
*/
tv_menu_uipara_t* tv_menu_get_uipara(__s32 rotate);

#endif


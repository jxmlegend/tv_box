#ifndef  _DRV_POWER_I_H_
#define  _DRV_POWER_I_H_

#include "epdk.h"


typedef struct
{
//	ES_FILE 				*tv_drv;
//	ES_FILE 				*audio_drv;
//	H_WIN       			h_deswin;	
	__u8 				thread_id;
	__u8				ubLocked;
	__u8				ub_PN_sys;		
	__u8				ubNorPicture;
	__u8				ubSearchStart;
	__u8				wait_timer;
	__u8				tv_barflag;
	__u8				tv_barflag_input;
	__u32				tv_barflag_inputval;	
	__u8				tv_menuID;	
	__u8				tv_muteflag;
	__u8				tv_voldata;		
	__u32				ucTestFre;				//读出的高频头数据
	__u32				ucSoundSys;
	__u32				cur_freq;
	__u32				manual_search_way;		//add by Kingvan
	__u32				auto_maual_mode;
	__u32				search_flag;/*1,searching,2,search over*/	
	__u32				total_channl;
	__u32				cur_channl;
	__u32				pre_channl;	
	__u32				bright;
	__u32				contrast;
	__u32				color;
	__u32				image_mode;
	__u8				image_mode_flag;
	__u32				lang;
	__u32				shemod;
	__u32				sourceInput;	
	__u32				channltable[200];
	__u8				SoundSystable[200];
	__u8				switch_counter;
}dsk_tv_rcv_t;


typedef struct
{
	ES_FILE 				*tv_drv;
	ES_FILE 				*audio_drv;	
	H_WIN       			h_tvwin;
	H_WIN       			h_menuwin;
	
}app_tv_data_t;


#define  TVMENU_NULL		0
#define  TVMENU_MAIN		1
#define  TVMENU_VOL			2
#define  TVMENU_NUM		3
#define  TVMENU_MUTE		4
#define  TVMENU_MODE		5

extern  dsk_tv_rcv_t *dsk_tv_rcv;
extern app_tv_data_t *app_tv_data;
#endif

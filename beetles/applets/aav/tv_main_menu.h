/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	:sub_menu.h
* By      	: Andy.zhang
* Func		: desk main thread
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#ifndef __SUB_MENU_H_
#define __SUB_MENU_H_

#include "app_home_i.h"

#define MAX_SUB_ITEM		4

typedef enum 
{
	MSG_SUB_OP_UP=GUI_MSG_USER_DEF,
	MSG_SUB_OP_DOWN,
	MSG_SUB_OP_ENTER,
}sub_msg_t;


//父窗口发往该窗口的消息
typedef enum
{
	tv_meun_scene_set_sta = GUI_MSG_+1

}tv_meun_scene_recv_msg_t;



#define SMENU_APP_SWITCH	0

typedef struct tag_smenu_uipara_pos
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 reserve;
}smenu_uipara_pos_t;

typedef struct tag_sub_menu
{
	H_WIN		layer;
	GUI_FONT 	*smenu_font;
	__s32			root_type;
	__u8	 		sub_menu_id;
	__u8	 		tv_channelflag;
   	 __s32           focus_item;
	 __s32 		tv_bright;
	 __s32 		tv_sourceInput;
	 __s32 		tv_video_sys;
	
}tv_menu_para_t;



//发往父窗口的消息
typedef enum
{
	tv_menu_scene_msg_timeout=0,
	tv_menu_scene_msg_brightset,
	tv_menu_scene_msg_num
}tv_menu_scene_msg_t;

/*
typedef struct  
{	
	H_WIN hparent;
	__s32 scene_id;
	__s32 item;
	
	//内部参数
	H_LYR hlyr;
	H_WIN hfrm;
	__u8  hide_timmer_id;	
}tv_menu_create_para_t;
*/



void * tv_sub_menu_win_create(H_WIN h_parent, tv_menu_para_t *para);
__s32 tv_menu_scene_delete(void* handle);

#endif

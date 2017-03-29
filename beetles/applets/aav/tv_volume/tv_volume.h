/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: volume.h
* By      	: Bayden.chen
* Func		:
* Version	: v1.0
* ============================================================================================================
* 2011-05-06  create this file
**************************************************************************************************************
*/

#ifndef __TV_VOLUME_H__
#define  __TV_VOLUME_H__

#include "beetles_app.h"
#include "tv_volume_ui.h"

//发往父窗口的消息
typedef enum
{
	tv_volume_scene_msg_timeout=0,
	tv_volume_scene_msg_volumeset,
	tv_volume_scene_msg_num
}tv_volume_scene_msg_t;

typedef struct  
{	
	H_WIN hparent;
	__s32 scene_id;
	__s32 min_val;
	__s32 max_val;
	__s32 cur_val;
}tv_volume_create_para_t;

void* tv_volume_scene_create(H_WIN h_parent, tv_volume_create_para_t *create_para);
__s32 tv_volume_scene_delete(void* handle);
__s32 tv_volume_scene_set_focus(void* handle);

#endif

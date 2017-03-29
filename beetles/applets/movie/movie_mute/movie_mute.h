/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: play_sta.h
* By      	: Bayden.chen
* Func		:
* Version	: v1.0
* ============================================================================================================
* 2011-05-06  create this file
**************************************************************************************************************
*/

#ifndef __MOVIE_MUTE_H__
#define  __MOVIE_MUTE_H__

#include "beetles_app.h"
//#include "movie_mute.h"

//发往父窗口的消息
typedef enum
{
//	movie_playsta_scene_msg_timeout=0,
//	movie_playsta_scene_msg_clicked,
//	movie_playsta_scene_msg_mute
	movie_mute_scene_msg_timeout=0,
	movie_mute_scene_msg_clicked,
	movie_mute_scene_msg_num
}movie_mute_scene_msg_t;

/*
typedef enum
{
	movie_playsta_play=0,
	movie_playsta_pause,
	movie_playsta_num
}movie_playsta_t;
*/

typedef struct  
{	
	H_WIN hparent;
	__s32 scene_id;
	__s32 min_val;
	__s32 max_val;
	__s32 cur_val;
}movie_mute_create_para_t;


typedef struct 
{
	//输入参数
	H_WIN hparent;	
	__s32 scene_id;
	__s32 max;
	__s32 min;
	__s32 value;
	__s32 type;

	//内部参数
	H_LYR hlyr;
	H_WIN hfrm;
	__u8  hide_timmer_id;	
}movie_mute_scene_t;

/*
void* movie_playsta_scene_create(movie_playsta_create_para_t* create_para);
__s32 movie_playsta_scene_delete(void* handle);
__s32 movie_playsta_scene_set_focus(void* handle);
__s32 movie_playsta_scene_get_hwnd(void* handle);
__s32 movie_playsta_scene_get_lyr_scn(RECT* rect);
*/

void* movie_mute_scene_create(movie_mute_create_para_t *create_para);
__s32 movie_mute_scene_delete(void* handle);
__s32 movie_mute_scene_set_focus(void* handle);
__s32 movie_mute_scene_get_hwnd(void* handle);
__s32 movie_mute_scene_get_lyr_scn(RECT* rect);

#endif


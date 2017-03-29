
/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: volume_ui.h
* By      	: Bayden.chen
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011-05-05  Bayden.chen  create this file
**************************************************************************************************************
*/

#ifndef __TV_VOLUME_UIPARA_H_
#define  __TV_VOLUME_UIPARA_H_

#include "beetles_app.h"

#define TV_VOLUME_MAX_ICON_RES_NUM 2

typedef struct  
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 res_id[TV_VOLUME_MAX_ICON_RES_NUM];
	HTHEME res_hdl[TV_VOLUME_MAX_ICON_RES_NUM];
}tv_volume_rect_t;

typedef enum
{	
	tv_volume_icon_lvolume=0,
	tv_volume_icon_rvolume,
	tv_volume_icon_prog_bg,
	tv_volume_icon_prog_cursor,	
	tv_volume_icon_num
}tv_volume_icon_t;

typedef struct  
{	
	__s32 pipe;
	tv_volume_rect_t uipara_lyr;
	tv_volume_rect_t uipara_frm;
	tv_volume_rect_t uipara_volume_bg;
	tv_volume_rect_t uipara_icon[tv_volume_icon_num];
	tv_volume_rect_t uipara_volume_text;
}tv_volume_uipara_t;

tv_volume_uipara_t* tv_volume_get_uipara(__s32 rotate);

#endif

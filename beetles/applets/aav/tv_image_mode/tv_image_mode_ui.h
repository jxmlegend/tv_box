
/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: playsta_ui.h
* By      	: Bayden.chen
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011-05-05  Bayden.chen  create this file
**************************************************************************************************************
*/

#ifndef __TV_IMAGE_MODE_UIPARA_H_
#define  __TV_IMAGE_MODE_UIPARA_H_

#include "beetles_app.h"

typedef struct  
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 res_id;
	HTHEME res_hdl;
}tv_image_mode_rect_t;

typedef struct  
{	
	__s32				 pipe;
	tv_image_mode_rect_t uipara_lyr;
	tv_image_mode_rect_t uipara_frm;
	tv_image_mode_rect_t uipara_mute;
	tv_image_mode_rect_t uipara_icon;
	tv_image_mode_rect_t uipara_mode[4]; //  ÎÄ×Ö
}tv_image_mode_uipara_t;

tv_image_mode_uipara_t* tv_image_mode_get_uipara(__s32 rotate);

#endif

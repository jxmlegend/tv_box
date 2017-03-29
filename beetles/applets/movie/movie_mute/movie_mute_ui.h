
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

#ifndef __MOVIE_MUTE_UIPARA_H_
#define  __MOVIE_MUTE_UIPARA_H_

#include "beetles_app.h"

#define MOVIE_MUTE_MAX_ICON_RES_NUM 2

typedef struct  
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 res_id[MOVIE_MUTE_MAX_ICON_RES_NUM];
	HTHEME res_hdl[MOVIE_MUTE_MAX_ICON_RES_NUM];
}movie_mute_rect_t;


typedef struct  
{	
	__s32				 pipe;
	movie_mute_rect_t uipara_lyr;
	movie_mute_rect_t uipara_frm;
	movie_mute_rect_t uipara_mute;
	movie_mute_rect_t uipara_icon;
}movie_mute_uipara_t;

movie_mute_uipara_t* movie_mute_get_uipara(__s32 rotate);

#endif

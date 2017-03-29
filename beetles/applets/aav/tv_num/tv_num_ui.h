
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

#ifndef __TV_NUM_UIPARA_H_
#define  __TV_NUM_UIPARA_H_

#include "beetles_app.h"

#define TV_NUM_MAX_ICON_RES_NUM 12

typedef struct  
{
	__s32 x;
	__s32 y;
	__s32 w;
	__s32 h;
	__s32 res_id[TV_NUM_MAX_ICON_RES_NUM];
	HTHEME res_hdl[TV_NUM_MAX_ICON_RES_NUM];
}tv_num_rect_t;


typedef struct  
{	
	__s32				 pipe;
	tv_num_rect_t uipara_lyr;
	tv_num_rect_t uipara_frm;
	tv_num_rect_t uipara_num0;
	tv_num_rect_t uipara_num1;
	tv_num_rect_t uipara_num2;
	tv_num_rect_t uipara_icon;
}tv_num_uipara_t;

tv_num_uipara_t* tv_num_get_uipara(__s32 rotate);

#endif

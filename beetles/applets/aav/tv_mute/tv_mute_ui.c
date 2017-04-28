
/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: playsta_ui.c
* By      	: Bayden.chen
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011-05-05  Bayden.chen  create this file
**************************************************************************************************************
*/

#include "tv_mute_ui.h"

static tv_mute_uipara_t uipara_720_576 = 
{
	1,
	{
		860, 80, 150, 28		
	},
	{
		0, 0, 150, 28		
	},	
	{
		64, 0, 28, 28		
	},
	{
		0, 0, 22, 22,		        
		ID_TV_TV_MUTE_BMP,
		ID_TV_TV_MUTE_BMP,
	}
};


tv_mute_uipara_t* tv_mute_get_uipara(__s32 rotate)
{
	__s32 			screen_width;
	__s32 			screen_height;
	
	/* get lcd size*/
	dsk_display_get_size(&screen_width, &screen_height);

	return &uipara_720_576;		
}

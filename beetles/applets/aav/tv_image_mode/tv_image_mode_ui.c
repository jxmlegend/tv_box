
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

#include "tv_image_mode_ui.h"

static tv_image_mode_uipara_t uipara_1024_768 = 
{
	1,
	{
		306, 614, 414, 58		
	},
	{
		0, 0, 414, 58		
	},	
	{
		0, 0, 414, 58		
	},
	{
		0, 0, 414, 58,		        
		ID_TV_TV_TEXT_BG_BMP,
	},
	{		
		{0, 0, 414, 58,STRING_TV_MODE_CUSTOM},	
		{0, 0, 414, 58,STRING_TV_MODE_BRIGHT},	
		{0, 0, 414, 58,STRING_TV_MODE_STANDARD},		
		{0, 0, 414, 58,STRING_TV_MODE_MILD},	
	}
};


tv_image_mode_uipara_t* tv_image_mode_get_uipara(__s32 rotate)
{
	__s32 			screen_width;
	__s32 			screen_height;
	
	/* get lcd size*/
	dsk_display_get_size(&screen_width, &screen_height);

	return &uipara_1024_768;		
}


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

#include "tv_num_ui.h"

static tv_num_uipara_t uipara_720_576 = 
{
	1,
	{
		530, 60, 150, 40		
	},
	{
		0, 0, 150, 40		
	},	
	{
		0, 0, 28, 40		
	},
	{
		32, 0, 28, 40		
	},
	{
		64, 0, 28, 40		
	},	
	{
		0, 0, 22, 22,		        
		ID_TV_TV_DIGITAL_0_BMP,
		ID_TV_TV_DIGITAL_1_BMP,
		ID_TV_TV_DIGITAL_2_BMP,
		ID_TV_TV_DIGITAL_3_BMP,
		ID_TV_TV_DIGITAL_4_BMP,
		ID_TV_TV_DIGITAL_5_BMP,
		ID_TV_TV_DIGITAL_6_BMP,
		ID_TV_TV_DIGITAL_7_BMP,
		ID_TV_TV_DIGITAL_8_BMP,
		ID_TV_TV_DIGITAL_9_BMP,
		ID_TV_TV_DIGITAL_LINE_BMP,
		ID_TV_AV_BMP,
	}
};


tv_num_uipara_t* tv_num_get_uipara(__s32 rotate)
{
	__s32 			screen_width;
	__s32 			screen_height;
	
	/* get lcd size*/
	dsk_display_get_size(&screen_width, &screen_height);
/*	switch(rotate)
	{
	case GUI_SCNDIR_NORMAL:
	case GUI_SCNDIR_ROTATE180:
		{
			if((screen_width == 400 )&&( screen_height == 240))
				return &uipara_400_240;	
			else if((screen_width == 720 )&&( screen_height == 576))
				return &uipara_720_576;	
			else if((screen_width == 720 )&&( screen_height == 480))
				return &uipara_720_480;			
			
		}		
	case GUI_SCNDIR_ROTATE90:
	case GUI_SCNDIR_ROTATE270:
		
		break;
	}	
*/	
	return &uipara_720_576;		
}


/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: spsc_prog_ui.c
* By      	: Bayden.chen
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011-05-05  Bayden.chen  create this file
**************************************************************************************************************
*/

#include "spsc_prog_ui.h"

static movie_spsc_prog_uipara_t uipara_400_240 = 
{	
	{
		0, 77, 364, 16
	},
	{
		{
			117, 109, 44, 26,
			ID_MOVIE_SPSC_PROG_PLAYSTA_PAUSE_BMP,
			ID_MOVIE_SPSC_PROG_PLAYSTA_PLAY_BMP,
		},
		{
			164, 117, 372, 8,
			ID_MOVIE_SPSC_PROG_BG_UF_BMP
		},
		{
			164, 117, 2, 8,
			ID_MOVIE_SPSC_PROG_CURSOR_UF_BMP
		},
		{
			164, 117, 2, 8,
			ID_MOVIE_SPSC_PROG_TIME_BG_BMP
		}
	},
	{
		{		
			40, 113, 16, 16					
		},
		{		
			70, 113, 16, 16					
		},
		{		
			100, 113, 16, 16					
		},
	},
	{
		{		
			58, 113, 8, 16					
		},
		{		
			88, 113, 8, 16					
		}
	},
	{
		{		
			550, 113, 16, 16					
		},
		{		
			580, 113, 16, 16					
		},
		{		
			610, 113, 16, 16					
		},
	},
	{
		{		
			568, 113, 8, 16					
		},
		{		
			598, 113, 8, 16					
		}
	},	
};

movie_spsc_prog_uipara_t* movie_spsc_prog_get_uipara(__s32 rotate)
{
	__s32 			screen_width;
	__s32 			screen_height;
	
	/* get lcd size*/
	dsk_display_get_size(&screen_width, &screen_height);
	switch(rotate)
	{
	case GUI_SCNDIR_NORMAL:
	case GUI_SCNDIR_ROTATE180:
		{
			if((screen_width == 400 )&&( screen_height == 240))
				return &uipara_400_240;			
			
		}		
	case GUI_SCNDIR_ROTATE90:
	case GUI_SCNDIR_ROTATE270:
		
		break;
	}	
	
	return &uipara_400_240;		
}

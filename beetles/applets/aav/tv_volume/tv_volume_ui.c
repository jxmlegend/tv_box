
/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: volume_ui.c
* By      	: Bayden.chen
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011-05-05  Bayden.chen  create this file
**************************************************************************************************************
*/

#include "Tv_volume_ui.h"

static tv_volume_uipara_t uipara_400_240 = 
{
	1,
	{
		(400-356)/2, 32, 356, 24
	},
	{
		0, 0, 356, 24
	},
	{
		0, 0, 356, 24,
		//ID_MOVIE_VOLUME_BG_BMP
	},
	{
		{
			29, 6, 15, 12,
			//ID_MOVIE_LVOLUME_F_BMP,
			//ID_MOVIE_LVOLUME_UF_BMP,
		},
		{
			314, 6, 18, 18,
			//ID_MOVIE_RVOLUME_F_BMP,
			//ID_MOVIE_RVOLUME_UF_BMP
		},
		{
			52, 10, 250, 4,
			//ID_MOVIE_VOLUME_PROG_BG_UF_BMP
		},
		{
			52, 10, 5, 4,
			//ID_MOVIE_VOLUME_PROG_CURSOR_UF_BMP
		}
	},
	{		
		336, 0, 16, 24					
	}
};

static tv_volume_uipara_t uipara_720_576 = 
{
	1,
	{
		35, 638, 954, 72
	},
	{
		0, 0, 954, 72
	},
	{
		0, 0, 954, 72,
		ID_COMMON_VOL_BG_BMP
	},
	{
		{
			19, 21, 38, 28,
			ID_COMMON_VOL_LEFT_BMP,
			ID_COMMON_VOL_MUTE_BMP,
		},
		{
			849, 21, 38, 28,
			ID_COMMON_VOL_RIGHT_BMP,
			ID_COMMON_VOL_MUTE_BMP
		},
		{
			101-35, 31, 778, 8,
			ID_COMMON_VOL_PROG_BG_BMP
		},
		{
			101-35, 31, 2, 8,
			ID_COMMON_VOL_CURSOR_MIDDLE_BMP
		}
	},
	{		
		932-35, 21, 22, 22,		//336			
		ID_COMMON_VOL_NUM_BG_BMP
	}
};

static tv_volume_uipara_t uipara_720_480 = 
{
	1,
	{
		(720-356)/2, 72, 356, 24
	},
	{
		0, 0, 356, 24
	},
	{
		0, 0, 356, 24,
		//ID_MOVIE_VOLUME_BG_BMP
	},
	{
		{
			29, 6, 15, 12,
			//ID_MOVIE_LVOLUME_F_BMP,
			//ID_MOVIE_LVOLUME_UF_BMP,
		},
		{
			314, 6, 18, 18,
			//ID_MOVIE_RVOLUME_F_BMP,
			//ID_MOVIE_RVOLUME_UF_BMP
		},
		{
			52, 10, 250, 4,
			//ID_MOVIE_VOLUME_PROG_BG_UF_BMP
		},
		{
			52, 10, 5, 4,
			//ID_MOVIE_VOLUME_PROG_CURSOR_UF_BMP
		}
	},
	{		
		336, 0, 16, 24					
	}
};


tv_volume_uipara_t* tv_volume_get_uipara(__s32 rotate)
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
			else if((screen_width == 720 )&&( screen_height == 576))
				return &uipara_720_576;	
			else if((screen_width == 720 )&&( screen_height == 480))
				return &uipara_720_480;	
			
		}		
	case GUI_SCNDIR_ROTATE90:
	case GUI_SCNDIR_ROTATE270:
		
		break;
	}	

	return &uipara_720_576;		
}

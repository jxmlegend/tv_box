
#include "TV_menu_ui.h"


/*
static tv_menu_uipara_t uipara_720_576 = 
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
		ID_MOVIE_BRIGHT_BG_BMP		
	},
	{
		{
			29, 6, 15, 12,
			ID_MOVIE_LBRIGHT_F_BMP,
			ID_MOVIE_LBRIGHT_UF_BMP,
		},
		{
			314, 6, 18, 18,
			ID_MOVIE_RBRIGHT_F_BMP,
			ID_MOVIE_RBRIGHT_UF_BMP
		},
		{
			52, 10, 250, 4,
			ID_MOVIE_BRIGHT_PROG_BG_UF_BMP
		},
		{
			52, 10, 5, 4,
			ID_MOVIE_BRIGHT_PROG_CURSOR_UF_BMP
		}
	},
	{		
		336, 0, 16, 24					
	}
};
*/

static tv_menu_uipara_t uipara_720_480 = 
{
	1,
	{
		115, 118, 720-115, 576-118
	},
	{
		0, 0, 360, 334
	},
	{
//		40, 280, 360, 30					//bar
/*	    	{446,312,5,4},								//进度条head
	    	{446,312,146,4},							//进度条body    	
	    	{446+5,312,5,4},							//进度条point,从head之后，因此加5   	
	    	{446+146-5,312,5,4},						//进度条tail		
*/	 
	    	{224,310,5,4},									//进度条head
	    	{224,310,255,4},								//进度条body    146
	    	{224+255-5,310,5,4},							//进度条tail
	    	{224+5,310,5,4},								//进度条point,从head之后，因此加5   	
	    		
	},	
	{
		ID_TV_TV_BG_BMP,
		ID_TV_COMMON_MENU_SHASHA_BMP,
		ID_TV_COMMON_MENU_SHASHA_BMP,	
		ID_TV_COMMON_MENU_SHASHA_BMP,
	},
	{
		{
			22, 18, 34, 36,
			ID_TV_COMMON_MENU_ALEFT_NORMAL_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_COMMON_MENU_ALEFT_FOCUS_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_COMMON_MENU_RIGHTWARD_NORMAL_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_COMMON_MENU_RIGHTWARD_FOCUS_BMP,	
		}
	},
	{
		{
			22, 18, 34, 36,
			ID_TV_TV_PAGE1_SET_NORMAL_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_PAGE1_SET_FOCUS_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_PAGE2_SET_NORMAL_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_PAGE2_SET_FOCUS_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_PAGE3_SET_NORMAL_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_PAGE3_SET_FOCUS_BMP,	
		}
	},	
	{
		{
			22, 18, 34, 36,
			ID_TV_PROCESS_BAR_HEAD_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_PROCESS_BAR_BODY_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_PROCESS_BAR_TAIL_BMP,	
		},
		{
			22, 18, 34, 36,
			ID_TV_PROCESS_BAR_POINT_BMP,	
		}
	},	
	{
		{
			22, 18, 34, 36,
			ID_TV_TV_BRIGHT_NORMAL_BMP,	
			ID_TV_TV_BRIGHT_FOCUS_BMP,
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_CONTRAST_NORMAL_BMP,	
			ID_TV_TV_CONTRAST_FOCUS_BMP,
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_COLOR_NORMAL_BMP,	
			ID_TV_TV_COLOR_FOCUS_BMP,
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_INPUT_NORMAL_BMP,	
			ID_TV_TV_INPUT_FOCUS_BMP,
		},		
		{
			22, 18, 34, 36,
			ID_TV_TV_STANDARD_NORMAL_BMP,	
			ID_TV_TV_STANDARD_FOCUS_BMP,			
		},	
		{
			22, 18, 34, 36,
			ID_TV_TV_CHANNEL_NORMAL_BMP,	
			ID_TV_TV_CHANNEL_FOCUS_BMP,
		},
		{
			22, 18, 34, 36,
			ID_TV_TV_AUTOSEARCH_NORMAL_BMP,	
			ID_TV_TV_AUTOSEARCH_FOCUS_BMP,
		},		
		{
			22, 18, 34, 36,
			ID_TV_TV_MANUALSEARCH_NORMAL_BMP,	
			ID_TV_TV_MANUALSEARCH_FOCUS_BMP,			
		},	
		{
			22, 18, 34, 36,
			ID_TV_TV_MINITRIM_NORMAL_BMP,	
			ID_TV_TV_MINITRIM_FOCUS_BMP,
		},		
	},
	{		
		{336, 0, 16, 24,STRING_TV_BRIGHT},	
		{336, 0, 16, 24,STRING_TV_CONTRAST},	
		{336, 0, 16, 24,STRING_TV_COLOR},	
		{336, 0, 16, 24,STRING_TV_INPUT_SOURCE},	
		{336, 0, 16, 24,STRING_TV_VIDEOSYS},	
		{336, 0, 16, 24,STRING_TV_CHANNELNU},	
		{336, 0, 16, 24,STRING_TV_AUTOSRH},	
		{336, 0, 16, 24,STRING_TV_MANUALSRH},	
		{336, 0, 16, 24,STRING_TV_FINETUNE},			
	},
	{		
		{336, 0, 16, 24,STRING_TV_CHANNLM},	
		{336, 0, 16, 24,STRING_TV_CHANNDOT},	
		{336, 0, 16, 24,STRING_TV_CH},			
	},
	{		
		{336, 0, 16, 24,STRING_TV_SET_IMG},	
		{336, 0, 16, 24,STRING_TV_SET_FUN},	
		{336, 0, 16, 24,STRING_TV_SET_FRE},			
	}		
};

tv_menu_uipara_t* tv_menu_get_uipara(__s32 rotate)
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
/*			if((screen_width == 400 )&&( screen_height == 240))
				return &uipara_400_240;	
			else if((screen_width == 720 )&&( screen_height == 576))
				return &uipara_720_576;	
			else if((screen_width == 720 )&&( screen_height == 480))
				return &uipara_720_480;			
*/			
			return &uipara_720_480;	
		}		
	case GUI_SCNDIR_ROTATE90:
	case GUI_SCNDIR_ROTATE270:
		
		break;
	}	
	
	return &uipara_720_480;		
}


/*
**********************************************************************************************************************
*                                                    ePDK
*                                    the Easy Portable/Player Develop Kits
*                                              LiveTouch Sub-System
*
*                                   (c) Copyright 2007-2009, Steven.ZGJ.China
*                                             All Rights Reserved
*
* Moudle  : ebook
* File    : ebook_uipara.c
*
* By      : Bayden.chen
* Version : v1.0
* Date    : 2009-12-25 14:53:05
**********************************************************************************************************************
*/

#ifndef __SETTING_PARA_H__
#define __SETTING_PARA_H__
#include "setting_para.h"

static tips_uipara_t setting_tips_uipara_800_480=
{
	{0,0},	//tips_bmp_pos
	{0,0,191,20},	//title pos 
	{15,28},	//tip_tsize_pos
	{15,50},	//tip_fsize_pos
	{61,72}	//tip_ok_bmp_pos

};

static tips_uipara_t setting_tips_uipara_400_240=
{
	{0,0},	//tips_bmp_pos
	{0,0,191,20},	//title pos 
	{15,28},	//tip_tsize_pos
	{15,50},	//tip_fsize_pos
	{61,72}	//tip_ok_bmp_pos

};

static set_general_para setting_general_uipara_800_480=
{    
		{8,668,1009,99},   //toolbar_rect
		{40,151},		  //bmp_big_setting_pos
		{24,705,24,22}, // bmp_prompt_rect;
		{59,705},		//  string_prompt_pos;
		{60,460,126,25},		//RECT  string_detail_prompt_rect;
		{60,500,126,25},		//RECT  string_detail_prompt_rect_ex;
		{
			{           //item0;
				{413,84},		// bmp_focus_pos;
				{413,84},		// bmp_unfocus_pos;
				{740,100},		//bmp_left_pos;
				{933,100},		//bmp_right_pos;
				{477,100},		//string_title_pos;
				{760,84,170,63} //string_content_rect;
			},
			{           //item1;
				{413,154},		// bmp_focus_pos;
				{413,154},		// bmp_unfocus_pos;
				{740,170},		//bmp_left_pos;
				{933,170},		//bmp_right_pos;
				{477,170},		//string_title_pos;
				{760,154,170,63} //string_content_rect;
			},
			{           //item2;
				{413,224},		// bmp_focus_pos;
				{413,224},		// bmp_unfocus_pos;
				{740,240},		//bmp_left_pos;
				{933,240},		//bmp_right_pos;
				{477,240},		//string_title_pos;
				{760,224,170,63} //string_content_rect;
			},
			{           //item3;
				{413,294},		// bmp_focus_pos;
				{413,294},		// bmp_unfocus_pos;
				{740,310},		//bmp_left_pos;
				{933,310},		//bmp_right_pos;
				{477,310},		//string_title_pos;
				{760,294,170,63} //string_content_rect;
			},
			
			{           //item4;
				{413,364},		// bmp_focus_pos;
				{413,364},		// bmp_unfocus_pos;
				{740,380},		//bmp_left_pos;
				{933,380},		//bmp_right_pos;
				{477,380},		//string_title_pos;
				{760,364,170,63} //string_content_rect;
			},
			{           //item5;
				{413,434},		// bmp_focus_pos;
				{413,434},		// bmp_unfocus_pos;
				{740,450},		//bmp_left_pos;
				{933,450},		//bmp_right_pos;
				{477,450},		//string_title_pos;
				{760,434,170,63} //string_content_rect;
			},
			{           //item6;
				{413,504},		// bmp_focus_pos;
				{413,504},		// bmp_unfocus_pos;
				{740,520},		//bmp_left_pos;
				{933,520},		//bmp_right_pos;
				{477,520},		//string_title_pos;
				{760,504,170,63} //string_content_rect;
			}
		}
};

static set_power_para setting_power_uipara_800_480=
{    
		{0,219,400,21},   //toolbar_rect
		{11,30},		  //bmp_big_setting_pos
		{10,219,30,16}, // bmp_prompt_rect;
		{45,217},		//  string_prompt_pos;
		{11,155,200,25},		//RECT  string_detail_prompt_rect;
		{11,180,200,25},		//RECT  string_detail_prompt_rect_ex;
		{
			{           //item0;
				{150,30},		// bmp_focus_pos;
				{150,30},		// bmp_unfocus_pos;
				{270,37},		//bmp_left_pos;
				{360,37},		//bmp_right_pos;
				{155,31},		//string_title_pos;
				{290,30,70,24} //string_content_rect;
			},
			{           //item1;
				{150,54},		// bmp_focus_pos;
				{150,54},		// bmp_unfocus_pos;
				{270,61},		//bmp_left_pos;
				{360,61},		//bmp_right_pos;
				{155,55},		//string_title_pos;
				{290,54,70,24} //string_content_rect;
			},
			{           //item2;
				{150,78},		// bmp_focus_pos;
				{150,78},		// bmp_unfocus_pos;
				{270,85},		//bmp_left_pos;
				{360,85},		//bmp_right_pos;
				{155,79},		//string_title_pos;
				{290,78,70,24} //string_content_rect;
			}
		}
};

static set_general_para setting_general_uipara_400_240=
{    
		{0,203,400,37},   //toolbar_rect
		{11,30},		  //bmp_big_setting_pos
		{10,219,30,16}, // bmp_prompt_rect;
		{45,217},		//  string_prompt_pos;
		{11,115,129,20},		//RECT  string_detail_prompt_rect;
		{11,135,129,20},		//RECT  string_detail_prompt_rect_ex;
		{
			{           //item0;
				{150,30},		// bmp_focus_pos;
				{150,30},		// bmp_unfocus_pos;
				{270,37},		//bmp_left_pos;
				{360,37},		//bmp_right_pos;
				{157,33},		//string_title_pos;
				{276,30,84,24} //string_content_rect;
			},
			{           //item1;
				{150,54},		// bmp_focus_pos;
				{150,54},		// bmp_unfocus_pos;
				{270,61},		//bmp_left_pos;
				{360,61},		//bmp_right_pos;
				{157,57},		//string_title_pos;
				{276,54,84,24} //string_content_rect;
			},
			{           //item2;
				{150,78},		// bmp_focus_pos;
				{150,78},		// bmp_unfocus_pos;
				{270,85},		//bmp_left_pos;
				{360,85},		//bmp_right_pos;
				{157,81},		//string_title_pos;
				{276,78,84,24} //string_content_rect;
			},
			{           //item3;
				{150,102},		// bmp_focus_pos;
				{150,102},		// bmp_unfocus_pos;
				{270,109},		//bmp_left_pos;
				{360,109},		//bmp_right_pos;
				{157,105},		//string_title_pos;
				{276,102,84,24} //string_content_rect;
			},
			
			{           //item4;
				{150,126},		// bmp_focus_pos;
				{150,126},		// bmp_unfocus_pos;
				{270,133},		//bmp_left_pos;
				{360,133},		//bmp_right_pos;
				{157,129},		//string_title_pos;
				{276,126,84,24} //string_content_rect;
			},
			{           //item5;
				{150,150},		// bmp_focus_pos;
				{150,150},		// bmp_unfocus_pos;
				{270,157},		//bmp_left_pos;
				{360,157},		//bmp_right_pos;
				{157,153},		//string_title_pos;
				{276,150,84,24} //string_content_rect;
			},
			{           //item6;
				{150,174},		// bmp_focus_pos;
				{150,174},		// bmp_unfocus_pos;
				{270,181},		//bmp_left_pos;
				{360,181},		//bmp_right_pos;
				{157,177},		//string_title_pos;
				{276,174,84,24} //string_content_rect;
			}
		}
};

static set_power_para setting_power_uipara_400_240=
{    
		{0,203,400,37},   //toolbar_rect
		{11,30},		  //bmp_big_setting_pos
		{10,219,30,16}, // bmp_prompt_rect;
		{45,217},		//  string_prompt_pos;
		{11,115,200,20},		//RECT  string_detail_prompt_rect;
		{11,135,200,20},		//RECT  string_detail_prompt_rect_ex;
		{
			{           //item0;
				{150,30},		// bmp_focus_pos;
				{150,30},		// bmp_unfocus_pos;
				{270,37},		//bmp_left_pos;
				{360,37},		//bmp_right_pos;
				{157,33},		//string_title_pos;
				{276,30,84,24} //string_content_rect;
			},
			{           //item1;
				{150,54},		// bmp_focus_pos;
				{150,54},		// bmp_unfocus_pos;
				{270,61},		//bmp_left_pos;
				{360,61},		//bmp_right_pos;
				{157,57},		//string_title_pos;
				{276,54,84,24} //string_content_rect;
			},
			{           //item2;
				{150,78},		// bmp_focus_pos;
				{150,78},		// bmp_unfocus_pos;
				{270,85},		//bmp_left_pos;
				{360,85},		//bmp_right_pos;
				{157,81},		//string_title_pos;
				{276,78,84,24} //string_content_rect;
			}
		}
};

 set_general_para* setting_get_general_para(SIZE screen_size)
{
	
	if((screen_size.width == 800 )&&( screen_size.height == 480))
		return &setting_general_uipara_800_480;
	else if((screen_size.width == 400 )&&( screen_size.height == 240))
		return &setting_general_uipara_400_240;
	else
	{
		__msg("ERR: NULL ui para..\n");
		return  &setting_general_uipara_800_480;	
	}		
}
set_power_para* setting_get_power_para(SIZE screen_size )
{
	__s32 			screen_width;
	__s32 			screen_height;
	
	if((screen_size.width == 800 )&&( screen_size.height == 480))
		return &setting_power_uipara_800_480;
	else if((screen_size.width == 400 )&&( screen_size.height == 240))
		return &setting_power_uipara_400_240;
	else
	{
		__msg("ERR: NULL ui para..\n");
		return  &setting_power_uipara_800_480;	
	}		
}

tips_uipara_t* setting_get_tips_para(SIZE screen_size)
{
	__s32			screen_width;
	__s32			screen_height;
		
	if((screen_size.width == 800 )&&( screen_size.height == 480))
		return &setting_tips_uipara_800_480;
	else if((screen_size.width == 400 )&&( screen_size.height == 240))
		return &setting_tips_uipara_400_240;
	else
	{
		__msg("ERR: NULL ui para..\n");
		return	&setting_tips_uipara_800_480;	
	}		
}


#endif;



/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: main_uipara.c
* By      	: Andy.zhang
* Func		: desk main thread
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/
#include "home_uipara.h"
#include "main_menu.h"
#include "sub_menu.h"

static home_uipara_t uipara_400_240 =
{
    {
        0, 366, 720, 480-366
 //		0, 266, 720, 480-266
    },
    {
       0, 220, 118, 123
    },
    720/5,//һ��5��
    5,
    5,//һ��5��
    66,//�����
    80,//���߶�
        
    118,//item width
    24,//item height
    118,//line width
    3,//line height
    118,//top width
    2,//top height
    118,//bottom width
    6//bottom height
};


home_uipara_t* home_get_ui_para(__s32 rotate)
{
    __s32           screen_width;
    __s32 			screen_height;
	
	/* get lcd size*/
	dsk_display_get_size(&screen_width, &screen_height);
    __msg("screen_width=%d,screen_height=%d\n", screen_width, screen_height);
	switch(rotate)
	{
	case GUI_SCNDIR_NORMAL:
	case GUI_SCNDIR_ROTATE180:
		{
//			if((screen_width == 720 )&&( screen_height == 480))		//400 240
				return &uipara_400_240;	
//			else if((screen_width == 480 )&&( screen_height == 272))
//				return &uipara_480_272;	
			
		}		
	case GUI_SCNDIR_ROTATE90:
	case GUI_SCNDIR_ROTATE270:
		
		break;
	}	

	return &uipara_400_240;		
}




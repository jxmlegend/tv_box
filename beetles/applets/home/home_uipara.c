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

static home_uipara_t uipara_1024_768 =
{
    {
        92, 494, 840, 768-494
 //		0, 266, 720, 480-266
    },
    {
       92, 324, 130, 170
    },
    140,//一屏5个
    6,
    6,//一屏5个
    130,//最大宽度
    130,//最大高度
        
    130,//item width
    30,//item height
    130,//line width
    2,//line height
    130,//top width
    6,//top height
    130,//bottom width
    6//bottom height
};

static home_uipara_t uipara_1280_768 =
{
    {
        97, 494, 1086, 768-494
 //		0, 266, 720, 480-266
    },
    {
       97, 324, 130, 170
    },
    181,//一屏5个
    6,
    6,//一屏5个
    130,//最大宽度
    130,//最大高度
        
    130,//item width
    30,//item height
    130,//line width
    2,//line height
    130,//top width
    6,//top height
    130,//bottom width
    6//bottom height
};

home_uipara_t* home_get_ui_para(__s32 rotate)
{
    __s32           screen_width;
    __s32 			screen_height;
	
	/* get lcd size*/
	dsk_display_get_size(&screen_width, &screen_height);
    __msg("screen_width=%d,screen_height=%d\n", screen_width, screen_height);
	if((screen_width == 1280 )&&( screen_height == 768))
		return &uipara_1280_768;	
	else
		return &uipara_1024_768;		
}




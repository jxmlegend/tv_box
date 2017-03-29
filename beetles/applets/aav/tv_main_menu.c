/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	:sub_menu.c
* By      	: Andy.zhang
* Func		: desk main thread
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/
//#include "common/common.h"
#include "Tv_main_menu.h"
#include "app_home_i.h"
#include "Tv_menu_ui.h"
#include "app_tv_i.h"

typedef struct 
{
	//输入参数
	H_WIN hparent;	
	__s8 scene_id;
	__u32 item;
	__bool  res_init;
	GUI_FONT *tvmenu_font;
	__s32 focus_txt_color;
	__s32 unfocus_txt_color;

	//内部参数
	H_LYR hlyr;
	H_WIN hfrm;
	__u8  hide_timmer_id;

	HTHEME bmp_bg[4];
	HTHEME icon_fs[18];		// 5个小图标
	HTHEME icon_selt[4];		// 两个三角形
	HTHEME icon_page[4];		// page 小图标
	HTHEME icon_bar[4];	
	char item_str[9][28];
	char item_ch_str[3][8];
	
}tv_menu_scene_t;



typedef struct 
{
	 __u32	item;
	 __u32	lastitem;
	 __u32	tv_page;
	 __u32	tv_sourceInput;
	 __u32	tv_video_sys;
	__u8 	serch_cnt;	 
	__u8 	serch_ing;
	
}tv_menu_data_t;

static tv_menu_data_t  tv_data;


static __s32 __tvmenu_install_hide_timmer(tv_menu_scene_t* scene_para)
{
	__u32	item_ree;
	if (!scene_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}	
	
	scene_para->hide_timmer_id = 0x14;

	if (!GUI_IsTimerInstalled(scene_para->hfrm, scene_para->hide_timmer_id))
	{
		item_ree = GUI_SetTimer(scene_para->hfrm, scene_para->hide_timmer_id
			, 400*2, NULL);//3秒		
			
	}
	else
	{
		__msg("timmer already install...\n");
		return EPDK_FAIL;
	}
	
	return EPDK_OK;
}

static __s32 __tvmenu_reset_hide_timmer(tv_menu_scene_t* scene_para)
{
	if (!scene_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}	
	
	if (GUI_IsTimerInstalled(scene_para->hfrm, scene_para->hide_timmer_id))
	{
		GUI_ResetTimer(scene_para->hfrm, scene_para->hide_timmer_id
			, 400*2, NULL);//3秒
	}			
	
	return EPDK_OK;
}

static __s32 __tvmenu_uninstall_hide_timmer(tv_menu_scene_t* scene_para)
{
	if (!scene_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}	
	
	if (GUI_IsTimerInstalled(scene_para->hfrm, scene_para->hide_timmer_id))
	{
		GUI_KillTimer(scene_para->hfrm, scene_para->hide_timmer_id);
	}			
	
	return EPDK_OK;
}




__s32  tvmeun_cmd2parent(H_WIN hwin, __s32 id, __s32 data2, __s32 reserved)
{
	H_WIN hparent;
	__gui_msg_t msg;
	
	hparent = GUI_WinGetParent(hwin);
	if (!hparent)
	{
		__err("hparent is null...\n");
		return EPDK_FAIL;
	}

	msg.h_deswin = hparent;
	msg.h_srcwin = hwin;
	msg.id = GUI_MSG_COMMAND;
	msg.dwAddData1 = MAKELONG(GUI_WinGetItemId(hwin), id);
	msg.dwAddData2 = data2;
	msg.dwReserved = reserved;
	
	GUI_SendNotifyMessage(&msg);
	
	return EPDK_OK;
}



/*
	资源id号的表
*/


static void tvmenu_init_res(tv_menu_scene_t *smenu_attr)
{
    	__u32 	i; 	

    	tv_menu_uipara_t* sub_ui_para;

    	if(EPDK_TRUE == smenu_attr->res_init)
    	{
        	return ;
    	}
    
    	sub_ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!sub_ui_para)
    	{
        	__err("sub_ui_para is null...\n");
        	return ;
    	}

    	smenu_attr->bmp_bg[0] = dsk_theme_open(sub_ui_para->uipara_menu_bg.res_id);
	smenu_attr->bmp_bg[1] = dsk_theme_open(sub_ui_para->uipara_menu_bg.res_id1);
    	smenu_attr->bmp_bg[2] = dsk_theme_open(sub_ui_para->uipara_menu_bg.res_id2);
    	smenu_attr->bmp_bg[3] = dsk_theme_open(sub_ui_para->uipara_menu_bg.res_id3);		
	
	smenu_attr->icon_fs[0] = dsk_theme_open(sub_ui_para->uipara_icon[0].res_id);
	smenu_attr->icon_fs[1] = dsk_theme_open(sub_ui_para->uipara_icon[0].res_id1);
	smenu_attr->icon_fs[2] = dsk_theme_open(sub_ui_para->uipara_icon[1].res_id);	
	smenu_attr->icon_fs[3] = dsk_theme_open(sub_ui_para->uipara_icon[1].res_id1);	
	smenu_attr->icon_fs[4] = dsk_theme_open(sub_ui_para->uipara_icon[2].res_id);	
	smenu_attr->icon_fs[5] = dsk_theme_open(sub_ui_para->uipara_icon[2].res_id1);
	smenu_attr->icon_fs[6] = dsk_theme_open(sub_ui_para->uipara_icon[3].res_id);	
	smenu_attr->icon_fs[7] = dsk_theme_open(sub_ui_para->uipara_icon[3].res_id1);	
	smenu_attr->icon_fs[8] = dsk_theme_open(sub_ui_para->uipara_icon[4].res_id);	
	smenu_attr->icon_fs[9] = dsk_theme_open(sub_ui_para->uipara_icon[4].res_id1);
	smenu_attr->icon_fs[10] = dsk_theme_open(sub_ui_para->uipara_icon[5].res_id);	
	smenu_attr->icon_fs[11] = dsk_theme_open(sub_ui_para->uipara_icon[5].res_id1);	
	smenu_attr->icon_fs[12] = dsk_theme_open(sub_ui_para->uipara_icon[6].res_id);	
	smenu_attr->icon_fs[13] = dsk_theme_open(sub_ui_para->uipara_icon[6].res_id1);
	smenu_attr->icon_fs[14] = dsk_theme_open(sub_ui_para->uipara_icon[7].res_id);	
	smenu_attr->icon_fs[15] = dsk_theme_open(sub_ui_para->uipara_icon[7].res_id1);	
	smenu_attr->icon_fs[16] = dsk_theme_open(sub_ui_para->uipara_icon[8].res_id);	
	smenu_attr->icon_fs[17] = dsk_theme_open(sub_ui_para->uipara_icon[8].res_id1);	

	smenu_attr->icon_selt[0] = dsk_theme_open(sub_ui_para->uipara_Selet_item[0].res_id);	
	smenu_attr->icon_selt[1] = dsk_theme_open(sub_ui_para->uipara_Selet_item[1].res_id);	
	smenu_attr->icon_selt[2] = dsk_theme_open(sub_ui_para->uipara_Selet_item[2].res_id);	
	smenu_attr->icon_selt[3] = dsk_theme_open(sub_ui_para->uipara_Selet_item[3].res_id);	

	smenu_attr->icon_page[0] = dsk_theme_open(sub_ui_para->uipara_page_icon[0].res_id);	
	smenu_attr->icon_page[1] = dsk_theme_open(sub_ui_para->uipara_page_icon[1].res_id);	
	smenu_attr->icon_page[2] = dsk_theme_open(sub_ui_para->uipara_page_icon[2].res_id);	
	smenu_attr->icon_page[3] = dsk_theme_open(sub_ui_para->uipara_page_icon[3].res_id);	

	smenu_attr->icon_bar[0] = dsk_theme_open(sub_ui_para->uipara_bar_icon[0].res_id);	
	smenu_attr->icon_bar[1] = dsk_theme_open(sub_ui_para->uipara_bar_icon[1].res_id);	
	smenu_attr->icon_bar[2] = dsk_theme_open(sub_ui_para->uipara_bar_icon[2].res_id);	
	smenu_attr->icon_bar[3] = dsk_theme_open(sub_ui_para->uipara_bar_icon[3].res_id);		
	

	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[0].res_id, smenu_attr->item_str[0], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[1].res_id, smenu_attr->item_str[1], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[2].res_id, smenu_attr->item_str[2], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[3].res_id, smenu_attr->item_str[3], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[4].res_id, smenu_attr->item_str[4], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[5].res_id, smenu_attr->item_str[5], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[6].res_id, smenu_attr->item_str[6], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[7].res_id, smenu_attr->item_str[7], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_bright_text[8].res_id, smenu_attr->item_str[8], GUI_TITLE_MAX); 

	dsk_langres_get_menu_text(sub_ui_para->uipara_ch_text[0].res_id, smenu_attr->item_ch_str[0], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_ch_text[1].res_id, smenu_attr->item_ch_str[1], GUI_TITLE_MAX); 
	dsk_langres_get_menu_text(sub_ui_para->uipara_ch_text[2].res_id, smenu_attr->item_ch_str[2], GUI_TITLE_MAX); 		
    	smenu_attr->res_init = EPDK_TRUE;

	return ;
}

/*
	释放资源
*/
static void tvmenu_uninit_res(tv_menu_scene_t *smenu_attr)
{
	__s32 i;

    	if(EPDK_FALSE == smenu_attr->res_init)
    	{
        	return ;
    	}
	
	dsk_theme_close(smenu_attr->bmp_bg[0]);
	dsk_theme_close(smenu_attr->bmp_bg[1]);
	dsk_theme_close(smenu_attr->bmp_bg[2]);
	dsk_theme_close(smenu_attr->bmp_bg[3]);

	dsk_theme_close(smenu_attr->icon_fs[0]);
	dsk_theme_close(smenu_attr->icon_fs[1]);
	dsk_theme_close(smenu_attr->icon_fs[2]);
	dsk_theme_close(smenu_attr->icon_fs[3]);
	dsk_theme_close(smenu_attr->icon_fs[4]);
	dsk_theme_close(smenu_attr->icon_fs[5]);
	dsk_theme_close(smenu_attr->icon_fs[6]);
	dsk_theme_close(smenu_attr->icon_fs[7]);
	dsk_theme_close(smenu_attr->icon_fs[8]);
	dsk_theme_close(smenu_attr->icon_fs[9]);

	dsk_theme_close(smenu_attr->icon_fs[10]);
	dsk_theme_close(smenu_attr->icon_fs[11]);
	dsk_theme_close(smenu_attr->icon_fs[12]);
	dsk_theme_close(smenu_attr->icon_fs[13]);
	dsk_theme_close(smenu_attr->icon_fs[14]);
	dsk_theme_close(smenu_attr->icon_fs[15]);
	dsk_theme_close(smenu_attr->icon_fs[16]);
	dsk_theme_close(smenu_attr->icon_fs[17]);

	
	dsk_theme_close(smenu_attr->icon_selt[0]);
	dsk_theme_close(smenu_attr->icon_selt[1]);
	dsk_theme_close(smenu_attr->icon_selt[2]);
	dsk_theme_close(smenu_attr->icon_selt[3]);

	dsk_theme_close(smenu_attr->icon_page[0]);
	dsk_theme_close(smenu_attr->icon_page[1]);
	dsk_theme_close(smenu_attr->icon_page[2]);
	dsk_theme_close(smenu_attr->icon_page[3]);	

	dsk_theme_close(smenu_attr->icon_bar[0]);
	dsk_theme_close(smenu_attr->icon_bar[1]);
	dsk_theme_close(smenu_attr->icon_bar[2]);
	dsk_theme_close(smenu_attr->icon_bar[3]);		
	
	smenu_attr->bmp_bg[0] = NULL;
	smenu_attr->bmp_bg[1] = NULL;
	smenu_attr->bmp_bg[2] = NULL;
	smenu_attr->bmp_bg[3] = NULL;
	smenu_attr->icon_fs[0] = NULL;
	smenu_attr->icon_fs[1] = NULL;
	smenu_attr->icon_fs[2] = NULL;
	smenu_attr->icon_fs[3] = NULL;	
	smenu_attr->icon_fs[4] = NULL;
	smenu_attr->icon_fs[5] = NULL;
	smenu_attr->icon_fs[6] = NULL;
	smenu_attr->icon_fs[7] = NULL;
	smenu_attr->icon_fs[8] = NULL;
	smenu_attr->icon_fs[9] = NULL;
	smenu_attr->icon_fs[10] = NULL;
	smenu_attr->icon_fs[11] = NULL;
	smenu_attr->icon_fs[12] = NULL;
	smenu_attr->icon_fs[13] = NULL;	
	smenu_attr->icon_fs[14] = NULL;
	smenu_attr->icon_fs[15] = NULL;
	smenu_attr->icon_fs[16] = NULL;
	smenu_attr->icon_fs[17] = NULL;
	
	smenu_attr->icon_selt[0] = NULL;	
	smenu_attr->icon_selt[1] = NULL;	
	smenu_attr->icon_selt[2] = NULL;	
	smenu_attr->icon_selt[3] = NULL;	

	smenu_attr->icon_page[0] = NULL;	
	smenu_attr->icon_page[1] = NULL;	
	smenu_attr->icon_page[2] = NULL;	
	smenu_attr->icon_page[3] = NULL;	

	smenu_attr->icon_bar[0] = NULL;	
	smenu_attr->icon_bar[1] = NULL;	
	smenu_attr->icon_bar[2] = NULL;	
	smenu_attr->icon_bar[3] = NULL;	
	
    	smenu_attr->res_init = EPDK_FALSE;
	
}



__s32 tv_menu_scene_delete(void* handle)
{
	tv_menu_scene_t* scene_para;

	scene_para = (tv_menu_scene_t*)handle;

//	__tvmenu_uninstall_hide_timmer(scene_para);
			
	__msg("scene_para->hfrm=%x\n", scene_para->hfrm);
	__msg("scene_para->hlyr=%x\n", scene_para->hlyr);
	
	if (NULL == handle)
	{
		__err("invalid para..\n");
		return EPDK_FAIL;
	}
	__here__;
	if (!scene_para->hfrm)
	{
		__err("invalid para..\n");
		return EPDK_FAIL;
	}
	GUI_FrmWinDelete(scene_para->hfrm);
	__here__;
	if (!scene_para->hlyr)
	{
		__err("invalid para..\n");
		return EPDK_FAIL;
	}
	GUI_LyrWinDelete(scene_para->hlyr);

	__here__;
//	eLIBs_memset(scene_para, 0, sizeof(tv_menu_scene_t));//防止重复释放
//	esMEMS_Bfree(scene_para, sizeof(tv_menu_scene_t));


	__msg("=============Delete TV_menu==============\n");
	
	return EPDK_OK;
}



/*
	paint

*/

#define  yoffset 	50

static __s32 tv_menu_paint_item(__gui_msg_t *msg,__s32 item,__s32 color)
{

	tv_menu_scene_t *smenu_attr;
	__s32 i;
	__s16 x, y;
	RECT rect;     
    	GUI_RECT gui_rect;  
    	tv_menu_uipara_t* ui_para;   
	char str_val[32]={0};
	
	
    	ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!ui_para)
    	{
        	__err("ui_para is null...\n");
        	return EPDK_FAIL;
    	}
		
	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    


        GUI_SetBkColor(0x00);
	 if(color>1)
	 	color = 1;
	 if(color==0)
	 	GUI_SetColor(GUI_WHITE);
	 else
	 	GUI_SetColor(GUI_YELLOW);


			gui_rect.x0 = 250;
		    	gui_rect.x1 = 320;
			gui_rect.y0 = 54*item+24;		//28
			gui_rect.y1 = gui_rect.y0+16;

		if(item>0)
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0 );
//	esKRNL_TimeDly(1);

	if(tv_data.tv_page==0)
	{
		switch (item)
		{
			case 1:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[0+color]), 202, 18+yoffset );	
					
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item-1].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);				
				break;
			case 2:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[2+color]), 202, 70+yoffset );
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item-1].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;
			case 3:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[4+color]), 202, 124+yoffset );
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item-1].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;
			case 4:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[6+color]), 202, 176+yoffset );
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item-1].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;
			case 5:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[8+color]), 202, 232+yoffset );	
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item-1].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;

			default:
				break;
		}
	}
	else
	{
		switch (item)
		{
			case 1:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[10+color]), 202, 18+yoffset );	
					
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item+4].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);				
				break;
			case 2:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[12+color]), 202, 70+yoffset );
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item+4].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;
			case 3:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[14+color]), 202, 124+yoffset );
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item+4].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;
			case 4:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_fs[16+color]), 202, 176+yoffset );
				dsk_langres_get_menu_text(ui_para->uipara_bright_text[item+4].res_id, smenu_attr->item_str[item-1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_str[item-1], gui_rect.x0 , gui_rect.y0);					
				break;
			case 5:
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0-60, gui_rect.y0-8 );				
				break;	
			default:
				break;
		}
	}
	
	return EPDK_OK;
}

static __s32 TVsys[] = 
{
	STRING_TV_SYS_AUTO,
	STRING_TV_SYS_PAL_DK,
	STRING_TV_SYS_PAL_I,
	STRING_TV_SYS_PAL_BG,
	STRING_TV_SYS_NTSC,
	STRING_TV_SYS_SECAM
};

static __s32 TVinput[] =
{
	STRING_TV_SOURCE_TV,
	STRING_TV_SOURCE_VIDEO	
};

static __s32 SysLang[] =
{
	STRING_TV_ENGLISH,
	STRING_TV_CHINESE	
};


extern void   uint2str( __u32 input, char * str );
static __s32 tv_menu_paint_protel(__gui_msg_t *msg,__s32 item,__s32 color)
{

	tv_menu_scene_t *smenu_attr;
	__s32 i;
	__s16 x, y,temp_color;
	RECT rect;     
    	GUI_RECT gui_rect;  
    	tv_menu_uipara_t* ui_para;   
	char str_val[32]={0};
	char protel_str[128];
	char str[5];
	
    	ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!ui_para)
    	{
        	__err("ui_para is null...\n");
        	return EPDK_FAIL;
    	}
	
	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    


        GUI_SetBkColor(0x00);

	 if(color>1)
	 	color = 1;
	 if(color==0)
	 {
	 	GUI_SetColor(GUI_WHITE);
		temp_color = 0;
	 }	
	 else
	 {
	 	GUI_SetColor(GUI_YELLOW);
		temp_color = 2;
	 }	

			gui_rect.x0 = 400;
		    	gui_rect.x1 = 460;
			gui_rect.y0 = 54*item+24;
			gui_rect.y1 = gui_rect.y0+16;

		if(item>0)
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0 );
//			esKRNL_TimeDly(1);

		if(tv_data.tv_page==0)
		{
			switch (item)
			{
				case 1:
					gui_rect.x0 = 425;
					uint2str(dsk_tv_rcv->bright, str);	
					GUI_DispStringAt(str, gui_rect.x0 , gui_rect.y0);		
					break;
				case 2:
					gui_rect.x0 = 425;
					uint2str(dsk_tv_rcv->contrast, str);	
					GUI_DispStringAt(str, gui_rect.x0 , gui_rect.y0);		
					break;
				case 3:
					gui_rect.x0 = 425;
					uint2str(dsk_tv_rcv->color, str);	
					GUI_DispStringAt(str, gui_rect.x0 , gui_rect.y0);		
					break;					
				case 4:
					gui_rect.x0 = 420;
					dsk_langres_get_menu_text(TVinput[dsk_tv_rcv->sourceInput], protel_str, GUI_TITLE_MAX);  
		 			GUI_DispStringAt(protel_str, gui_rect.x0 , gui_rect.y0);		
							
					break;
				case 5:
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0]), 332, 232+yoffset  );
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1]), 494, 232+yoffset  );						
					gui_rect.x0 = 420;
					if(dsk_tv_rcv->lang==EPDK_LANGUAGE_ENM_CHINESES)
						dsk_langres_get_menu_text(SysLang[1], protel_str, GUI_TITLE_MAX);  
					else
						dsk_langres_get_menu_text(SysLang[0], protel_str, GUI_TITLE_MAX); 
					
		 			GUI_DispStringAt(protel_str, gui_rect.x0 , gui_rect.y0);						
					break;

				default:
					break;
			}
		}
		else
		{
			switch (item)
			{					
				case 1:
					gui_rect.x0 = 400;
					if(dsk_tv_rcv->sourceInput==0)
					{
						if((dsk_tv_rcv->ucSoundSys==2)||(dsk_tv_rcv->ucSoundSys==5))
							gui_rect.x0 += 10;
						if(dsk_tv_rcv->ucSoundSys==4)
							gui_rect.x0 += 16;						
						dsk_langres_get_menu_text(TVsys[dsk_tv_rcv->ucSoundSys], protel_str, GUI_TITLE_MAX);  
					}	
					else
					{
						gui_rect.x0 = 420;
						dsk_langres_get_menu_text(TVsys[0], protel_str, GUI_TITLE_MAX); 
					}	
		 			GUI_DispStringAt(protel_str, gui_rect.x0 , gui_rect.y0);						
					break;
				case 2:
					
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1+temp_color]), 415, 125 );
					break;
				case 3:
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0+temp_color]), 395, 179 );
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1+temp_color]), 435, 179 );
					break;
				case 4:
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0+temp_color]), 395, 233 );
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1+temp_color]), 435, 233 );					
					break;
				case 5:
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0-60, gui_rect.y0-8 );
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0+50, gui_rect.y0-8 );
					break;
				default:
					break;
			}

		}
	
	return EPDK_OK;
}


static __s32 tv_menu_page_change(__gui_msg_t *msg)
{
	__u8 temp,i;
	
	if(tv_data.tv_page==0)
		temp = 6;
	else
		temp = 6;
	
	for(i=1;i<temp;i++)
	{
		if(tv_data.item==i)
		{
			tv_menu_paint_item(msg,i,1);
			tv_menu_paint_protel(msg,i,1);
		}
		else
		{
			tv_menu_paint_item(msg,i,0);
			tv_menu_paint_protel(msg,i,0);
		}
	}

}

/*
void* Tv_get_icon_res(__u32 index)
{
    music_icon_data_t *icon_table = NULL;
    
    
    icon_table = music_ui_400_240.icon_table;
    
    if(index > MUSIC_ICON_MAX)    
    {
    	return NULL;	
    }
    //__msg("----icon_id: %d, res_id: %d\n", index, icon_table[index].res_id);
    if(icon_table == NULL)
    {
        return NULL;
    }    
    else if(icon_table[index].res_id == 0)
    {
        return NULL;
    }    
    else if(icon_table[index].res_handle == NULL)
    {

        icon_table[index].res_handle = theme_open(icon_table[index].res_id);
        icon_table[index].res_buffer = theme_hdl2buf(icon_table[index].res_handle);                        
        return icon_table[index].res_buffer;
    }
    else
    {
        return icon_table[index].res_buffer;
    }
}
*/

__s32 DrawTvProgressBarPoint(__gui_msg_t *msg,__u32 total, __u32 cur_value)
{
	void *pic_buf = NULL;
	__s32 X = 0, Y = 0, BodyWidth = 0, PointWidth = 0;	
//	music_palyer_ui_t *player_ui;
	__u32 total_pieces = 0;
	__u32 average = 0;
	__u32 point = 0, i = 0;
	

	tv_menu_scene_t *smenu_attr;
	RECT rect;     
    	GUI_RECT gui_rect;  
    	tv_menu_uipara_t* ui_para;   
	char str_val[32]={0};
	char protel_str[128];
	char str[5];
	
    	ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!ui_para)
    	{
        	__err("ui_para is null...\n");
        	return EPDK_FAIL;
    	}
	
	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    				
		
	if((total == 0)||(cur_value == 0))
	{		
		X = ui_para->uipara_bar[1].x;
		Y = ui_para->uipara_bar[1].y;
//		pic_buf = music_get_icon_res(ID_MUSIC_PROCESS_BAR_BODY_ICON);
		GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_bar[1]), X, Y);
		return EPDK_OK;						//没有任何进度
	}

	BodyWidth = ui_para->uipara_bar[1].w;
	PointWidth = ui_para->uipara_bar[3].w;
	total_pieces = BodyWidth / PointWidth;
	

	{
		__u32 cnt = 0, len = 0;
		__s16 offsetX = 0, offsetY = 0;

		if( cur_value >= total )
			cur_value = total-1;
		len = (cur_value*total_pieces)/total;
		if( cnt == 0 )
		{
			X = ui_para->uipara_bar[0].x;
			Y = ui_para->uipara_bar[0].y;
//			pic_buf = music_get_icon_res(ID_MUSIC_PROCESS_BAR_HEAD_ICON);
			if(pic_buf != NULL)
			{
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_bar[0]), X, Y);
			}
			X += PointWidth;
		}
		for( cnt = 0; cnt < len; cnt++ )
		{
//			pic_buf = music_get_icon_res(ID_MUSIC_PROCESS_BAR_POINT_ICON);
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_bar[3]), X, Y);

			X += PointWidth;
		}
		if( cnt == total_pieces-1 )
		{
			X -= PointWidth;
//			pic_buf = music_get_icon_res(ID_MUSIC_PROCESS_BAR_POINT_ICON);
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_bar[3]), X, Y);
			X = ui_para->uipara_bar[2].x;
			Y = ui_para->uipara_bar[2].y;
//			pic_buf = music_get_icon_res(ID_MUSIC_PROCESS_BAR_TAIL_ICON);
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_bar[2]), X, Y);
		}
	}

	return EPDK_OK;
}

//画进度条,total为总量， cur_value为当前进度值
__s32 DrawTVProgressBar(__gui_msg_t *msg,__u32 total, __u32 cur_value)
{
	void *pic_buf = NULL;
	__s32 X = 0, Y = 0;	
	tv_menu_uipara_t* ui_para;
	tv_menu_scene_t *smenu_attr;

	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    		
	
	ui_para = tv_menu_get_uipara(GUI_GetScnDir());				
	
	X = ui_para->uipara_bar[1].x;
	Y = ui_para->uipara_bar[1].y;			
//	pic_buf = music_get_icon_res(ID_MUSIC_PROCESS_BAR_BODY_ICON);		

//	if(pic_buf != NULL)
	{
		GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_bar[1]), X, Y);	
	}	
	if((total == 0)||(cur_value == 0))
	{
		return EPDK_OK;						//没有任何进度
	}
	
	DrawTvProgressBarPoint(msg,total, cur_value);
	return EPDK_OK;
}


static __s32 tv_freBar_updata(__gui_msg_t *msg)
{
		__s32 tmp_fre;
		char protel_str[128];
		char str[6];
		tv_menu_scene_t *smenu_attr;
		__s32 i;
		__s16 x, y;
		RECT rect;     
	    	GUI_RECT gui_rect;  
	    	tv_menu_uipara_t* ui_para;   		

    	ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!ui_para)
    	{
        	__err("ui_para is null...\n");
        	return EPDK_FAIL;
    	}
	
	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    

	 GUI_SetColor(GUI_YELLOW);		
		
			tmp_fre = dsk_tv_rcv->cur_freq/1000000;
			DrawTVProgressBar(msg,870,tmp_fre);
			tmp_fre = dsk_tv_rcv->cur_freq/1000000;
			uint2str(tmp_fre, str);	
			if(tmp_fre<100)
			{

				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), 320, 275 );
				GUI_DispStringAt(str, 338 , 280);	
				
				dsk_langres_get_menu_text(ui_para->uipara_ch_text[1].res_id, smenu_attr->item_ch_str[1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_ch_str[1], 356 , 280);	

				tmp_fre = dsk_tv_rcv->cur_freq/10000;
				tmp_fre = tmp_fre%100;
				uint2str(tmp_fre, str);	
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), 365, 275 );
				GUI_DispStringAt(str, 365 , 280);

				dsk_langres_get_menu_text(ui_para->uipara_ch_text[0].res_id, smenu_attr->item_ch_str[0], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_ch_str[0], 385 , 280);					
				
			}
			else
			{
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), 320, 275 );
				GUI_DispStringAt(str, 330 , 280);	
				
				dsk_langres_get_menu_text(ui_para->uipara_ch_text[1].res_id, smenu_attr->item_ch_str[1], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_ch_str[1], 356 , 280);	

				tmp_fre = dsk_tv_rcv->cur_freq/10000;
				tmp_fre = tmp_fre%100;
				uint2str(tmp_fre, str);	
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), 365, 275 );
				GUI_DispStringAt(str, 365 , 280);

				dsk_langres_get_menu_text(ui_para->uipara_ch_text[0].res_id, smenu_attr->item_ch_str[0], GUI_TITLE_MAX);  
	 			GUI_DispStringAt(smenu_attr->item_ch_str[0], 385 , 280);	
				
			}	
}


static __s32 tv_menu_updata_search_ui(__gui_msg_t *msg)
{

	tv_menu_scene_t *smenu_attr;
	__s32 i;
	__s16 x, y;
	RECT rect;     
    	GUI_RECT gui_rect;  
    	tv_menu_uipara_t* ui_para;   
	char str_val[32]={0};
	char protel_str[128];
	char str[6];
	__s32 tmp_fre;
	
    	ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!ui_para)
    	{
        	__err("ui_para is null...\n");
        	return EPDK_FAIL;
    	}
	
	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    

	 GUI_SetColor(GUI_YELLOW);


	gui_rect.x0 = 400;
	gui_rect.x1 = 460;
	gui_rect.y0 = 125;
	gui_rect.y1 = gui_rect.y0+16;					

	if(tv_data.serch_ing==1)
	{
		if(tv_data.serch_cnt>1)
			tv_data.serch_cnt = 0;
		else
			tv_data.serch_cnt++;

		if(dsk_tv_rcv->auto_maual_mode==0x10)
		{
			if(tv_data.serch_cnt==0)
			{
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0 );
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[3]), 400, 125 );	
			}
			if(tv_data.serch_cnt==1)
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[3]), 420, 125 );	
			if(tv_data.serch_cnt==2)
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[3]), 440, 125 );	

		}
		else
		{
			if(dsk_tv_rcv->auto_maual_mode==0x20)
			{
				if(tv_data.serch_cnt==0)
				{
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0+60 );
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[3]), 400, 179 );	
				}
				if(tv_data.serch_cnt==1)
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[3]), 420, 179 );	
				if(tv_data.serch_cnt==2)
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[3]), 440, 179 );	
			}
			if(dsk_tv_rcv->auto_maual_mode==0x21)
			{
				if(tv_data.serch_cnt==0)
				{
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0+60 );
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[2]), 440, 179 );	
				}
				if(tv_data.serch_cnt==1)
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[2]), 420, 179 );	
				if(tv_data.serch_cnt==2)
					GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[2]), 400, 179 );	
			}	
		}
		tv_freBar_updata(msg);
	}
	else
	{
//		GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0 );
//		GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[3]), gui_rect.x0, gui_rect.y0+60 );
	}
	return EPDK_OK;
}


static __s32 tv_menu_paint_all(__gui_msg_t *msg)
{

	tv_menu_scene_t *smenu_attr;
	__s32 i;
	__s16 x, y;
	__u8 temp;
	RECT rect;     
    	GUI_RECT gui_rect;  
    	tv_menu_uipara_t* ui_para;   
	char str_val[32]={0};
	char protel_str[128];
	char str[5];
	__s32 tmp_fre;
	
    	ui_para = tv_menu_get_uipara(GUI_GetScnDir());
    	if(!ui_para)
    	{
        	__err("ui_para is null...\n");
        	return EPDK_FAIL;
    	}
	
	if (GUI_LyrWinGetSta(GUI_WinGetLyrWin(msg->h_deswin)) != GUI_LYRWIN_STA_ON)
	{
        __msg("layer not on, do not paint...\n");
		return EPDK_FAIL;
	}

	smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);	
    	if (smenu_attr==NULL)
    	{
        	__err("invalid para...\n");
        	return EPDK_FAIL;
    	}    
    	if(EPDK_FALSE == smenu_attr->res_init)
    	{
        	tvmenu_init_res(smenu_attr);
    	}

//	if(tv_data.serch_ing==1)
//		tv_data.tv_page = 1;


	GUI_LyrWinSel(smenu_attr->hlyr);   
	GUI_SetFont(smenu_attr->tvmenu_font);
	GUI_UC_SetEncodeUTF8();  
    	GUI_SetBkColor(0);
    	GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
		
	{
		{
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[0]), 180, 0 );	
			
			if(tv_data.tv_page==0)
			{
//				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[1]), 192, 50 );	
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[1]), 285, 50 );	
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_page[2]), 208, 20 );
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_page[1]), 304, 20  );	
			}
			else
			{
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[1]), 192, 50 );	
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_page[0]), 208, 20 );
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_page[3]), 304, 20  );					
//				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->bmp_bg[1]), 285, 50 );	
			}
			
//			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_page[0]), 208, 20 );
//			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_page[2]), 304, 20  );		
			
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0]), 332, 18+yoffset+5 );
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1]), 494, 18+yoffset+5  );
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0]), 332, 70+yoffset+5  );
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1]), 494, 70+yoffset+5  );
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0]), 332, 124+yoffset+5  );

			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1]), 494, 124+yoffset+5  );
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0]), 332, 176+yoffset+7  );
			GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1]), 494, 176+yoffset+7  );

			if(tv_data.tv_page==0)
			{
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[0]), 332, 232+yoffset+6  );
				GUI_BMP_Draw(dsk_theme_hdl2buf(smenu_attr->icon_selt[1]), 494, 232+yoffset+6  );	
			}	
		}
	}
	if(tv_data.tv_page==0)
		temp = 6;
	else
		temp = 5;

	for(i=1;i<temp;i++)
	{
		if(tv_data.item==i)
		{
			tv_menu_paint_item(msg,i,1);
			tv_menu_paint_protel(msg,i,1);
		}
		else
		{
			tv_menu_paint_item(msg,i,0);
			tv_menu_paint_protel(msg,i,0);
		}
	}

	if(tv_data.tv_page==1)
	{
		tv_freBar_updata(msg);
	}

	return EPDK_OK;
}

static __s32 tv_menu_end_serch(__gui_msg_t *msg)
{
		tv_menu_scene_t *scene_para;
		scene_para = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);
		if (!scene_para)
		{
			__err("invalid para...\n");
			return EPDK_FAIL;
		}	
		tv_data.serch_ing = 0;
	return EPDK_OK;
}

static __s32 tv_menu_stat_serch(__gui_msg_t *msg)
{
		tv_menu_scene_t *scene_para;
		scene_para = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);
		if (!scene_para)
		{
			__err("invalid para...\n");
			return EPDK_FAIL;
		}	

 	   	__msg("Tv start serch channel\n");

		tv_data.serch_cnt = 3;
		tv_data.serch_ing = 1;
		app_tv_data->h_menuwin = msg->h_deswin;
		TvSearchChannel(2);	
	return EPDK_OK;		
}


static __s32 tvsouinputselect_menu(void)
{
	if(dsk_tv_rcv->sourceInput==0)
		dsk_tv_rcv->sourceInput = 1;
	else
		dsk_tv_rcv->sourceInput = 0;
	
	dsk_tv_set_sourceInput(0);

	if(dsk_tv_rcv->sourceInput==0)
	{
		 eLIBs_fioctrl(app_tv_data->audio_drv, AUDIO_DEV_CMD_STOP, 0, 0);	
		 eLIBs_fioctrl(app_tv_data->audio_drv, AUDIO_DEV_CMD_START, 0xff, 0);	
	}	 
	else
	{
		 eLIBs_fioctrl(app_tv_data->audio_drv, AUDIO_DEV_CMD_STOP, 0xff, 0);
		 eLIBs_fioctrl(app_tv_data->audio_drv,  AUDIO_DEV_CMD_START, 0, 0);	
	}	
}

/*

*/
static __s32  tv_main_menu_key(__gui_msg_t *msg)
{
	static __s32 last_key = -1;
	static __s32 atiurset = 0;
	tv_menu_scene_t *tv_para;
	__u32 arg[3]={0};

    	__msg("tv_meun_key->dwAddData1=%d, msg->dwAddData2=%d\n"
      		  ,msg->dwAddData1, msg->dwAddData2);

    	__msg(" tv_data.item=%d,  tv_data.last=%d\n"
      		  , tv_data.item,  tv_data.lastitem);			
		
	if (KEY_UP_ACTION == msg->dwAddData2)
	{
		if (GUI_MSG_KEY_ENTER == last_key)
		{
//			main_cmd2parent(msg->h_deswin, ID_OP_SUB_ENTER, mmenu_attr->focus_item, mmenu_attr->first_item);
		}
		__msg("**********tvmenu_key_proc**********\n");
	}
	else
	{
		__msg("**********tvmenu_key_proc 2**********\n");
		tv_para = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);

		if(tv_data.serch_ing == 1)
		{
			switch (msg->dwAddData1)
			{
				case GUI_MSG_IR_UP:
				case GUI_MSG_IR_DOWN:			
				case GUI_MSG_KEY_UP:
				case GUI_MSG_KEY_DOWN:
				case GUI_MSG_KEY_ENTER:	
				case GUI_MSG_KEY_RIGHT:
				case GUI_MSG_KEY_LEFT:
				case GUI_MSG_KEY_MENU:
					if(tv_data.serch_cnt <3)
					{
						dsk_tv_rcv->manual_search_way = 0;
						dsk_tv_rcv->auto_maual_mode = 0xee;
						tv_data.serch_ing = 0;
					}	
					break;
				default:
					break;
			}
	
		}

		switch( msg->dwAddData1 )
		{
			case GUI_MSG_IR_UP:
			case GUI_MSG_IR_LONGUP:	
			case GUI_MSG_KEY_LONGDOWN:
			case GUI_MSG_KEY_DOWN:					
			{		
				if(tv_data.tv_page==0)
				{
					tv_data.lastitem = tv_data.item;
					if(tv_data.item==0)
						tv_data.item = 5;
					else
						if(tv_data.item>0)
							tv_data.item--;
				}
				else
				{
					tv_data.lastitem = tv_data.item;
					if(tv_data.item==0)
						tv_data.item = 4;
					else
						if(tv_data.item>0)
							tv_data.item--;
				}
				tv_menu_paint_item(msg,tv_data.item,1);
				tv_menu_paint_protel(msg,tv_data.item,1);
				tv_menu_paint_item(msg,tv_data.lastitem,0);
				tv_menu_paint_protel(msg,tv_data.lastitem,0);		
				atiurset = 1;
			}
			break;
			case GUI_MSG_IR_DOWN:
			case GUI_MSG_IR_LONGDOWN:				
			case GUI_MSG_KEY_UP:
			case GUI_MSG_KEY_LONGUP:		
			case GUI_MSG_KEY_ENTER:					
			{
				if(tv_data.tv_page==0)
				{
					tv_data.lastitem = tv_data.item;
					if(tv_data.item==5)
						tv_data.item = 0;
					else
						if(tv_data.item<5)
							tv_data.item++;
				}
				else
				{
					tv_data.lastitem = tv_data.item;
					if(tv_data.item==4)
						tv_data.item = 0;
					else
						if(tv_data.item<4)
							tv_data.item++;
				}

				tv_menu_paint_item(msg,tv_data.item,1);
				tv_menu_paint_protel(msg,tv_data.item,1);
				tv_menu_paint_item(msg,tv_data.lastitem,0);
				tv_menu_paint_protel(msg,tv_data.lastitem,0);	
				atiurset = 1;			
			}
			break;
			case GUI_MSG_KEY_RIGHT:
			case GUI_MSG_KEY_LONGRIGHT:
				if(tv_data.tv_page==0)
				{
					switch(tv_data.item)
					{
						case 0:
							if(dsk_tv_rcv->sourceInput==0)
							{
								tv_data.tv_page = 1;
								tv_menu_paint_all(msg);
							}	
							break;
							
						case 1:
							if(dsk_tv_rcv->bright < 100)
								dsk_tv_rcv->bright++;

							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_set_cur_bright();
							break;
						case 2:
							if(dsk_tv_rcv->contrast < 100)
								dsk_tv_rcv->contrast++;

							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_set_cur_contrast();
							break;
						case 3:					
							if(dsk_tv_rcv->color < 100)
								dsk_tv_rcv->color++;

							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_set_cur_color();
							break;
						case 4:
							tvsouinputselect_menu();
							tv_menu_paint_protel(msg,tv_data.item,1);
							tv_menu_paint_protel(msg,1,0);
							break;
						case 5:
							if(dsk_tv_rcv->lang==EPDK_LANGUAGE_ENM_CHINESES)
								dsk_tv_rcv->lang = EPDK_LANGUAGE_ENM_ENGLISH;
							else
								dsk_tv_rcv->lang = EPDK_LANGUAGE_ENM_CHINESES;
							
								dsk_langres_set_type(dsk_tv_rcv->lang);	
							tv_menu_paint_all(msg);		

							if(dsk_tv_rcv->lang == EPDK_LANGUAGE_ENM_ENGLISH)
							{
								arg[0] = 0;
								eLIBs_fioctrl(app_tv_data->tv_drv, 8, 1, arg);
							}
							else
							{
								arg[0] = 1;
								eLIBs_fioctrl(app_tv_data->tv_drv, 8, 1, arg);
							}							
							
//							dsk_tv_rcv->auto_maual_mode=0x20;
//							tv_menu_stat_serch(msg);
							break;
						default:
							break;
							
					}
				}
				else
				{
					switch(tv_data.item)
					{
						case 0:
							tv_data.tv_page = 0;
							tv_menu_paint_all(msg);
							break;
							
						case 1:
							if(dsk_tv_rcv->sourceInput==0)
							{
								if(dsk_tv_rcv->ucSoundSys<5)
									dsk_tv_rcv->ucSoundSys++;
								else
									dsk_tv_rcv->ucSoundSys = 1;
								tv_menu_paint_protel(msg,tv_data.item,1);
								dsk_tv_SetTvSys();
							}
							else
							{
								dsk_tv_rcv->ucSoundSys=0;
							}
							break;
						case 2:
							dsk_tv_rcv->auto_maual_mode=0x10;
							tv_menu_stat_serch(msg);							
							break;
						case 3:					
							dsk_tv_rcv->auto_maual_mode=0x20;
							tv_menu_stat_serch(msg);
							break;
						case 4:
							dsk_tv_finerFreq(1);
							tv_freBar_updata(msg);
							break;
						default:
							break;
							
					}
				}
				atiurset = 1;
				break;
			case GUI_MSG_KEY_LEFT:
			case GUI_MSG_KEY_LONGLEFT:
				if(tv_data.tv_page==0)
				{
					switch(tv_data.item)
					{
						case 0:
							if(dsk_tv_rcv->sourceInput==0)
							{
								tv_data.tv_page = 1;
								tv_menu_paint_all(msg);
							}	
							break;
							
						case 1:
							if(dsk_tv_rcv->bright > 0)
								dsk_tv_rcv->bright--;

							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_set_cur_bright();
							break;
						case 2:
							if(dsk_tv_rcv->contrast > 0)
								dsk_tv_rcv->contrast--;

							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_set_cur_contrast();
							break;
						case 3:					
							if(dsk_tv_rcv->color > 0)
								dsk_tv_rcv->color--;

							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_set_cur_color();
							break;
						case 4:
							tvsouinputselect_menu();
							tv_menu_paint_protel(msg,tv_data.item,1);
							tv_menu_paint_protel(msg,1,0);
							break;
						case 5:
							if(dsk_tv_rcv->lang==EPDK_LANGUAGE_ENM_CHINESES)
								dsk_tv_rcv->lang = EPDK_LANGUAGE_ENM_ENGLISH;
							else
								dsk_tv_rcv->lang = EPDK_LANGUAGE_ENM_CHINESES;
							
								dsk_langres_set_type(dsk_tv_rcv->lang);	
							tv_menu_paint_all(msg);	

							if(dsk_tv_rcv->lang == EPDK_LANGUAGE_ENM_ENGLISH)
							{
								arg[0] = 0;
								eLIBs_fioctrl(app_tv_data->tv_drv, 8, 1, arg);
							}
							else
							{
								arg[0] = 1;
								eLIBs_fioctrl(app_tv_data->tv_drv, 8, 1, arg);
							}
							
//							dsk_tv_rcv->auto_maual_mode=0x20;
//							tv_menu_stat_serch(msg);
							break;
						default:
							break;
							
					}
				}
				else
				{
					switch(tv_data.item)
					{
						case 0:
							tv_data.tv_page = 0;
							tv_menu_paint_all(msg);
							break;
							
						case 1:
							if(dsk_tv_rcv->sourceInput==0)
							{
								if(dsk_tv_rcv->ucSoundSys>1)
									dsk_tv_rcv->ucSoundSys--;
								else
									dsk_tv_rcv->ucSoundSys = 4;
								tv_menu_paint_protel(msg,tv_data.item,1);
								dsk_tv_SetTvSys();
							}
							else
							{
								dsk_tv_rcv->ucSoundSys=0;
							}
							break;
						case 2:
							dsk_tv_rcv->auto_maual_mode=0x10;
							tv_menu_stat_serch(msg);							
							break;
						case 3:					
							dsk_tv_rcv->auto_maual_mode=0x21;
							tv_menu_stat_serch(msg);
							break;
						case 4:
							dsk_tv_finerFreq(0);
							tv_freBar_updata(msg);
							break;
						default:
							break;
							
					}
				}
				atiurset = 1;
/*
				
				switch(tv_data.item)
				{
					case 0:
						if(tv_data.tv_page>0)
							tv_data.tv_page = 0;
						else
							tv_data.tv_page = 1;

//						tv_menu_page_change(msg);
						tv_menu_paint_all(msg);
						break;
						
					case 1:
						if(dsk_tv_rcv->bright>0)
							dsk_tv_rcv->bright--;
						
						tv_menu_paint_protel(msg,tv_data.item,1);
						dsk_tv_set_cur_bright();
						break;
					case 2:
						if(dsk_tv_rcv->sourceInput==0)
						{
							if(dsk_tv_rcv->ucSoundSys>1)
								dsk_tv_rcv->ucSoundSys--;
							else
								dsk_tv_rcv->ucSoundSys = 5;
							tv_menu_paint_protel(msg,tv_data.item,1);
							dsk_tv_SetTvSys();
						}
						else
						{
							dsk_tv_rcv->ucSoundSys=0;
						}
						
						break;
					case 3:		
						//dsk_tv_set_sourceInput(1);
						tvsouinputselect_menu();
						tv_menu_paint_protel(msg,tv_data.item,1);
						tv_menu_paint_protel(msg,1,0);
						break;
					case 4:
						
						break;
					case 5:
						dsk_tv_rcv->auto_maual_mode=0x21;
						tv_menu_stat_serch(msg);						
						break;
						
					default:
						break;
						
				}
				atiurset = 1;
*/

				break;				
				
            		case GUI_MSG_KEY_VADD:
          		case GUI_MSG_KEY_LONGVADD:
			{
				break;
			}		
			case GUI_MSG_KEY_MENU:
			{					
				break;
			}
				
			case GUI_MSG_KEY_LONGMENU:	
				
				break;
			default:
				break;	
		}

		if(atiurset == 1)
			__tvmenu_reset_hide_timmer(tv_para);
	}	

	if (KEY_UP_ACTION == msg->dwAddData2)
	{
		last_key = -1;	
	}
	else
	{
		last_key = msg->dwAddData1;	
	}

	return EPDK_OK;
}


/*
	
*/
static void tv_main_menu_create(__gui_msg_t *msg)
{
	tv_menu_scene_t *smenu_attr;
	tv_menu_scene_t *smenu_para;

	tv_menu_scene_t *sence_para;	
	tv_menu_uipara_t* ui_para;

	smenu_para = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);

	smenu_attr = (tv_menu_scene_t *)esMEMS_Balloc(sizeof(tv_menu_scene_t));
    if(!smenu_attr)
    {
        return ;
    }
	eLIBs_memset((void *)smenu_attr, 0, sizeof(tv_menu_scene_t));    
    
	smenu_attr->scene_id = smenu_para->scene_id;
	
	smenu_attr->hlyr = smenu_para->hlyr;
	smenu_attr->tvmenu_font = smenu_para->tvmenu_font;
	smenu_attr->focus_txt_color = GUI_YELLOW;
	smenu_attr->unfocus_txt_color = GUI_WHITE;
    	smenu_attr->res_init = EPDK_FALSE;

	tvmenu_init_res(smenu_attr);

//	com_set_palette_by_id(ID_TV_TV_PAL_BMP);//设置调色板

		    __msg("%$&*(**(*^&^%%^ \n");
		__msg("scene_para->hlyr=%x\n", smenu_para->hlyr);
		 __msg("%$&*(**(*^&^%%^ \n");
		__msg("smenu_para->tvmenu_font=%x\n", smenu_attr->tvmenu_font);
	
	GUI_WinSetAddData(msg->h_deswin, (__u32)smenu_attr);

	GUI_LyrWinSetTop(smenu_para->hlyr);
	
	//GUI_InvalidateRect(msg->h_deswin, 0, EPDK_TRUE);
}

/*

*/

static __s32 __tv_meun_ctrl_notify_parent(__gui_msg_t* msg, __s32 icon_id)
{
	switch(icon_id)
	{
		case 0:
		{
			tvmeun_cmd2parent(msg->h_deswin, 0, 0, 0);
			return EPDK_OK;
		}
		case 1:
		{
			tvmeun_cmd2parent(msg->h_deswin, 1, 0, 0);
			return EPDK_OK;
		}
		case 2:
		{
			tvmeun_cmd2parent(msg->h_deswin, 2, 0, 0);
			return EPDK_OK;
		}
		case 3:
		{
			tvmeun_cmd2parent(msg->h_deswin, 3, 0, 0);
			return EPDK_OK;
		}
		case 4:
		{
			tvmeun_cmd2parent(msg->h_deswin, 4, 0, 0);
			return EPDK_OK;
		}
		case 5:
		{
			tvmeun_cmd2parent(msg->h_deswin, 5, 0, 0);
			return EPDK_OK;
		}		
		default:
			break;
	}	
}

/*
	回调
*/
static __s32 _tv_main_menu_Proc(__gui_msg_t *msg)
{

	GUI_MEMDEV_Handle	draw_mem;
	
    __msg("_sub_menu_Proc msg->id=%d, msg->h_deswin=%x, msg->dwAddData1=%d, msg->dwAddData2=%d\n"
        ,msg->id, msg->h_deswin, msg->dwAddData1, msg->dwAddData2);

	
	switch(msg->id)
	{
	case GUI_MSG_CREATE:
		{            
			tv_menu_scene_t *scene_para;
			scene_para = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);
			if (!scene_para)
			{
				__err("invalid para...\n");
				return EPDK_FAIL;
			}	
			
			scene_para->hfrm = msg->h_deswin;//必须在此初始化，因为窗口创建未返回，否则该值仍然是空

			__tvmenu_install_hide_timmer(scene_para);
//			tv_main_menu_create(msg);

//			tv_menu_paint( msg);
			__msg("*********************************111111******************\n");
		
		}

		return EPDK_OK;
	case GUI_MSG_CLOSE:
		{
			__here__;
			GUI_FrmWinDelete(msg->h_deswin);
		}
		return EPDK_OK;
	case GUI_MSG_DESTROY:
		{
			tv_menu_scene_t *smenu_attr;
//			tv_menu_para_t *smenu_para;
            
//			smenu_para = (tv_menu_para_t *)GUI_WinGetAttr(msg->h_deswin);
			smenu_attr = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);
			__tvmenu_uninstall_hide_timmer(smenu_attr);
			tvmenu_uninit_res(smenu_attr);
		}
		return EPDK_OK;
	case GUI_MSG_PAINT:   
		{

			tv_main_menu_create(msg);
			draw_mem = GUI_MEMDEV_Create(180, 96,400,300);
			GUI_MEMDEV_Select(draw_mem);
					
//			__tvmenu_draw_bg(msg);
//			esKRNL_TimeDly(1);
			tv_menu_paint_all( msg);	

			
			GUI_MEMDEV_CopyToLCD(draw_mem); 
			GUI_MEMDEV_Select( NULL );			
			GUI_MEMDEV_Delete(draw_mem);
			draw_mem = NULL;	
		
			return EPDK_OK;
		}
	case GUI_MSG_KEY:
//		tv_main_menu_key(msg);
		draw_mem = GUI_MEMDEV_Create(180, 96,400,300);
		GUI_MEMDEV_Select(draw_mem);
					
		tv_main_menu_key(msg);

			
		GUI_MEMDEV_CopyToLCD(draw_mem); 
		GUI_MEMDEV_Select( NULL );			
		GUI_MEMDEV_Delete(draw_mem);
		draw_mem = NULL;	
		return EPDK_OK;
	case GUI_MSG_TOUCH:
		break;
	case GUI_MSG_COMMAND:
		{
			tv_menu_scene_t *scene_para;
			scene_para = (tv_menu_scene_t *)GUI_WinGetAttr(msg->h_deswin);
			if (!scene_para)
			{
				__err("invalid para...\n");
				return EPDK_FAIL;
			}				
					switch(HIWORD(msg->dwAddData1))
					{
						case 0:break;
						case 1:break;
						case 2:break;
						case 3:break;
						case 4:break;
						case 5:
							tv_data.serch_ing = 0;
							__tvmenu_reset_hide_timmer(scene_para);
							tv_menu_updata_search_ui(msg);
							break;
						case 6:
							__tvmenu_reset_hide_timmer(scene_para);
							tv_menu_updata_search_ui(msg);
							break;
						default:break;
							
					}	
					
		}
		return EPDK_OK;
		
	case GUI_MSG_TIMER:
		{
/*			if(dsk_tv_rcv->search_flag==1)
				tv_menu_updata_search_ui(msg);
			else
			{
			
				if(tv_data.serch_ing==1)
				{
					tv_data.serch_ing = 0;
					tv_menu_updata_search_ui(msg);
					tv_menu_end_serch(msg);
				}
				else
*/
				
					tvmeun_cmd2parent(msg->h_deswin, 6, 0, 0);	
//			}	
			return EPDK_OK;								
		}		
	case MSG_SUB_OP_UP:
		{
			tv_menu_scene_t *smenu_attr;
			smenu_attr = (tv_menu_scene_t *)GUI_WinGetAddData(msg->h_deswin);            


//			tv_menu_paint( msg);
		}
		return EPDK_OK;
	case MSG_SUB_OP_DOWN:
		{
			tv_menu_scene_t *smenu_attr;
			smenu_attr = (tv_menu_scene_t *)GUI_WinGetAddData(msg->h_deswin);


//			tv_menu_paint( msg);
		}
		return EPDK_OK;
	case MSG_SUB_OP_ENTER:
		{
			tv_menu_scene_t *smenu_attr;
   
			smenu_attr = (tv_menu_scene_t *)GUI_WinGetAddData(msg->h_deswin);
		}
		return EPDK_OK;
	default:
		break;
	}
	
	return GUI_FrmWinDefaultProc(msg);	
}

/*
	建立窗口
*/
void * tv_sub_menu_win_create(H_WIN h_parent, tv_menu_para_t *para)
{
	__gui_framewincreate_para_t framewin_para;
	tv_menu_scene_t *smenu_para;
	FB fb;

	GUI_LyrWinGetFB(para->layer, &fb);

	smenu_para = (tv_menu_scene_t *)esMEMS_Balloc(sizeof(tv_menu_scene_t));
    	if(!smenu_para)
    	{
       	return NULL;
    	}
	eLIBs_memset(smenu_para, 0, sizeof(tv_menu_scene_t));

	smenu_para->tvmenu_font = para->smenu_font;
	smenu_para->hparent = h_parent;
	smenu_para->hlyr= para->layer;
	smenu_para->scene_id = 1;
    	smenu_para->item = 0;
	smenu_para->res_init = 0;
//	smenu_para->tv_sys_data = para->tv_sys_data;

	tv_data.item = 0;
	tv_data.lastitem = 0;
	tv_data.tv_page = 0;
	tv_data.tv_sourceInput = para->tv_sourceInput;
	tv_data.tv_video_sys= para->tv_video_sys;


	eLIBs_memset(&framewin_para, 0, sizeof(__gui_framewincreate_para_t));
	
	framewin_para.name =	"tv_menu_win",
	framewin_para.dwExStyle = WS_EX_NONE;
	framewin_para.dwStyle = WS_NONE|WS_VISIBLE;
	framewin_para.spCaption =  NULL;
	framewin_para.hOwner	= NULL;
	framewin_para.hHosting = h_parent;
	framewin_para.id         = (APP_TV_ID+1);
	framewin_para.FrameWinProc = (__pGUI_WIN_CB)esKRNL_GetCallBack((__pCBK_t)_tv_main_menu_Proc);
	
	framewin_para.rect.x = 0;// 0;
	framewin_para.rect.y = 0;//0;
	framewin_para.rect.width=  fb.size.width;//movie_layout.spsc_scnwin.width; //800		//180, 96, 292, 180
	framewin_para.rect.height =  fb.size.height;//movie_layout.spsc_scnwin.height;//300
	

	framewin_para.BkColor.alpha =  0;
	framewin_para.BkColor.red = 0;
	framewin_para.BkColor.green = 0;
	framewin_para.BkColor.blue = 0;
	framewin_para.attr =  (void *)smenu_para;
	framewin_para.hLayer = para->layer;

	__msg("scene_para->hfrm=%x\n", smenu_para->hfrm);
	__msg("scene_para->hlyr=%x\n", smenu_para->hlyr);
	__msg("smenu_para->tvmenu_font=%x\n", smenu_para->tvmenu_font);	

	smenu_para->hfrm = GUI_FrmWinCreate(&framewin_para);



	if (NULL == smenu_para->hfrm)
	{
		esMEMS_Bfree(smenu_para, sizeof(tv_menu_scene_t));
		smenu_para = NULL;
		__msg("GUI_FrmWinCreate fail...\n");
		return NULL;
	}


	if (smenu_para->hlyr)
	{
		GUI_LyrWinSetSta(smenu_para->hlyr, GUI_LYRWIN_STA_ON);
		GUI_LyrWinSetTop(smenu_para->hlyr);
	}
	else
	{
		__err("invalid para...\n");
	}

	GUI_WinSetFocusChild(smenu_para->hfrm);
	
	return smenu_para;	
}

void  tv_menu_win_delete(H_WIN smenu_win)
{
	GUI_FrmWinDelete(smenu_win);
}

void tv_menu_init_res(H_WIN hwin)
{
    tv_menu_scene_t * smenu_attr = (tv_menu_scene_t *)GUI_WinGetAddData(hwin);
    if(smenu_attr)
    {
        tvmenu_init_res(smenu_attr);
    }
}

void tv_menu_uninit_res(H_WIN hwin)
{
    tv_menu_scene_t * smenu_attr = (tv_menu_scene_t *)GUI_WinGetAddData(hwin);
    if(smenu_attr)
    {
        tvmenu_uninit_res(smenu_attr);
    }
}




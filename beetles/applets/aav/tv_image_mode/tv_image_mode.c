/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: tvmute.c
* By      	:
* Func		: 
* Version	: v1.0
* ============================================================================================================
* 2011-05-05  Bayden.chen  create this file
**************************************************************************************************************
*/
#include "tv_image_mode.h"
#include "common/common.h"
#include "tv_image_mode_ui.h"
#include "app_tv_i.h"
#include "tv_mannger.h"


/***********************************************************************************************************
	建立图层
************************************************************************************************************/
static H_LYR __tv_image_mode_8bpp_layer_create(RECT *rect, __s32 pipe)
{
	__s32           screen_width;
    __s32 			screen_height;
	H_LYR layer = NULL;
	FB  fb =
	{
	    {0, 0},                                   		/* size      */
	    {0, 0, 0},                                      /* buffer    */
	    {FB_TYPE_RGB, {PIXEL_COLOR_ARGB8888, 0, (__rgb_seq_t)0}},    /* fmt       */
	};

	__disp_layer_para_t lstlyr =
	{
//	    DISP_LAYER_WORK_MODE_PALETTE,                    /* mode      */
	    DISP_LAYER_WORK_MODE_NORMAL,
	    0,                                              /* ck_mode   */
	    0,                                              /* alpha_en  */
	    0,                                              /* alpha_val */
	    1,                                              /* pipe      */
	    0xff,                                           /* prio      */
	    {0, 0, 0, 0},                           		/* screen    */
	    {0, 0, 0, 0},                               	/* source    */
	    DISP_LAYER_OUTPUT_CHN_DE_CH1,                   /* channel   */
	    NULL                                            /* fb        */
	};

	__layerwincreate_para_t lyrcreate_info =
	{
	    "sub menu layer",
	    NULL,
	    GUI_LYRWIN_STA_SUSPEND,
	    GUI_LYRWIN_NORMAL
	};
	dsk_display_get_size(&screen_width, &screen_height);
	
	fb.size.width		= rect->width;
	fb.size.height		= rect->height;	
	
	lstlyr.src_win.x  		= 0;
	lstlyr.src_win.y  		= 0;
	lstlyr.src_win.width 	= rect->width;
	lstlyr.src_win.height 	= rect->height;
	
	lstlyr.scn_win.x		= rect->x + (screen_width - 1024)/2;
	lstlyr.scn_win.y		= rect->y + (screen_height - 768)/2;
	lstlyr.scn_win.width  	= rect->width;
	lstlyr.scn_win.height 	= rect->height;
	
	lstlyr.pipe = pipe;
	lstlyr.fb = &fb;
	lyrcreate_info.lyrpara = &lstlyr;
	
	layer = GUI_LyrWinCreate(&lyrcreate_info);
	if( !layer )
	{
		__err("app bar layer create error !\n");
	} 
		
	return layer;	
}

static __s32 __tv_image_mode_init_ui(tv_image_mode_scene_t* scene_para)
{
	tv_image_mode_uipara_t* ui_para;
	
	ui_para = tv_image_mode_get_uipara(GUI_GetScnDir());
	
	if (NULL == ui_para)
	{				
		__msg("tv_image_mode_get_uipara fail...\n");
		return EPDK_FAIL;
	}		

	if (ui_para->uipara_icon.res_id)
	{
		ui_para->uipara_icon.res_hdl = dsk_theme_open(ui_para->uipara_icon.res_id);
		if (!ui_para->uipara_icon.res_hdl)
		{
			__msg("dsk_theme_open fail...\n");
		}
	}
	dsk_langres_get_menu_text(ui_para->uipara_mode[0].res_id, scene_para->mode_str[0], 16); 
	dsk_langres_get_menu_text(ui_para->uipara_mode[1].res_id, scene_para->mode_str[1], 16); 
	dsk_langres_get_menu_text(ui_para->uipara_mode[2].res_id, scene_para->mode_str[2], 16); 	
	dsk_langres_get_menu_text(ui_para->uipara_mode[3].res_id, scene_para->mode_str[3], 16); 		
	
	return EPDK_OK;
}


static __s32 __tv_image_mode_update_ui(tv_image_mode_scene_t* scene_para)
{
	tv_image_mode_uipara_t* ui_para;
   
	ui_para = tv_image_mode_get_uipara(GUI_GetScnDir());
	
	if (NULL == ui_para)
	{				
		__msg("tv_mute_get_uipara fail...\n");
		return EPDK_FAIL;
	}	

	if (!scene_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}
	
	if (!scene_para->hlyr)
	{
		__msg("scene_para->hlyr is null..., do not paint\n");
		return EPDK_FAIL;
	}
	if (GUI_LYRWIN_STA_ON != GUI_LyrWinGetSta(scene_para->hlyr))
	{
		__msg("GUI_LYRWIN_STA_ON != scene_para->hlyr, do not paint...\n");
		return EPDK_FAIL;
	}
    
	GUI_LyrWinSel(scene_para->hlyr);	    
    
	//com_memdev_create(scene_para->hlyr);    
    
	{
		void* pbmp;
		GUI_RECT gui_rect;

	   	gui_rect.x0 = ui_para->uipara_icon.x;
	    gui_rect.y0 = ui_para->uipara_icon.y;
	    gui_rect.x1 = gui_rect.x0+ui_para->uipara_icon.w;
	    gui_rect.y1 = gui_rect.y0+ui_para->uipara_icon.h;
	    //GUI_ClearRectEx(&gui_rect);	
		pbmp = dsk_theme_hdl2buf(ui_para->uipara_icon.res_hdl);	
		GUI_BMP_Draw(pbmp, gui_rect.x0, gui_rect.y0);
		GUI_SetColor(GUI_WHITE);
		GUI_DispStringInRect(scene_para->mode_str[dsk_tv_rcv->image_mode], &gui_rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
		
	}	   
	//com_memdev_delete();
	return EPDK_OK;
}

static __s32 __tv_image_mode_deinit_ui(void)
{
	tv_image_mode_uipara_t* ui_para;
	
	ui_para = tv_image_mode_get_uipara(GUI_GetScnDir());
	
	if (NULL == ui_para)
	{				
		__msg("tv_image_mode_get_uipara fail...\n");
		return EPDK_FAIL;
	}			
	
	if (ui_para->uipara_icon.res_hdl)
	{
		dsk_theme_close(ui_para->uipara_icon.res_hdl);
		ui_para->uipara_icon.res_hdl = NULL;					
	}
	
	return EPDK_OK;
}



static __s32 __tv_image_mode_install_hide_timmer(tv_image_mode_scene_t* scene_para)
{
	if (!scene_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}	
	
	scene_para->hide_timmer_id = 0x12;

	if (!GUI_IsTimerInstalled(scene_para->hfrm, scene_para->hide_timmer_id))
	{
		GUI_SetTimer(scene_para->hfrm, scene_para->hide_timmer_id
			, 400*2, NULL);//3秒		
	}
	else
	{
		__msg("timmer already install...\n");
		return EPDK_FAIL;
	}
	
	return EPDK_OK;
}

static __s32 __tv_image_mode_reset_hide_timmer(tv_image_mode_scene_t* scene_para)
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

static __s32 __tv_image_mode_uninstall_hide_timmer(tv_image_mode_scene_t* scene_para)
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


static __s32  tv_image_mode_key_proc(__gui_msg_t *msg)
{
	static __s32 last_key = -1;
	tv_image_mode_scene_t* scene_para;

	scene_para = GUI_WinGetAttr(msg->h_deswin);		

    	__msg("app_tv_image_mode_key->dwAddData1=%d, msg->dwAddData2=%d\n"
      		  ,msg->dwAddData1, msg->dwAddData2);
		
	if (KEY_UP_ACTION == msg->dwAddData2)
	{
		if (GUI_MSG_KEY_ENTER == last_key)
		{
		}
		__msg("**********tv_mute_key_proc**********\n");
	}
	else
	{
		__msg("**********tvm_mute_key_proc 2**********\n");


			
			
		switch( msg->dwAddData1 )
		{

			case GUI_MSG_KEY_NUM0:
				break;
			case GUI_MSG_KEY_LEFT:
			case GUI_MSG_KEY_LONGLEFT:
			{			

			}
			break;
			case GUI_MSG_KEY_RIGHT:
			case GUI_MSG_KEY_LONGRIGHT:
			{
			
			}
			break;
			case GUI_MSG_KEY_UP:
			case GUI_MSG_KEY_LONGUP:
			{

				break;
			}	
            		case GUI_MSG_KEY_VADD:
          		case GUI_MSG_KEY_LONGVADD:
			{
				break;
			}		
			case GUI_MSG_KEY_LONGDOWN:
			case GUI_MSG_KEY_DOWN:
			{

				break;
			}
			case GUI_MSG_KEY_ENTER:	
			case GUI_MSG_KEY_LONGENTER:	
			{	

				break;
			}	
			case GUI_MSG_KEY_MENU:
			{

			}
			break;
			case GUI_MSG_KEY_LONGMENU:	
				break;
			case GUI_MSG_KEY_MODE:
				if(dsk_tv_rcv->image_mode < TV_IMAGE_MODE_MILD)
					dsk_tv_rcv->image_mode++;
				else
					dsk_tv_rcv->image_mode = TV_IMAGE_MODE_CUSTOM;
				dsk_tv_set_image_mode(dsk_tv_rcv->image_mode);
				dsk_tv_rcv->image_mode_flag = 1;
				__tv_image_mode_update_ui(scene_para);
				__tv_image_mode_reset_hide_timmer(scene_para);
				break;
			default:
				break;	
		}
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


static __s32 __tv_image_mode_proc(__gui_msg_t* msg)
{
	switch(msg->id)
	{
		case GUI_MSG_CREATE:
		{
			tv_image_mode_scene_t* scene_para;

			__msg("__tv_image_mode_proc GUI_MSG_CREATE begin\n");

			scene_para = GUI_WinGetAttr(msg->h_deswin);
			if (!scene_para)
			{
				__err("invalid para...\n");
				return EPDK_FAIL;
			}	
			
			scene_para->hfrm = msg->h_deswin;//必须在此初始化，因为窗口创建未返回，否则该值仍然是空
			
			__tv_image_mode_init_ui(scene_para);
			
			__tv_image_mode_install_hide_timmer(scene_para);

			__msg("__tv_image_mode_proc GUI_MSG_CREATE end\n");
			return EPDK_OK;
		}
		case GUI_MSG_DESTROY:
		{
			tv_image_mode_scene_t* scene_para;
			
			__msg("__tv_image_mode_proc GUI_MSG_DESTROY begin\n");

			scene_para = GUI_WinGetAttr(msg->h_deswin);
			if (!scene_para)
			{
				__err("invalid para...\n");
				return EPDK_FAIL;
			}
			if(dsk_tv_rcv->image_mode_flag)
				dsk_tv_rcv_save_image_mode();
			__tv_image_mode_uninstall_hide_timmer(scene_para);
			__tv_image_mode_deinit_ui();

			__msg("__tv_image_mode_proc GUI_MSG_DESTROY end\n");
			return EPDK_OK;
		}
		case GUI_MSG_KEY:
		{		
			tv_image_mode_key_proc(msg);
			return EPDK_OK;
		}
		case GUI_MSG_PAINT:
		{
			tv_image_mode_scene_t* scene_para;
			
			__msg("__tv_image_mode_proc GUI_MSG_PAINT begin\n");
			
			scene_para = GUI_WinGetAttr(msg->h_deswin);
			if (!scene_para)
			{
				__err("invalid para...\n");
				return EPDK_FAIL;
			}			
			
			__tv_image_mode_update_ui(scene_para);

			__msg("__tv_image_mode_proc GUI_MSG_PAINT end\n");

			return EPDK_OK;
		}
		case GUI_MSG_TIMER:
		{
			__s32 ret;
			tv_image_mode_scene_t* scene_para;

			__msg("__tv_image_mode_proc GUI_MSG_TIMER begin\n");

			scene_para = GUI_WinGetAttr(msg->h_deswin);

			ret = -1;

			movie_cmd2parent(msg->h_deswin, 0, 0, 0);	

			__msg("__tv_image_mode_proc GUI_MSG_TIMER end\n");
			
			if (-1 == ret)//未处理，交给子场景处理
			{
				break;
			}
			else//已处理
			{
				return EPDK_OK;
			}									
		}
		case GUI_MSG_CLOSE:
		{
			__msg("__tv_image_mode_proc GUI_MSG_CLOSE begin\n");
			movie_cmd2parent(msg->h_deswin, tv_image_mode_scene_msg_timeout, 0, 0);
			__msg("__tv_image_mode_proc GUI_MSG_CLOSE end\n");
			break;
		}
		default:
		{
			break;
		}
	}

	return GUI_FrmWinDefaultProc(msg);
}

void* tv_image_mode_scene_create(H_WIN h_parent,tv_image_mode_create_para_t *create_para)
{
	__gui_framewincreate_para_t framewin_para;
	tv_image_mode_scene_t *sence_para;	
	tv_image_mode_uipara_t* ui_para;
	RECT lyr_rect;

	sence_para = (tv_image_mode_scene_t *)esMEMS_Balloc(sizeof(tv_image_mode_scene_t));
	if (!sence_para)
	{
		__msg("mem not enough...\n");
		return NULL;
	}

	eLIBs_memset(sence_para, 0, sizeof(tv_image_mode_scene_t));

	sence_para->hparent = create_para->hparent;	
	sence_para->scene_id = create_para->scene_id;

	ui_para = tv_image_mode_get_uipara(GUI_GetScnDir());

	if (NULL == ui_para)
	{
		esMEMS_Bfree(sence_para, sizeof(tv_image_mode_scene_t));
		sence_para = NULL;
		__msg("tv_image_mode_get_uipara fail...\n");
		return NULL;
	}

	lyr_rect.x		= ui_para->uipara_lyr.x;
	lyr_rect.y		= ui_para->uipara_lyr.y;
	lyr_rect.width	= ui_para->uipara_lyr.w;
	lyr_rect.height = ui_para->uipara_lyr.h;

	sence_para->hlyr = __tv_image_mode_8bpp_layer_create(&lyr_rect, ui_para->pipe);
	if (NULL == sence_para->hlyr)
	{
		esMEMS_Bfree(sence_para, sizeof(tv_image_mode_scene_t));
		sence_para = NULL;
		__msg("sence_para->hlyr is null...\n");
		return NULL;
	}

	eLIBs_memset(&framewin_para, 0, sizeof(__gui_framewincreate_para_t));
	framewin_para.name			= "tv_image_mode_win",
	framewin_para.dwExStyle		= WS_EX_NONE;
	framewin_para.dwStyle		= WS_NONE|WS_VISIBLE;
	framewin_para.spCaption		= NULL;
	framewin_para.hOwner		= NULL;
	framewin_para.id			= (APP_TV_ID+5);
	framewin_para.hHosting		=  h_parent;
	framewin_para.FrameWinProc	= (__pGUI_WIN_CB)esKRNL_GetCallBack((__pCBK_t)__tv_image_mode_proc);
	framewin_para.rect.x		= ui_para->uipara_frm.x;
	framewin_para.rect.y		= ui_para->uipara_frm.y;
	framewin_para.rect.width	= ui_para->uipara_frm.w;
	framewin_para.rect.height	= ui_para->uipara_frm.h;
	framewin_para.BkColor.alpha = 0;
	framewin_para.BkColor.red	= 0;
	framewin_para.BkColor.green = 0;
	framewin_para.BkColor.blue	= 0;
	framewin_para.attr			= (void *)sence_para;
	framewin_para.hLayer		= sence_para->hlyr;

	sence_para->hfrm = GUI_FrmWinCreate(&framewin_para);
	if (NULL == sence_para->hfrm)
	{
		esMEMS_Bfree(sence_para, sizeof(tv_image_mode_scene_t));
		sence_para = NULL;
		__msg("GUI_FrmWinCreate fail...\n");
		return NULL;
	}

	if (sence_para->hlyr)
	{
		GUI_LyrWinSetSta(sence_para->hlyr, GUI_LYRWIN_STA_ON);
        GUI_LyrWinSetTop(sence_para->hlyr);
	}
	else
	{
		__msg("invalid para...\n");
	}
	
	GUI_WinSetFocusChild(sence_para->hfrm);
	return sence_para;
}

__s32 tv_image_mode_scene_delete(void* handle)
{
	tv_image_mode_scene_t* scene_para;

	scene_para = (tv_image_mode_scene_t*)handle;

	if (NULL == handle)
	{
		__msg("invalid para..\n");
		return EPDK_FAIL;
	}

	if (!scene_para->hfrm)
	{
		__msg("invalid para..\n");
		return EPDK_FAIL;
	}
	GUI_FrmWinDelete(scene_para->hfrm);

	if (!scene_para->hlyr)
	{
		__msg("invalid para..\n");
		return EPDK_FAIL;
	}
	GUI_LyrWinDelete(scene_para->hlyr);

	eLIBs_memset(scene_para, 0, sizeof(tv_image_mode_scene_t));//防止重复释放
	esMEMS_Bfree(scene_para, sizeof(tv_image_mode_scene_t));
	
	return EPDK_OK;
}

__s32 tv_image_mode_scene_set_focus(void* handle)
{
	tv_image_mode_scene_t* scene_para;
	
	scene_para = (tv_image_mode_scene_t*)handle;
	
	if (NULL == handle)
	{
		__msg("invalid para..\n");
		return EPDK_FAIL;
	}
	
	if (!scene_para->hfrm)
	{
		__msg("invalid para..\n");
		return EPDK_FAIL;
	}
	
	GUI_WinSetFocusChild(scene_para->hfrm);
	
	return EPDK_OK;
}

__s32 tv_image_mode_scene_get_hwnd(void* handle)
{
	tv_image_mode_scene_t* scene_para;
	
	scene_para = (tv_image_mode_scene_t*)handle;
	
	if (NULL == handle)
	{
		__msg("invalid para..\n");
		return EPDK_FAIL;
	}

    return scene_para->hfrm;    
}

__s32 tv_image_mode_scene_get_lyr_scn(RECT* rect)
{
    tv_image_mode_uipara_t* ui_para;
    ui_para = tv_image_mode_get_uipara(GUI_GetScnDir());

	if (NULL == ui_para)
	{		
		__msg("image_mode_get_uipara fail...\n");
		return NULL;
	}
    
    rect->x = ui_para->uipara_lyr.x;
    rect->y = ui_para->uipara_lyr.y;
    rect->width = ui_para->uipara_lyr.w;
    rect->height = ui_para->uipara_lyr.h;    
    
    return EPDK_OK;
}


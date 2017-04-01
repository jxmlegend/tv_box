/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
*						        	 (c) Copyright 2007-2010, ANDY, China
*											 All Rights Reserved
*
* File    	: app_main.c
* By      	: Andy.zhang
* Func		: desk main thread
* Version	: v1.0
* ============================================================================================================
* 2009-7-20 8:51:52  andy.zhang  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#include "beetles_app.h"
#include "app_tv.h"
#include "com_video_in.h"
#include "drv_tvd.h"
#include "tv_main_menu.h"
#include "tv_menu_ui.h"
#include "tv_volume.h"
#include "tv_num.h"
#include "tv_mute.h"
#include "tv_mannger.h"
#include "app_tv_i.h"

typedef struct tag_tv_para
{
	void*	h_app_main;
	void*	h_tv_menu;
	void*	h_tv_volume;
	void*	h_Channel;
	void*	h_mute;

	H_WIN	lyr_mmenu;
	H_WIN	lyr_msound;
	H_WIN	lyr_mchannel;	
	H_WIN	lyr_mute;	

	H_WIN tv_manager;//	tvµÄmanwin

	__s32	focus_id;
	__s32   first_item;
	GUI_FONT *main_font;

	__u32  scene_id;
}tv_para_t;

//static reg_tv_para_t* tv_reg_para;

app_tv_data_t *app_tv_data = NULL;

static reg_system_para_t* setting_reg_para;
static int long_key = 0;
extern __u32 movie_muteflag;
extern __u32 movie_volume;
/***********************************************************************************************************
	½¨Á¢Í¼²ã
************************************************************************************************************/
static H_LYR tv_8bpp_layer_create(RECT *rect, __s32 pipe)
{
	H_LYR layer = NULL;
	FB  fb =
	{
	    {0, 0},                                   		/* size      */
	    {0, 0, 0},                                      /* buffer    */
	    {FB_TYPE_RGB, {PIXEL_COLOR_ARGB8888, 0, (__rgb_seq_t)0}},    /* fmt       */  ////PIXEL_MONO_8BPP
	};

	__disp_layer_para_t lstlyr =
	{
	    DISP_LAYER_WORK_MODE_NORMAL,                    /* mode      */		//DISP_LAYER_WORK_MODE_PALETTE
//	    DISP_LAYER_WORK_MODE_PALETTE,
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
	    "tv menu layer",
	    NULL,
	    GUI_LYRWIN_STA_SUSPEND,
	    GUI_LYRWIN_NORMAL
	};
__here__;	
	fb.size.width		= rect->width;
	fb.size.height		= rect->height;	
	
	lstlyr.src_win.x  		= 0;
	lstlyr.src_win.y  		= 0;
	lstlyr.src_win.width 	= rect->width;
	lstlyr.src_win.height 	= rect->height;
	
	lstlyr.scn_win.x		= rect->x;
	lstlyr.scn_win.y		= rect->y;
	lstlyr.scn_win.width  	= rect->width;
	lstlyr.scn_win.height 	= rect->height;
__here__;	
	lstlyr.pipe = pipe;
	lstlyr.fb = &fb;
	lyrcreate_info.lyrpara = &lstlyr;
__here__;	
	layer = GUI_LyrWinCreate(&lyrcreate_info);
__here__;	
	if( !layer )
	{
		__err("app bar layer create error !\n");
	} 
__here__;		
	return layer;	
}


void  TV_cmd2parent(H_WIN hwin, __s32 id, __s32 data1, __s32 data2)
{
	__gui_msg_t msg;

	msg.h_deswin = GUI_WinGetParent(hwin);
	msg.h_srcwin = NULL;
	msg.id = GUI_MSG_COMMAND;
	msg.dwAddData1 = MAKELONG(GUI_WinGetItemId(hwin), id);
	msg.dwAddData2 = data1;
	msg.dwReserved = data2;

	GUI_SendNotifyMessage(&msg);
	
}


static void __tv_menu_scene_create(tv_para_t *tv_para)
{
	tv_menu_para_t smenu_para;
	RECT	rect;
	tv_menu_uipara_t * home_ui_para;

	__here__;

	home_ui_para = tv_menu_get_uipara(GUI_GetScnDir());	
    	if(!home_ui_para)
    	{
        	__err("home_ui_para is null...\n");
			__here__;
       	 return ;
    	}
		
	rect.x = home_ui_para->uipara_lyr.x;
	rect.y = home_ui_para->uipara_lyr.y;
	rect.width = home_ui_para->uipara_lyr.w;
	rect.height = home_ui_para->uipara_lyr.h;

__here__;
	if (rect.x+rect.width >= home_ui_para->uipara_lyr.w)
	{
		rect.x = home_ui_para->uipara_lyr.w-rect.width;
	}
__here__;	
	tv_para->lyr_mmenu = tv_8bpp_layer_create(&rect, 1);   
__here__;
	__msg("<================= AFTER MUSIC Destroy Free MEMSIZE = 0x%X \n", esMEMS_FreeMemSize() );
	smenu_para.layer = tv_para->lyr_mmenu;
	smenu_para.sub_menu_id = tv_para->focus_id;
	smenu_para.smenu_font = tv_para->main_font;

	smenu_para.tv_bright = 30;
	smenu_para.tv_sourceInput = 0;
	smenu_para.tv_video_sys= 1;
	
//	smenu_para.tv_sys_data = tv_reg_para;
__here__;	
	tv_para->h_tv_menu = tv_sub_menu_win_create(tv_para->tv_manager, &smenu_para);	
	GUI_LyrWinSetSta(tv_para->lyr_mmenu, GUI_LYRWIN_STA_ON);
__here__;
//	GUI_WinSetFocusChild(tv_para->h_tv_menu);
	dsk_tv_rcv->tv_menuID = TVMENU_MAIN;
__here__;
}


static __s32 __tv_menu_scene_delete(tv_para_t* tv_ctrl)
{
	__s32 ret;	
	
	if (NULL == tv_ctrl)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}
	
	{
		__msg("tv_ctrl->h_tv_menu=%x\n", tv_ctrl->h_tv_menu);
		if (tv_ctrl->h_tv_menu)
		{
			tv_menu_scene_delete(tv_ctrl->h_tv_menu);
			tv_ctrl->h_tv_menu = NULL;
		}
	}
	dsk_tv_rcv->tv_menuID = TVMENU_NULL;
	return EPDK_OK;
}

static __s32 __tv_volume_scene_create(tv_para_t *tv_para)
{
	__s32 ret;	
	
	if (NULL == tv_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}
	
 	{
 		tv_volume_create_para_t create_para;
 		eLIBs_memset(&create_para, 0, sizeof(tv_volume_create_para_t));
 		create_para.hparent = tv_para->lyr_msound;
 		create_para.scene_id = 2;
		create_para.max_val = 30;
		create_para.min_val = 0;

		if(movie_muteflag == 1)
		{
			movie_muteflag = 0;
			dsk_volume_set(movie_volume);
		}
		create_para.cur_val = dsk_volume_get();	
		
		__msg("movie_volume_scene_create ...\n");
 		tv_para->h_tv_volume = tv_volume_scene_create(tv_para->tv_manager,&create_para);
 		if (NULL == tv_para->h_tv_volume)
 		{
 			__msg("movie_volume_scene_create fail...\n");
 			return EPDK_FAIL;
 		}
 	}
	dsk_tv_rcv->tv_menuID = TVMENU_VOL;
	return EPDK_OK;

}


static __s32 __tv_volume_scene_delete(tv_para_t* tv_para)
{
	__s32 ret;	
	
	if (NULL == tv_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}
	
 	{
 		if (tv_para->h_tv_volume)
 		{
 			movie_volume_scene_delete(tv_para->h_tv_volume);
 			tv_para->h_tv_volume = NULL;
 		}
 	}
	dsk_tv_rcv->tv_menuID = TVMENU_NULL;
	return EPDK_OK;
}


static __s32 __tv_num_scene_create(tv_para_t* tv_para)
{
	__s32 ret;	
	
	if (NULL == tv_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}

//    if (NULL == tv_para->playsta_scene)
	{
		tv_num_create_para_t create_para;
		eLIBs_memset(&create_para, 0, sizeof(tv_num_create_para_t));
	 	create_para.hparent = tv_para->lyr_mchannel;
 		create_para.scene_id = 3;
		create_para.max_val = 249;
		create_para.min_val = 1;
		create_para.cur_val = dsk_volume_get();
		tv_para->h_Channel = tv_num_scene_create(tv_para->tv_manager,&create_para);
		if (NULL == tv_para->h_Channel)
		{
			__msg("tv_num_scene_create fail...\n");
			return EPDK_FAIL;
		}
		
	}
	dsk_tv_rcv->tv_menuID = TVMENU_NUM;
	return EPDK_OK;
}

static __s32 __tv_num_scene_delete(tv_para_t* tv_para)
{
	__s32 ret;	
	
	if (NULL == tv_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}
	
	{
		if (tv_para->h_Channel)
		{
			tv_num_scene_delete(tv_para->h_Channel);
			tv_para->h_Channel = NULL;
		}
	}
	dsk_tv_rcv->tv_barflag = 0;
	dsk_tv_rcv->tv_barflag_input=0;
	dsk_tv_rcv->tv_barflag_inputval=0;	
	dsk_tv_rcv->tv_menuID = TVMENU_NULL;
	return EPDK_OK;
}


static __s32 __tv_mute_scene_create(tv_para_t* tv_para)
{
	__s32 ret;	
	
	if (NULL == tv_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}

//    if (NULL == tv_para->playsta_scene)
	{
		tv_mute_create_para_t create_para;
		eLIBs_memset(&create_para, 0, sizeof(tv_mute_create_para_t));
	 	create_para.hparent = tv_para->lyr_mute;
 		create_para.scene_id = 3;
		create_para.max_val = 249;
		create_para.min_val = 1;
		create_para.cur_val = dsk_volume_get();
		tv_para->h_mute = tv_mute_scene_create(tv_para->tv_manager,&create_para);
		if (NULL == tv_para->h_mute)
		{
			__msg("tv_mute_scene_create fail...\n");
			return EPDK_FAIL;
		}
		
	}
	dsk_tv_rcv->tv_menuID = TVMENU_MUTE;
	return EPDK_OK;
}

static __s32 __tv_mute_scene_delete(tv_para_t* tv_para)
{
	__s32 ret;	
	
	if (NULL == tv_para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}
	
	{
		if (tv_para->h_mute)
		{
			tv_mute_scene_delete(tv_para->h_mute);
			tv_para->h_mute = NULL;
		}
	}
	dsk_tv_rcv->tv_barflag = 0;
	dsk_tv_rcv->tv_barflag_input=0;
	dsk_tv_rcv->tv_barflag_inputval=0;	
	dsk_tv_rcv->tv_menuID = TVMENU_NULL;
	return EPDK_OK;
}


__s32 __TvOSD_si(__gui_msg_t *msg)
{

	tv_para_t *tv_para;

	tv_para = (tv_para_t *)GUI_WinGetAddData(msg->h_deswin);
	
	switch (dsk_tv_rcv->tv_menuID)
	{
		case TVMENU_MAIN:
		{
			__tv_menu_scene_delete(tv_para);
		}
		break;
		case TVMENU_VOL:
		{
			__tv_volume_scene_delete(tv_para);
		}
		break;
		case TVMENU_NUM:
		{
			__tv_num_scene_delete(tv_para);
		}
		break;
		case TVMENU_MUTE:
		{
			__tv_mute_scene_delete(tv_para);
		}
		break;		
		default:
			break;
	}
}

__s32 __TvOSD_OPEN(__gui_msg_t *msg,__s32 num)
{

	tv_para_t *tv_para;

	tv_para = (tv_para_t *)GUI_WinGetAddData(msg->h_deswin);

	__msg("num=%d\n",num);
	
	switch (num)
	{
		case TVMENU_MAIN:
		{
			__tv_menu_scene_create(tv_para);
		}
		break;
		case TVMENU_VOL:
		{
			__tv_volume_scene_create(tv_para);
		}
		break;
		case TVMENU_NUM:
		{
			__tv_num_scene_create(tv_para);
		}
		break;
		case TVMENU_MUTE:
		{
			__tv_mute_scene_create(tv_para);
		}
		break;		
		default:
			break;
	}
}


//extern __s32 com_video_in_open(__s32 dev_index, __s32 tvd_channel, __s32 enable_3d,__drv_TVD_system system);
static __s32 __tv_ctrl_para_init(__gui_msg_t *msg)
{
	     	__u32 raid;
		__u32 arg[3]={0};
			
		volatile __u32	addr ;
		volatile __u32 reg_vule=0 ;
	     		
		ES_FILE *paudio;
		ES_FILE *Fmdrv;
		
//		__u32 arg[3]={0};
	     	__u32 ret;

		if(app_tv_data)
		{		
			return EPDK_OK;
		}

		setting_reg_para = (reg_system_para_t*)dsk_reg_get_para_by_app(REG_APP_SYSTEM);
		
		app_tv_data = (app_tv_data_t *)esMEMS_Malloc(0,sizeof(app_tv_data_t));
		if(app_tv_data == NULL)
		{
			__msg("app_tv_data malloc error!\n");
			return EPDK_FAIL;
		}
		eLIBs_memset(app_tv_data, 0, sizeof(app_tv_data_t));	

		app_tv_data->h_tvwin = msg->h_deswin;	
		esDEV_Plugin("\\drv\\tv.drv", 0, 0, 1);

		dsk_tv_rcv_open();
		
		if(dsk_tv_rcv->sourceInput==0)
			com_video_in_open(1,1,0,1);
		else
			com_video_in_open(1,0,0,1);
		dsk_tv_rcv->ub_PN_sys = 1;
			
		__msg("__tv_para_init success...\n");

// AV audio  input    
            paudio = eLIBs_fopen("b:\\AUDIO\\FM", "r+");
           	if(!paudio)
    		{
        		__wrn("Open Audio Dev File Failed\n");
        		return EPDK_FAIL;
        	}
		app_tv_data->audio_drv = paudio;

		if(dsk_tv_rcv->sourceInput==0)
		 	eLIBs_fioctrl(paudio, AUDIO_DEV_CMD_START, 0xff, 0);	
		else
			eLIBs_fioctrl(paudio, AUDIO_DEV_CMD_START, 0, 0);	

		dsk_tv_rcv->lang = setting_reg_para->language;

	
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

		dsk_tv_set_sourceInput(0);

		 dsk_tv_set_cur_bright();
		 dsk_tv_set_cur_contrast();
		 dsk_tv_set_cur_color();	
		
		return EPDK_OK;
}


static __s32 tvinputnum(__u8 num)
{
	if(dsk_tv_rcv->sourceInput==0)
	{
		if(dsk_tv_rcv->tv_barflag<2)
			dsk_tv_rcv_curchafornum_play(num);		
	}		
}

static __s32 tvsouinputselect(void)
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

static __s32 tv_set_mute(void)
{
	if(movie_muteflag==1)
	{
		movie_muteflag = 0;
		dsk_volume_set(movie_volume);
	}
	else
	{
		movie_muteflag = 1;
		movie_volume = dsk_volume_get();
		dsk_volume_set(0);
	}
}


static __s32 tv_set_recall(void)
{
	__u32 num;
	num = dsk_tv_rcv->pre_channl;
	dsk_tv_rcv_curchafornum_play(num);
}

//movie_volume_scene_msg_volumeset


static __s32  tvmenu_key_proc(__gui_msg_t *msg)
{
	static __s32 last_key = -1;
	tv_para_t *tv_para;
	__u32 arg[3]={0};

    	__msg("app_tv_key->dwAddData1=%d, msg->dwAddData2=%d\n"
      		  ,msg->dwAddData1, msg->dwAddData2);


    	__msg("dsk_tv_rcv->tv_menuID=%d\n",dsk_tv_rcv->tv_menuID);	
		

	tv_para = (tv_para_t *)GUI_WinGetAddData(msg->h_deswin);

	if(msg->dwAddData1==GUI_MSG_IR_RIGHT)	
		msg->dwAddData1 = GUI_MSG_KEY_RIGHT;
	if(msg->dwAddData1==GUI_MSG_IR_LEFT)	
		msg->dwAddData1 = GUI_MSG_KEY_LEFT;		

		if(msg->dwAddData1==GUI_MSG_IR_LONGRIGHT)	
			msg->dwAddData1 = GUI_MSG_KEY_LONGRIGHT;
		if(msg->dwAddData1==GUI_MSG_IR_LONGLEFT)	
			msg->dwAddData1 = GUI_MSG_KEY_LONGLEFT;
		
		
	if (KEY_UP_ACTION == msg->dwAddData2)
	{

		__msg("**********tvmenu_key_proc 2**********\n");
		
			if(GUI_MSG_KEY_MENU==msg->dwAddData1)				
			{
				if(dsk_tv_rcv->tv_menuID==TVMENU_MAIN)
				{
					__TvOSD_si(msg);
					if(movie_muteflag==1)
						__TvOSD_OPEN(msg,TVMENU_MUTE);
				}
				else
				{
					__TvOSD_si(msg);
					__here__;
					__TvOSD_OPEN(msg,TVMENU_MAIN);
					
				}								
			}
			else if(GUI_MSG_KEY_LONGMENU==msg->dwAddData1)
			{			
				//__TvOSD_si(msg);
				//TV_cmd2parent(msg->h_deswin, SWITCH_TO_MMENU, 0, 0);
				long_key = 0;
			}	
	}
	else
	{
		__here__;
		__msg("app_tv_proc msg->id=%x,tv_para->scene_id=%d\n",tv_para->tv_manager,tv_para->scene_id);
			
		{
			{
	
				switch( msg->dwAddData1 )
				{
					case GUI_MSG_KEY_NUM0:
					case GUI_MSG_KEY_NUM1:
					case GUI_MSG_KEY_NUM2:
					case GUI_MSG_KEY_NUM3:
					case GUI_MSG_KEY_NUM4:
					case GUI_MSG_KEY_NUM5:
					case GUI_MSG_KEY_NUM6:
					case GUI_MSG_KEY_NUM7:
					case GUI_MSG_KEY_NUM8:
					case GUI_MSG_KEY_NUM9:	
						if(dsk_tv_rcv->sourceInput==0)
						{
							if(dsk_tv_rcv->tv_barflag==0)
							{
								if(dsk_tv_rcv->tv_menuID==TVMENU_NUM)
								{
									tvinputnum(msg->dwAddData1-GUI_MSG_KEY_NUM0);
								}						
								if(dsk_tv_rcv->tv_menuID==TVMENU_NULL)
								{
									tvinputnum(msg->dwAddData1-GUI_MSG_KEY_NUM0);
									__TvOSD_OPEN(msg,TVMENU_NUM);
								}
								if(dsk_tv_rcv->tv_menuID==TVMENU_VOL)
								{
									__TvOSD_si(msg);
									tvinputnum(msg->dwAddData1-GUI_MSG_KEY_NUM0);
									__TvOSD_OPEN(msg,TVMENU_NUM);
								}
								if(dsk_tv_rcv->tv_menuID==TVMENU_MUTE)
								{
									__TvOSD_si(msg);
									tvinputnum(msg->dwAddData1-GUI_MSG_KEY_NUM0);
									__TvOSD_OPEN(msg,TVMENU_NUM);
								}								
							}
						}	
						break;
					case GUI_MSG_KEY_VIDEO:
						if(dsk_tv_rcv->tv_menuID !=TVMENU_MAIN)
						{
							__TvOSD_si(msg);
							tvsouinputselect();
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}	
						break;
					case GUI_MSG_KEY_INFO:
						if(dsk_tv_rcv->tv_menuID==TVMENU_NUM)
						{
							__TvOSD_si(msg);
						}						
						else if(dsk_tv_rcv->tv_menuID==TVMENU_NULL)
						{
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						else if(dsk_tv_rcv->tv_menuID==TVMENU_VOL)
						{
							__TvOSD_si(msg);
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						else if(dsk_tv_rcv->tv_menuID==TVMENU_MUTE)
						{
							__TvOSD_si(msg);
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						break;
					case GUI_MSG_KEY_INTWO:
						if(dsk_tv_rcv->tv_menuID==TVMENU_VOL)
						{
							dsk_tv_rcv->tv_barflag = 1;	
							dsk_tv_rcv->tv_barflag_input=0;
							dsk_tv_rcv->tv_barflag_inputval=0;
							__TvOSD_si(msg);
							__TvOSD_OPEN(msg,TVMENU_NUM);				
						}
						if(dsk_tv_rcv->tv_menuID==TVMENU_NULL)
						{
							dsk_tv_rcv->tv_menuID = 1;
							dsk_tv_rcv->tv_barflag_input=0;
							dsk_tv_rcv->tv_barflag_inputval=0;
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						if(dsk_tv_rcv->tv_menuID==TVMENU_MUTE)
						{
							__TvOSD_si(msg);
							dsk_tv_rcv->tv_menuID = 1;
							dsk_tv_rcv->tv_barflag_input=0;
							dsk_tv_rcv->tv_barflag_inputval=0;
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						break;
					case GUI_MSG_KEY_RECALL:
						if(dsk_tv_rcv->tv_menuID==TVMENU_NUM)
						{
							tv_set_recall();
						}						
						if((dsk_tv_rcv->tv_menuID==TVMENU_VOL)||(dsk_tv_rcv->tv_menuID==TVMENU_MUTE))
						{
							__TvOSD_si(msg);
							tv_set_recall();
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						if(dsk_tv_rcv->tv_menuID==TVMENU_NULL)
						{
							tv_set_recall();
							__TvOSD_OPEN(msg,TVMENU_NUM);
						}
						break;
					case GUI_MSG_KEY_MUTE:
//						if(dsk_tv_rcv->tv_menuID!=TVMENU_VOL)
							__TvOSD_si(msg);
							tv_set_mute();
							if(movie_muteflag==1)
								__TvOSD_OPEN(msg,TVMENU_MUTE);
							else
								__TvOSD_si(msg);
						break;
						
					case GUI_MSG_KEY_LEFT:
					case GUI_MSG_KEY_LONGLEFT:	
					{			
						if(dsk_tv_rcv->tv_menuID==TVMENU_NULL)
						{
							__TvOSD_OPEN(msg,TVMENU_VOL);
						}
						if((dsk_tv_rcv->tv_menuID==TVMENU_NUM)||(dsk_tv_rcv->tv_menuID==TVMENU_MUTE))
						{
							__TvOSD_si(msg);
							__TvOSD_OPEN(msg,TVMENU_VOL);
						}
						
					}
					break;
					case GUI_MSG_KEY_RIGHT:
					case GUI_MSG_KEY_LONGRIGHT:
					{
						if(dsk_tv_rcv->tv_menuID==TVMENU_NULL)
						{
							__TvOSD_OPEN(msg,TVMENU_VOL);
						}
						if((dsk_tv_rcv->tv_menuID==TVMENU_NUM)||(dsk_tv_rcv->tv_menuID==TVMENU_MUTE))
						{
							__TvOSD_si(msg);
							__TvOSD_OPEN(msg,TVMENU_VOL);
						}				
					}
					break;
					case GUI_MSG_IR_DOWN:
					case GUI_MSG_IR_LONGDOWN:						
					case GUI_MSG_KEY_UP:
					case GUI_MSG_KEY_LONGUP:
					{
						if(dsk_tv_rcv->tv_barflag != 0)
						{
							dsk_tv_rcv->tv_barflag = 0;
							dsk_tv_rcv->tv_barflag_input=0;
							dsk_tv_rcv->tv_barflag_inputval=0;
						}						
						switch (dsk_tv_rcv->tv_menuID)
						{
							case TVMENU_NULL:
							{
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);							
							}	
								break;
							case TVMENU_VOL:	
							{
								__tv_volume_scene_delete(tv_para);
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);							
							}	
								break;
							case TVMENU_NUM:
							{
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();
							}
							break;
							case TVMENU_MUTE:
								__TvOSD_si(msg);
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);
								break;
							default:
								break;
						}
	
					}	
					break;		

					case GUI_MSG_IR_UP:
					case GUI_MSG_IR_LONGUP:	
					case GUI_MSG_KEY_LONGDOWN:
					case GUI_MSG_KEY_DOWN:	
					{
						if(dsk_tv_rcv->tv_barflag != 0)
						{
							dsk_tv_rcv->tv_barflag = 0;
							dsk_tv_rcv->tv_barflag_input=0;
							dsk_tv_rcv->tv_barflag_inputval=0;
						}							
						switch (dsk_tv_rcv->tv_menuID)
						{
							case TVMENU_NULL:
							{
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_next_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);
							}	
								break;
							case TVMENU_VOL:	
							{
								__TvOSD_si(msg);
								
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_next_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);
							}	
								break;
							case 3:
							{
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_next_freq_play();
							}
							break;
							case TVMENU_MUTE:
								__TvOSD_si(msg);
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_next_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);
								break;
							default:
								break;
						}

					}
					break;
					case GUI_MSG_KEY_ENTER:
					case GUI_MSG_KEY_LONGENTER:
					{
						switch (dsk_tv_rcv->tv_menuID)
						{
							case TVMENU_NULL:
							{				
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();
								__TvOSD_OPEN(msg,TVMENU_NUM);
							}
								break;
							case TVMENU_VOL:	
							{
								__TvOSD_si(msg);
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();								
								__TvOSD_OPEN(msg,TVMENU_NUM);
							}	
								break;
							case TVMENU_NUM:	
							{
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();
							}	
								break;
							case TVMENU_MUTE:

								__TvOSD_si(msg);
								if(dsk_tv_rcv->sourceInput==0)
									dsk_tv_rcv_pre_freq_play();								
								__TvOSD_OPEN(msg,TVMENU_NUM);								
								break;
							default:
								break;
						}		
					}
					break;
					case GUI_MSG_KEY_LONGMENU:
					{
						if(long_key++ >= 5) {
							long_key = 0;
							__TvOSD_si(msg);
							TV_cmd2parent(msg->h_deswin, SWITCH_TO_MMENU, 0, 0);
						}
					}
					break;
					default:
						break;
				}
			}	
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


static __s32 PNsysChange(__gui_msg_t *msg)
{

	__u8 PNsys;
	__u8 PNsys2;
	__u8 menunum=0;

	if(dsk_tv_rcv->search_flag==0)
	{
		dsk_tv_rcv->ubNorPicture = com_video_get_status();
		
		if(dsk_tv_rcv->ubNorPicture==1)
		{
			esKRNL_TimeDly(1);
			dsk_tv_rcv->ubNorPicture = com_video_get_status();

			if(dsk_tv_rcv->ubNorPicture==1)
			{
				esKRNL_TimeDly(1);
				PNsys = com_video_get_format();
				__msg("ubNorPicture=%d,PNsys=%d\n",dsk_tv_rcv->ubNorPicture,dsk_tv_rcv->ub_PN_sys);
				__msg("PNsys1=%d\n",dsk_tv_rcv->ubNorPicture,PNsys);
		
				if(dsk_tv_rcv->ub_PN_sys != PNsys)
				{
				
					esKRNL_TimeDly(1);
					PNsys2 = com_video_get_format();
					__msg("PNsys1=%d\n",dsk_tv_rcv->ubNorPicture,PNsys2);
					if(dsk_tv_rcv->ub_PN_sys != PNsys2)
					{
						dsk_tv_rcv->ub_PN_sys = PNsys;
						
						com_video_in_close();
						__msg("close video in\n");
						esKRNL_TimeDly(1);

						menunum = dsk_tv_rcv->tv_menuID;
						__TvOSD_si(msg);
						if(dsk_tv_rcv->sourceInput==0)
						{
							if(dsk_tv_rcv->ub_PN_sys==0)
								com_video_in_open(1,1,0,0);
							else
								com_video_in_open(1,1,0,1);
						}	
						else
						{
							if(dsk_tv_rcv->ub_PN_sys==0)
								com_video_in_open(1,0,0,0);
							else
								com_video_in_open(1,0,0,1);
						}					
						__TvOSD_OPEN(msg,menunum);
						__msg("open video in\n");
						
						
					}
						
				}
			}
		}
	}
}

static void searchOver(__gui_msg_t *msg)
{
	if(dsk_tv_rcv->manual_search_way==1)
	{
		dsk_tv_rcv ->cur_channl = 1;
		dsk_tv_rcv ->pre_channl = 1;
		dsk_tv_rcv_curchafornum_play(0);	

		__TvOSD_si(msg);
		__TvOSD_OPEN(msg,TVMENU_NUM);		
	}
}


#define TV_MENU_ID  		(APP_TV_ID +1)
#define TV_VOL_ID		(APP_TV_ID +2)
#define TV_CHA_ID		(APP_TV_ID +3)	
#define TV_MUTE_ID		(APP_TV_ID +4)

static __s32 app_tv_proc(__gui_msg_t *msg)
{
//    __msg("app_home_proc msg->id=%d, msg->h_deswin=%x, msg->dwAddData1=%d, msg->dwAddData2=%d\n"
//       ,msg->id, msg->h_deswin, msg->dwAddData1, msg->dwAddData2);

//	__msg("OSD ID=%d\n",dsk_tv_rcv->tv_menuID);
//	__msg("cur_freq=%d,cur_channl=%d,total_channl=%d\n",dsk_tv_rcv->cur_freq,dsk_tv_rcv->cur_channl,dsk_tv_rcv->total_channl);	

	switch(msg->id)
	{
	case GUI_MSG_CREATE:
		{
			tv_para_t *tv_para;
			root_para_t *root_para;
			RECT	rect;
			__s32           		screen_width;
    			__s32 			screen_height;

			root_para = (root_para_t *)GUI_WinGetAttr(msg->h_deswin);
			tv_para = (tv_para_t *)esMEMS_Balloc(sizeof(tv_para_t));
   	             if(!tv_para)
   	             {
   	                 return EPDK_FAIL;
   	             }
			eLIBs_memset((void *)tv_para, 0, sizeof(tv_para_t));

			tv_para->main_font = root_para->font;

			__msg("tv_para->main_font=%x\n",tv_para->main_font);
			
			GUI_WinSetAddData(msg->h_deswin, (__u32)tv_para);
			tv_para->tv_manager = msg->h_deswin;
			
			tv_para->focus_id = 0;	
			tv_para->first_item = 0;
			tv_para->scene_id = 0;
			
			g_disable_close_scn();
            		//__movie_set_title();
            		//gscene_hbar_set_state(HBAR_ST_SHOW);
            		gscene_hbar_set_state(HBAR_ST_HIDE);
            		gscene_bgd_set_state(BGD_STATUS_HIDE);

					
			__msg("tv sin=%x\n",msg->h_deswin);
			
//			dsk_tv_rcv->h_tvwin = msg->h_deswin;	
			
//			__msg("win to dsk_tv_rcv=%x\n",dsk_tv_rcv->h_tvwin);		
			//background
//			gscene_bgd_set_state(GUI_LYRWIN_STA_ON);//   BGD_STATUS_HIDE//GUI_LYRWIN_STA_ON
			__tv_ctrl_para_init(msg);

			__tv_num_scene_create(tv_para);
//			com_set_palette_by_id(ID_HOME_PAL_BMP);

//			tv_reg_para = dsk_reg_get_para_by_app(REG_APP_TV);

			__here__;
			__msg("tv_para->tv_manager=%x\n",tv_para->tv_manager);
			
		}
		return EPDK_OK;
	case GUI_MSG_CLOSE:
		GUI_ManWinDelete(msg->h_deswin);
		return EPDK_OK;
	case GUI_MSG_DESTROY:
		{
			tv_para_t *home_para;

			home_para = (tv_para_t *)GUI_WinGetAddData(msg->h_deswin);
			
            		esMEMS_Bfree(home_para, sizeof(tv_para_t));

			if(dsk_tv_rcv->sourceInput==1)
			{
				 eLIBs_fioctrl(app_tv_data->audio_drv, AUDIO_DEV_CMD_STOP, 0, 0);	
			}	 
			else
			{
				 eLIBs_fioctrl(app_tv_data->audio_drv, AUDIO_DEV_CMD_STOP, 0xff, 0);
			}	

			__TvOSD_si(msg);

			com_video_in_close();		
			setting_reg_para->language = dsk_tv_rcv->lang;
			dsk_tv_rcv_save_search_result();
			dsk_tv_rcv_close();
			

			esMEMS_Mfree(0,app_tv_data);
			app_tv_data = NULL;
		}
		return EPDK_OK;
	case GUI_MSG_KEY:
		__msg("******app_home_proc GUI_MSG_KEY*****\n");
			tvmenu_key_proc(msg);
			break;
	case GUI_MSG_TOUCH:
		return EPDK_OK;
			break;
	case DSK_MSG_FS_PART_PLUGIN:
	case DSK_MSG_FS_PART_PLUGOUT:

		return EPDK_OK;
	case DSK_APP_RESTORE:

		return EPDK_OK;
	case GUI_MSG_COMMAND:
		{
			tv_para_t *tv_para_comman;

			tv_para_comman = (tv_para_t *)GUI_WinGetAddData(msg->h_deswin);

			switch(LOWORD(msg->dwAddData1))
			{
				case TV_MENU_ID:
				{
					switch(HIWORD(msg->dwAddData1))
					{
						case 0:break;
						case 1:break;
						case 2:break;
						case 3:break;
						case 4:break;
						case 5:break;
						case 6:
							__tv_menu_scene_delete(tv_para_comman);	
							if(movie_muteflag==1)
								__TvOSD_OPEN(msg,TVMENU_MUTE);
							break;
						default:break;
							
					}
				}
				case TV_VOL_ID:
					switch(HIWORD(msg->dwAddData1))
					{
						case 0:
							__tv_volume_scene_delete(tv_para_comman);	
							if(movie_muteflag==1)
								__TvOSD_OPEN(msg,TVMENU_MUTE);
							break;
						case 1:break;
						case 2:break;
						default:break;	
					}					
					break;
				case TV_CHA_ID:
					switch(HIWORD(msg->dwAddData1))
					{
						case 0:
							__tv_num_scene_delete(tv_para_comman);	
							if(movie_muteflag==1)
								__TvOSD_OPEN(msg,TVMENU_MUTE);
							break;
						case 1:break;
						case 2:break;
						default:break;
							
					}						
					break;
				case TV_MUTE_ID:
					switch(HIWORD(msg->dwAddData1))
					{
						case 0:
							__tv_mute_scene_delete(tv_para_comman);	
							if(movie_muteflag==1)
								__TvOSD_OPEN(msg,TVMENU_MUTE);
							break;
						case 1:break;
						case 2:break;
						default:break;
							
					}						
					break;					
				case APP_TV_ID:
					switch(HIWORD(msg->dwAddData1))
					{
						case 0:
							PNsysChange(msg);
							break;
						case 1:
							searchOver(msg);
							break;
						case 2:
							dsk_tv_rcv_curchafornum_play(0);
							break;
						default:break;
							
					}						
					break;				
				default:break;
			}	
		return EPDK_OK;
	}
	default:break;
}
	
	return GUI_ManWinDefaultProc(msg);	
}

/*******************************************************************************************************
*********************************************************************************************************/
H_WIN app_tv_create(root_para_t *para)
{
	__gui_manwincreate_para_t create_info;

	__inf("****************************************************************************************\n");
	__inf("********  enter TV app  **************\n");
	__inf("****************************************************************************************\n");

	//__wait__;
	
	eLIBs_memset(&create_info, 0, sizeof(__gui_manwincreate_para_t));
	
	create_info.name            = APP_TV;
	create_info.hParent         = para->h_parent;
	create_info.ManWindowProc   = (__pGUI_WIN_CB)esKRNL_GetCallBack((__pCBK_t)app_tv_proc); 
	create_info.attr            = (void*)para;
	create_info.id				= APP_TV_ID;
	create_info.hHosting        = NULL;

	return(GUI_ManWinCreate(&create_info));
}

/*
**************************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           LARK app sample
*
*						        	(c) Copyright 2006-2007, TERRY, China
*											 All Rights Reserved
*
* File    : dsk_radio.c
* By      : terry
* Version : V1.00
* time    : 2009-12-01
**************************************************************************************************************
*/

//#include "..\\dsk_radio_i.h"
//#include "list_file.h"
//#include "com_video_in.h"
#include "epdk.h"
#include "tv_mannger.h"
#include "app_tv_i.h"

/*
__pCBK_t volatile  cb_search_success  = NULL;
void   * volatile  cb_ctx_search_success  = NULL;

__pCBK_t volatile  cb_search_fail  = NULL;
void   * volatile  cb_ctx_search_fail  = NULL;

__pCBK_t volatile  cb_search_over  = NULL;
void   * volatile  cb_ctx_search_over  = NULL;
*/

#if 0
typedef struct
{
	ES_FILE 				*tv_drv;
	ES_FILE 				*audio_drv;
	H_WIN       			h_deswin;	
	__u8 				thread_id;
	__u8				ubLocked;
	__u8				ub_PN_sys;		
	__u8				ubNorPicture;
	__u8				ubSearchStart;
	__u8				wait_timer;
	__u8				tv_barflag;
	__u8				tv_barflag_input;
	__u32				tv_barflag_inputval;	
	__u8				tv_menuID;	
	__u8				tv_muteflag;
	__u8				tv_voldata;		
	__u32				ucTestFre;				//读出的高频头数据
	__u32				ucSoundSys;
	__u32				cur_freq;
	__u32				manual_search_way;		//add by Kingvan
	__u32				auto_maual_mode;
	__u32				search_flag;/*1,searching,2,search over*/	
	__u32				total_channl;
	__u32				cur_channl;
	__u32				pre_channl;	
	__u32				bright;
	__u32				sourceInput;	
	__u32				channltable[200];
	__u8				SoundSystable[200];

}dsk_tv_rcv_t;
#endif

dsk_tv_rcv_t *dsk_tv_rcv = NULL;


__s32  tvserch_cmd2tvmenu(H_WIN hwin, __s32 id, __s32 data2, __s32 reserved)
{
	H_WIN hparent;
	__gui_msg_t msg;
	
	hparent = GUI_WinGetParent(hwin);
	if (!hparent)
	{
		__err("hparent is null...\n");
		return EPDK_FAIL;
	}

//	msg.h_deswin = hparent;
	msg.h_deswin = hwin;
	msg.h_srcwin = hwin;
	
	if((msg.h_srcwin==NULL)||(msg.h_deswin==NULL))
		return EPDK_OK;
	
	msg.id = GUI_MSG_COMMAND;
	msg.dwAddData1 = MAKELONG(GUI_WinGetItemId(hwin), id);
	msg.dwAddData2 = data2;
	msg.dwReserved = reserved;
	
	GUI_SendNotifyMessage(&msg);
	
	return EPDK_OK;
}



void __autosearch_thread(void *p_arg)
{
	dsk_tv_rcv_t *dsk_tv_rcv;
	
	__u32 result=0;
	__s32 channel_no=0;
//	__u32 shemod=0;
	__u32 timercnt=0;

	
	dsk_tv_rcv = (dsk_tv_rcv_t *)p_arg;
	
	while(1)
	{
		if(esKRNL_TDelReq(EXEC_prioself) == OS_TASK_DEL_REQ)
        	{     
            		esKRNL_TDel(EXEC_prioself);

            		break;
        	}
        	if(dsk_tv_rcv->search_flag == 0x01)
        	{
        		if(dsk_tv_rcv->wait_timer>0)
        		{
				dsk_tv_rcv->wait_timer--;
				if(dsk_tv_rcv->wait_timer==0)
				{
					timercnt++;
					if(timercnt>2)
					{
						timercnt = 0;
						result++;
						tvserch_cmd2tvmenu(app_tv_data->h_menuwin,6,0,0);
					}
						
					__msg("total ch =%d, cur_fre=%d, Loced=%d, ubNorPicture=%d\n"
        				,dsk_tv_rcv->total_channl, dsk_tv_rcv->cur_freq, dsk_tv_rcv->ubLocked, dsk_tv_rcv->ubNorPicture);
	
					if ((dsk_tv_rcv->auto_maual_mode == 0x31) || (dsk_tv_rcv->auto_maual_mode== 0x30))  //微调..
					{
						dsk_tv_rcv->wait_timer = 20;
						dsk_tv_rcv->search_flag  =2;
					}            
		            
					if (dsk_tv_rcv->ubLocked==1)  //当信号锁定
					{
						dsk_tv_rcv->ubLocked = 0;
				
						if (dsk_tv_rcv->auto_maual_mode == 0x10)			
						{
							dsk_tv_rcv->cur_channl++;
							dsk_tv_rcv->total_channl++;

							dsk_tv_rcv->ubSearchStart = 1;  	 
							dsk_tv_rcv->wait_timer = 3;

						   	dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl] = dsk_tv_rcv->cur_freq;
							dsk_tv_rcv->SoundSystable[dsk_tv_rcv->cur_channl] = dsk_tv_rcv->ucSoundSys;							
						}
						else 
						{
							dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl] = dsk_tv_rcv->cur_freq;
							dsk_tv_rcv->SoundSystable[dsk_tv_rcv->cur_channl] = dsk_tv_rcv->ucSoundSys;	
							dsk_tv_rcv->auto_maual_mode	 = 0xff;
							dsk_tv_rcv->search_flag = 2;
						}
					}
					else  //信号未锁定
					{               
						if (dsk_tv_rcv->auto_maual_mode == 0xee)
						{
							dsk_tv_rcv->auto_maual_mode = 0xff;
							dsk_tv_rcv->search_flag = 2;
						}
						else
						{

							if(dsk_tv_rcv->auto_maual_mode==0x10)
								dsk_tv_rcv->shemod = 1;
							else
								dsk_tv_rcv->shemod = 0;

							dsk_tv_rcv->wait_timer = 4;			//   2
							dsk_tv_rcv->ubNorPicture = com_video_get_status();
	

							if ((dsk_tv_rcv->auto_maual_mode == 0x10)||(dsk_tv_rcv->auto_maual_mode == 0x20))
							{
								TVSearchNextChannel();                    
							}
							else if (dsk_tv_rcv->auto_maual_mode == 0x21)
							{
								TVSearchPreChannel();
							}						
						}
					}
				}
        		}
	        }
	        if(dsk_tv_rcv->search_flag == 0x02)
	        {
				if(dsk_tv_rcv->shemod == 1)
				{
					dsk_tv_rcv ->cur_channl = 1;
					dsk_tv_rcv ->pre_channl = 1;
//					dsk_tv_rcv_curchafornum_play(0);
					tvserch_cmd2tvmenu(app_tv_data->h_tvwin,2,0,0);
				}
				dsk_tv_rcv_save_search_result();
				
				tvserch_cmd2tvmenu(app_tv_data->h_tvwin,1,0,0);
				
				tvserch_cmd2tvmenu(app_tv_data->h_menuwin,5,0,0);
				
			    	dsk_tv_rcv->search_flag = 0x00;
				dsk_tv_rcv->auto_maual_mode = 0xff;
				__here__;			
	        }
		if(dsk_tv_rcv->search_flag==0)
		{
			timercnt++;
			if(timercnt>4)
			{
				timercnt = 0;
				result++;
				tvserch_cmd2tvmenu(app_tv_data->h_tvwin,0,0,0);
			}
		}
        	esKRNL_TimeDly(4);
	}
}

__u32 dsk_tv_rcv_open(void)
{	
	__u32 freq;
	__u32 arg[3]={0};
	

	if(dsk_tv_rcv)
	{		
		return EPDK_OK;
	}
	
	dsk_tv_rcv = (dsk_tv_rcv_t *)esMEMS_Malloc(0,sizeof(dsk_tv_rcv_t));
	if(dsk_tv_rcv == NULL)
	{
		__msg("dsk_tv_rcv malloc error!\n");
		return EPDK_FAIL;
	}
	eLIBs_memset(dsk_tv_rcv, 0, sizeof(dsk_tv_rcv_t));

	app_tv_data->tv_drv =eLIBs_fopen("b:\\USER\\TUNER", "r+");

		
	esKRNL_TimeDly(3);		
		
	dsk_tv_rcv_get_sd_data();

//	dsk_tv_rcv->cvbsflag = 0;
	
	dsk_tv_rcv->thread_id = esKRNL_TCreate(__autosearch_thread, (void *)dsk_tv_rcv, 0x400,KRNL_priolevel3);

	return EPDK_OK;
}


__bool dsk_tv_rcv_is_open(void)
{
	if(dsk_tv_rcv)
	{
		return EPDK_TRUE;
	}
	else
	{
		return EPDK_FALSE;
	}
}

__s32 dsk_tv_rcv_next_freq_play(void)
{
	__u32 freq;
	__s32 result;
	__u32 arg[3]={0};
	__u32 num;
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}

	num = dsk_tv_rcv->cur_channl;
	if(num<dsk_tv_rcv->total_channl)
		num++;
	else
		num = 1;	
	
	dsk_tv_rcv_curchafornum_play(num);
/*
	dsk_tv_rcv->pre_channl = dsk_tv_rcv->cur_channl;
	
	if(dsk_tv_rcv->cur_channl<dsk_tv_rcv->total_channl)
		dsk_tv_rcv->cur_channl++;
	else
		dsk_tv_rcv->cur_channl = 1;


	dsk_tv_rcv->ucSoundSys = dsk_tv_rcv->SoundSystable[dsk_tv_rcv->cur_channl ];
	if(dsk_tv_rcv->ucSoundSys>5)
		dsk_tv_rcv->ucSoundSys = 1;

	dsk_tv_rcv->cur_freq = dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl];
	freq = dsk_tv_rcv->cur_freq;
	
	if(dsk_tv_rcv->search_flag == 0x01 || dsk_tv_rcv->search_flag == 0x02)
	{
		return -1;
	}

    	if(freq > FREQ_TOP_BAND_VALUE)
    	{
        	freq = FREQ_LOW_BAND_VALUE;
    	}
//	arg[0] = freq+2750000;	
	__msg("cur_fre=%d,cur_channl=%d,total_num=%d\n",dsk_tv_rcv->cur_freq,dsk_tv_rcv->cur_channl,dsk_tv_rcv->total_channl);
 //   	result = eLIBs_fioctrl(app_tv_data->tv_drv, 3, 1, (void *)arg);
 	SetFreDatato2137(freq);
	SetColorDatato2137();
 	SetSoundDatato2137();	
 */
 
	return result;
}

__s32 dsk_tv_rcv_pre_freq_play(void)
{
	__u32 freq;
	__s32 result;
	__u32 arg[3]={0};
	__u32 num;
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}

	num = dsk_tv_rcv->cur_channl;
	if(num>1)
		num--;
	else
		num = dsk_tv_rcv->total_channl;	
	
	dsk_tv_rcv_curchafornum_play(num);	

/*	
	dsk_tv_rcv->pre_channl = dsk_tv_rcv->cur_channl;
	
	if(dsk_tv_rcv->cur_channl>1)
		dsk_tv_rcv->cur_channl--;
	else
		dsk_tv_rcv->cur_channl = dsk_tv_rcv->total_channl;

	dsk_tv_rcv->cur_freq = dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl];
	freq = dsk_tv_rcv->cur_freq;
	
	if(dsk_tv_rcv->search_flag == 0x01 || dsk_tv_rcv->search_flag == 0x02)
	{
		return -1;
	}

    	if(freq > FREQ_TOP_BAND_VALUE)
    	{
        	freq = FREQ_LOW_BAND_VALUE;
    	}
		
	dsk_tv_rcv->ucSoundSys = dsk_tv_rcv->SoundSystable[dsk_tv_rcv->cur_channl ];
	if(dsk_tv_rcv->ucSoundSys>5)
		dsk_tv_rcv->ucSoundSys = 1;
		
//	arg[0] = freq+2750000;	
	__msg("cur_fre=%d,cur_channl=%d,total_num=%d\n",dsk_tv_rcv->cur_freq,dsk_tv_rcv->cur_channl,dsk_tv_rcv->total_channl);
//    	result = eLIBs_fioctrl(app_tv_data->tv_drv, 3, 1, (void *)arg);
	SetFreDatato2137(freq);
	SetColorDatato2137();
	SetSoundDatato2137();	
*/	
	return 1;
}




__s32 dsk_tv_rcv_curchafornum_play(__u32 num)
{
	__u32 freq;
	__s32 result;
	__u32 arg[3]={0};
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}

	dsk_tv_rcv->pre_channl = dsk_tv_rcv->cur_channl;	
	if(num>0)
	{
		dsk_tv_rcv->cur_channl = num;
		dsk_tv_rcv->cur_freq = dsk_tv_rcv->channltable[num]; 
	}		
	else
	{
		dsk_tv_rcv->cur_freq = dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl];
	}
	freq = dsk_tv_rcv->cur_freq;
	
	if(dsk_tv_rcv->search_flag == 0x01 || dsk_tv_rcv->search_flag == 0x02)
	{
		return -1;
	}

    	if(freq > FREQ_TOP_BAND_VALUE)
    	{
        	freq = FREQ_LOW_BAND_VALUE;
    	}
		
	dsk_tv_rcv->ucSoundSys = dsk_tv_rcv->SoundSystable[dsk_tv_rcv->cur_channl ];
	if((dsk_tv_rcv->ucSoundSys>5)||(dsk_tv_rcv->ucSoundSys==0))
		dsk_tv_rcv->ucSoundSys = 1;
	
//	arg[0] = freq+2750000;	

//		result = eLIBs_fioctrl(app_tv_data->tv_drv, 3, 1, arg);
		SetFreDatato2137(freq);
		SetSoundDatato2137();
		SetColorDatato2137();

//		SetFreDatato2137(freq);
//		SetSoundDatato2137();
//		SetColorDatato2137();
				
	return 1;
}




__s32 dsk_tv_rcv_get_search_result_vn(void)
{
	__s32 valid_num;
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}
	
	valid_num = dsk_tv_rcv->total_channl;
	
	return valid_num;
}


__s32 dsk_tv_rcv_get_sd_data(void)
{
	__u32 i;
	reg_tv_para_t* para;
    __msg("get tv data!\n");	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}

	para = (reg_tv_para_t*)dsk_reg_get_para_by_app(REG_APP_TV);

	dsk_tv_rcv->bright = para->bright;
	if(dsk_tv_rcv->bright>100)
		dsk_tv_rcv->bright = 50;
	dsk_tv_rcv->contrast = para->contrast;	
	if(dsk_tv_rcv->contrast>100)
		dsk_tv_rcv->contrast = 50;
	dsk_tv_rcv->color = para->color;		
	if(dsk_tv_rcv->color>100)
		dsk_tv_rcv->color = 50;	
	dsk_tv_rcv->sourceInput = para->sourceInput;
	if(dsk_tv_rcv->sourceInput>1)
		dsk_tv_rcv->sourceInput = 0;
	dsk_tv_rcv->cur_channl= para->channel_id;

	dsk_tv_rcv->pre_channl= dsk_tv_rcv->cur_channl;
	dsk_tv_rcv->total_channl= para->total_channel;
	if(dsk_tv_rcv->total_channl>199)
		dsk_tv_rcv->total_channl = 1;

	if(dsk_tv_rcv->cur_channl>dsk_tv_rcv->total_channl)
		dsk_tv_rcv->cur_channl=1;
	
	for(i=1;i<=dsk_tv_rcv->total_channl;i++)
	{
		dsk_tv_rcv->channltable[i] =para->tv_channel[i]; 
		dsk_tv_rcv->SoundSystable[i] =para->SoundSystable[i]; 		
	}

	dsk_tv_rcv->tv_barflag = 0;
	
}


__s32 dsk_tv_rcv_save_search_result(void)
{
	__u32 i;
	reg_tv_para_t* para;
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}
    __msg("save tv data!\n");
	para = (reg_tv_para_t*)dsk_reg_get_para_by_app(REG_APP_TV);
//	para->mode = 1;
	for(i=1;i<200;i++)
	{
		para->tv_channel[i] = 0;
		para->SoundSystable[i] = 0;
	}

	for(i=1;i<200;i++)
	{
		para->tv_channel[i] = dsk_tv_rcv->channltable[i];
		para->SoundSystable[i] = dsk_tv_rcv->SoundSystable[i];		
	}
	para->bright = dsk_tv_rcv->bright;
	para->contrast= dsk_tv_rcv->contrast;
	para->color= dsk_tv_rcv->color;
	para->sourceInput = dsk_tv_rcv->sourceInput;
	para->channel_id = dsk_tv_rcv->cur_channl;
	para->Pre_channel_id = dsk_tv_rcv->pre_channl;
	para->total_channel= dsk_tv_rcv->total_channl;
	
	dsk_reg_flush();
	
	return EPDK_OK;
}


__s32 dsk_tv_rcv_close(void)
{
	__s32 result = 0;
	
	if(dsk_tv_rcv == NULL)
	{
		__msg("radio receive not open!\n");
		return EPDK_FAIL;
	}	

	if(dsk_tv_rcv->thread_id)
	{
		while(1)
		{       
			if(esKRNL_TDelReq(dsk_tv_rcv->thread_id) == OS_TASK_NOT_EXIST)
			{
			    break;
			}
			esKRNL_TimeDly(3);        
		}
	}
	
	result = eLIBs_fioctrl(app_tv_data->tv_drv, 2, 0, 0);
	
	esMEMS_Mfree(0,dsk_tv_rcv);
	dsk_tv_rcv = NULL;
	return result;
}


__s32 SetFreDatato2137(__u32 frep)
{
	__u32 arg[3]={0};
	if((frep>FREQ_TOP_BAND_VALUE)||(frep<FREQ_LOW_BAND_VALUE))
		return EPDK_FAIL;
	
	switch(dsk_tv_rcv->ucSoundSys) 
	{
		case 1:
		case 2:
			frep = frep + 2750000;
			break;
		case 3:
			frep = frep + 2250000;
			break;
		case 4:
		case 5:
			frep = frep + 1750000;
			break;
		default:
			break;
	}
	arg[0] = frep;
	eLIBs_fioctrl(app_tv_data->tv_drv, 3, 1, arg);	
	return 1;
}

__s32 SetSoundDatato2137(void)
{
	__u32 arg[3]={0};

	if(dsk_tv_rcv->ucSoundSys==4)
		arg[0] = 1;
	else
		arg[0] = 0;
	eLIBs_fioctrl(app_tv_data->tv_drv, 4, 1, arg);	
	return 1;
}

__s32 SetColorDatato2137(void)
{
	__u32 arg[3]={0};

	arg[0] = dsk_tv_rcv->ucSoundSys;
	eLIBs_fioctrl(app_tv_data->tv_drv, 5, 1, arg);	
	return 1;
}


void Get2137PllData(void)
{
	__u32 var=0;
	__u8 ucTestTT[11];
//	__u32 arg[3]={0};

	dsk_tv_rcv->ucTestFre = 0;
//	TestWrite2137Data();
	eLIBs_fioctrl(app_tv_data->tv_drv, 6, 1, ucTestTT);
	var = ucTestTT[5];
	var = var<<8;
	var += ucTestTT[4];

	__msg("ucTestTT[4] =%d, ucTestTT[5]=%d\n",ucTestTT[4], ucTestTT[5]);
	
	if(ucTestTT[5]>0xf0)
	{
		var = 0x10000 - var;
//		ucTestFre = 1000*var;
		dsk_tv_rcv->ucTestFre = 1000*var;
		dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq- dsk_tv_rcv->ucTestFre; 
		
	}	
	else
	{
//		ucTestFre = 1000*var;
//		ucSi2137Fre = ucSi2137Fre + ucTestFre; 	
		dsk_tv_rcv->ucTestFre = 1000*var;
		dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq + dsk_tv_rcv->ucTestFre; 
	}	
	if(dsk_tv_rcv->ucTestFre>40000)
	{
//		CTunerSetFreq(0);
//		arg[0] = dsk_tv_rcv->cur_freq;
//		eLIBs_fioctrl(app_tv_data->tv_drv, 3, 1, arg);
		SetFreDatato2137(dsk_tv_rcv->cur_freq);
	}	

}

/*
void Get2137PllData(void)
{
	UINT32 var=0;
	ucTestFre = 0;
	var = ucTestTT[5];
	var = var<<8;
	var += ucTestTT[4];
	
	if(ucTestTT[5]>0xf0)
	{
		var = 0x10000 - var;
		ucTestFre = 1000*var;
		ucSi2137Fre = ucSi2137Fre -ucTestFre; 
	}	
	else
	{
		ucTestFre = 1000*var;
		ucSi2137Fre = ucSi2137Fre + ucTestFre; 
	}	
	
	if(ucTestFre>40000)
		CTunerSetFreq(0);
}
*/

void PllChangeTuneStep(__u32 step,__u32 flag)
{
	__u32 arg[3]={0};
	__u32 freq;
	if (flag==1)
	{
		freq = dsk_tv_rcv->cur_freq;
		freq += step;
		if(freq>=FREQ_TOP_BAND_VALUE)
		{
			if (dsk_tv_rcv->auto_maual_mode == 0x10)
				dsk_tv_rcv->auto_maual_mode = 0xee;
			dsk_tv_rcv->cur_freq = FREQ_LOW_BAND_VALUE;
		}
		else
			dsk_tv_rcv->cur_freq  = freq;
		
	}
	else//ud_flag = 0
	{
		freq = dsk_tv_rcv->cur_freq;
		freq -= step;
		if(freq>FREQ_LOW_BAND_VALUE)
			dsk_tv_rcv->cur_freq = freq;
		else
		{
			dsk_tv_rcv->cur_freq = FREQ_TOP_BAND_VALUE;
		}
	}

	SetFreDatato2137(dsk_tv_rcv->cur_freq);

//	SetFreDatato2137(dsk_tv_rcv->cur_freq);
}

void PllSearchChannelProcessDown(void)
{
	 __u32 arg[3]={0};
        if (dsk_tv_rcv->ubSearchStart==1)
	{
          	if (dsk_tv_rcv->ubNorPicture==1)
		{
			PllChangeTuneStep(2000000, 0);
			return;
		}
		else
		{	
			dsk_tv_rcv->ubSearchStart = 0;
			PllChangeTuneStep(1000000, 0);
			return;
		}
		
        }
        else
        {
            	if((dsk_tv_rcv->ubNorPicture==0)) //无信号
           	{
			PllChangeTuneStep(500000, 0);
			return;
            	}
            	else             
            	{
             
 			esKRNL_TimeDly(5);
			Get2137PllData();
			esKRNL_TimeDly(5);
			dsk_tv_rcv->ubNorPicture = com_video_get_status();
			if(dsk_tv_rcv->ubNorPicture==1)
			{
				dsk_tv_rcv->ubLocked = 1;
/*				if((dsk_tv_rcv->ucSoundSys==0)||(dsk_tv_rcv->ucSoundSys==1))
					dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq - 2750000;
				else if(dsk_tv_rcv->ucSoundSys==2)
					dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq - 2250000;
				else
					dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq - 1750000;
*/					
			}		
            
            	}
       }
}


/*通用自动搜台&&向前手动搜台*/
void PllSearchChannelProcessUp(void)
{
	__u32 arg[3]={0};
	
	if ((dsk_tv_rcv->auto_maual_mode== 0x20) || (dsk_tv_rcv->auto_maual_mode == 0x10))
	{
		if (dsk_tv_rcv->ubSearchStart==1)
		{          
			if (dsk_tv_rcv->ubNorPicture)
			{				
				PllChangeTuneStep(2000000, 1);
				return;
			}
			else
			{	
				dsk_tv_rcv->ubSearchStart = 0;
				PllChangeTuneStep(1000000, 1);
				return;
			}
			
		}
		else
		{
			if((dsk_tv_rcv->ubNorPicture==0)) //无信号
			{            
				PllChangeTuneStep(500000,1);
				return;
			}
			else             
			{                 	
				esKRNL_TimeDly(5);
				Get2137PllData();
				esKRNL_TimeDly(5);
				dsk_tv_rcv->ubNorPicture = com_video_get_status();
				if(dsk_tv_rcv->ubNorPicture==1)
				{
					dsk_tv_rcv->ubLocked = 1;
/*					if((dsk_tv_rcv->ucSoundSys==0)||(dsk_tv_rcv->ucSoundSys==1))
						dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq - 2750000;
					else if(dsk_tv_rcv->ucSoundSys==2)
						dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq - 2250000;
					else
						dsk_tv_rcv->cur_freq = dsk_tv_rcv->cur_freq - 1750000;
*/						
				}					
			}
		}
	}
}

/*
*自动搜台或向前手动搜台
*/
void TVSearchNextChannel(void)
{	
	{
		PllSearchChannelProcessUp();
	}
}

/*
*  向后手动搜台
*/
void TVSearchPreChannel(void)
{	
	{
		PllSearchChannelProcessDown();				
	}
}


void TvSearchChannel(__u32 tvsys)
{
	__u32 arg[3]={0};
	dsk_tv_rcv->ubLocked = 0;
	dsk_tv_rcv->ubNorPicture = 0;
	dsk_tv_rcv->ubSearchStart = 1;
	dsk_tv_rcv->wait_timer =5;
	dsk_tv_rcv->search_flag = 1;/*1,searching,2,search over*/	

	if(dsk_tv_rcv->auto_maual_mode==0x10)
	{
		dsk_tv_rcv->cur_freq = FREQ_LOW_BAND_VALUE;
		dsk_tv_rcv->total_channl = 0;
		dsk_tv_rcv->cur_channl = 0;
		dsk_tv_rcv->pre_channl = 0;	
		dsk_tv_rcv->manual_search_way = 1;


		arg[0] = dsk_tv_rcv->cur_freq;
		eLIBs_fioctrl(app_tv_data->tv_drv, 3, 1, arg);			
	}	
	else
	{
		dsk_tv_rcv->manual_search_way = 0;
	}
	__msg("Tv start serch channel 2\n");


	SetSoundDatato2137();
	SetColorDatato2137();
}



void dsk_tv_set_cur_bright(void)
{
	__u32 tmp_bright;
	
	tmp_bright = dsk_tv_rcv->bright;
//	tmp_bright = (tmp_bright*100)/156;
	tmp_bright = (tmp_bright*66)/100;
	com_video_set_bright(tmp_bright);
}

void dsk_tv_set_cur_contrast(void)
{
	__u32 tmp_contrast;
	
	tmp_contrast = dsk_tv_rcv->contrast;
//	tmp_contrast = (tmp_contrast*255)/100;
	tmp_contrast = (tmp_contrast*230)/100;
	
	com_video_set_contrast(tmp_contrast);
}

void dsk_tv_set_cur_color(void)
{
	__u32 tmp_color;
	
	tmp_color = dsk_tv_rcv->color;
//	tmp_color = (tmp_color*255)/100;
	if(tmp_color<51)
		tmp_color = (tmp_color*128)/100;
	else
	{
		tmp_color = tmp_color - 50;
		tmp_color = 64+tmp_color*2;
	}
	com_video_set_saturation(tmp_color);
}

__s32 dsk_tv_rcv_cur_channelnum(void)
{
	__s32 valid_num;
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}
	
	valid_num = dsk_tv_rcv->cur_channl;
	
	return valid_num;
}


__u32 dsk_tv_get_sourceInput(void)
{
	__u32 valid_num;
	
	if(dsk_tv_rcv == NULL)
	{
		__err("radio receive not open!\n");
		return EPDK_FAIL;
	}
	
	valid_num = dsk_tv_rcv->sourceInput;
	
	return valid_num;
}

void dsk_tv_set_sourceInput(__u32 flag)
{
	__u32 freq;
	if(dsk_tv_rcv->sourceInput==0)
	{
//		eLIBs_fioctrl(app_tv_data->tv_drv, 2, 0, 0);
//		esKRNL_TimeDly(20);
		eLIBs_fioctrl(app_tv_data->tv_drv, 1, 0, 0); 
		freq = 85250000;
		dsk_tv_rcv->ucSoundSys = 3;
		SetFreDatato2137(freq);
		SetSoundDatato2137();
		SetColorDatato2137();
		
		esKRNL_TimeDly(3);	
		
		dsk_tv_rcv_curchafornum_play(0);
		com_video_in_set_sel(1);
	}	
	else
	{
		eLIBs_fioctrl(app_tv_data->tv_drv, 2, 0, 0);
		com_video_in_set_sel(0);
	}
	
}


void dsk_tv_finerFreq(__u32 flag)
{
	if(flag==0)
		dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl] -= 10000;
	else
		dsk_tv_rcv->channltable[dsk_tv_rcv->cur_channl] += 10000;
	
	dsk_tv_rcv_curchafornum_play(0);
}


void dsk_tv_SetTvSys(void)
{
	dsk_tv_rcv->SoundSystable[dsk_tv_rcv->cur_channl] = dsk_tv_rcv->ucSoundSys;

	dsk_tv_rcv_curchafornum_play(0);

}



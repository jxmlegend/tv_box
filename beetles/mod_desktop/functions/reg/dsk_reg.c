
#include "..\\functions_i.h"

#if EPDK_LOAD_FROM_SD
#define REG_SETTING_PARA_FILE_PATH 			EPDK_ROOTFS_PATH"setting.bin"
#else
#define REG_SETTING_PARA_FILE_PATH 			"e:\\setting.bin"
#endif
#define REG_DEFAULT_BGD_PATH   BEETLES_APP_ROOT"apps\\"

#define REG_VERSION_INFO "REG1"

#define REG_VERSION_INFO_LEN (eLIBs_strlen(REG_VERSION_INFO))

typedef struct
{	
	reg_system_para_t	system_para;
	reg_init_para_t	    init_para;			
	reg_root_para_t	    root_para;
	reg_movie_para_t	movie_para;
	reg_music_para_t	music_para;
	reg_photo_para_t	photo_para;
	reg_fm_para_t		fm_para;
	reg_ebook_para_t	ebook_para;
	reg_record_para_t   record_para;
	reg_calendar_para_t calendar_para;    
	reg_dv_para_t		dv_para ;
	reg_tv_para_t		tv_para ;
}reg_app_para_t;

typedef struct  
{
	__u32   restore_flag[REG_APP_MAX];
	reg_app_para_t para_current;//当前值
	reg_app_para_t para_default;//出厂默认值
	__u32   reserverd[4]; //保留参数
}reg_all_para_t;

static reg_all_para_t*	all_app_para = NULL;

static __s32 __reg_paramter_init(reg_app_para_t* para)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif
	__u32 i=0;

	if (!para)
	{
		__err("invalid para...\n");
		return EPDK_FAIL;
	}	

	para->system_para.audio_output = 0;//normal
	para->system_para.channel=0;//立体声
	para->system_para.charset=5;//gbk
	para->system_para.detect_gate=1;//on
	para->system_para.saturation=63;
	para->system_para.volume=20;
	para->system_para.language=EPDK_LANGUAGE_ENM_ENGLISH;//简体中文
	para->system_para.style=0;
	para->system_para.backlight=10;
	para->system_para.backlightoff=0;//不自动关屏
	para->system_para.poweroff=0;//不自动关机
	para->system_para.keytone=0;//按键音是否打开
	para->system_para.gamma_r_value=0x0a;
	para->system_para.gamma_g_value=0x0a;
	para->system_para.gamma_b_value=0x0a;
	para->system_para.output=LION_DISP_LCD;
    para->system_para.pal_ntsc=0;//0代表ntsc, 1代表pal
    para->system_para.time_set = 1;
	para->system_para.date.year= 2011;
	para->system_para.date.month= 1;
	para->system_para.date.day = 1;
	para->system_para.time.hour= 12;
	para->system_para.time.minute= 0;
	para->system_para.time.second= 0;
	para->system_para.tp_adjust_finish_flag = 0;

	para->init_para.default_bgd_index=0;
	eLIBs_strcpy(para->init_para.default_bgd_path,REG_DEFAULT_BGD_PATH);
	eLIBs_strcpy(para->init_para.setting_bgd_path, "");
	para->init_para.bgd_flag=1;//默认背景
	para->init_para.bgd_flag_in_main = 1;//默认背景

	//   para->root_para.last_app_name;
	para->root_para.last_movie_index_sd=0;
	//  para->root_para.last_movie_path_sd;
	para->root_para.last_movie_index_ud=0;
	//  para->root_para.last_movie_path_ud;
	para->root_para.last_music_index_sd=0;
	//  para->root_para.last_music_path_sd;
	para->root_para.last_music_index_ud=0;
	//  para->root_para.last_music_path_ud;
	para->root_para.last_photo_index_sd=0;
	//  para->root_para.last_photo_path_sd;
	para->root_para.last_photo_index_ud=0;
	//  para->root_para.last_photo_path_ud;
	para->root_para.last_ebook_index_sd=0;
	//  para->root_para.last_ebook_path_sd;
	para->root_para.last_ebook_index_ud=0;
	//  para->root_para.last_ebook_path_ud =0;

	para->movie_para.rotate_mode=2;//ROTATE_ALL
	para->movie_para.zoom_mode=0;//VIDEO_RATIO
	para->movie_para.sub_state=1;//on
	para->movie_para.sub_color=GUI_WHITE;
    para->movie_para.sub_stream=0;
	para->movie_para.sub_pos=0;//下面

	para->music_para.start_item_id=0;
	para->music_para.focus_item_id=0;
	para->music_para.play_mode=2;//ROTATE_ALL
	para->music_para.EQ_mode=0;//NORMAL

	para->photo_para.bgmusic=0;//关闭
	para->photo_para.speedflag=1;
	para->photo_para.interval_time=6;
	para->photo_para.ratio=0;
	para->photo_para.effect=0;//默认无切换效果

	para->ebook_para.text_colour=GUI_WHITE;
	para->ebook_para.switch_time=10;
	para->ebook_para.switch_time_flag=0;
	para->ebook_para.bg_music_switch=0;

	para->fm_para.mode=0;
	para->fm_para.channel_id=0;          

    //para->ebook_para

	para->tv_para.Pre_channel_id=1;
	para->tv_para.channel_id=1;
	para->tv_para.sourceInput = 0;
	para->tv_para.bright = 50;
	para->tv_para.contrast = 50;
	para->tv_para.color = 50;
	para->tv_para.tv_channel[1] = 49750000;
	para->tv_para.tv_channel[2] = 61250000;
	para->tv_para.tv_channel[3] = 77250000;
	para->tv_para.tv_channel[4] = 91250000;
	para->tv_para.tv_channel[5] = 120250000;
	para->tv_para.tv_channel[6] = 152250000;
	para->tv_para.tv_channel[7] = 160250000;
	para->tv_para.tv_channel[8] = 168250000;
	para->tv_para.tv_channel[9] = 181250000;
	para->tv_para.tv_channel[10] = 192250000;
	para->tv_para.tv_channel[11] = 211250000;
	para->tv_para.tv_channel[12] = 304250000;
	para->tv_para.tv_channel[13] = 312250000;
	para->tv_para.tv_channel[14] = 392250000;
	para->tv_para.tv_channel[15] = 400250000;
	para->tv_para.tv_channel[16] = 408250000;
	para->tv_para.tv_channel[17] = 416250000;
	para->tv_para.tv_channel[18] = 456250000;
	para->tv_para.tv_channel[19] = 471250000;
	para->tv_para.tv_channel[20] = 483250000;
	para->tv_para.tv_channel[21] = 603250000;
	para->tv_para.tv_channel[22] = 655250000;

	para->tv_para.SoundSystable[1] = 3;
	para->tv_para.SoundSystable[2] = 3;
	para->tv_para.SoundSystable[3] = 3;
	para->tv_para.SoundSystable[4] = 3;
	para->tv_para.SoundSystable[5] = 3;
	para->tv_para.SoundSystable[6] = 3;
	para->tv_para.SoundSystable[7] = 3;
	para->tv_para.SoundSystable[8] = 3;
	para->tv_para.SoundSystable[9] = 3;
	para->tv_para.SoundSystable[10] = 3;
	para->tv_para.SoundSystable[11] = 3;
	para->tv_para.SoundSystable[12] = 3;
	para->tv_para.SoundSystable[13] = 3;
	para->tv_para.SoundSystable[14] = 3;
	para->tv_para.SoundSystable[15] = 3;
	para->tv_para.SoundSystable[16] = 3;
	para->tv_para.SoundSystable[17] = 3;
	para->tv_para.SoundSystable[18] = 3;
	para->tv_para.SoundSystable[19] = 3;
	para->tv_para.SoundSystable[20] = 3;
	para->tv_para.SoundSystable[21] = 3;
	para->tv_para.SoundSystable[22] = 3;
	
	para->tv_para.total_channel = 22;
/*
	for(i=22;i<200;i++)
	{
		para->tv_para.tv_channel[i] = 312250000;
		para->tv_para.SoundSystable[i] = 3;
	}
	para->tv_para.total_channel = 199;
*/
    para->calendar_para.time_format=0;

	return EPDK_OK;
}

__s32 dsk_reg_init_para(void)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

	//分配内存
	{		
		if (all_app_para)
		{
			__msg("para already init...\n");
			return EPDK_OK;
		}
		
		all_app_para = esMEMS_Balloc(sizeof(reg_all_para_t));
		if (!all_app_para)
		{
			__msg("mem not enough...\n");
			return EPDK_FAIL;
		}
	}

	//尝试加载文件
	{
		ES_FILE* fp;
		
		fp = eLIBs_fopen(REG_SETTING_PARA_FILE_PATH, "rb");
		if(fp == NULL)
    	{
    		eLIBs_format("e:\\","fat",0);
			fp = eLIBs_fopen(REG_SETTING_PARA_FILE_PATH, "rb");			
    	}

		if (fp)
		{
			__s32 file_len;
			__s32 read_num;

            __msg("file exist:%s\n", REG_SETTING_PARA_FILE_PATH);
			eLIBs_fseek(fp, 0, SEEK_END);
			file_len = eLIBs_ftell(fp);
			if (file_len == sizeof(reg_all_para_t)+REG_VERSION_INFO_LEN)
			{
				char version[5]={0};
				eLIBs_fseek(fp, 0, SEEK_SET);	
                __here__;
				read_num = eLIBs_fread(version, 1, REG_VERSION_INFO_LEN, fp);
				if (REG_VERSION_INFO_LEN == read_num)
				{
                    __here__;
					if (0 == eLIBs_strncmp(version, REG_VERSION_INFO, REG_VERSION_INFO_LEN))
					{
                        __here__;
						read_num = eLIBs_fread(all_app_para, 1, sizeof(reg_all_para_t), fp);
						if(sizeof(reg_all_para_t) == read_num)
						{	
                            __here__;
							eLIBs_fclose(fp);
							__msg("load reg para success...\n");				
							return EPDK_OK;
						}	
					}	
					else
					{
						__msg("reg version info incorrect...\n");
					}
				}
				else
				{					
					__msg("read file fail:%s\n", REG_SETTING_PARA_FILE_PATH);									
				}				
			}

			eLIBs_fclose(fp);
		}
        else
        {
            __msg("file not exist:%s\n", REG_SETTING_PARA_FILE_PATH);
        }
	}

    __here__;

	//文件不存在或大小不对，则重新写入
	//初始化参数
	{
		__s32 sta;
		__s32 ret;		
		
		eLIBs_memset(all_app_para, 0, sizeof(reg_all_para_t));
		
		ret = EPDK_OK;
		sta =__reg_paramter_init(&all_app_para->para_current);
		if (EPDK_FAIL == sta)
		{
			__msg("__reg_paramter_init fail...\n");
			ret = EPDK_FAIL;
		}
		
		sta =__reg_paramter_init(&all_app_para->para_default);
		if (EPDK_FAIL == sta)
		{
			__msg("__reg_paramter_init fail...\n");
			ret = EPDK_FAIL;
		}
		
		if (EPDK_FAIL == ret)
		{
			return EPDK_FAIL;
		}		
	}   

	//写入文件
	if(1){//
		ES_FILE* fp;
		__s32 write_num;

		fp = eLIBs_fopen(REG_SETTING_PARA_FILE_PATH, "wb");
		if (!fp)
		{
			__msg("open file fail:%s\n", REG_SETTING_PARA_FILE_PATH);
			return EPDK_FAIL;
		}

		write_num = eLIBs_fwrite(REG_VERSION_INFO, 1, REG_VERSION_INFO_LEN, fp);
		if (write_num != REG_VERSION_INFO_LEN)
		{
			eLIBs_fclose(fp);
			__msg("eLIBs_fwrite fail:%s\n", REG_SETTING_PARA_FILE_PATH);
			return EPDK_FAIL;
		}
		
		write_num = eLIBs_fwrite(all_app_para, 1, sizeof(reg_all_para_t), fp);
		if (write_num != sizeof(reg_all_para_t))
		{
			eLIBs_fclose(fp);
			__msg("eLIBs_fwrite fail:%s\n", REG_SETTING_PARA_FILE_PATH);
			return EPDK_FAIL;
		}
		else
		{
			__msg("write para success...\n");
			eLIBs_fclose(fp);
			dsk_reg_flush();
			return EPDK_OK;
		}
	}		    

	return EPDK_OK;
}

__s32 dsk_reg_deinit_para(void)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

	if (all_app_para)
	{
		esMEMS_Bfree(all_app_para, sizeof(reg_all_para_t));
		all_app_para = NULL;
	}

	return EPDK_OK;
}

__s32 dsk_reg_flush(void)
{
	__s32 result;
	ES_FILE* fp = NULL;
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif
    if(1)//
    {
    	if (!all_app_para)
    	{
    		__err("reg para not init...\n");
    		return EPDK_FALSE;
    	}
    	
    	fp = eLIBs_fopen(REG_SETTING_PARA_FILE_PATH, "wb");
    	if(fp == NULL)
    	{
    		eLIBs_format("e:\\","fat",0);
			fp = eLIBs_fopen(REG_SETTING_PARA_FILE_PATH, "wb");
			if(fp == NULL)
			{
    			__msg("2open file fail:%s\n", REG_SETTING_PARA_FILE_PATH);
    			return EPDK_FAIL;
			}
    	}

    	result = eLIBs_fwrite(REG_VERSION_INFO, 1, REG_VERSION_INFO_LEN, fp);
    	if (result != REG_VERSION_INFO_LEN)
    	{
    		eLIBs_fclose(fp);
    		__msg("eLIBs_fwrite fail:%s\n", REG_SETTING_PARA_FILE_PATH);
    		return EPDK_FAIL;
    	}
    	
    	result = eLIBs_fwrite(all_app_para, 1, sizeof(reg_all_para_t), fp);
    	if(result < sizeof(reg_all_para_t))
    	{
            eLIBs_fclose(fp);
    		__msg("write file fail:%s\n", REG_SETTING_PARA_FILE_PATH);
    		return EPDK_FAIL;
    	}
    	
    	eLIBs_fclose(fp);


        {//
            ES_FILE* hFile;
            
            //flush user disk data to NOR flash
            hFile = eLIBs_fopen("b:\\STORAGE\\SPINOR", "rb");
            if (hFile == NULL)
            {
                __wrn("open NOR file failed\n");
                return EPDK_FAIL;
            }
            __msg("flush file ....\n");
            eLIBs_fioctrl(hFile, DEV_IOC_USR_FLUSH_CACHE, 0, 0);
            
            __msg("flush end ....\n");
            eLIBs_fclose(hFile);
        }
    }  

	return EPDK_OK;
}

void* dsk_reg_get_para_by_app(reg_app_e eApp)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

	if (!all_app_para)
	{
		__err("reg para not init...\n");
		return EPDK_FALSE;
	}

	switch(eApp)
	{
		case REG_APP_SYSTEM:
			return &all_app_para->para_current.system_para;		
		case REG_APP_INIT:
			return &all_app_para->para_current.init_para;		
		case REG_APP_ROOT:
			return &all_app_para->para_current.root_para;		
		case REG_APP_MOVIE:
			return &all_app_para->para_current.movie_para;		
		case REG_APP_MUSIC:
			return &all_app_para->para_current.music_para;		
		case REG_APP_PHOTO:
			return &all_app_para->para_current.photo_para;		
		case REG_APP_EBOOK:
			return &all_app_para->para_current.ebook_para;		
		case REG_APP_FM:
			return &all_app_para->para_current.fm_para;		
		case REG_APP_RECORD:
			return &all_app_para->para_current.record_para;		
		case REG_APP_CALENDAR:
			return &all_app_para->para_current.calendar_para;
		case REG_APP_DV:
			return &all_app_para->para_current.dv_para;
		case REG_APP_TV:
			return &all_app_para->para_current.tv_para;			
	}

	__err("invalid para...\n");
	return NULL;
}

void* dsk_reg_get_default_para_by_app(reg_app_e eApp)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

	if (!all_app_para)
	{
		__err("reg para not init...\n");
		return EPDK_FALSE;
	}

	switch(eApp)
	{
	case REG_APP_SYSTEM:
		return &all_app_para->para_default.system_para;		
	case REG_APP_INIT:
		return &all_app_para->para_default.init_para;		
	case REG_APP_ROOT:
		return &all_app_para->para_default.root_para;		
	case REG_APP_MOVIE:
		return &all_app_para->para_default.movie_para;		
	case REG_APP_MUSIC:
		return &all_app_para->para_default.music_para;		
	case REG_APP_PHOTO:
		return &all_app_para->para_default.photo_para;		
	case REG_APP_EBOOK:
		return &all_app_para->para_default.ebook_para;		
	case REG_APP_FM:
		return &all_app_para->para_default.fm_para;		
	case REG_APP_RECORD:
		return &all_app_para->para_default.record_para;		
	case REG_APP_CALENDAR:
		return &all_app_para->para_default.calendar_para;
	case REG_APP_DV:
		return &all_app_para->para_default.dv_para;
	case REG_APP_TV:
		return &all_app_para->para_default.tv_para;
	}
	
	__err("invalid para...\n");
	return NULL;
}

__bool dsk_reg_get_app_restore_flag(reg_app_e eApp)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

	if (!all_app_para)
	{
		__err("reg para not init...\n");
		return EPDK_FALSE;
	}

	if (eApp >= REG_APP_MAX)
	{
		__err("invalid para...\n");
		return NULL;
	}
	
	return (__bool)(all_app_para->restore_flag[eApp]);
}

__s32 dsk_reg_set_app_restore_flag(reg_app_e eApp, __bool flag)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

	if (!all_app_para)
	{
		__err("reg para not init...\n");
		return EPDK_FALSE;
	}
	
	if (eApp >= REG_APP_MAX)
	{
		__err("invalid para...\n");
		return NULL;
	}
	
	all_app_para->restore_flag[eApp] = flag;

	return EPDK_OK;
}

__s32 dsk_reg_save_cur_play_info(reg_app_e eApp, __s32 index, char* filename, rat_root_t root_type)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif
	 if (!all_app_para)
	{
		__err("reg para not init...\n");
		return EPDK_FAIL;
	}

	switch(eApp)
	{		
    	case REG_APP_MOVIE:
        {
            if(RAT_TF == root_type)
            {
                all_app_para->para_current.root_para.last_movie_index_sd = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_movie_path_sd, filename);
            }
            else if(RAT_USB == root_type)
            {
                all_app_para->para_current.root_para.last_movie_index_ud = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_movie_path_ud, filename);
            }
    		
            break;
    	}
    	case REG_APP_MUSIC:
    	{
            if(RAT_TF == root_type)
            {
                all_app_para->para_current.root_para.last_music_index_sd = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_music_path_sd, filename);
            }
            else if(RAT_USB == root_type)
            {
                all_app_para->para_current.root_para.last_music_index_ud = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_music_path_ud, filename);
            }
    		
            break;
    	}	
    	case REG_APP_PHOTO:
    	{
            if(RAT_TF == root_type)
            {
                all_app_para->para_current.root_para.last_photo_index_sd = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_photo_path_sd, filename);
            }
            else if(RAT_USB == root_type)
            {
                all_app_para->para_current.root_para.last_photo_index_ud = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_photo_path_ud, filename);
            }
    		
            break;
    	}			
    	case REG_APP_EBOOK:
    	{
            if(RAT_TF == root_type)
            {
                all_app_para->para_current.root_para.last_ebook_index_sd = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_ebook_path_sd, filename);
            }
            else if(RAT_USB == root_type)
            {
                all_app_para->para_current.root_para.last_ebook_index_ud = index;
                eLIBs_strcpy(all_app_para->para_current.root_para.last_ebook_path_ud, filename);
            }
    		
            break;
    	}
        default:
            __wrn("invalid app type...\n");            
            return EPDK_FAIL;
	}
	    
    return EPDK_OK;
}


__s32 dsk_reg_set_app_restore_all(void)
{
#if (EPDK_SPI_READY==0)
	return EPDK_OK ;
#endif

    if (!all_app_para)
	{
		__err("reg para not init...\n");
		return EPDK_FAIL;
	}
	
	eLIBs_memcpy(&all_app_para->para_current,(const void*)(&all_app_para->para_default),sizeof(reg_app_para_t));
    return EPDK_OK;
}


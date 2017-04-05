
//libaiao

#include "beetles_app.h"
#include "music_ui.h"


#if 1
static music_ui_t  music_ui_400_240 =
{    
    //layer window
    { 
        PIXEL_COLOR_ARGB8888,       //fmt 
        { 720, 576 },               //fb size
        { 0, 0, 720, 576 },         //src rect
        { 0, 0, 720, 576 },         //scn rect
        { 0 },                      //reserved
    },
    
 /*   //list window, ����ļ�
    {
    		{20, 20, 350, 450},						//listbar area
    		{0, 0, 350, 50},						//item rectangle
    		{5, 9, 370, 50},						//focus icon(select border)
    		{11,12,15, 15 },						//file icon 
    		{11+15+10, 0, 188-11-15-10-3-1, 36},		//text rectangle
    },
*/
    //list window, ����ļ�
    {
    		{6, 42, 360, 462},						//listbar area
    		{0, 0, 360, 42},						//item rectangle
    		{0, 0, 360, 42},						//focus icon(select border)
    		{30,0,15, 15 },						//file icon 
    		{38,0, 310, 42},		//text rectangle
    },
    
    //scroll bar ui
/*    {
    		{351,	20,	7,	430},					//scroll bar background
    		{351,	32,	3,	430},					//scroll 
    		6,										//head
    		1,										//body
    		6,										//tail
    },
 */   
    	{
    		{368,	40,	8,	456},					//scroll bar background
    		{368,	54,	8,	426},					//scroll 
    		6,										//head
    		1,										//body
    		6,										//tail
    	},
			
    //head bar ui   
    {
    	{370,80,700-370,250-80},					//headbar background
    	#if BEETLES_RTC_EXIST
    	{400,42,26,16},								//����ģʽ״̬ͼ��
    	{494,42,50,16},								//EQģʽ״̬ͼ��		
    	{426,10,26,16},								//����ر�ʱ��ͼ��
    	{642,42,26,16},								//����ͼ��
    	{686,46,18,16},								//����text
    	{526,12,31,12},								//���ͼ��
    	{559,6,40,16},								//ʱ����ʾ����
    	#else
    	{198,5,26,16},								//����ģʽ״̬ͼ��
    	{229,5,50,16},								//EQģʽ״̬ͼ��		
    	{284,5,26,16},								//����ر�ʱ��ͼ��
    	{315,5,26,16},								//����ͼ��
    	{341,4,18,16},								//����text
    	{364,6,31,12},								//���ͼ��
    	{0,0,0,16},									//ʱ����ʾ����
		#endif
    },			
    //palyer ui
    {
/*
	{360,50,700-360,230-50},					//���ư�ť��������()��Ƶ�׹���
    	{410,160,150,16},							//������ʾ�ַ�����
    	{444,98,26,16},								//����ģʽ��ť  
    	{478,98,26,16},								//EQģʽ��ť               
    	{514,98,26,16},								// ����ʱ����ư�ť             
    	
    	{408,135,26,16},							//��һ�װ�ť                
    	{441,135,26,16},							//��һ�װ�ť                
    	{474,135,26,16},							//������ͣ��ť              
    	{507,135,26,16},							//���˰�ť                  
    	{540,135,26,16},							//�����ť   
*/  

	{390,100,700-400,250-100},					//���ư�ť��������()��Ƶ�׹���
    	{440,220,150,16},							//������ʾ�ַ�����
    	{474,138,26,16},								//����ģʽ��ť  
    	{526,138,26,16},								//EQģʽ��ť               
    	{544,138,26,16},								// ����ʱ����ư�ť             
    	
    	{438,165,26,16},							//��һ�װ�ť                
    	{471,165,26,16},							//��һ�װ�ť                
    	{504,165,26,16},							//������ͣ��ť              
    	{545,165,26,16},							//���˰�ť                  
    	{580,165,26,16},							//�����ť  

    	{425,307,26,20},							//����״̬ͼ��(��ͣ�򲥷�)	

	
    	{443,322,70,20},	              		//��ǰ����ʱ��              
    	{560 ,322,60,20},				//��ʱ����ʾ����
    	
    	{446,312,5,4},								//������head
    	{446,312,146,4},							//������body    	
    	{446+5,312,5,4},							//������point,��head֮����˼�5   	
    	{446+146-5,312,5,4},						//������tail

    	    	
    	{416,386,26,16},						//�ݳ���ͼ��
    	{416+26,	386,70,16},						//�ݳ�������
    	{550,386,26,16},						//�ļ���Сͼ��
    	{550+26,	386,70,16},						//�ļ���С��ʾ
    	
    	{414,412,26,16},						//ר������ͼ��
    	{414+26,	412,70,16},						//ר������
    	{550,412,26,16},						//bitrateͼ��
    	{550+26,	412,70,16},						//bitrate��С��ʾ
    },
    
    //volume bar ui
    {
    	{0,0,0,0},									//��������������ʾ����
    	{0,0,0,0},									//���speakerͼ����ʾ��������״̬
    	{0,0,0,0},									//�м�������ʾ������
    	{0,0,0,0},    								//�ұ�speakerͼ����ʾ
   	}, 

	//spectrum
    {
    	{420,150,700-420,200-80}
    },
    //icon table    
    {				//ID															res	handle,    	res buffer    
  		//���������
		{ ID_MUSIC_PALETTE_BMP,           			NULL,  				 NULL },    //
        { NULL,           	NULL,  				 NULL },    //
        { ID_MUSIC_FILE_UNFOCUSED_BMP,      		NULL,  				 NULL }, 	//                                                       				
        { ID_MUSIC_FILE_UNFOCUSED_BMP,      		NULL,  				 NULL }, 	//�ļ�ͼ�꣬δ��ѡ��ʱ
        { ID_MUSIC_FILE_FOCUSED_BMP,      			NULL,  				 NULL }, 	//�ļ�ͼ�꣬��ѡ��ʱ                                                     				                                                				        
        { ID_MUSIC_LIST_ITEM_FOCUS_BMP,    			NULL,  				 NULL }, 	//ѡ���                                                         				        
	    { ID_MUSIC_LONG_STR_SCROLL_BMP,				NULL,  			 	 NULL },     //���ļ�������������         
        //header bar
        				//play mode
        { ID_MUSIC_PLAY_ALL_BMP,    				NULL,  				 NULL }, 	//	����ȫ��,���ظ�
        { ID_MUSIC_PLAY_ONE_BMP,    				NULL,  				 NULL }, 	//����һ��
        { ID_MUSIC_PLAY_RANDOM_BMP,    				NULL,  				 NULL }, 	//�漴����
        { ID_MUSIC_REPEAT_ALL_BMP,    				NULL,  				 NULL }, 	//�ظ�����
        { ID_MUSIC_REPEAT_ONE_BMP,    				NULL,  				 NULL }, 	//�ظ�һ��
        
        				//EQ mode
        { ID_MUSIC_EQ_NORMAL_BMP,    				NULL,  				 NULL }, 	//EQ normal
        { ID_MUSIC_EQ_CLASSIC_BMP,    				NULL,  				 NULL }, 	//EQ classic
        { ID_MUSIC_EQ_ROCK_BMP,    					NULL,  				 NULL }, 	//	EQ Rock
        { ID_MUSIC_EQ_JAZZ_BMP,    					NULL,  				 NULL }, 	//	EQ JAZZ
        { ID_MUSIC_EQ_POP_BMP,    					NULL,  				 NULL }, 	//	EQ POP
        
        				//BL Time
        { ID_MUSIC_BL_ON_BMP,    					NULL,  				 NULL }, 	//	Backlight never off
        { ID_MUSIC_BL_10S_BMP,    					NULL,  				 NULL }, 	//last 10 second
        { ID_MUSIC_BL_30S_BMP,    					NULL,  				 NULL }, 	//
        { ID_MUSIC_BL_60S_BMP,    					NULL,  				 NULL }, 	//
        { ID_MUSIC_BL_90S_BMP,    					NULL,  				 NULL }, 	//
                				
        				//volume
        { ID_MUSIC_VOLUME_STATUS_BMP,    			NULL,  				 NULL }, 	//
        			
        				//bettery
        { ID_MUSIC_BETTERY0_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY1_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY2_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY3_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY4_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY5_BMP,    				NULL,  				 NULL }, 	//
        						
        { ID_MUSIC_CHARGE_BETTERY0_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY1_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY2_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY3_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY4_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY5_BMP,    				NULL,  				 NULL }, 	//
        						
        //������
        				//play mode button
        { ID_MUSIC_PLAY_ALL_BMP,    				NULL,  				 NULL }, 		//����ȫ��, unfocused
        { ID_MUSIC_PLAY_ALL_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//����ȫ��, focused
        { ID_MUSIC_PLAY_ALL_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//����ȫ��, pressed

        { ID_MUSIC_PLAY_ONE_BMP,    				NULL,  				 NULL }, 		//����һ��, unfocused
        { ID_MUSIC_PLAY_ONE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//����һ��, focused
        { ID_MUSIC_PLAY_ONE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//����һ��, pressed

        { ID_MUSIC_PLAY_RANDOM_BMP,    				NULL,  				 NULL }, 		//�������, unfocused
        { ID_MUSIC_PLAY_RANDOM_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//�������, focused
        { ID_MUSIC_PLAY_RANDOM_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//�������, pressed
                        
        { ID_MUSIC_REPEAT_ALL_BMP,    				NULL,  				 NULL }, 		//�ظ�����ȫ��, unfocused
        { ID_MUSIC_REPEAT_ALL_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//�ظ�����ȫ��, focused
        { ID_MUSIC_REPEAT_ALL_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//�ظ�����ȫ��, pressed

        { ID_MUSIC_REPEAT_ONE_BMP,    				NULL,  				 NULL }, 		//�ظ�����һ��, unfocused
        { ID_MUSIC_REPEAT_ONE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//�ظ�����һ��, focused
        { ID_MUSIC_REPEAT_ONE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//�ظ�����һ��, pressed
                        
								//EQ mode button
        { ID_MUSIC_EQ_MODE_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 		//EQ mode button, unfocused
        { ID_MUSIC_EQ_MODE_BTN_FOCUSED_BMP,			NULL,  				 NULL }, 		//focused
        { ID_MUSIC_EQ_MODE_BTN_PRESSED_BMP,			NULL,  				 NULL }, 		//pressed
 
 								//BL time button
        { ID_MUSIC_BL_TIME_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 		//EQ mode button, unfocused
        { ID_MUSIC_BL_TIME_BTN_FOCUSED_BMP,			NULL,  				 NULL }, 		//focused
        { ID_MUSIC_BL_TIME_BTN_PRESSED_BMP,			NULL,  				 NULL }, 		//pressed
        				
        				//play previous button
        { ID_MUSIC_PLAY_PRE_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 	//������һ��, unfocused
        { ID_MUSIC_PLAY_PRE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_PRE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//pressed
								//play next button
        { ID_MUSIC_PLAY_NEXT_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 	//������һ��, unfocused
        { ID_MUSIC_PLAY_NEXT_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_NEXT_BTN_PRESSED_BMP,		NULL,  				 NULL }, 	//pressed                      				      
								//play pause button
        { ID_MUSIC_PLAY_PAUSE_BTN_UNFOCUSED_BMP,	NULL,  				 NULL }, 	//������ͣ, unfocused
        { ID_MUSIC_PLAY_PAUSE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_PAUSE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 	//pressed                      				      
 
 								//play backward button
        { ID_MUSIC_PLAY_BACKWARD_BTN_UNFOCUSED_BMP,	NULL,  				 NULL }, 	//����, unfocused
        { ID_MUSIC_PLAY_BACKWARD_BTN_FOCUSED_BMP,	NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_BACKWARD_BTN_PRESSED_BMP,	NULL,  				 NULL }, 	//pressed  

 								//play forward button
        { ID_MUSIC_PLAY_FORWARD_BTN_UNFOCUSED_BMP,	NULL,  				 NULL }, 	//���, unfocused
        { ID_MUSIC_PLAY_FORWARD_BTN_FOCUSED_BMP,	NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_FORWARD_BTN_PRESSED_BMP,	NULL,  				 NULL }, 	//pressed   
        
        				//play status button,
       { ID_MUSIC_PLAYING_STATUS_BMP,				NULL,				NULL }, 								//���ڲ���״̬
       { ID_MUSIC_PAUSE_STATUS_BMP,					NULL,  				NULL }, 								//��ͣ״̬
       { ID_MUSIC_PREVIOUS_STATUS_BMP,				NULL,  		 		NULL }, 								//��һ��״̬
       { ID_MUSIC_NEXT_STATUS_BMP,					NULL,  				NULL }, 								//��һ��״̬

        				//process bar 
       { ID_MUSIC_PROCESS_BAR_HEAD_BMP,				NULL,  			 	NULL }, 								//process bar ͷ��
       { ID_MUSIC_PROCESS_BAR_BODY_BMP,				NULL,  				NULL }, 								//body
       { ID_MUSIC_PROCESS_BAR_TAIL_BMP,				NULL,  		 		NULL }, 								//β��
       { ID_MUSIC_PROCESS_BAR_POINT_BMP,			NULL,  				NULL }, 								//���ȵ�

       //������Ϣͼ��
       { ID_MUSIC_PERFORMER_NAME_BMP,				NULL,  			 	NULL }, 								//����ͼ��
       { ID_MUSIC_FILE_SIZE_BMP,					NULL,  				NULL }, 								//
       { ID_MUSIC_ALBUM_NAME_BMP,					NULL,  		 		NULL }, 								//
       { ID_MUSIC_BIT_RATE_BMP,						NULL,  				NULL }, 								//
       
       //Ƶ��ͼͼ��
       { ID_MUSIC_PARTICLE_BMP,						NULL,  			 	NULL }, 
       { ID_MUSIC_BOUY_BMP,							NULL,  			 	NULL },        

		//�������������
       { ID_EXPLORER_LIST_SCROLL_BG_BMP,				NULL,  			 	NULL }, 
       { ID_EXPLORER_LIST_SCROLL_HEAD_BMP,				NULL,  			 	NULL },        
       { ID_EXPLORER_LIST_SCROLL_BODY_BMP,				NULL,  			 	NULL },        
       { ID_EXPLORER_LIST_SCROLL_TAIL_BMP,				NULL,  			 	NULL }, 

     	{ ID_MUSIC_SPEAKER_BMP,				NULL,				NULL }, 								//���ڲ���״̬
       { ID_MUSIC_MUTE_BMP,					NULL,  				NULL }, 								//��ͣ״̬

	{ 0,                                    		NULL,  				NULL }      	//browser_icon_max
    },                                                 				
};

#else
static music_ui_t  music_ui_400_240 =
{    
    //layer window
    { 
        PIXEL_COLOR_ARGB8888,       //fmt 
        { 400, 240 },               //fb size
        { 0, 0, 400, 240 },         //src rect
        { 0, 0, 400, 240 },         //scn rect
        { 0 },                      //reserved
    },
    
    //list window, ����ļ�
    {
    		{0, 7, 188, 216},						//listbar area
    		{0, 0, 188, 36},						//item rectangle
    		{5, 9, 181, 22},						//focus icon(select border)
    		{11,12,15, 15 },						//file icon 
    		{11+15+10, 0, 188-11-15-10-3-1, 36},		//text rectangle
    },
    
    //scroll bar ui
    {
    		{189,	7,	7,	224},					//scroll bar background
    		{191,	22,	3,	194},					//scroll 
    		6,										//head
    		1,										//body
    		6,										//tail
    }, 
    
    //head bar ui   
    {
    	{210,40,400-210,150-40},					//headbar background
    	#if BEETLES_RTC_EXIST
    	{198,5,26,16},								//����ģʽ״̬ͼ��
    	{226,5,50,16},								//EQģʽ״̬ͼ��		
    	{226,5,26,16},								//����ر�ʱ��ͼ��
    	{278,5,26,16},								//����ͼ��
    	{304,3,18,16},								//����text
    	{326,6,31,12},								//���ͼ��
    	{359,3,40,16},								//ʱ����ʾ����
    	#else
    	{198,5,26,16},								//����ģʽ״̬ͼ��
    	{229,5,50,16},								//EQģʽ״̬ͼ��		
    	{284,5,26,16},								//����ر�ʱ��ͼ��
    	{315,5,26,16},								//����ͼ��
    	{341,4,18,16},								//����text
    	{364,6,31,12},								//���ͼ��
    	{0,0,0,16},									//ʱ����ʾ����
		#endif
    },			
    //palyer ui
    {
    	{210,40,190,80},					//���ư�ť��������()��Ƶ�׹���
    	{230,120,150,16},							//������ʾ�ַ�����
    	{254,68,26,16},								//����ģʽ��ť  
    	{288,68,26,16},								//EQģʽ��ť               
    	{324,68,26,16},								// ����ʱ����ư�ť             
    	
    	{228,100,26,16},							//��һ�װ�ť                
    	{261,100,26,16},							//��һ�װ�ť                
    	{294,100,26,16},							//������ͣ��ť              
    	{327,100,26,16},							//���˰�ť                  
    	{360,100,26,16},							//�����ť   
    	               
    	{214,154,26,20},							//����״̬ͼ��(��ͣ�򲥷�)	
    	
    	{239+3,160 - 21,70,20},	              		//��ǰ����ʱ��              
    	{239+146-70-3+28 ,160 - 21,60,20},			//��ʱ����ʾ����
    	
    	{239,160,5,4},								//������head
    	{239,160,146,4},							//������body    	
    	{239+5,160,5,4},							//������point,��head֮����˼�5   	
    	{239+146-5,160,5,4},						//������tail
    	
    	{213,		183,26,16},						//�ݳ���ͼ��
    	{213+26,	183,70,16},						//�ݳ�������
    	{310,		183,26,16},						//�ļ���Сͼ��
    	{310+26,	183,70,16},						//�ļ���С��ʾ
    	
    	{213,		213,26,16},						//ר������ͼ��
    	{213+26,	213,70,16},						//ר������
    	{310,		213,26,16},						//bitrateͼ��
    	{310+26,	213,70,16},						//bitrate��С��ʾ
    },
    
    //volume bar ui
    {
    	{0,0,0,0},									//��������������ʾ����
    	{0,0,0,0},									//���speakerͼ����ʾ��������״̬
    	{0,0,0,0},									//�м�������ʾ������
    	{0,0,0,0},    								//�ұ�speakerͼ����ʾ
   	}, 

	//spectrum
    {
    	{210,40,400-210,150-40}
    },
    //icon table    
    {				//ID															res	handle,    	res buffer    
  		//���������
		{ ID_MUSIC_PALETTE_BMP,           			NULL,  				 NULL },    //
        { NULL,           	NULL,  				 NULL },    //
        { ID_MUSIC_FILE_UNFOCUSED_BMP,      		NULL,  				 NULL }, 	//                                                       				
        { ID_MUSIC_FILE_UNFOCUSED_BMP,      		NULL,  				 NULL }, 	//�ļ�ͼ�꣬δ��ѡ��ʱ
        { ID_MUSIC_FILE_FOCUSED_BMP,      			NULL,  				 NULL }, 	//�ļ�ͼ�꣬��ѡ��ʱ                                                     				                                                				        
        { ID_MUSIC_LIST_ITEM_FOCUS_BMP,    			NULL,  				 NULL }, 	//ѡ���                                                         				        
	    { ID_MUSIC_LONG_STR_SCROLL_BMP,				NULL,  			 	 NULL },     //���ļ�������������         
        //header bar
        				//play mode
        { ID_MUSIC_PLAY_ALL_BMP,    				NULL,  				 NULL }, 	//	����ȫ��,���ظ�
        { ID_MUSIC_PLAY_ONE_BMP,    				NULL,  				 NULL }, 	//����һ��
        { ID_MUSIC_PLAY_RANDOM_BMP,    				NULL,  				 NULL }, 	//�漴����
        { ID_MUSIC_REPEAT_ALL_BMP,    				NULL,  				 NULL }, 	//�ظ�����
        { ID_MUSIC_REPEAT_ONE_BMP,    				NULL,  				 NULL }, 	//�ظ�һ��
        
        				//EQ mode
        { ID_MUSIC_EQ_NORMAL_BMP,    				NULL,  				 NULL }, 	//EQ normal
        { ID_MUSIC_EQ_CLASSIC_BMP,    				NULL,  				 NULL }, 	//EQ classic
        { ID_MUSIC_EQ_ROCK_BMP,    					NULL,  				 NULL }, 	//	EQ Rock
        { ID_MUSIC_EQ_JAZZ_BMP,    					NULL,  				 NULL }, 	//	EQ JAZZ
        { ID_MUSIC_EQ_POP_BMP,    					NULL,  				 NULL }, 	//	EQ POP
        
        				//BL Time
        { ID_MUSIC_BL_ON_BMP,    					NULL,  				 NULL }, 	//	Backlight never off
        { ID_MUSIC_BL_10S_BMP,    					NULL,  				 NULL }, 	//last 10 second
        { ID_MUSIC_BL_30S_BMP,    					NULL,  				 NULL }, 	//
        { ID_MUSIC_BL_60S_BMP,    					NULL,  				 NULL }, 	//
        { ID_MUSIC_BL_90S_BMP,    					NULL,  				 NULL }, 	//
                				
        				//volume
        { ID_MUSIC_VOLUME_STATUS_BMP,    			NULL,  				 NULL }, 	//
        			
        				//bettery
        { ID_MUSIC_BETTERY0_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY1_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY2_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY3_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY4_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_BETTERY5_BMP,    				NULL,  				 NULL }, 	//
        						
        { ID_MUSIC_CHARGE_BETTERY0_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY1_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY2_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY3_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY4_BMP,    				NULL,  				 NULL }, 	//
        { ID_MUSIC_CHARGE_BETTERY5_BMP,    				NULL,  				 NULL }, 	//
        						
        //������
        				//play mode button
        { ID_MUSIC_PLAY_ALL_BMP,    				NULL,  				 NULL }, 		//����ȫ��, unfocused
        { ID_MUSIC_PLAY_ALL_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//����ȫ��, focused
        { ID_MUSIC_PLAY_ALL_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//����ȫ��, pressed

        { ID_MUSIC_PLAY_ONE_BMP,    				NULL,  				 NULL }, 		//����һ��, unfocused
        { ID_MUSIC_PLAY_ONE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//����һ��, focused
        { ID_MUSIC_PLAY_ONE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//����һ��, pressed

        { ID_MUSIC_PLAY_RANDOM_BMP,    				NULL,  				 NULL }, 		//�������, unfocused
        { ID_MUSIC_PLAY_RANDOM_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//�������, focused
        { ID_MUSIC_PLAY_RANDOM_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//�������, pressed
                        
        { ID_MUSIC_REPEAT_ALL_BMP,    				NULL,  				 NULL }, 		//�ظ�����ȫ��, unfocused
        { ID_MUSIC_REPEAT_ALL_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//�ظ�����ȫ��, focused
        { ID_MUSIC_REPEAT_ALL_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//�ظ�����ȫ��, pressed

        { ID_MUSIC_REPEAT_ONE_BMP,    				NULL,  				 NULL }, 		//�ظ�����һ��, unfocused
        { ID_MUSIC_REPEAT_ONE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 		//�ظ�����һ��, focused
        { ID_MUSIC_REPEAT_ONE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//�ظ�����һ��, pressed
                        
								//EQ mode button
        { ID_MUSIC_EQ_MODE_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 		//EQ mode button, unfocused
        { ID_MUSIC_EQ_MODE_BTN_FOCUSED_BMP,			NULL,  				 NULL }, 		//focused
        { ID_MUSIC_EQ_MODE_BTN_PRESSED_BMP,			NULL,  				 NULL }, 		//pressed
 
 								//BL time button
        { ID_MUSIC_BL_TIME_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 		//EQ mode button, unfocused
        { ID_MUSIC_BL_TIME_BTN_FOCUSED_BMP,			NULL,  				 NULL }, 		//focused
        { ID_MUSIC_BL_TIME_BTN_PRESSED_BMP,			NULL,  				 NULL }, 		//pressed
        				
        				//play previous button
        { ID_MUSIC_PLAY_PRE_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 	//������һ��, unfocused
        { ID_MUSIC_PLAY_PRE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_PRE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 		//pressed
								//play next button
        { ID_MUSIC_PLAY_NEXT_BTN_UNFOCUSED_BMP,		NULL,  				 NULL }, 	//������һ��, unfocused
        { ID_MUSIC_PLAY_NEXT_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_NEXT_BTN_PRESSED_BMP,		NULL,  				 NULL }, 	//pressed                      				      
								//play pause button
        { ID_MUSIC_PLAY_PAUSE_BTN_UNFOCUSED_BMP,	NULL,  				 NULL }, 	//������ͣ, unfocused
        { ID_MUSIC_PLAY_PAUSE_BTN_FOCUSED_BMP,		NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_PAUSE_BTN_PRESSED_BMP,		NULL,  				 NULL }, 	//pressed                      				      
 
 								//play backward button
        { ID_MUSIC_PLAY_BACKWARD_BTN_UNFOCUSED_BMP,	NULL,  				 NULL }, 	//����, unfocused
        { ID_MUSIC_PLAY_BACKWARD_BTN_FOCUSED_BMP,	NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_BACKWARD_BTN_PRESSED_BMP,	NULL,  				 NULL }, 	//pressed  

 								//play forward button
        { ID_MUSIC_PLAY_FORWARD_BTN_UNFOCUSED_BMP,	NULL,  				 NULL }, 	//���, unfocused
        { ID_MUSIC_PLAY_FORWARD_BTN_FOCUSED_BMP,	NULL,  				 NULL }, 	//focused
        { ID_MUSIC_PLAY_FORWARD_BTN_PRESSED_BMP,	NULL,  				 NULL }, 	//pressed   
        
        				//play status button,
       { ID_MUSIC_PLAYING_STATUS_BMP,				NULL,				NULL }, 								//���ڲ���״̬
       { ID_MUSIC_PAUSE_STATUS_BMP,					NULL,  				NULL }, 								//��ͣ״̬
       { ID_MUSIC_PREVIOUS_STATUS_BMP,				NULL,  		 		NULL }, 								//��һ��״̬
       { ID_MUSIC_NEXT_STATUS_BMP,					NULL,  				NULL }, 								//��һ��״̬

        				//process bar 
       { ID_MUSIC_PROCESS_BAR_HEAD_BMP,				NULL,  			 	NULL }, 								//process bar ͷ��
       { ID_MUSIC_PROCESS_BAR_BODY_BMP,				NULL,  				NULL }, 								//body
       { ID_MUSIC_PROCESS_BAR_TAIL_BMP,				NULL,  		 		NULL }, 								//β��
       { ID_MUSIC_PROCESS_BAR_POINT_BMP,			NULL,  				NULL }, 								//���ȵ�

       //������Ϣͼ��
       { ID_MUSIC_PERFORMER_NAME_BMP,				NULL,  			 	NULL }, 								//����ͼ��
       { ID_MUSIC_FILE_SIZE_BMP,					NULL,  				NULL }, 								//
       { ID_MUSIC_ALBUM_NAME_BMP,					NULL,  		 		NULL }, 								//
       { ID_MUSIC_BIT_RATE_BMP,						NULL,  				NULL }, 								//
       
       //Ƶ��ͼͼ��
       { ID_MUSIC_PARTICLE_BMP,						NULL,  			 	NULL }, 
       { ID_MUSIC_BOUY_BMP,							NULL,  			 	NULL },        

		//�������������
       { ID_MUSIC_LIST_SCROLL_BG_BMP,				NULL,  			 	NULL }, 
       { ID_MUSIC_LIST_SCROLL_HEAD_BMP,				NULL,  			 	NULL },        
       { ID_MUSIC_LIST_SCROLL_BODY_BMP,				NULL,  			 	NULL },        
       { ID_MUSIC_LIST_SCROLL_TAIL_BMP,				NULL,  			 	NULL }, 

       
       { 0,                                    		NULL,  				NULL }      	//browser_icon_max
    },                                                 				
};


#endif

//�������explorer AP��Ƶ�UI����
music_ui_t* music_get_ui_param(void)
{	
		return &(music_ui_400_240);
}

//������������UI����
music_list_ui_t *music_get_list_ui_param(void)
{	
		return &(music_ui_400_240.list_ctrl);		
}

//��ö���HeadbarUI����
music_headbar_ui_t *music_get_headbar_ui_param(void)
{
		return 	&(music_ui_400_240.headbar);
}

//��ö���playerUI����
music_palyer_ui_t *music_get_player_ui_param(void)
{
		return 	&(music_ui_400_240.player);	
}

//���volume barUI����
music_volume_bar_ui_t *music_get_volume_bar_ui_param(void)
{
		return 	&(music_ui_400_240.volume_bar);	
}
/*
************************************************************************************************************************
*Function	:         void* explorer_get_listview_icon_res(__u32 index)
*
*Description	: 		
*					
*Arguments  	: 		
*
*Return     	: 	
*
************************************************************************************************************************
*/
void* music_get_icon_res(__u32 index)
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
    	#if 1
        icon_table[index].res_handle = theme_open(icon_table[index].res_id);
        icon_table[index].res_buffer = theme_hdl2buf(icon_table[index].res_handle);                        
        return icon_table[index].res_buffer;
		#else
		{
			int i = 0;
			__msg("------------open all of the picture at first\n");
			app_print_memory_usage("new memory for picture resource", NULL);
			app_print_memory_usage("new memory for picture resource", NULL);
	        for(i = 0; i < MUSIC_ICON_MAX; i++)
	        {
	            if(icon_table[i].res_handle == NULL)
	            {
        			icon_table[i].res_handle = theme_open(icon_table[i].res_id);
			        icon_table[i].res_buffer = theme_hdl2buf(icon_table[i].res_handle);                        
	            }
	        }   			
			app_print_memory_usage("new memory for picture resource finished", NULL);

        	return icon_table[index].res_buffer;			
		}
		#endif
		
    }
    else
    {
        return icon_table[index].res_buffer;
    }
}

/*
************************************************************************************************************************
*Function	:         __s32 explorer_free_listview_icon_res(void)
*
*Description	: 		
*					
*Arguments  	: 		
*
*Return     	: 	
*
************************************************************************************************************************
*/
__s32 music_free_icon_res(void)
{    
    __s32 i = 0;
    music_icon_data_t *icon_table = NULL;
    icon_table = music_ui_400_240.icon_table;
    
    if(icon_table == NULL)
    {
        return EPDK_FAIL;
    }
    else
    {
	    //app_print_memory_usage("release memory for picture resource", NULL);
		//app_print_memory_usage("release memory for picture resource", NULL);
        for(i = 0; i < MUSIC_ICON_MAX; i++)
        {
            if(icon_table[i].res_handle != NULL)
            {
                theme_close(icon_table[i].res_handle); 
                icon_table[i].res_handle = NULL;
                icon_table[i].res_buffer = NULL;
            }
        }    
		//app_print_memory_usage("release memory for picture resource finished", NULL);
        return EPDK_OK;       
    }
}

//���Explorer ����layer size
__s32 music_get_screen_rect(RECT *screen_rect)
{	
	music_ui_t *ui_param;
	ui_param = music_get_ui_param();
	
	screen_rect->x = ui_param->layer.scn_rect.x;
	screen_rect->y = ui_param->layer.scn_rect.y;
	screen_rect->width = ui_param->layer.scn_rect.width;
	screen_rect->height = ui_param->layer.scn_rect.height;
	return EPDK_OK;
}

//����listbarÿҳ������ʾ����Ŀ����
__u32 music_count_listbar_pagenum(void)
{
	__u32 pagenum = 0;
	
	music_ui_t *ui_param;
	ui_param = music_get_ui_param();
    pagenum = ui_param->list_ctrl.listbar_rect.height / ui_param->list_ctrl.item_rect.height;	
	return pagenum;
}














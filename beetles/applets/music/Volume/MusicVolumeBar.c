/*
**************************************************************************************************************
*											         ePDK
*						            the Easy Portable/Player Develop Kits
*									           desktop system 
*
* File    	: 	VolumeBar
*			
* By      	: 	Libaiao
* Func	: 
* Version	: 	v1.0
* ============================================================================================================
* 2010-5-25 15:24:52  Libaiao  create this file, implements the fundemental interface;
**************************************************************************************************************
*/

#include "beetles_app.h"
#include "music_player.h"
#include "player_face.h"

#include "VolumeBar.h"




#define C_MUSIC_VB_HEIGHT			21

const VolumeBarUI_t MusicVolBarUI = {
		{0,538,720,40},					//Background rect
		ID_MUSIC_VOL_BAR_BG_BMP,			//BG bmp id
		
		{52,9,20,20},						//Leftspeaker
		ID_MUSIC_VOL_SPEAKER_LEFT_BMP,		//leftespeaker icon id
		
		{80,16,550,8},					//BarBody rect
		ID_MUSIC_VOL_BAR_BODY_BMP,			//BarBody icon id
		
		{80,16,2,8},						//Point rect
		ID_MUSIC_VOL_BAR_POINT_BMP,			//point icon id
		
		{634,9,30,20},				//Rightspeaker
		ID_MUSIC_VOL_SPEAKER_RIGHT_BMP,		//Rightespeaker icon id
		
		{0,0,30,20},						//Mutespeaker
		ID_MUSIC_VOL_SHUT_DOWN_BMP,			//Mutespeaker icon id	

		{688, 12, 20, 16}		//volume number
};


__s32 MusicVolumeBarOnAddEvent(void *Attr)
{
	music_player_ctrl_t *This = Attr;
	if(This == NULL)
	{
		return EPDK_FAIL;
	}
	__msg("volume bar on Add event\n");
	//__wait__;
	This->volume = dsk_volume_get();
	GUI_LyrWinSel(This->music_layer);		
	DrawMusicVolumeStatus(This->volume);
}

__s32 MusicVolumeBarCreate(music_player_ctrl_t *This)
{	
	VolumeBarPara_t VBPara;
	
	eLIBs_memset((void *)(&VBPara), 0, sizeof(VolumeBarPara_t));
	eLIBs_memcpy((&(VBPara.UI)), &MusicVolBarUI, sizeof(VolumeBarUI_t));
	
	VBPara.CtrlVar.hParent = GUI_WinGetParent(This->h_framewin);
	VBPara.CtrlVar.UserLayer = This->music_layer;
	VBPara.CtrlVar.Pipe = 1;
	VBPara.CtrlVar.ViewAlign = GUI_TA_HORIZONTAL;
	VBPara.CtrlVar.vol_max = AUDIO_DEVICE_VOLUME_MAX;
	VBPara.CtrlVar.AutoExitTime = 3;			//10秒没有动作自动退出

	VBPara.Event.VolAddKey = GUI_MSG_KEY_RIGHT;
	VBPara.Event.VolAddRepeatKey = GUI_MSG_KEY_LONGRIGHT;
	VBPara.Event.VolDecKey = GUI_MSG_KEY_LEFT;
	VBPara.Event.VolDecRepeatKey = GUI_MSG_KEY_LONGVADD;	
	VBPara.Event.VolExitKey = GUI_MSG_KEY_MENU;
	VBPara.CtrlVar.attr = This;								//Musicplayer作为参数传入给VolumeBar
	VBPara.Event.OnVolAdd = MusicVolumeBarOnAddEvent;
	VBPara.Event.OnVolDec = MusicVolumeBarOnAddEvent;		//一样的函数即可

	This->hVolumeBar = VolumeBarCreate(&VBPara);
	if(This->hVolumeBar != NULL)
	{
		//VolumeBarSetFocus(This->hVolumeBar);
		//VolumeBarShow(This->hVolumeBar);
		//__msg("error in volume bar");
	}
	return EPDK_OK;
}






/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011-2014 CRI Middleware Co.,Ltd.
 *
 * Library  : CRIWARE
 * Module   : CRIWARE Sample for Unity
 * File     : ScriptSample03_GameScene.cs
 *
 ****************************************************************************/
 
using UnityEngine;
using System.Collections;

public class ScriptSample03_GameScene : MonoBehaviour {

	private int 	SceneMusicCueId = 2;
	private string 	nextSceneName   = "ScriptSample03_TitleScene";


	/* 始めてのUpdate()の前に呼ばれる */
	void Start () {
		/* BGM再生 */
		ScriptSample03_SoundManager.PlayCueId(SceneMusicCueId);
	}
		
	/* シーン切り替えGUIの表示と制御 */
	void OnGUI(){
		if (Scene_00_SampleList.ShowList == true) {
			return;
		}

		/* UIスキンの設定 */
		GUI.skin = Scene_00_SampleList.uiSkin;

		Scene_00_GUI.BeginGui("01/SampleMain");
		if (Scene_00_GUI.Button(new Rect(Screen.width-150,0,150,150), "change\nscene")) {
			Application.LoadLevel(nextSceneName);				
		}
		Scene_00_GUI.EndGui();
	}
}

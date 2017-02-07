/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011-2014 CRI Middleware Co.,Ltd.
 *
 * Library  : CRIWARE
 * Module   : CRIWARE Sample for Unity
 * File     : PlayAndStopSoundOnClick.cs
 *
 ****************************************************************************/
 
using UnityEngine;
using System.Collections;

/* クリックしたオブジェクトにCriAtomSourceがあればその音を鳴らす。すでに鳴っていたら止める */
public class PlayAndStopSoundOnClick : MonoBehaviour {
	
	private bool trigger = false;

	void Start () {
	}

	void Update () {
		if (trigger) {
			CriAtomSource atomSrc = gameObject.GetComponent<CriAtomSource>();
			if (atomSrc != null) {
				CriAtomSource.Status status = atomSrc.status;
				if ((status == CriAtomSource.Status.Stop) || (status == CriAtomSource.Status.PlayEnd)) {
					atomSrc.Play();
				} else {
					atomSrc.Stop();
				}
			}
			trigger = false;
		}
	}
	
	void OnGUI()
	{
		if (Scene_00_SampleList.ShowList == true) {
			return;
		}

		if (Camera.main == null) {
			return;
		}
		
		Scene_00_GUI.BeginGui("01/SampleMain2");
		
		/* UIスキンの設定 */
		GUI.skin = Scene_00_SampleList.uiSkin;

		var pos = Camera.main.WorldToScreenPoint(transform.position);
		pos.y   = Screen.height - pos.y;
		if (Scene_00_GUI.Button(new Rect(pos.x, pos.y, 150, 150), "Play/Stop")) {
			trigger = true;
		}
		
		Scene_00_GUI.EndGui();
	}
}

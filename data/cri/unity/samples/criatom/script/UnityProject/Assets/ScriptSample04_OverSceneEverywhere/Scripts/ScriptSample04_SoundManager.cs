/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011-2014 CRI Middleware Co.,Ltd.
 *
 * Library  : CRIWARE
 * Module   : CRIWARE Sample for Unity
 * File     : ScriptSample04_SoundManager.cs
 *
 ****************************************************************************/

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class ScriptSample04_SoundManager : MonoBehaviour {
	/* ACBファイル名(キューシート名) */
	public string cueSheetName = "CueSheet_0";
	
	private CriAtomSource atomSourceMusic;
	static private ScriptSample04_SoundManager instance = null;
	
	void Awake ()
	{
		if (instance != null) {
			/* 多重生成を回避するため, 後から作られたSoundManagerは自分自身を破棄する.
			 * ただし, SoundManagerをコンポーネントにもつGameObject自体は破棄されない. 
			 * そのため, Unityエディタのヒエラルキー上には, 同じ名前のGameObjectが複数存在することになる */
			GameObject.Destroy(this);
			return;
		}
		
		/* Bgm音用のCriAtomSourceを作成 */
		atomSourceMusic = gameObject.AddComponent<CriAtomSource> ();
		atomSourceMusic.cueSheet = cueSheetName;	
		
		/* シーン切り替え時にSoundMangerを破棄しない */
		GameObject.DontDestroyOnLoad(this.gameObject);
		instance = this;
	}
	
	static public void PlayCueId(int cueId){
		instance.atomSourceMusic.Play(cueId);
	}
	
	void OnDestroy(){
		if (instance == this) {
			instance = null;
		}
	}

}


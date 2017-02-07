/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011-2012 CRI Middleware Co.,Ltd.
 *
 * Library  : CRI Atom
 * Module   : CRI Atom Sample for Unity
 * File     : Scene_03_AISAC.cs
 *
 ****************************************************************************/
/*JP
 * 本サンプルは、AISACのコントロールを行います。
 *
 * データ上のAISACにはピッチのカーブが設定されており、 スライダーを動かして
 * AISACコントロール値を変化させることでピッチが変化します。
 */
/*EN
 * This sample performs AISAC controls
 *
 * An AISAC that has a pitch curve is set up on the data.
 * By changing the AISAC control value, the pitch changes.
 */
using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Scene_03_AISAC : MonoBehaviour
{
	#region Variables
	/* AISAC control value */
	private float[] aisacValueList = new float[16];
	/* CriAtomSource */
	private CriAtomSource atomSource = null;
	private List<CriAtomEx.AisacControlInfo> aisacControlInfoList = new List<CriAtomEx.AisacControlInfo>();
	#endregion

	void Start()
	{
		/* Get the AtomSource */
		atomSource = gameObject.GetComponent<CriAtomSource>();
		
		/* Get the AISACControlInfo */
		GetAisacControlInfo();

		/* Set 0.0 to the AISAC */
		foreach(CriAtomEx.AisacControlInfo aisacControlInfo in aisacControlInfoList) {
			aisacValueList[aisacControlInfo.id] = 0.0f;
			atomSource.SetAisac(aisacControlInfo.id, aisacValueList[aisacControlInfo.id]);
		}

		/* Play the Cue */
		atomSource.Play();
	}
	
	void GetAisacControlInfo()
	{
		/* Get the information about the Cues in the CueSheet */
		CriAtomExAcb acb = CriAtom.GetAcb("DemoProj");	
		CriAtomEx.AisacControlInfo[] tmpAisacControlInfoList = acb.GetUsableAisacControlList(atomSource.cueName);
		
		aisacControlInfoList.Clear();
		foreach(CriAtomEx.AisacControlInfo aisacControlInfo in tmpAisacControlInfoList){
			aisacControlInfoList.Add(aisacControlInfo);
		}
		
		for (int i = 0; i < 16; i++) {
			this.aisacValueList[i] = 0.0f;
		}
	}
	
	#region Functions
	void OnGUI()
	{
		if (Scene_00_SampleList.ShowList == true) {
			return;
		}
		
		Scene_00_GUI.BeginGui("01/SampleMain");
		
		/* Set UI skin */
		GUI.skin = Scene_00_SampleList.uiSkin;
		
		GUILayout.BeginArea(new Rect(12, 70, 480, 150), "", Scene_00_SampleList.TextStyle);
		foreach(CriAtomEx.AisacControlInfo aisacControlInfo in aisacControlInfoList){
			GUILayout.Label( "AISAC Control Value " 
				+ this.aisacValueList[aisacControlInfo.id].ToString("0.00")
				+ " " +  aisacControlInfo.name);
			this.aisacValueList[aisacControlInfo.id] = Scene_00_GUI.HorizontalSlider(this.aisacValueList[aisacControlInfo.id], 0.0f, 1.0f);
			if (GUI.changed) {
				/* Configure the AISAC */
				atomSource.SetAisac(aisacControlInfo.id, this.aisacValueList[aisacControlInfo.id]);
			}			
			
		}
		GUILayout.EndArea();
		
		Scene_00_GUI.EndGui();
	}
	#endregion
}
/* end of file */

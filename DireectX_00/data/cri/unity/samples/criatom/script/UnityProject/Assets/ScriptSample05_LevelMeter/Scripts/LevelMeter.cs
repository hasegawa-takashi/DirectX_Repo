﻿/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2011-2014 CRI Middleware Co.,Ltd.
 *
 * Library  : CRIWARE
 * Module   : CRIWARE Sample for Unity
 * File     : LevelMeter.cs
 *
 ****************************************************************************/

using UnityEngine;
using System.Collections;

public class LevelMeter : MonoBehaviour {
	
	public int		monitoredChannelId = 0;

	private int		analyzedDspBusId = 0;
	private float	objScaleBaseVal = 2.0f;
	
	/* This "Start()" method is called before "Update()".*/
	void Start () {
		CriAtom.AttachDspBusSetting("DspBusSetting_0");
		/* Set Bus Analayzer to use "BusAnalyzeInfo" */
		CriAtom.SetBusAnalyzer(true);
	}
		
	/* Update the local scale value of GameObject */
	void Update(){
		/* Get BusAnalyzerInfo from a DSP Buss verifyed by mDspBusId*/
		CriAtomExAsr.BusAnalyzerInfo lBusInfo = CriAtom.GetBusAnalyzerInfo(analyzedDspBusId);

		/* calculate new value of GameObject scale */
		//float lObjScaleNewVal = 0.1f + objScaleBaseVal * lBusInfo.rmsLevels[monitoredChannelId];
		float lObjScaleNewVal = 0.1f + objScaleBaseVal * lBusInfo.peakLevels[monitoredChannelId];
		Debug.Log("Channel_" + monitoredChannelId + " : " + lBusInfo.peakLevels[monitoredChannelId]);
		
		/* update local scale of 'this' game object */
		this.transform.localScale = new Vector3(lObjScaleNewVal, lObjScaleNewVal, lObjScaleNewVal);
	}
}

/****************************************************************************
*
* CRI Middleware SDK
*
* Copyright (c) 2011-2012 CRI Middleware Co., Ltd.
*
* Library  : CRI Atom
* Module   : CRI Atom for Unity
* File     : CriAtomProjInfo_Unity.cs
* Tool Ver.          : CRI Atom Craft LE Ver.2.19.01
* Date Time          : 2016/03/30 16:06
* Project Name       : Pinball
* Project Comment    : 
*
****************************************************************************/
using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public partial class CriAtomAcfInfo
{
    static partial void GetCueInfoInternal()
    {
        acfInfo = new AcfInfo("ACF", 0, "", "Pinball.acf","3e4fa558-fe39-443f-94ac-61369ebedf69","DspBusSetting_0");
        acfInfo.aisacControlNameList.Add("Any");
        acfInfo.aisacControlNameList.Add("Distance");
        acfInfo.aisacControlNameList.Add("AisacControl02");
        acfInfo.aisacControlNameList.Add("AisacControl03");
        acfInfo.aisacControlNameList.Add("AisacControl04");
        acfInfo.aisacControlNameList.Add("AisacControl05");
        acfInfo.aisacControlNameList.Add("AisacControl06");
        acfInfo.aisacControlNameList.Add("AisacControl07");
        acfInfo.aisacControlNameList.Add("AisacControl08");
        acfInfo.aisacControlNameList.Add("AisacControl09");
        acfInfo.aisacControlNameList.Add("AisacControl10");
        acfInfo.aisacControlNameList.Add("AisacControl11");
        acfInfo.aisacControlNameList.Add("AisacControl12");
        acfInfo.aisacControlNameList.Add("AisacControl13");
        acfInfo.aisacControlNameList.Add("AisacControl14");
        acfInfo.aisacControlNameList.Add("AisacControl15");
        acfInfo.acbInfoList.Clear();
        AcbInfo newAcbInfo = null;
        newAcbInfo = new AcbInfo("PinballMain", 0, "", "PinballMain.acb", "PinballMain.awb","3352f5db-33de-4d1d-b496-67ee2ca5f1cd");
        acfInfo.acbInfoList.Add(newAcbInfo);
        newAcbInfo.cueInfoList.Add(6, new CueInfo("aaa", 6, ""));
        newAcbInfo.cueInfoList.Add(0, new CueInfo("Ball", 0, ""));
        newAcbInfo.cueInfoList.Add(1, new CueInfo("BallLost", 1, ""));
        newAcbInfo.cueInfoList.Add(2, new CueInfo("Bumper", 2, ""));
        newAcbInfo.cueInfoList.Add(3, new CueInfo("HitTarget", 3, ""));
        newAcbInfo.cueInfoList.Add(4, new CueInfo("GameOver", 4, ""));
        newAcbInfo.cueInfoList.Add(5, new CueInfo("Paddle", 5, ""));
        newAcbInfo.cueInfoList.Add(100, new CueInfo("BGM", 100, ""));
    }
}

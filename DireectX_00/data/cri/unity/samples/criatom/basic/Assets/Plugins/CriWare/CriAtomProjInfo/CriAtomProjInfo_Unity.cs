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
* Date Time          : 2016/03/30 16:00
* Project Name       : demoProj
* Project Comment    : Atom Craftデモ
*
****************************************************************************/
using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public partial class CriAtomAcfInfo
{
    static partial void GetCueInfoInternal()
    {
        acfInfo = new AcfInfo("ACF", 0, "", "demoProj.acf","dd2acb67-4399-4314-9d07-4ffc228a55e2","DspBusSetting_0");
        acfInfo.aisacControlNameList.Add("Rnd");
        acfInfo.aisacControlNameList.Add("Distance");
        acfInfo.aisacControlNameList.Add("AisacControl");
        acfInfo.aisacControlNameList.Add("Any");
        acfInfo.aisacControlNameList.Add("rainlevel");
        acfInfo.aisacControlNameList.Add("RotateSpeed");
        acfInfo.aisacControlNameList.Add("rpm");
        acfInfo.aisacControlNameList.Add("load");
        acfInfo.aisacControlNameList.Add("Pitch");
        acfInfo.aisacControlNameList.Add("FIlter");
        acfInfo.aisacControlNameList.Add("AisacControl10");
        acfInfo.aisacControlNameList.Add("AisacControl11");
        acfInfo.aisacControlNameList.Add("AisacControl12");
        acfInfo.aisacControlNameList.Add("AisacControl13");
        acfInfo.aisacControlNameList.Add("AisacControl14");
        acfInfo.aisacControlNameList.Add("AisacControl15");
        acfInfo.acbInfoList.Clear();
        AcbInfo newAcbInfo = null;
        newAcbInfo = new AcbInfo("DemoProj", 0, "Atom Craft機能紹介デモデータ", "DemoProj.acb", "DemoProj.awb","b9d09b07-7e2d-473c-ab34-899d16da89d2");
        acfInfo.acbInfoList.Add(newAcbInfo);
        newAcbInfo.cueInfoList.Add(0, new CueInfo("gun1_High", 0, "単純再生（1Shot）"));
        newAcbInfo.cueInfoList.Add(1, new CueInfo("bomb2", 1, "単純再生（1Shot長め）"));
        newAcbInfo.cueInfoList.Add(2, new CueInfo("heli_Loop", 2, "ループ音"));
        newAcbInfo.cueInfoList.Add(4, new CueInfo("Ttrailer_ShortLoop", 4, "音楽ループ"));
        newAcbInfo.cueInfoList.Add(8, new CueInfo("SE_SEQ", 8, "シーケンスのサンプル"));
        newAcbInfo.cueInfoList.Add(10, new CueInfo("RichThunder", 10, "雷３音のミックス"));
        newAcbInfo.cueInfoList.Add(11, new CueInfo("RichThunder_3D", 11, "サラウンド配置した音"));
        newAcbInfo.cueInfoList.Add(12, new CueInfo("RichThunder_Random", 12, "距離、音程、タイミングなどランダム"));
        newAcbInfo.cueInfoList.Add(13, new CueInfo("RichThunder_with_AISAC", 13, "AISACで雨の音をコントロール"));
        newAcbInfo.cueInfoList.Add(6, new CueInfo("ThunderSeq", 6, "雷シーケンス（雷後雨の音が上がる）"));
        newAcbInfo.cueInfoList.Add(16, new CueInfo("heli_Loop_AISAC", 16, "AISACで回転数をコントロール"));
        newAcbInfo.cueInfoList.Add(19, new CueInfo("RichHeli_Complex", 19, "AISACでコントロール。回転数大の時に風切音が追加される。"));
        newAcbInfo.cueInfoList.Add(22, new CueInfo("FootStep_Distance", 22, "交互に足音を再生（AISACによる距離減衰）"));
        newAcbInfo.cueInfoList.Add(23, new CueInfo("bomb_Distance", 23, "爆発音（AISACによる距離減衰コントロール）"));
        newAcbInfo.cueInfoList.Add(5, new CueInfo("DistanceDemoSeq", 5, "距離減衰をコントロールしたシーケンス"));
        newAcbInfo.cueInfoList.Add(25, new CueInfo("Voice_FantomCenter", 25, "L、Rスピーカ出力によるファントムセンター再生"));
        newAcbInfo.cueInfoList.Add(26, new CueInfo("Voice_RealCenter", 26, "センタースピーカ出力によるリアルセンター再生"));
        newAcbInfo.cueInfoList.Add(27, new CueInfo("KALIMBA_G", 27, "カリンバの音（単発）"));
        newAcbInfo.cueInfoList.Add(28, new CueInfo("KALIMBA_Random", 28, "AISACを使った音階を持つランダム"));
        newAcbInfo.cueInfoList.Add(29, new CueInfo("KALIMBA_Random3D", 29, "音パンニングと音程の連動したランダム"));
        newAcbInfo.cueInfoList.Add(30, new CueInfo("KalimbaSequence", 30, "ランダム生成ジングル"));
        newAcbInfo.cueInfoList.Add(35, new CueInfo("Fireworks", 35, "花火の音（複雑な組み合わせのランダム）"));
        newAcbInfo.cueInfoList.Add(40, new CueInfo("Engine_AISAC_2AXIS", 40, "エンジン音（２つのAISACを使用）"));
        newAcbInfo.cueInfoList.Add(7, new CueInfo("EngineDemoSeq", 7, "２つのAISACをシーケンスで動かす"));
        newAcbInfo.cueInfoList.Add(41, new CueInfo("DJ_Scratch", 41, "AISACのさまざまなパラメータグラフ（AISACによるコントロール）"));
        newAcbInfo.cueInfoList.Add(70, new CueInfo("Music4Tk", 70, "４つのシチュエーションのある音楽（AISACによるコントロール）"));
        newAcbInfo.cueInfoList.Add(56, new CueInfo("Music18Trk", 56, "18Trkの音楽（AISACによるコントロール）"));
        newAcbInfo.cueInfoList.Add(57, new CueInfo("SwitchTrack", 57, "18Trkの一つのみ再生する（AISACによるSwitch）"));
        newAcbInfo.cueInfoList.Add(71, new CueInfo("Theremin", 71, "テルミン音（ループ）"));
        newAcbInfo.cueInfoList.Add(72, new CueInfo("Ambient_4Spekers", 72, "怖い音のサンプル"));
        newAcbInfo.cueInfoList.Add(73, new CueInfo("Moving_Heli", 73, "ヘリコプタの音をまわすサンプル（AISACオートモジュレーション）"));
        newAcbInfo.cueInfoList.Add(77, new CueInfo("Kansei", 77, "AISACによる歓声量のコントロール"));
        newAcbInfo.cueInfoList.Add(15, new CueInfo("KanseiSEQ", 15, "シーケンスのトラックオートメーションによる歓声量の自動変化"));
        newAcbInfo.cueInfoList.Add(14, new CueInfo("yutorehito", 14, "言語設定を変更すると音が変化するデモ(言語設定を「English」に変更)"));
        newAcbInfo.cueInfoList.Add(17, new CueInfo("cri_middleware_sdk_Special", 17, "Trailer_ShoerLoopを再生しながら再生すると、REACTが起動し、MUSICカテゴリが小さくなる。"));
        newAcbInfo.cueInfoList.Add(18, new CueInfo("Ttrailer_ShortLoop_BGM", 18, "cri_middleware_sdkを再生するとこのカテゴリの音が小さくなる。再生が終わると自動で元のボリュームに戻る。"));
        newAcbInfo.cueInfoList.Add(31, new CueInfo("ReactTest", 31, "REACTの実行テスト"));
        newAcbInfo.cueInfoList.Add(3, new CueInfo("cri_middleware_sdk", 3, "台詞"));
        newAcbInfo.cueInfoList.Add(9, new CueInfo("Echo", 9, "エコー"));
        newAcbInfo.cueInfoList.Add(20, new CueInfo("PitichSift", 20, "ピッチシフト"));
        newAcbInfo.cueInfoList.Add(21, new CueInfo("Compresor", 21, "コンプレッサ（前半コンプ、後半はダイレクト）"));
        newAcbInfo.cueInfoList.Add(24, new CueInfo("beamUp", 24, ""));
        newAcbInfo.cueInfoList.Add(32, new CueInfo("kalimbaScaleUp", 32, ""));
        newAcbInfo.cueInfoList.Add(33, new CueInfo("Music", 33, ""));
        newAcbInfo.cueInfoList.Add(34, new CueInfo("bgm_01", 34, ""));
        newAcbInfo.cueInfoList.Add(36, new CueInfo("bgm_02", 36, ""));
        newAcbInfo.cueInfoList.Add(37, new CueInfo("bgm_03", 37, ""));
        newAcbInfo.cueInfoList.Add(38, new CueInfo("bgm_04", 38, ""));
        newAcbInfo.cueInfoList.Add(39, new CueInfo("bgm_05", 39, ""));
        newAcbInfo = new AcbInfo("DemoProj2", 1, "Atom Craft機能紹介デモデータ2", "DemoProj2.acb", "DemoProj2.awb","bb0a52aa-eddb-4e4f-a7aa-4eb63b027a22");
        acfInfo.acbInfoList.Add(newAcbInfo);
        newAcbInfo.cueInfoList.Add(0, new CueInfo("cri_middleware_sdk", 0, "声デフォルト"));
        newAcbInfo.cueInfoList.Add(1, new CueInfo("cri_middleware_sdk_PitchHi", 1, "声高め"));
        newAcbInfo.cueInfoList.Add(2, new CueInfo("gun1_High_TrackAutomation", 2, "トラックオートメーションによる効果音"));
        newAcbInfo.cueInfoList.Add(3, new CueInfo("VoiceBehavior", 3, "ボイスビヘイビア仮想ボイスデモ(Vol0で停止、復帰時刻経過あり)"));
        newAcbInfo.cueInfoList.Add(4, new CueInfo("ExtCue", 4, "外部キューリンク"));
    }
}

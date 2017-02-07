/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2014 CRI Middleware Co.,Ltd.
 *
 * Library  : CRIWARE
 * Module   : CRIWARE Sample for Unity
 * File     : Scene_00_SampleListData.cs
 *
 ****************************************************************************/

public static class Scene_00_SampleListData {
    public const string Title = "< CRI Atom Sample >";
	
	public static readonly string[,] SceneList = new string[,]{
		{"Scene_01_SimplePlayback",
			"キューブをクリックすると音声が再生される\nシンプルなサンプルです。"
		},
		{"Scene_02_3DPosition",
			"3Dポジショニングによるヘリコプターの距離減衰が\n行われるサンプルです。"
		},
		{"Scene_03_AISAC",
			"AISACによるパラメータコントロールを\n行うサンプルです。\nスライダーを変化させることでピッチが変化します。"
		},
		{"Scene_04_ControlParameter",
			"SoundSourceによるパラメータコントロールを\n行うサンプルです。\nスライダーを変化させることで音色が変化します。"
		},
		{"Scene_05_Category",
			"カテゴリによるパラメータコントロールを\n行うサンプルです。\nスライダによりボリュームが変化します。"
		},
		{"Scene_06_BlockPlayback",
			"ブロック再生を行うサンプルです。\n再生中にブロックを切り替える事で\n音声の状態が変化します。"
		},
		{"Scene_07_Ingame_Pinball",
			"ピンボールゲーム風のサンプルです。\nスクリプトにより音声を再生しており、\nCRI Atom Craftからの\nインゲームプレビュー接続が可能です。"
		},
	};
}

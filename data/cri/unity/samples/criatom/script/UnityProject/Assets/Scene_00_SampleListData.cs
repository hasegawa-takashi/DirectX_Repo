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
		{"ScriptSample01_ClickToPlay",
			"オブジェクトをクリックしてサウンドを\n再生するスクリプトのサンプルです。"
		},
		{"ScriptSample02_SoundTest",
			"キューシートファイル(ACBファイル)内のキューの\n一覧をボタンで表示するサンプルスクリプトです。"
		},
		{"ScriptSample03_TitleScene",
			"シーン切り替え時に音楽をクロスフェードさせる\nスクリプトのサンプルです。"
		},
		{"ScriptSample04_TitleScene",
			"シーンを越えてサウンド制御しつつ\nどのシーンからでも実行可能にするサンプルです"
		},
		{"ScriptSample05_LevelMeter",
			"再生音量をリアルタイムに取得し\nキューブのサイズとして視覚化するサンプルです。"
		},
		{"GameSample_Pinball",
			"ゲーム風ピンボールの\n CRI Atom Craft サンプルプロジェクトです。"
		},
	};
}

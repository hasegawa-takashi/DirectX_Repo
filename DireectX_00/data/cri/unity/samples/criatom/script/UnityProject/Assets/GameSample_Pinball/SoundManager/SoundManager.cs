using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class SoundManager : MonoBehaviour {
	
	/* キューシート名 */
	private string cueSheetName = "PinballMain";
	
	CriAtomSource atomSourceSe;
	CriAtomSource atomSourceBall;
	CriAtomSource atomSourceBgm;
	CriAtomSource atomSourceBumper;
	
	
	void Awake ()
	{
		/* SE音用のCriAtomSource作成 */
		atomSourceSe = gameObject.AddComponent<CriAtomSource> ();
		atomSourceSe.cueSheet = cueSheetName;
		
		/* Ball音用のCriAtomSource作成 */
		atomSourceBall = gameObject.AddComponent<CriAtomSource> ();
		atomSourceBall.cueSheet = cueSheetName;
		
		/* Bumper音用のCriAtomSource作成 */
		atomSourceBumper = gameObject.AddComponent<CriAtomSource> ();
		atomSourceBumper.cueSheet = cueSheetName;
		
		/* Bgm音用のCriAtomSource作成 */
		atomSourceBgm = gameObject.AddComponent<CriAtomSource> ();
		atomSourceBgm.cueSheet = cueSheetName;
	}
	// Use this for initialization
	void Start () {
		/* DSPバス設定: CRIWARE Object 側で指定済み*/
		//CriAtom.AttachDspBusSetting("DspBusSetting_0");
		
		/* インゲームプレビュー時のレベルモニタ機能追加　*/
		CriAtom.SetBusAnalyzer(true);
	}
	
	float lastResumeBgmTime = 0;
	// Update is called once per frame
	void Update () {
		
		if(lastResumeBgmTime + 2 < Time.timeSinceLevelLoad){
			ResumeBGM();
			lastResumeBgmTime = Time.timeSinceLevelLoad;	
		}
	}
	
	public void PlaybackCue(int index)
	{
		atomSourceSe.Play(index);
	}
	
	public void PlayGameOver()
	{
		//atomSourceSe.Play(4); // by Cue ID
		atomSourceSe.Play("GameOver"); // by Cue Name
	}
		
	
	float lastPlaybackBallTime = 0;
	public float lastVelocity = 0.0f;
	/// <summary>
	/// ボールあたり音
	/// </summary>
	public void PlaybackBall(int index,float velocity)
	{
		if(lastPlaybackBallTime+0.25 < Time.timeSinceLevelLoad){
			velocity = Mathf.Min(velocity,1.0f);
			atomSourceBall.SetAisac(0,velocity);
			atomSourceBall.Play(index);
			lastPlaybackBallTime = Time.timeSinceLevelLoad;
			
			lastVelocity = velocity;
		}
	}
	
	float lastPlaybackBumperTime = 0;
	public void PlaybackBumper(int index)
	{
		if(lastPlaybackBumperTime+0.25 < Time.timeSinceLevelLoad){
			atomSourceBumper.Play(index);
			lastPlaybackBumperTime = Time.timeSinceLevelLoad;
		}
	}
	
	public void ResumeBGM()
	{
		/* 再生終了か停止状態の時に再生します（ACB更新時などに自動復帰させる） */
		CriAtomSource.Status status = atomSourceBgm.status;
		if ((status == CriAtomSource.Status.Stop) || (status == CriAtomSource.Status.PlayEnd)) {
			/* 再生 */
			PlayBGM();
			

			
		}
	}
	private CriAtomExPlayback playbackBGM;
	CriAtomEx.CueInfo cueInfo;
	public void PlayBGM()
	{
		bool startFlag = false;
		CriAtomSource.Status status = atomSourceBgm.status;
		if ((status == CriAtomSource.Status.Stop) || (status == CriAtomSource.Status.PlayEnd)) {
			this.playbackBGM = atomSourceBgm.Play(100);
			startFlag = true;
		}
		
		/*	初回再生以外ならブロックをすすめる　*/
		if(startFlag == false){
			int cur = this.playbackBGM.GetCurrentBlockIndex();
			CriAtomExAcb acb = CriAtom.GetAcb("PinballMain");
			if(acb != null){
				acb.GetCueInfo("BGM",out this.cueInfo);
				
				cur++;
				if(this.cueInfo.numBlocks > 0){
					this.playbackBGM.SetNextBlockIndex(cur % this.cueInfo.numBlocks);
				}
				
			}
		}
	}
	
	public void Pause()
	{
		atomSourceBgm.Pause(true);
	}
	public void Resume()
	{
		atomSourceBgm.Pause(false);
	}
	
	
}

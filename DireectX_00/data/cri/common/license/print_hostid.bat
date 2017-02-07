@echo off

rem ライセンスキーファイル申請用ホストIDの表示

lmhostid | %SystemRoot%\system32\find "FLEXnet" >> %TMP%\temp_ipconfig.txt
%SystemRoot%\system32\notepad %TMP%\temp_ipconfig.txt
del %TMP%\temp_ipconfig.txt

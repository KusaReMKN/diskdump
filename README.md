# DiskDump

A diskette image generator

## これは何

MS-DOS や Windows 9x の上でディスケットのイメージを生成する CUI アプリケーションです。
PC-98 で利用される 1.2 MB でフォーマットされたディスケットのイメージを生成するために作られました。

## 書式

```console
> DISKDUMP[.COM] [/V] drive[:] filename
```

- `/V`: よく喋るようになります。
- `drive[:]`: イメージを生成するドライブを指定します。ハードディスクすら指定できるので注意してください。
- `filename`: イメージのファイル名を指定します。長いファイル名は利用できません。

## ビルド環境

ビルドには Open Watcom C/C++ Version 1.9 を利用しています。
http://openwatcom.org/ からダウンロードできます。

## ライセンス

MIT License

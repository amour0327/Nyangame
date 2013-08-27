## インストールするもの
* cocos2d-x 2.1.4
* Android NDK 8e
* Eqlipse 
* Xcode 4.6.3 

## Android NDK のセットアップ
Android DeveloperサイトのNDKページからダウンロードしてきます。  
ただし、Cocos2d-x 2.1.4バージョンだと NDK r9 を使うとエラーになる為、今回はr8eを使用しました。

**Eclipse上の環境設定**  
Eclipseを起動してメニュー上から「Eqlipse >環境設定」を選びます。  
「Android > NDK」にある「NDKLocation」項目へ「/(Android NDKを配置したディレクトリ)/android-ndk-r8e」を設定します。
同じように環境設定から「C/C++ > Build > Environment」で「Add」ボタンを押下し、  
「Name」項目に「NDK_ROOT」、「Value」項目に「/(Android NDKを配置したディレクトリ)/android-ndk-r8e」を設定します。

## Cocos2d-x のセットアップ
Cocos2d-xのwikiからCocos2d-xをダウンロードしてください。

**Android SDK/NDKインストール ディレクトリを設定**  
cocos2d-x-2.1.4/create-android-project.sh ファイルの最初にある二行を以下のように置き換えます。
```
NDK_ROOT_LOCAL="/(Android NDKを配置したディレクトリ)/android-ndk-r8e"
ANDROID_SDK_ROOT_LOCAL="/(Android SDKを配置したディレクトリ)/android-sdk"
```

cocos2d-x-2.1.4/template/android/build_native.sh ファイルの二行目に以下の一文を挿入します。

```
NDK_ROOT="/(Android NDKを配置したディレクトリ)/android-ndk-r8e"
```

**Cocos2d-xのAndroid向けライブラリ libcocos2dx を追加**

Eclipseを起動してメニュー上から「File > Import」を選びます。  
「Android > Existing Android Code Into Workspace」を選択し、「Import Projects」画面の  
Root ディレクトリ項目に「/(cocos2d-xを配置したディレクトリ)/cocos2d-x-2.1.4/cocos2dx/platform/android/java」を  
指定して「Finish」ボタンを押下します。

## プロジェクトの作成
ターミナル上から以下のように create_project.py を実行する事でプロジェクトを新規作成できます。  
以下の例ではプロジェクト名「Nyangame」で、パッケージ名「jp.hoge.nyangame」で、  
開発言語「C++」を指定して作成しています。

```
cd cocos2d-x-2.1.4/tools/project-creator
./create_project.py -project Nyangame -package jp.hoge.nyangame -language cpp
```

create_project.py のオプションは以下のようになっています。

| オプション名 | 意味 | 具体的な指定名 | 備考 |
| :----------: | :--: | :------------: | :--- |
| project	| プロジェクト名 | | |
| package	| パッケージ名 | |.は2つ以上付けないとエラーになります |
| language | 開発言語 | cpp<br>lua<br>javascript | |

//
//  BRScanJob.h
//  BRScanKit
//
//
//  Copyright (c) 2014 Brother Industries, Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
@protocol BRScanJobDelegate;

/// スキャンジョブの結果を示す定数です。
typedef NS_ENUM(NSUInteger, BRScanJobResult) {
    /// ジョブは成功しました。
    BRScanJobResultSuccess,
    
    /// ジョブはキャンセルされました。
    BRScanJobResultCancel,
    
    /// ジョブは失敗しました。
    BRScanJobResultFail,
};

/// スキャンジョブが失敗した際のエラーの内容を示す定数です。
typedef NS_ENUM(NSUInteger, BRScanJobError) {
    // Generic
    
    /// スキャンデバイスとの接続に失敗しました。
    BRScanJobErrorConnection,
    
    /// iOS端末がメモリ不足です。
    BRScanJobErrorMemory,
    
    // Scan
    
    /// iOS端末の容量不足等によりファイルの書き込みに失敗しました。
    BRScanJobErrorDisk,
    
    /// 原稿ジャムです。
    BRScanJobErrorPaperJam,
    
    /// タイムアウトです。
    BRScanJobErrorTimeout,
    
    /// カバーが開いています。<br>
    /// (インクモデルのみ)
    BRScanJobErrorCoverOpen,
    
    /// スキャンデバイスが動作中です。
    BRScanJobErrorDeviceBusy,
    
    /// スキャンデバイスのメモリーエラーです。
    BRScanJobErrorDeviceMemory,
    
    /// 原稿がセットされていません。
    BRScanJobErrorNoPaper,
    
    /// 原稿が長すぎます。
    BRScanJobErrorTooLongDocument,
    
    /// スキャンデバイスのスキャン機能がロックされています。
    BRScanJobErrorFunctionLocked,
    
    /// ADFが開いています。
    BRScanJobErrorADFCoverOpen,
    
    /// 排紙トレイに原稿が残っている状態でスキャンしようとしました。<br>
    /// (一部レーザーモデルのみ)
    BRScanJobErrorPapersOnTray,
    
    /// 原稿の幅が大きすぎます。
    BRScanJobErrorTooWideDocument,
    
    /// 対応していない原稿サイズです。
    BRScanJobErrorUnsupportedDocument,
    
    /// 複数枚の原稿が給紙されました。<br>
    /// (ドキュメントスキャナモデルのみ)
    BRScanJobErrorMultifeed,
    
    /// カード排紙トレイが開いています。<br>
    /// (カード排紙トレイが搭載されているモデルのみ)
    BRScanJobErrorCardTrayOpen,
    
    /// カード排紙トレイが閉じています。<br>
    /// (カード排紙トレイが搭載されているモデルのみ)
    BRScanJobErrorCardTrayClose,
    
    /// ADFで対応していない原稿サイズです。
    BRScanJobErrorADFUnsupportedSize,
    
    /// カードスロットが開いています。 <br>
    /// (ADS-1000W, ADS-1100W, ADS-1500W, ADS-1600Wのみ)
    BRScanJobErrorCardScanTopCoverOpen,
    
    /// カードスロットがスキャン中に開かれました。<br>
    /// (ADS-1000W, ADS-1100W, ADS-1500W, ADS-1600Wのみ)
    BRScanJobErrorCardScanTopCoverOpenDuringScan,
    
    /// カードスロットに原稿が挿入されました。<br>
    /// (ADS-1000W, ADS-1100W, ADS-1500W, ADS-1600Wのみ)
    BRScanJobErrorCardScanSlotInsert,
    
    /// カードスロットが空です。<br>
    /// (ADS-1000W, ADS-1100W, ADS-1500W, ADS-1600Wのみ)
    BRScanJobErrorCardScanSlotEmpty,
    
    /// カードスロットがジャムを起こしています。<br>
    /// (ADS-1000W, ADS-1100W, ADS-1500W, ADS-1600Wのみ)
    BRScanJobErrorCardScanSlotJam,
    
    // Other
    
    /// パラメーターエラーです。
    BRScanJobErrorInternalParameter,
    
    /// 内部プロセスのエラーです。
    BRScanJobErrorInternalProcess,
    
    /// その他の要因によるエラーです。
    BRScanJobErrorOther,
};

#pragma mark -

/**
 スキャンジョブを管理するクラスです。
 */
@interface BRScanJob : NSObject

/// delegateによる通知を行うための変数です。
@property (nonatomic, weak) id <BRScanJobDelegate>  delegate;

/**
 スキャンオプションを指定するNSDictionaryです。
 
 以下のkeyでオプションを指定します。
 NSNumberクラスで数値をラップして指定してください。
 
 - BRScanJobOptionColorTypeKey
  - カラータイプの指定
  - [BRScanJobOptionColorType](../Constants/BRScanJobOptionColorType.html) 参照
 
 - BRScanJobOptionDocumentSizeKey
  - 原稿サイズの指定
  - [BRScanJobOptionDocumentSize](../Constants/BRScanJobOptionDocumentSize.html) 参照
 
 - BRScanJobOptionDuplexKey
  - 両面スキャンの指定
  - [BRScanJobOptionDuplex](../Constants/BRScanJobOptionDuplex.html) 参照
 
 - BRScanJobOptionSkipBlankPageKey
  - NO  : 白紙除去を無効にします
  - YES : 白紙除去を有効にします
 
 - BRScanJobOptionUseVirtualScanModeKey
  - 開発のためのオプションです。
  - 仮想的なスキャナデバイスを用いて、実機なしでスキャンの実行をエミュレートします。
  - NO  : 仮想的なスキャナデバイスを利用しません
  - YES : 仮想的なスキャナデバイスを利用します
 
 - BRScanJobOptionVirtualScanPageCountKey
  - 開発のためのオプションです。
  - 仮想的なスキャナデバイスによって行われるスキャンの枚数を指定します。
  - NSUInteger型をNSNumberクラスでラップして指定してください。
 
 - BRScanJobOptionVirtualScanPageIntervalKey
  - 開発のためのオプションです。
  - 仮想的なスキャナデバイスでスキャンを行った際に、ページが追加される周期を秒で指定します。
  - CGFloat型をNSNumberクラスでラップして指定してください。
 */
@property (nonatomic, strong) NSDictionary *        options;

/// スキャンデバイスのIP Addressです。
@property (nonatomic, strong, readonly) NSString *  IPAddress;

/// スキャン結果の画像ファイルのパスが格納されるNSArrayです。
@property (nonatomic, strong, readonly) NSArray *   filePaths;

/// エラーが発生した際に、NSErrorが格納されます。
@property (nonatomic, strong, readonly) NSError *   error;

/**
 BRScanJobクラスを初期化します。
 
 @param IPAddress スキャンデバイスのIP Address
 @return BRScanJobクラスのインスタンス
 */
- (id)initWithIPAddress:(NSString *)IPAddress;

/// スキャンを開始します。
- (void)start;

/// スキャンをキャンセルします。
- (void)cancel;

@end

#pragma mark -

/**
 BRScanJobクラスからdelegateを用いた通知を受け取る際に利用するプロトコルです。
 */
@protocol BRScanJobDelegate <NSObject>
@required

/**
 全ページのスキャンが完了した際に呼ばれるdelegateメソッドです。
 
 @param job このメソッドを呼んだBRScanJobクラスの変数です。
 @param result ジョブの結果を表します。[BRScanJobResult](../Constants/BRScanJobResult.html) 参照。
 */
- (void)scanJobDidFinishJob:(BRScanJob *)job result:(BRScanJobResult)result;

@optional
/**
 スキャンが1ページ完了した際に呼ばれるdelegateメソッドです。
 
 @param job このメソッドを呼んだBRScanJobクラスの変数です。
 @param didFinishPage スキャン結果の画像ファイルのパスです。
 */
- (void)scanJob:(BRScanJob *)job didFinishPage:(NSString *)path;

/**
 スキャンジョブが進行した際に呼ばれるdelegateメソッドです。
 
 @param job このメソッドを呼んだBRScanJobクラスの変数です。
 @param progress 現在のジョブの進行度です。
 */
- (void)scanJob:(BRScanJob *)job progress:(float)progress;
@end

#pragma mark -

// BRScanJob key for options
extern NSString * const BRScanJobOptionColorTypeKey;                /* NSNumber (see enum below) */
extern NSString * const BRScanJobOptionDocumentSizeKey;             /* NSNumber (see enum below) */
extern NSString * const BRScanJobOptionDuplexKey;                   /* NSNumber (see enum below) */
extern NSString * const BRScanJobOptionSkipBlankPageKey;            /* NSNumber (BOOL value) */
// BRScanJob key for options (virtual scan mode)
extern NSString * const BRScanJobOptionUseVirtualScanModeKey;       /* NSNumber (BOOL value) */
extern NSString * const BRScanJobOptionVirtualScanPageCountKey;     /* NSNumber (NSUInteger value) */
extern NSString * const BRScanJobOptionVirtualScanPageIntervalKey;  /* NSNumber (CGFloat value) */

/// スキャン時のカラータイプを指定するための列挙型です。
typedef NS_ENUM(NSUInteger, BRScanJobOptionColorType) {
    /// カラースキャン
    BRScanJobOptionColorTypeColor,
    
    /// 低解像度のカラースキャン
    BRScanJobOptionColorTypeColorHighSpeed,
    
    /// グレースキャン
    BRScanJobOptionColorTypeGrayscale,
};

/// スキャン時の原稿サイズを指定するための列挙型です。
typedef NS_ENUM(NSUInteger, BRScanJobOptionDocumentSize) {
    /// 自動
    BRScanJobOptionDocumentSizeAuto,
    
    /// A3
    BRScanJobOptionDocumentSizeA3,
    
    /// レジャー
    BRScanJobOptionDocumentSizeLedger,
    
    /// JIS B4
    BRScanJobOptionDocumentSizeJISB4,
    
    /// リーガル
    BRScanJobOptionDocumentSizeLegal,
    
    /// A4
    BRScanJobOptionDocumentSizeA4,
    
    /// レター
    BRScanJobOptionDocumentSizeLetter,
    
    /// JIS B5
    BRScanJobOptionDocumentSizeJISB5,
    
    /// 名刺
    BRScanJobOptionDocumentSizeBusinessCard,
    
    /// フォト
    BRScanJobOptionDocumentSizePhoto,          // 4 x 6 inch
    
    /// L版
    BRScanJobOptionDocumentSizePhotoL,         // 3.5 x 5 inch
};

/// 両面スキャンを指定するための列挙型です。
typedef NS_ENUM(NSUInteger, BRScanJobOptionDuplex) {
    /// 両面スキャンOFF
    BRScanJobOptionDuplexOff,
    
    /// 長辺とじ
    BRScanJobOptionDuplexLongEdge,
    
    /// 短辺とじ
    BRScanJobOptionDuplexShortEdge,
};

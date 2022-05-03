//
//  BRScanDevice.h
//  BRScanKit
//
//
//  Copyright (c) 2015 Brother Industries, Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 BRScanDeviceクラスはスキャナデバイスを表すクラスです。
 モデル名やIP Address、両面スキャンの使用可否など、スキャナデバイスの情報を取得できます。
 */
@interface BRScanDevice : NSObject

///デバイスのモデル名です。
@property (nonatomic, strong, readonly) NSString *      modelName;

///デバイスのURIです。
@property (nonatomic, strong, readonly) NSString *      deviceURI;  // Bonjour Device URI


///デバイスのIP Addressです。
@property (nonatomic, strong, readonly) NSString *      IPAddress;

/**
 デバイスのスペックが格納されたNSDictionaryです。(read-only)
 
 以下のkeyによって値を取得可能です。
 
- BRScanDeviceCapabilityIsScannerAvailableKey
  - NO  : スキャナは利用不可です。
  - YES : スキャナを利用可能です。
 
- BRScanDeviceCapabilityIsColorScannerAvailableKey
  - NO  : カラースキャンは利用不可です。
  - YES : カラースキャンを利用可能です。
 
- BRScanDeviceCapabilityIsFBScannerAvailableKey
  - NO  : フラッドベッドでスキャン不可です。
  - YES : フラッドベッドでスキャン可能です。
 
- BRScanDeviceCapabilityIsADFScannerAvailableKey
  - NO  : ADFでスキャン不可です。
  - YES : ADFでスキャン可能です。
 
- BRScanDeviceCapabilityIsDuplexScannerAvailableKey
  - NO  : 両面スキャンは利用不可です。
  - YES : 両面スキャンを利用可能です。
 
- BRScanDeviceCapabilityIsAutoDocumentSizeAvailableKey
  - NO  : 自動原稿サイズは利用不可です。
  - YES : 自動原稿サイズを利用可能です。
 
- BRScanDeviceCapabilityMaxScanDocumentKey
  - 片面スキャンにおけるスキャン可能な最大原稿サイズです。
  - [BRScanDeviceCapabilityMaxScanDocument](../Constants/BRScanDeviceCapabilityMaxScanDocument.html) 参照
 
- BRScanDeviceCapabilityMaxDuplexScanDocumentKey
  - 両面スキャンにおけるスキャン可能な最大原稿サイズです。
  - [BRScanDeviceCapabilityMaxScanDocument](../Constants/BRScanDeviceCapabilityMaxScanDocument.html) 参照
 
 */
@property (nonatomic, strong, readonly) NSDictionary *  capability;


/**
 BRScanDeviceクラスを作成します。
 ネットワークアクセスによって情報を取得するため、deviceWithModelName:modelName:deviceURI:IPAddress と比較して時間がかかります。
 
 @param IPAddress デバイスのIP Address
 @return BRScanDeviceクラスのインスタンス
 */
+ (BRScanDevice *)deviceWithIPAddress:(NSString *)IPAddress;

/**
 BRScanDeviceクラスを作成します。
 
 @param modelName モデル名
 @param deviceURI デバイスのURI
 @param IPAddress デバイスのIP Address
 @return BRScanDeviceクラスのインスタンス
 */
+ (BRScanDevice *)deviceWithModelName:(NSString *)modelName deviceURI:(NSString *)deviceURI IPAddress:(NSString *)IPAddress;

/**
 デバイスのURIからIP Addressを取得します。
 
 @param deviceURI デバイスのURI
 @return デバイスのIP Address
 */
+ (NSString *)resolveIPAddressFromURI:(NSString *)deviceURI;

@end

#pragma mark -

// BRScanDevice key for capability
extern NSString * const BRScanDeviceCapabilityIsScannerAvailableKey;
extern NSString * const BRScanDeviceCapabilityIsColorScannerAvailableKey;
extern NSString * const BRScanDeviceCapabilityIsFBScannerAvailableKey;
extern NSString * const BRScanDeviceCapabilityIsADFScannerAvailableKey;
extern NSString * const BRScanDeviceCapabilityIsDuplexScannerAvailableKey;
extern NSString * const BRScanDeviceCapabilityIsAutoDocumentSizeAvailableKey;
extern NSString * const BRScanDeviceCapabilityMaxScanDocumentKey;               /* NSNumber (see enum below) */
extern NSString * const BRScanDeviceCapabilityMaxDuplexScanDocumentKey;         /* NSNumber (see enum below) */

/**
 スキャン可能な最大原稿サイズを表す列挙型です。
 */
typedef NS_ENUM(NSUInteger, BRScanDeviceCapabilityMaxScanDocument) {
    /// 最大原稿サイズはA3です。
    BRScanDeviceCapabilityMaxScanDocumentA3,
    
    /// 最大原稿サイズはリーガルです。
    BRScanDeviceCapabilityMaxScanDocumentLegal,
    
    /// 最大原稿サイズはA4/レターです。
    BRScanDeviceCapabilityMaxScanDocumentA4,
};

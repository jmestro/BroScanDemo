//
//  BRScanDeviceBrowser.h
//  BRScanKit
//
//
//  Copyright (c) 2015 Brother Industries, Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BRScanDevice.h"

@protocol BRScanDeviceBrowserDelegate;

/**
 BRScanDeviceBrowserクラスは同一ネットワーク上に存在するスキャナデバイスの探索を行うためのクラスです。
 */
@interface BRScanDeviceBrowser : NSObject

/// delegateによる通知を行うための変数です。
@property (nonatomic, weak) id <BRScanDeviceBrowserDelegate> delegate;

/**
 開発のためのオプションです。
 仮想的なスキャナデバイスの設定を行います。
 
 以下のkeyでオプションを指定します。
 NSNumberクラスで数値をラップして指定してください。
 
 - BRScanDeviceBrowserOptionUseVirtualSearchModeKey
  - 仮想的なスキャナデバイスを用いて、スキャンデバイスの探索をエミュレートします。
  - NO  : 仮想的なスキャナデバイスを利用しません。
  - YES : 仮想的なスキャナデバイスを利用します。

 
 - BRScanDeviceBrowserOptionVirtualSearchDeviceCountKey
  - 仮想的なスキャナデバイスの数を指定します。
  - 探索を開始すると、この項目で指定した数だけ仮想的なスキャナデバイスが発見されます。
  - 0~999の範囲のNSUInteger型をNSNumberクラスでラップして指定してください。
 
 - BRScanDeviceBrowserOptionVirtualSearchDeviceIntervalKey
  - 探索を行った際に、仮想的なスキャナデバイスが発見される間隔を秒で指定します。
  - CGFloat型をNSNumberクラスでラップして指定してください。
 */
@property (nonatomic, strong) NSDictionary * options;


/// スキャナデバイスの探索を開始します。
- (void)search;

/// スキャナデバイスの探索を終了します。
- (void)stop;

@end

#pragma mark -

/**
 BRScanDeviceBrowserクラスからdelegateを用いた通知を受け取る際に利用するプロトコルです。
 */
@protocol BRScanDeviceBrowserDelegate <NSObject>
@required

/**
 スキャンデバイスが新たに発見された際に呼ばれるdelegateメソッドです。
 
 @param browser このメソッドを呼んだBRScanDeviceBrowserクラスの変数です。
 @param didFindDevice 新たに発見されたBRScanDeviceクラスの変数です。
 */
- (void)scanDeviceBrowser:(BRScanDeviceBrowser *)browser didFindDevice:(BRScanDevice *)device;

/**
 発見済みのスキャンデバイスがネットワーク上から消失した際に呼ばれるdelegateメソッドです。
 
 @param browser このメソッドを呼んだBRScanDeviceBrowserクラスの変数です。
 @param didRemoveDevice ネットワーク上から消失したBRScanDeviceクラスの変数です。
 */
- (void)scanDeviceBrowser:(BRScanDeviceBrowser *)browser didRemoveDevice:(BRScanDevice *)device;
@end

#pragma mark -

// BRScanDeviceBrowser key for options (virtual search mode)
extern NSString * const BRScanDeviceBrowserOptionUseVirtualSearchModeKey;           /* NSNumber (BOOL value) */
extern NSString * const BRScanDeviceBrowserOptionVirtualSearchDeviceCountKey;       /* NSNumber (NSUInteger value: 0 - 999) */
extern NSString * const BRScanDeviceBrowserOptionVirtualSearchDeviceIntervalKey;    /* NSNumber (CGFloat value) */

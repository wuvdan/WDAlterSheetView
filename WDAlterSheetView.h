//
//  WDAlterSheetView.h
//  Templates
//
//  Created by wudan on 2020/4/21.
//  Copyright © 2020 wudan. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface WDAlterSheetModel : NSObject
/// 仅显示主标题 黑色 ，16号字体
/// @param title 标题内容
+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title;

/// 主标题（黑色 ，16号字体）和副标题（灰色 ，10号字体）
/// @param title 主标题内容
/// @param subTitle 副标题内容
+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                             subTitle:(NSString *)subTitle;


/// 仅显示主标题 16号字体
/// @param title 标题内容
/// @param titleColor 颜色配置
+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                           titleColor:(UIColor *)titleColor;


/// 仅显示主标题
/// @param title 主标题内容
/// @param titleColor 颜色配置
/// @param titleFount 字体配置
+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                           titleColor:(UIColor *)titleColor
                            titleFont:(UIFont *)titleFount;


/// 主标题和副标题
/// @param title 主标题内容
/// @param titleColor 主标题颜色配置
/// @param titleFont 主标题字体配置
/// @param subTitle 副标题内容
/// @param subTitleColor 副标题字体配置
/// @param subTitleFont 副标题字体配置
+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                           titleColor:(UIColor *)titleColor
                            titleFont:(UIFont *)titleFont
                             subTitle:(NSString *)subTitle
                        subTitleColor:(UIColor *)subTitleColor
                         subTitleFont:(UIFont *)subTitleFont;

@end

// 点击回调（取消按钮除外）
typedef void (^DidSelectedBlock)(NSUInteger index);

@interface WDAlterSheetView : UIControl

/// 仅显示按钮 默认样式
/// @param items 按钮文字数组
+ (void)showAlterWithTitleItems:(NSArray<NSString *> *)items
                 didSelectBlock:(DidSelectedBlock)selectBlock;

/// 仅显示按钮 自定义样式按钮
/// @param items 按钮样式模型数组
+ (void)showAlterWithTitleAttItems:(NSArray<WDAlterSheetModel *> *)items
                    didSelectBlock:(DidSelectedBlock)selectBlock;


/// 显示按钮（默认样式） + 取消按钮
/// @param items 按钮文字数组
/// @param cancelText 取消按钮文字
/// @param cancelColor 取消按钮颜色
+ (void)showAlterWithTitleItems:(NSArray<NSString *> *)items
                     cancelText:(NSString *)cancelText
                    cancelColor:(UIColor * _Nullable)cancelColor // 默认颜色红色
                 didSelectBlock:(DidSelectedBlock)selectBlock;

/// 显示按钮（自定义样式） + 取消按钮
/// @param items 按钮样式模型数组
/// @param cancelText 取消按钮文字
/// @param cancelColor 取消按钮颜色
+ (void)showAlterWithTitleAttItems:(NSArray<WDAlterSheetModel *> *)items
                        cancelText:(NSString *)cancelText
                       cancelColor:(UIColor * _Nullable)cancelColor // 默认颜色红色
                    didSelectBlock:(DidSelectedBlock)selectBlock;
@end

NS_ASSUME_NONNULL_END

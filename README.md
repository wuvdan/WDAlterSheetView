![镇楼图](https://upload-images.jianshu.io/upload_images/3334769-b779b2b4e3c10261.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

模仿微信底部弹窗样式。

### 接口文件
```
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
```
### 实现文件
```
#import "WDAlterSheetView.h"
// 按钮高度
static CGFloat KButtonHeight = 55;
// 取消按钮与其他间距
static CGFloat KSpace = 8;
// 圆角
static CGFloat KCornersSpace = 10;

// 屏幕高度
static CGFloat kScreenHeight() {
    return [[UIScreen mainScreen] bounds].size.height;
}

// 屏幕宽度
static CGFloat kScreenWidth() {
    return [[UIScreen mainScreen] bounds].size.width;
}

// 是否是刘海屏
static BOOL kDevice_iPhoneX() {
    BOOL isPhoneX = NO;
    if (@available(iOS 11.0, *)) {
        isPhoneX = [[UIApplication sharedApplication] delegate].window.safeAreaInsets.bottom > 0.0;
    }
    return isPhoneX;
}

// 主标题颜色
static UIColor * kTitleColor() {
    return [UIColor colorWithRed:0.1 green:0.1 blue:0.1 alpha:1];
}

// 副标题颜色
static UIColor * kSubTitleColor() {
    return [UIColor colorWithRed:0.90 green:0.90 blue:0.90 alpha:1];
}

// 间隙颜色
static UIColor * kSpaceColor() {
    return [UIColor colorWithRed:0.95 green:0.95 blue:0.95 alpha:1];
}

// 分割线颜色
static UIColor * kSpaceLineColor() {
    return [UIColor colorWithRed:0.90 green:0.90 blue:0.90 alpha:1];
}

// 主标题字体
static UIFont * kTitleFont() {
    return [UIFont systemFontOfSize:16];
}

// 副标题字体
static UIFont * kSubTitleFont() {
    return [UIFont systemFontOfSize:12];
}

@interface WDAlterSheetModel ()
// 文字
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subTitle;
// 颜色
@property (nonatomic, strong) UIColor *titleColor;
@property (nonatomic, strong) UIColor *subTitleColor;
// 字体
@property (nonatomic, strong) UIFont *titleFont;
@property (nonatomic, strong) UIFont *subTitleFont;
@end

@implementation WDAlterSheetModel

+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title {
    return [self setupWithTitle:title titleColor:kTitleColor()];
}

+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                             subTitle:(NSString *)subTitle {
    
    return [self setupWithTitle:title
                    titleColor:kTitleColor()
                    titleFont:kTitleFont()
                       subTitle:subTitle
                  subTitleColor:kSubTitleColor()
                  subTitleFont:kSubTitleFont()];
}

+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                           titleColor:(UIColor *)titleColor {
    return [self setupWithTitle:title titleColor:titleColor titleFont:kTitleFont()];
}

+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                           titleColor:(UIColor *)titleColor
                            titleFont:(UIFont *)titleFont {
    
    return [self setupWithTitle:title
                     titleColor:titleColor
                      titleFont:titleFont
                       subTitle:@""
                  subTitleColor:kSubTitleColor()
                   subTitleFont:kSubTitleFont()];
}


+ (WDAlterSheetModel *)setupWithTitle:(NSString *)title
                           titleColor:(UIColor *)titleColor
                            titleFont:(UIFont *)titleFont
                             subTitle:(NSString *)subTitle
                        subTitleColor:(UIColor *)subTitleColor
                         subTitleFont:(UIFont *)subTitleFont {
    WDAlterSheetModel *model = [[WDAlterSheetModel alloc] init];
    model.title = title;
    model.titleColor = titleColor;
    model.titleFont = titleFont;
    model.subTitle = subTitle;
    model.subTitleColor = subTitleColor;
    model.subTitleFont = subTitleFont;
    return model;
}
@end

@interface WDAlterSheetControl : UIControl

@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *subTitleLabel;
@property (nonatomic, copy) NSArray<NSLayoutConstraint *> *totalLayoutConstraints;
@property (nonatomic, strong) UIView *bottomLineView;

@end

@implementation WDAlterSheetControl
- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor whiteColor];
        
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _titleLabel.textAlignment = NSTextAlignmentCenter;
        [self addSubview:_titleLabel];
        
        _subTitleLabel = [[UILabel alloc] init];
        _subTitleLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _subTitleLabel.textAlignment = NSTextAlignmentCenter;
        [self addSubview:_subTitleLabel];
        
        _bottomLineView = [[UIView alloc] init];
        _bottomLineView.backgroundColor = kSpaceLineColor();
        [self addSubview:_bottomLineView];
    
        self.totalLayoutConstraints = @[
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:-2],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:2],
        ];
        [self addConstraints:self.totalLayoutConstraints];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    _bottomLineView.frame = CGRectMake(0, CGRectGetHeight(self.frame) - 0.5, CGRectGetWidth(self.frame), 0.5);
    
    if (_subTitleLabel.text.length == 0) {
        [self removeConstraints:self.totalLayoutConstraints];
        [self addConstraints:@[
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:0],
        ]];
    }
}
@end

@interface WDAlterSheetLastControl : UIControl

@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) UILabel *subTitleLabel;
@property (nonatomic, copy) NSArray<NSLayoutConstraint *> *totalLayoutConstraints;
@property (nonatomic, strong) UIView *bottomView;

@end

@implementation WDAlterSheetLastControl

- (instancetype)init {
    self = [super init];
    if (self) {
        
        self.backgroundColor = [UIColor whiteColor];
        
        _titleLabel = [[UILabel alloc] init];
        _titleLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _titleLabel.textAlignment = NSTextAlignmentCenter;
        [self addSubview:_titleLabel];
        
        _subTitleLabel = [[UILabel alloc] init];
        _subTitleLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _subTitleLabel.textAlignment = NSTextAlignmentCenter;
        [self addSubview:_subTitleLabel];
        
        _bottomView = [[UIView alloc] init];
        _bottomView.translatesAutoresizingMaskIntoConstraints = NO;
        _bottomView.backgroundColor = [UIColor clearColor];
        [self addSubview:_bottomView];
        
        self.totalLayoutConstraints = @[
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:-2 - (kDevice_iPhoneX() ? 34 : 0)],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:2 - (kDevice_iPhoneX() ? 34 : 0)],
        ];
        
        NSMutableArray *array = [NSMutableArray array];
        [array addObjectsFromArray:@[
            [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeBottom multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeHeight multiplier:1 constant:kDevice_iPhoneX() ? 34 : 0],
            [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeLeading multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_bottomView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeTrailing multiplier:1 constant:0]
        ]];
        [array addObjectsFromArray:self.totalLayoutConstraints];
        [self addConstraints:array];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    if (_subTitleLabel.text.length == 0) {
        [self removeConstraints:self.totalLayoutConstraints];
        [self addConstraints:@[
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_titleLabel attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:- (kDevice_iPhoneX() ? 34 : 0) / 2],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterX multiplier:1 constant:0],
            [NSLayoutConstraint constraintWithItem:_subTitleLabel attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1 constant:- (kDevice_iPhoneX() ? 34 : 0) / 2],
        ]];
    }
}
@end


@interface WDAlterSheetView ()
@property (nonatomic, strong) UIView *backView;
@property (nonatomic, assign) CGFloat totalHeight;
@property (nonatomic, copy) DidSelectedBlock selectedBlock;

@end

@implementation WDAlterSheetView

+ (instancetype)shared {
    static dispatch_once_t onceToken;
    static WDAlterSheetView *view = nil;
    dispatch_once(&onceToken, ^{
        view = [[WDAlterSheetView alloc] init];
        view.frame = [[UIScreen mainScreen] bounds];
    });
    return view;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        [self addTarget:self action:@selector(hidenView) forControlEvents: UIControlEventTouchUpInside];
    }
    return self;
}

+ (void)showAlterWithTitleItems:(NSArray<NSString *> *)items
                 didSelectBlock:(DidSelectedBlock)selectBlock {
    [self showAlterWithTitleItems:items cancelText:@"" cancelColor:nil didSelectBlock:selectBlock];
}

+ (void)showAlterWithTitleItems:(NSArray<NSString *> *)items
                     cancelText:(NSString *)cancelText
                    cancelColor:(UIColor *)cancelColor
                 didSelectBlock:(DidSelectedBlock)selectBlock {
    
    NSMutableArray<WDAlterSheetModel *> *array = [NSMutableArray arrayWithCapacity:items.count];
    for (NSString *title in items) {
        WDAlterSheetModel *model = [WDAlterSheetModel setupWithTitle:title];
        [array addObject:model];
    }
    [self showAlterWithTitleAttItems:array cancelText:cancelText cancelColor:cancelColor didSelectBlock:selectBlock];
}

+ (void)showAlterWithTitleAttItems:(NSArray<WDAlterSheetModel *> *)items
                    didSelectBlock:(DidSelectedBlock)selectBlock {
    [self showAlterWithTitleAttItems:items cancelText:@"" cancelColor:nil didSelectBlock:selectBlock];
}

+ (void)showAlterWithTitleAttItems:(NSArray<WDAlterSheetModel *> *)items
                        cancelText:(NSString *)cancelText
                       cancelColor:(UIColor *)cancelColor
                    didSelectBlock:(DidSelectedBlock)selectBlock {

    NSAssert(items.count > 0, @"Thead Reason ===> [WDAlterSheetView · itmes`count not be null]");
       
    WDAlterSheetView *view = [WDAlterSheetView shared];
    view.selectedBlock = selectBlock;
    [view addSubViews];
    
    CGFloat cornersSpace = KCornersSpace;
    if (items.firstObject.subTitle.length == 0) {
        cornersSpace = 0;
    }
    
    NSMutableArray *array = [NSMutableArray arrayWithArray:items];
    if (cancelText.length != 0) {
        WDAlterSheetModel *cancelModel = [WDAlterSheetModel setupWithTitle:cancelText titleColor:cancelColor];
        if (cancelColor == nil) {
            cancelModel = [WDAlterSheetModel setupWithTitle:cancelText titleColor:[UIColor redColor]];
        }
        [array addObject:cancelModel];
    }
    
    [array enumerateObjectsUsingBlock:^(WDAlterSheetModel * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if (idx == array.count - 1) {
            WDAlterSheetLastControl *button = [view createLastButtonWithModel:obj tag:idx];
            if (cancelText.length == 0) {
                if (kDevice_iPhoneX()) {
                    button.frame = CGRectMake(0, KButtonHeight * (items.count - 1) + cornersSpace, kScreenWidth(), KButtonHeight + 34);
                } else {
                    button.frame = CGRectMake(0, KButtonHeight * (items.count - 1) + cornersSpace, kScreenWidth(), KButtonHeight);
                }
            } else {
                if (kDevice_iPhoneX()) {
                    button.frame = CGRectMake(0, KButtonHeight * items.count + KSpace + cornersSpace, kScreenWidth(), KButtonHeight + 34);
                } else {
                    button.frame = CGRectMake(0, KButtonHeight * items.count + KSpace + cornersSpace, kScreenWidth(), KButtonHeight);
                }
            }
            [view.backView addSubview:button];

        } else {
            WDAlterSheetControl *button = [view createButtonWithModel:obj tag:idx];
            if (idx == 0) {
                button.bottomLineView.hidden = idx == items.count - 1;
                button.frame = CGRectMake(0, 0, kScreenWidth(), KButtonHeight + cornersSpace);
            } else {
                button.bottomLineView.hidden = idx == items.count - 2;
                button.frame = CGRectMake(0, cornersSpace + KButtonHeight * idx, kScreenWidth(), KButtonHeight);
            }
            [view.backView addSubview:button];
        }
    }];

    
    [view showView];
    
    CGFloat totoalHeight = KButtonHeight * items.count;
    
    if (cancelText.length != 0) {
        totoalHeight += KSpace + KButtonHeight;
    }
    
    if (kDevice_iPhoneX()) {
        totoalHeight += 34;
    }
    
    view.backView.frame = CGRectMake(0, kScreenHeight(), kScreenWidth(), totoalHeight);

    [UIView animateWithDuration:0.35 animations:^{
        view.backgroundColor = [UIColor colorWithWhite:0 alpha:0.35];
        view.backView.frame = CGRectMake(0, kScreenHeight() - totoalHeight, kScreenWidth(), totoalHeight);
    }];
    [self setupRoundedCornersWithView:view.backView];

    view.totalHeight = totoalHeight;
}


#pragma mark - Private

#pragma mark Operation Methods
- (UIView *)kWindowView {
    if ([self viewController].view != nil) {
        return [self viewController].view;
    } else if ([UIApplication sharedApplication].delegate.window != nil) {
        return [UIApplication sharedApplication].delegate.window;
    } else {
        return [UIApplication sharedApplication].keyWindow;
    }
}

- (void)hidenView {
    [UIView animateWithDuration:0.35 animations:^{
        self.backView.frame = CGRectMake(0, kScreenHeight(), kScreenWidth(), self.totalHeight);
        self.backgroundColor = [UIColor colorWithWhite:0 alpha:0];
    } completion:^(BOOL finished) {
        [self removeSubViews];
        [self removeFromSuperview];
    }];
}

- (void)showView {
    self.backgroundColor = [UIColor colorWithWhite:0 alpha:0];
    [[self kWindowView] addSubview:self];
}

- (void)addSubViews {
    _backView = [[UIView alloc] init];
    _backView.backgroundColor = kSpaceColor();
    [self addSubview:_backView];
}

- (void)removeSubViews {
    [_backView removeFromSuperview];
}

#pragma mark Target Action Method
- (void)buttonDidClickTargetAction:(UIControl *)sender {
    sender.backgroundColor = [UIColor whiteColor];

    [self hidenView];
    if (sender.tag != 0) {
        if (self.selectedBlock) {
            self.selectedBlock(sender.tag - 1);
        }
    }
}

- (void)buttonTouchUpOutSideTargetAction:(UIControl *)sender {
    sender.backgroundColor = [UIColor colorWithRed:0.93 green:0.93 blue:0.93 alpha:1];
}

#pragma mark Common UI Create Methods
- (UIButton *)creatButton:(NSString *)title tag:(NSUInteger)tag {
    UIButton *button = [[UIButton alloc] init];
    button.tag = tag;
    [button setTitle:title forState:UIControlStateNormal];
    button.titleLabel.font = kTitleFont();
    button.backgroundColor = [UIColor whiteColor];
    [button addTarget:self action:@selector(buttonDidClickTargetAction:) forControlEvents:UIControlEventTouchUpInside];
    return button;
}

- (WDAlterSheetControl *)createButtonWithModel:(WDAlterSheetModel *)model tag:(NSUInteger)tag {
    WDAlterSheetControl *v = [[WDAlterSheetControl alloc] init];
    v.titleLabel.text = model.title;
    v.titleLabel.textColor = model.titleColor;
    v.titleLabel.font = model.titleFont;
    v.subTitleLabel.text = model.subTitle;
    v.subTitleLabel.textColor = model.subTitleColor;
    v.subTitleLabel.font = model.subTitleFont;
    v.tag = tag;
    [v addTarget:self action:@selector(buttonTouchUpOutSideTargetAction:) forControlEvents:UIControlEventTouchDown];
    [v addTarget:self action:@selector(buttonDidClickTargetAction:) forControlEvents:UIControlEventTouchUpInside];
    return v;
}

- (WDAlterSheetLastControl *)createLastButtonWithModel:(WDAlterSheetModel *)model tag:(NSUInteger)tag {
    WDAlterSheetLastControl *v = [[WDAlterSheetLastControl alloc] init];
    v.titleLabel.text = model.title;
    v.titleLabel.textColor = model.titleColor;
    v.titleLabel.font = model.titleFont;
    v.subTitleLabel.text = model.subTitle;
    v.subTitleLabel.textColor = model.subTitleColor;
    v.subTitleLabel.font = model.subTitleFont;
    v.tag = tag;
    [v addTarget:self action:@selector(buttonTouchUpOutSideTargetAction:) forControlEvents:UIControlEventTouchDown];
    [v addTarget:self action:@selector(buttonDidClickTargetAction:) forControlEvents:UIControlEventTouchUpInside];
    return v;
}

- (UIViewController *)viewController {
    UIResponder *next = [self nextResponder];
    do {
        if ([next isKindOfClass:[UIViewController class]]) {
            return (UIViewController *)next;
        }
        next = [next nextResponder];
    } while (next != nil);
    return nil;
}

#pragma mark - Tool Method
+ (void)setupRoundedCornersWithView:(UIView *)view {
    
    CAShapeLayer *mask = [CAShapeLayer layer];
    UIBezierPath * path = [UIBezierPath bezierPathWithRoundedRect:view.bounds
                                                byRoundingCorners:(UIRectCornerTopLeft | UIRectCornerTopRight)
                                                      cornerRadii:CGSizeMake(15, 15)];
    mask.path = path.CGPath;
    mask.frame = view.bounds;
    
    CAShapeLayer *borderLayer = [CAShapeLayer layer];
    borderLayer.path = path.CGPath;
    borderLayer.fillColor = [UIColor clearColor].CGColor;
    borderLayer.strokeColor = [UIColor clearColor].CGColor;
    borderLayer.lineWidth = 0;
    borderLayer.frame = view.bounds;
    view.layer.mask = mask;
    [view.layer addSublayer:borderLayer];
}
@end
```

### 使用实例
```
WDAlterSheetModel *m1 = [WDAlterSheetModel setupWithTitle:@"拍摄" titleColor:UIColor.blackColor titleFont:[UIFont systemFontOfSize:16] subTitle:@"照片或视频" subTitleColor:UIColor.lightGrayColor subTitleFont:[UIFont systemFontOfSize:11]];
WDAlterSheetModel *m2 = [WDAlterSheetModel setupWithTitle:@"从手机相册选择" titleColor:UIColor.blackColor];
[WDAlterSheetView showAlterWithTitleAttItems:@[m1, m2] cancelText:@"取消" cancelColor:[UIColor redColor] didSelectBlock:^(NSUInteger index) {
    NSLog(@"点击了：%lu", index);
}];
```

### 示例图
![4.7 inch](https://upload-images.jianshu.io/upload_images/3334769-afd04fff32d300b0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![刘海屏](https://upload-images.jianshu.io/upload_images/3334769-d6bab3410bbf2317.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![刘海屏](https://upload-images.jianshu.io/upload_images/3334769-dc10a58e38728cb5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

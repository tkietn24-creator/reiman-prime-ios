#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

// ============================================================================
// REIMAN PRIME iOS OVERLAY - CHUYỂN ĐỔI SANG UIVIEW PASSTHROUGH ĐỂ KHÔNG VĂNG APP
// Kế thừa UIView thay vì UIWindow để tương thích 100% với Unity Engine của Free Fire
// ============================================================================
@interface MenuMetalOverlay : UIView <MTKViewDelegate>

@property (nonatomic, strong) MTKView *metalView;
@property (nonatomic, strong) id<MTLDevice> device;
@property (nonatomic, strong) id<MTLCommandQueue> commandQueue;

+ (instancetype)sharedInstance;
+ (UIWindow *)findGameWindow;
- (void)setupOverlay;
- (void)toggleMenu;

@end

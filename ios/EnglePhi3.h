#ifdef __cplusplus
#include "engle_onnx.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNEngleLlmSpec.h"

@interface EnglePhi3 : NSObject <NativeEngleLlmSpec>
#else
#import <React/RCTBridgeModule.h>
@interface EnglePhi3 : NSObject <RCTBridgeModule>
#endif

@end




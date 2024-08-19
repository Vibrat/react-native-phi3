#import <Foundation/Foundation.h>
#import "EnglePhi3.h"

@implementation EnglePhi3
RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(
    init: (NSString *) NSPath
    resolve: (RCTPromiseResolveBlock) resolve
    reject: (RCTPromiseRejectBlock) reject 
) 
{
    NSLog(@"Loading model from path %@", NSPath);
    const char * modelPath = [NSPath UTF8String];
    
    bool success = EngleOnnx::init(modelPath);
    BOOL successNS = static_cast<BOOL>(success);
    
    NSLog(@"Finished created model");
    if (successNS) {
        resolve(@(successNS));
    } else {
        NSError * error = [NSError errorWithDomain:@"com.englellm.initalization"
            code:1002
            userInfo:@{NSLocalizedDescriptionKey: @"An error occurred"}
        ];
        reject(@"IncorrectModel", @"An exception was raised when loading model", error);
    }
}


RCT_EXPORT_METHOD(
    ask: (NSString *) userText 
    resolve:(RCTPromiseResolveBlock) resolve
    reject:(RCTPromiseRejectBlock) reject
)
{   
    // getting the session runner
    auto& session = EngleOnnx::getInstance();

    // inference step
    NSLog(@"Starting to tokenize text %@", userText);
    std::string userTextString = std::string([userText UTF8String]);
    const std::string response = session.infer(userTextString);

    NSLog(@"Starting to send results");
    NSString * decodedString = [NSString stringWithUTF8String:response.c_str()];
    if (decodedString != nullptr) {
        resolve(decodedString);
    } else {
        NSError * error = [NSError errorWithDomain:@"com.englellm.inference"
            code:1003
            userInfo:@{NSLocalizedDescriptionKey: @"An error occurred"}
        ];
        reject(@"inference_failure", @"Unable to infer information", error);
    }
}

@end

//
//  SpotzHttpSessionManager.h
//  LocalzSDK
//
//  Created by Melvin Artemas on 28/04/2014.
//  Copyright (c) 2014 Localz Pty Ltd. All rights reserved.
//

@import UIKit;
@import Foundation;

typedef enum {
    SpotzHttpSessionAuthNone = 1,
    SpotzHttpSessionAuthBasic,
    SpotzHttpSessionAuthOAuth2
} SpotzHttpSessionAuthType;

@protocol SpotzHttpSessionManagerDelegate<NSObject>
- (void) networkConnectionChanged:(BOOL) isConnected;
@optional
- (NSDictionary *) additionalHeader;
- (NSDictionary *) additionalSecureHeader;
@end

@interface SpotzHttpSessionManager : NSObject
@property (nonatomic,assign) id<SpotzHttpSessionManagerDelegate> delegate;
@property (nonatomic) BOOL isConnected;
@property (nonatomic) BOOL isBackground; // set all completion call to background mode

+ (SpotzHttpSessionManager *) instanceWithBaseURL:(NSURL *)baseURL projectId:(NSString *)projectId projectKey:(NSString *)projectKey;
- (SpotzHttpSessionManager *) initWithBaseURL:(NSURL *)url projectId:(NSString *)projectId projectKey:(NSString *)projectKey;

- (void) setTimeoutInterval:(NSTimeInterval) timeInterval;

- (NSURLSessionDataTask *)secureApiPOST:(NSString *)URLString deviceId:(NSString *)deviceId auth:(SpotzHttpSessionAuthType)authType parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)secureApiPOST:(NSString *)URLString deviceId:(NSString *)deviceId parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)apiPOST:(NSString *)URLString parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;

- (NSURLSessionDataTask *)secureApiPUT:(NSString *)URLString deviceId:(NSString *)deviceId auth:(SpotzHttpSessionAuthType)authType parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)secureApiPUT:(NSString *)URLString deviceId:(NSString *)deviceId parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)apiPUT:(NSString *)URLString parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;

- (NSURLSessionDataTask *)secureApiGET:(NSString *)URLString deviceId:(NSString *)deviceId auth:(SpotzHttpSessionAuthType)authType parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)secureApiGET:(NSString *)URLString deviceId:(NSString *)deviceId parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)apiGET:(NSString *)URLString parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;

- (NSURLSessionDataTask *)secureApiDELETE:(NSString *)URLString deviceId:(NSString *)deviceId auth:(SpotzHttpSessionAuthType)authType parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)secureApiDELETE:(NSString *)URLString deviceId:(NSString *)deviceId parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;
- (NSURLSessionDataTask *)apiDELETE:(NSString *)URLString parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *error))failure;

//- (NSURLSessionDataTask *)apiMultipartPOST:(NSString *)URLString fileName:(NSString *)filename fileData:(NSData *)fileData mime:(NSString *)mimeType parameters:(id)parameters success:(void (^)(NSURLSessionDataTask *task, id responseObject))success failure:(void (^)(NSURLSessionDataTask *task, NSError *))failure;

//- (void) downloadImageFromURL:(NSURL *)url completion:(void (^)(NSError *error, UIImage *image)) completion;

// varios ways to check for network availability. Pick one.
//- (BOOL) isNetworkAvailable;
//- (BOOL) isConnectionAvailable;
@end

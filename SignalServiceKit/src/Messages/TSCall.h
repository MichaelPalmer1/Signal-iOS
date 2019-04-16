//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "OWSReadTracking.h"
#import "TSInteraction.h"

NS_ASSUME_NONNULL_BEGIN

@class TSContactThread;

typedef NS_ENUM(NSUInteger, RPRecentCallType) {
    RPRecentCallTypeIncoming = 1,
    RPRecentCallTypeOutgoing,
    RPRecentCallTypeIncomingMissed,
    // These call types are used until the call connects.
    RPRecentCallTypeOutgoingIncomplete,
    RPRecentCallTypeIncomingIncomplete,
    RPRecentCallTypeIncomingMissedBecauseOfChangedIdentity,
    RPRecentCallTypeIncomingDeclined,
    RPRecentCallTypeOutgoingMissed,
};

NSString *NSStringFromCallType(RPRecentCallType callType);

@interface TSCall : TSInteraction <OWSReadTracking, OWSPreviewText>

@property (nonatomic, readonly) RPRecentCallType callType;

- (instancetype)initInteractionWithTimestamp:(uint64_t)timestamp inThread:(TSThread *)thread NS_UNAVAILABLE;

- (instancetype)initWithTimestamp:(uint64_t)timestamp
                   withCallNumber:(NSString *)contactNumber
                         callType:(RPRecentCallType)callType
                         inThread:(TSContactThread *)thread NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithUniqueId:(NSString *)uniqueId
             receivedAtTimestamp:(uint64_t)receivedAtTimestamp
                          sortId:(uint64_t)sortId
                       timestamp:(uint64_t)timestamp
                  uniqueThreadId:(NSString *)uniqueThreadId
               callSchemaVersion:(NSUInteger)callSchemaVersion
                        callType:(RPRecentCallType)callType
                            read:(BOOL)read NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (void)updateCallType:(RPRecentCallType)callType;
- (void)updateCallType:(RPRecentCallType)callType transaction:(YapDatabaseReadWriteTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END

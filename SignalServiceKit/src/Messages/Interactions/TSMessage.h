//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "TSInteraction.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Abstract message class.
 */

@class OWSContact;
@class OWSLinkPreview;
@class SDSAnyReadTransaction;
@class TSAttachment;
@class TSAttachmentStream;
@class TSQuotedMessage;
@class YapDatabaseReadWriteTransaction;

@interface TSMessage : TSInteraction <OWSPreviewText>

@property (nonatomic, readonly) NSMutableArray<NSString *> *attachmentIds;
@property (nonatomic, readonly, nullable) NSString *body;
@property (nonatomic, readonly) uint32_t expiresInSeconds;
@property (nonatomic, readonly) uint64_t expireStartedAt;
@property (nonatomic, readonly) uint64_t expiresAt;
@property (nonatomic, readonly) BOOL isExpiringMessage;
@property (nonatomic, readonly, nullable) TSQuotedMessage *quotedMessage;
@property (nonatomic, readonly, nullable) OWSContact *contactShare;
@property (nonatomic, readonly, nullable) OWSLinkPreview *linkPreview;

- (instancetype)initInteractionWithTimestamp:(uint64_t)timestamp inThread:(TSThread *)thread NS_UNAVAILABLE;

- (instancetype)initMessageWithTimestamp:(uint64_t)timestamp
                                inThread:(nullable TSThread *)thread
                             messageBody:(nullable NSString *)body
                           attachmentIds:(NSArray<NSString *> *)attachmentIds
                        expiresInSeconds:(uint32_t)expiresInSeconds
                         expireStartedAt:(uint64_t)expireStartedAt
                           quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                            contactShare:(nullable OWSContact *)contactShare
                             linkPreview:(nullable OWSLinkPreview *)linkPreview NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithUniqueId:(NSString *)uniqueId
             receivedAtTimestamp:(unsigned long long)receivedAtTimestamp
                          sortId:(unsigned long long)sortId
                       timestamp:(unsigned long long)timestamp
                  uniqueThreadId:(NSString *)uniqueThreadId
                   attachmentIds:(NSArray<NSString *> *)attachmentIds
                            body:(nullable NSString *)body
                    contactShare:(nullable OWSContact *)contactShare
                 expireStartedAt:(unsigned long long)expireStartedAt
                       expiresAt:(unsigned long long)expiresAt
                expiresInSeconds:(unsigned int)expiresInSeconds
                     linkPreview:(nullable OWSLinkPreview *)linkPreview
                   quotedMessage:(nullable TSQuotedMessage *)quotedMessage
                   schemaVersion:(unsigned long)schemaVersion
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(uniqueId:receivedAtTimestamp:sortId:timestamp:uniqueThreadId:attachmentIds:body:contactShare:expireStartedAt:expiresAt:expiresInSeconds:linkPreview:quotedMessage:schemaVersion:));

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (BOOL)hasAttachments;
- (NSArray<TSAttachment *> *)attachmentsWithTransaction:(YapDatabaseReadTransaction *)transaction;
- (NSArray<TSAttachment *> *)mediaAttachmentsWithTransaction:(YapDatabaseReadTransaction *)transaction;
- (nullable TSAttachment *)oversizeTextAttachmentWithTransaction:(YapDatabaseReadTransaction *)transaction;

- (void)removeAttachment:(TSAttachment *)attachment
             transaction:(YapDatabaseReadWriteTransaction *)transaction NS_SWIFT_NAME(removeAttachment(_:transaction:));

// Returns ids for all attachments, including message ("body") attachments,
// quoted reply thumbnails, contact share avatars, link preview images, etc.
- (NSArray<NSString *> *)allAttachmentIds;

- (void)setQuotedMessageThumbnailAttachmentStream:(TSAttachmentStream *)attachmentStream;

- (nullable NSString *)oversizeTextWithTransaction:(YapDatabaseReadTransaction *)transaction;
- (nullable NSString *)bodyTextWithTransaction:(SDSAnyReadTransaction *)transaction;

- (BOOL)shouldStartExpireTimerWithTransaction:(YapDatabaseReadTransaction *)transaction;

#pragma mark - Update With... Methods

- (void)updateWithExpireStartedAt:(uint64_t)expireStartedAt transaction:(YapDatabaseReadWriteTransaction *)transaction;

- (void)updateWithLinkPreview:(OWSLinkPreview *)linkPreview transaction:(YapDatabaseReadWriteTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END

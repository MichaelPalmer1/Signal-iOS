//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

import Foundation
import GRDBCipher
import SignalCoreKit

// NOTE: This file is generated by /Scripts/sds_codegen/sds_generate.py.
// Do not manually edit it, instead run `sds_codegen.sh`.

// MARK: - SDSSerializer

// The SDSSerializer protocol specifies how to insert and update the
// row that corresponds to this model.
class OWSContactOffersInteractionSerializer: SDSSerializer {

    private let model: OWSContactOffersInteraction
    public required init(model: OWSContactOffersInteraction) {
        self.model = model
    }

    public func serializableColumnTableMetadata() -> SDSTableMetadata {
        return TSInteractionSerializer.table
    }

    public func insertColumnNames() -> [String] {
        // When we insert a new row, we include the following columns:
        //
        // * "record type"
        // * "unique id"
        // * ...all columns that we set when updating.
        return [
            TSInteractionSerializer.recordTypeColumn.columnName,
            uniqueIdColumnName()
            ] + updateColumnNames()

    }

    public func insertColumnValues() -> [DatabaseValueConvertible] {
        let result: [DatabaseValueConvertible] = [
            SDSRecordType.contactOffersInteraction.rawValue
            ] + [uniqueIdColumnValue()] + updateColumnValues()
        if OWSIsDebugBuild() {
            if result.count != insertColumnNames().count {
                owsFailDebug("Update mismatch: \(result.count) != \(insertColumnNames().count)")
            }
        }
        return result
    }

    public func updateColumnNames() -> [String] {
        return [
            TSInteractionSerializer.receivedAtTimestampColumn,
            TSInteractionSerializer.sortIdColumn,
            TSInteractionSerializer.timestampColumn,
            TSInteractionSerializer.uniqueThreadIdColumn,
            TSInteractionSerializer.beforeInteractionIdColumn,
            TSInteractionSerializer.hasAddToContactsOfferColumn,
            TSInteractionSerializer.hasAddToProfileWhitelistOfferColumn,
            TSInteractionSerializer.hasBlockOfferColumn,
            TSInteractionSerializer.recipientIdColumn
            ].map { $0.columnName }
    }

    public func updateColumnValues() -> [DatabaseValueConvertible] {
        let result: [DatabaseValueConvertible] = [
            self.model.receivedAtTimestamp,
            self.model.sortId,
            self.model.timestamp,
            self.model.uniqueThreadId,
            self.model.beforeInteractionId,
            self.model.hasAddToContactsOffer,
            self.model.hasAddToProfileWhitelistOffer,
            self.model.hasBlockOffer,
            self.model.recipientId

        ]
        if OWSIsDebugBuild() {
            if result.count != updateColumnNames().count {
                owsFailDebug("Update mismatch: \(result.count) != \(updateColumnNames().count)")
            }
        }
        return result
    }

    public func uniqueIdColumnName() -> String {
        return TSInteractionSerializer.uniqueIdColumn.columnName
    }

    // TODO: uniqueId is currently an optional on our models.
    //       We should probably make the return type here String?
    public func uniqueIdColumnValue() -> DatabaseValueConvertible {
        // FIXME remove force unwrap
        return model.uniqueId!
    }
}

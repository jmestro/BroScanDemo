//
//  BRScanDevice+Helpers.swift
//  BroScanDemo
//
//  Created by Joe Mestrovich on 4/26/21.
//

import BRScanKit

// Key constants for the BRScanDevice.capability dictionary. Expect additions and changes
// with SDK updates.
struct CapabilityKey {
	static let scannerAvailable = "IsScannerAvailable"
	static let colorScannerAvailable = "IsColorScannerAvailable"
	static let flatbedScannerAvailable = "IsFBScannerAvailable"
	static let autoDocumentFeederScannerAvilable = "IsADFScannerAvailable"
	static let duplexScannerAvailbale = "IsDuplexScannerAvailable"
	static let autoDocumentSizeAvailable = "IsAutoDocumentSizeAvailable"
	static let maxScanDocumentSize = "MaxScanDocument"
	static let maxDuplexScanDocumentSize = "MaxDuplexScanDocument"
}

// Document sizes used by Brother scanners. Not all options are currently implemented.
// Note: This enum should have additional helpers that specify paper size and rawvalue
// order. If you build it before I do, please let me know so it can be included.
enum DocumentSize: String, CaseIterable {
	case unknown = "Unknown"
	case auto = "Auto"
	case a3 = "A3"
	case ledger = "Ledger"
	case jisB4 = "JIS B4"
	case legal = "Legal"
	case a4 = "A4"
	case letter = "Letter"
	case jisB5 = "JIS B5"
	case businessCard = "Business Card"
	case photo = "Photo"
	case photoL = "Photo L"
}

// This returns text that describes an optional boolean state
extension Optional where Wrapped == Bool {
	var availabilityStatement: String {
		guard let availability = self else { return "Unknown" }
		
		return availability ? "Yes" : "No"
	}
}

// Device capability helpers so that you can avoid dictionary lookups. If a SDK update
// changes a key string or is not available, nil is returned. Note that this extends the
// BRScanDevice class from the SDK.
extension BRScanDevice {
	var isScannerAvailable: Bool? {
		get {
			return self.capability[CapabilityKey.scannerAvailable] as? Bool
		}
	}
	
	var isColorScannerAvailable: Bool? {
		get {
			return self.capability[CapabilityKey.colorScannerAvailable] as? Bool
		}
	}
	
	var isFlatbedScannerAvailable: Bool? {
		get {
			return self.capability[CapabilityKey.flatbedScannerAvailable] as? Bool
		}
	}
	
	var isAutoDocumentFeederScannerAvailable: Bool? {
		get {
			return self.capability[CapabilityKey.autoDocumentFeederScannerAvilable] as? Bool
		}
	}
	
	var isDuplexScannerAvailable: Bool? {
		get {
			return self.capability[CapabilityKey.duplexScannerAvailbale] as? Bool
		}
	}
	
	var isAutoDocumentSizeAvailable: Bool? {
		get {
			return self.capability[CapabilityKey.autoDocumentSizeAvailable] as? Bool
		}
	}
	
	var maxScanDocument: DocumentSize {
		get {
			guard let maxScanDocument = self.capability[CapabilityKey.maxScanDocumentSize] as? Int else { return .unknown }

			switch maxScanDocument {
			case 0:
				return .a3
			case 1:
				return .legal
			case 2:
				return .a4
			default:
				return .unknown
			}
		}
	}
	
	var maxDuplexScanDocument: DocumentSize {
		get {
			guard let maxDuplexScanDocument = self.capability[CapabilityKey.maxDuplexScanDocumentSize] as? Int else { return .unknown }
			
			switch maxDuplexScanDocument {
			case 0:
				return .a3
			case 1:
				return .legal
			case 2:
				return .a4
			default:
				return .unknown
			}
		}
	}
	
}

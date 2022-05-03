//
//  SelectedScannerViewController.swift
//  BroScanDemo
//
//  Created by Joe Mestrovich on 4/26/21.
//

import UIKit
import BRScanKit

class SelectedScannerViewController: UIViewController {
	
	@IBOutlet var availableLabel: UILabel!
	@IBOutlet var colorCapabilityLabel: UILabel!
	@IBOutlet var flatbedCapabilityLabel: UILabel!
	@IBOutlet var documentFeederCapabilityLabel: UILabel!
	@IBOutlet var duplexCapabilityLabel: UILabel!
	@IBOutlet var documentSizingCapabilityLabel: UILabel!
	@IBOutlet var maxScanningSizeLabel: UILabel!
	@IBOutlet var maxDuplexSizeLabel: UILabel!

	@IBOutlet var colorOptionsControl: UISegmentedControl!
	@IBOutlet var documentSizePicker: UIPickerView!
	@IBOutlet var duplexOptionsControl: UISegmentedControl!
	@IBOutlet var skipBlanksSwitch: UISwitch!
	
	// Note: this array is populated in order of enum raw value. Be very careful
	// to maintain this order. A better solution is to use a Dictionary:
	// "Auto Size": 0, "Photo L": 1, ...
	let paperSizes = ["Auto Size", "Photo L", "Photo", "Business Card", "JIS B5",
					  "A4", "Letter", "Legal", "JIS B4", "Ledger", "A3"]
	
	var selectedDevice = BRScanDevice()
	
	override func viewDidLoad() {
		super.viewDidLoad()
		
		documentSizePicker.delegate = self

		availableLabel.text = selectedDevice.isScannerAvailable.availabilityStatement
		colorCapabilityLabel.text = selectedDevice.isColorScannerAvailable.availabilityStatement
		flatbedCapabilityLabel.text = selectedDevice.isFlatbedScannerAvailable.availabilityStatement
		documentFeederCapabilityLabel.text = selectedDevice.isAutoDocumentFeederScannerAvailable.availabilityStatement
		duplexCapabilityLabel.text = selectedDevice.isDuplexScannerAvailable.availabilityStatement
		documentSizingCapabilityLabel.text = selectedDevice.isAutoDocumentSizeAvailable.availabilityStatement
		maxScanningSizeLabel.text = selectedDevice.maxScanDocument.rawValue
		maxDuplexSizeLabel.text = selectedDevice.maxDuplexScanDocument .rawValue
	}
	
	// Helper methods are used to build the job options. 
	@IBAction func forwardScanningJob(_ sender: UIButton) {
		let scanJob = BRScanJob(ipAddress: selectedDevice.ipAddress)
		var jobOptions = [String: UInt]()
		jobOptions[BRScanJobOptionColorTypeKey] = colorOption()
		jobOptions[BRScanJobOptionDocumentSizeKey] = documentSizeOption()
		jobOptions[BRScanJobOptionDuplexKey] = duplexOption()
		jobOptions[BRScanJobOptionSkipBlankPageKey] = skipBlankPageOption()
		scanJob?.options = jobOptions
		
		let storyboard = UIStoryboard(name: "Main", bundle: nil)
		let scanViewController = storyboard.instantiateViewController(identifier: "ScanView") as! ScanViewController
		scanViewController.scanJob = scanJob!
		scanViewController.title = "Scanning Result"

		navigationItem.backBarButtonItem = UIBarButtonItem(title: "Configure", style: .plain, target: nil, action: nil)
		navigationController?.pushViewController(scanViewController, animated: true)
	}
	
	private func colorOption() -> UInt {
		switch colorOptionsControl.selectedSegmentIndex {
		case 0:
			return BRScanJobOptionColorType.color.rawValue
		case 1:
			return BRScanJobOptionColorType.colorHighSpeed.rawValue
		case 2:
			return BRScanJobOptionColorType.grayscale.rawValue
		default:
			return BRScanJobOptionColorType.color.rawValue
		}
	}
	
	private func documentSizeOption() -> UInt {
		return UInt(documentSizePicker.selectedRow(inComponent: 0))
	}
	
	private func duplexOption() -> UInt {
		switch duplexOptionsControl.selectedSegmentIndex {
		case 0:
			return BRScanJobOptionDuplex.off.rawValue
		case 1:
			return BRScanJobOptionDuplex.longEdge.rawValue
		case 2:
			return BRScanJobOptionDuplex.shortEdge.rawValue
		default:
			return BRScanJobOptionDuplex.off.rawValue
		}
	}
	
	private func skipBlankPageOption() -> UInt {
		return skipBlanksSwitch.isOn ? 1 : 0
	}
}

extension SelectedScannerViewController: UIPickerViewDelegate, UIPickerViewDataSource {
	func numberOfComponents(in pickerView: UIPickerView) -> Int {
		return 1
	}
	
	func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
		return paperSizes.count
	}
	
	func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
		return paperSizes[row]
	}
	
}

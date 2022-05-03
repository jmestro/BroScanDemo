//
//  ViewController.swift
//  BroScanDemo
//
//  Created by Joe Mestrovich on 4/25/21.
//

import UIKit
import BRScanKit

class ViewController: UITableViewController {
	
	// Make an instance of a Brother device browser
	private let brotherBrowser = BRScanDeviceBrowser()
	
	// All found devices will be in this array
	private var brotherDevices = [BRScanDevice]()
	
	private let tableCellID = "DeviceCell"

	override func viewDidLoad() {
		super.viewDidLoad()
		_ = ProcessInfo.processInfo.hostName
		tableView.delegate = self
		
		// Delegated methods for the device browser are found in the extension below
		brotherBrowser.delegate = self
	}
	
	override func viewWillAppear(_ animated: Bool) {
		// Start with an empty device array when searching. The device browser does not
		// remove or check for existing devices on the network.
		brotherDevices.removeAll()
		brotherBrowser.search()
	}
	
	// End device searching when the view is dismissed
	override func viewWillDisappear(_ animated: Bool) {
		brotherBrowser.stop()
	}
	
	// MARK: - Tableview support
	private func refreshTableView() {
		// Devices are added to the TableView in a background thread
		DispatchQueue.main.async { [weak self] in
			self?.tableView.reloadData()
		}
	}
	
	override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
		return brotherDevices.count
	}
	
	override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
		let cell = tableView.dequeueReusableCell(withIdentifier: tableCellID, for: indexPath)
		
		cell.textLabel?.text = brotherDevices[indexPath.row].modelName
		cell.detailTextLabel?.text = brotherDevices[indexPath.row].ipAddress
		
		if let scannerAvailable = brotherDevices[indexPath.row].isScannerAvailable {
			cell.textLabel?.textColor = scannerAvailable ? .black : .red
		} else {
			cell.textLabel?.textColor = .lightGray
		}
		
		return cell
	}
	
	override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
		let storyboard = UIStoryboard(name: "Main", bundle: nil)
		let selectedScannerViewController = storyboard.instantiateViewController(identifier: "SelectedScanner") as! SelectedScannerViewController
		selectedScannerViewController.title = brotherDevices[indexPath.row].modelName
		selectedScannerViewController.selectedDevice = brotherDevices[indexPath.row]

		navigationController?.pushViewController(selectedScannerViewController, animated: true)
	}
}

// MARK: - Browser delegates
// Methods delegated to finding and deleting Brother devices. The scanDeviceBrowser(_:didRemove)
// method does not seem to invoke. The code in that method may work once the method is active
// in a future SDK release.
extension ViewController: BRScanDeviceBrowserDelegate {
	func scanDeviceBrowser(_ browser: BRScanDeviceBrowser!, didFind device: BRScanDevice!) {
		brotherDevices.append(device)
		
		refreshTableView()
	}
	
	func scanDeviceBrowser(_ browser: BRScanDeviceBrowser!, didRemove device: BRScanDevice!) {
		guard let index = brotherDevices.firstIndex(of: device) else { return }
		
		brotherDevices.remove(at: index)
	}
}

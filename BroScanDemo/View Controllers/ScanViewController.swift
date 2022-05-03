//
//  ScanViewController.swift
//  BroScanDemo
//
//  Created by Joe Mestrovich on 4/26/21.
//

import UIKit
import BRScanKit

class ScanViewController: UIViewController {

	@IBOutlet var scannedImageView: UIImageView!
	@IBOutlet var imageIndexStepper: UIStepper!
	@IBOutlet var scanProgressView: UIProgressView!
	
	// This is the configuration for the scanning job
	var scanJob = BRScanJob()
	//
	private var scannedImages = [UIImage]()
	
    override func viewDidLoad() {
        super.viewDidLoad()
		
		imageIndexStepper.minimumValue = 0
		imageIndexStepper.maximumValue = 0

		scanJob.delegate = self
		scanJob.start()
    }
	
	// This is a hack for selecting which scanned image to view in a
	// multiple page scan job. You should never use this in production.
	@IBAction func stepThroughImages(_ sender: UIStepper) {
		if imageIndexStepper.value < 0 {
			imageIndexStepper.value = 0
		} else if Int(imageIndexStepper.value) > scannedImages.count - 1 {
			imageIndexStepper.value = Double(scannedImages.count - 1)
		}
		
		scannedImageView.image = scannedImages[Int(imageIndexStepper.value)]
	}
	
	@IBAction func forwardOCRJob(_ sender: UIButton) {
		let storyboard = UIStoryboard(name: "Main", bundle: nil)
		let ocrViewController = storyboard.instantiateViewController(identifier: "OCRView") as! OCRViewController
		ocrViewController.ocrTargetImage = scannedImages[Int(imageIndexStepper.value)]
		ocrViewController.title = "OCR Result"

		navigationItem.backBarButtonItem = UIBarButtonItem(title: "Configure", style: .plain, target: nil, action: nil)
		navigationItem.largeTitleDisplayMode = .never
		navigationController?.pushViewController(ocrViewController, animated: true)
	}
	
}

// MARK: - Scan Job Support
extension ScanViewController: BRScanJobDelegate {
	
	// Periodically update progress during the scanning process. For multipage scans the
	// progress indicator will step backwards and may even exceed 0.0 ... 1.0
	func scanJob(_ job: BRScanJob!, progress: Float) {
		DispatchQueue.main.async { [weak self] in
			guard progress <= 1 else { return }
			
			self?.scanProgressView.setProgress(progress, animated: true)
		}
	}
	
	// Process your scanned image with this method. For visual interest, this demo updates the
	// UIImageView with the last scanned image.
	func scanJob(_ job: BRScanJob!, didFinishPage path: String!) {
		DispatchQueue.main.async { [weak self] in
			if let scannedImage = UIImage(contentsOfFile: path) {
				self?.scannedImages.append(scannedImage)
				self?.imageIndexStepper.maximumValue = Double(self?.scannedImages.count ?? 0)
				self?.scannedImageView.image = scannedImage
			}
		}
	}
	
	// Report the result of the scanning job and handle end of job activities here.
	// Notice that this is non-throwing. Examine the BRScanJobResult enum for status and errors.
	func scanJobDidFinish(_ job: BRScanJob!, result: BRScanJobResult) {
		guard job.filePaths.count > 0 else { return }
		
		defer {
			DispatchQueue.main.async { [weak self] in
				self?.scanProgressView.isHidden = true
				self?.scannedImageView.image = self?.scannedImages[0]
				print("Job result code: \(result.rawValue)")
			}
		}
		
		// Do something interesting here
		print("Scanned pages: \(job.filePaths.count)")
	}
}

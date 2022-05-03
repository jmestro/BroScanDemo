//
//  OCRViewController.swift
//  BroScanDemo
//
//  Created by Joe Mestrovich on 4/26/21.
//

import UIKit
import Vision

class OCRViewController: UIViewController {

	@IBOutlet var ocrTextView: UITextView!
	@IBOutlet var confidenceScoreLabel: UILabel!
	@IBOutlet var busyIndicator: UIActivityIndicatorView!
	
	var ocrTargetImage: UIImage?
	
    override func viewDidLoad() {
        super.viewDidLoad()
    }
	
	override func viewWillAppear(_ animated: Bool) {
		guard let cgImage = ocrTargetImage?.cgImage else { return }

		busyIndicator.startAnimating()
		
		// OCR begins as soon as this view loads
		DispatchQueue.main.async { [weak self] in
			let request = VNRecognizeTextRequest(completionHandler: self?.handleDetectedText)
			// Slowest but most accurate OCR
			request.recognitionLevel = .accurate
			request.recognitionLanguages = ["en-US", "en-GB"]
			// The Vision framework will use grammar and spell-checking to improve accuracy
			request.usesLanguageCorrection = true
			
			let requests = [request]
			let imageRequestHandler = VNImageRequestHandler(cgImage: cgImage, orientation: .up, options: [:])
			
			do {
				try imageRequestHandler.perform(requests)
			} catch let error {
				print("Error \(error.localizedDescription)")
			}
		}
	}

	func handleDetectedText(request: VNRequest?, error: Error?) {
		if let error = error {
			print("ERROR: \(error)")
			return
		}
		guard let results = request?.results, results.count > 0 else {
			print("No text found")
			return
		}

		// Run this in a simulator and examine the console output to learn more
		var docText = ""
		var summedConfidence: Float = 0.0
		for result in results {
			if let observation = result as? VNRecognizedTextObservation {
				for text in observation.topCandidates(1) {
					print(text.string)
					print(text.confidence)
					print(observation.boundingBox)
					print("\n")
					
					docText += text.string + "\n"
					summedConfidence += text.confidence
				}
				
				confidenceScoreLabel.text = "Confidence Score: \(summedConfidence / Float(results.count))"
				ocrTextView.text = docText
				busyIndicator.stopAnimating()
			}
		}
	}
}

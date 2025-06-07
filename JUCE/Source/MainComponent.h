/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.10

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Projucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::ChangeListener,
                       public juce::Button::Listener,
                       public juce::ComboBox::Listener,
                       public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	enum TransportState
	{
		Stopped,
		Starting,
		Playing,
		Pausing,
		Paused,
		Stopping
	};

	enum RecordState
	{
		Recording,
		Off
	};

	enum TestMethod
	{
		STIPA,
		IR
	};

	// to complicated for no reason, no major improvements encountered with Hirata
	// plus, for practical reasons you would rather use a longer Schroeder than a short Hirata
	// and generally, you would prefer short signals anyway...
	//enum IrMethod
	//{
	//    Schroeder,
	//    Hirata
	//};

	enum IrTime
	{
		Short,
		Medium,
		Long
	};

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void transportStateChanged(TransportState newState);
	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
	void loadAudioFile(juce::String fileName);
	void chooseTestSignalSize();
	void selectIR();
	void changeButtonColor();

	void stiSTIPA();
	void processIR();
	void hOfilterMaker();
	void OfilterMaker();
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	//std::unique_ptr<juce::FileChooser> chooser;
	// app UI variables:
	juce::AudioFormatManager formatManager;
	juce::File file;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transport;
	juce::String testSignalName;
	TestMethod test;
	IrTime time;
	RecordState recording;
	bool validMeas;
	TransportState state;
	int testSignalSize;
	std::vector<double> readSignal;
	int fifoIndex;
	bool debugMode;

	double snr[7] = { 2, 4, 5, 8, 11, 13, 14 };

	// filter params:
	std::vector<std::vector<juce::SingleThreadedIIRFilter>> hOiirChain; // first variabele -> band nr [0:6], second variable, number in chain [0:9]
	std::vector<std::vector<juce::SingleThreadedIIRFilter>> OiirChain; // first variabele -> band nr [0:6], second variable, number in chain [0:9]

	int numberOfFilters; // shorten processing time;

	// variables for STI extraction from STIPA:
	double finalMTF[7][2];

	const double Tstart1[7] = { 1.25, 1, 1.5873015,	1, 0.8,	1.25, 1.2 };
	const double Tstart2[7] = { 1, 1, 0.9524, 1, 0.96, 1, 1.04 };
	const double Tstop1[7] = { 8.75, 9, 7.9365, 9, 8.8, 8.75, 8.8 };
	const double Tstop2[7] = { 9, 9, 8.8889, 9, 8.96, 9, 8.96 };

	const double inputMTF[7][2] = {
		0.0001, 0.27968,
		0.0104, 0.29562,
		0.22887, 0.37764,
		0.25889, 0.27709,
		0.25503, 0.28095,
		0.28787, 0.26398,
		0.27778, 0.26798
	};
	// half - octave filtering:
	//frequencies:
	const double fLeftHalfOctave[7] = { 105.112, 210.224, 420.448, 840.896, 1681.973, 3363.586, 6727.171 };
	const double fRightHalfOCtave[7] = { 148.651, 297.302, 594.604, 1189.207, 2378.414, 4756.828, 9523.657 };
	const double fm1STIPA[7] = { 1.6, 1, 0.63, 2, 1.25, 0.8, 2.5 };
	const double fm2STIPA[7] = { 8, 5, 3.15, 10, 6.25, 4, 12.5 };

	// filter coeficeints
	// format: b0 b1 b2 a0 a1 a2
	// 10 x 2nd order IIR filers for one bigger better faster stronger bp filer:
	const double filerCoefHalfOctave1[7][6] = {
		0.0029,         0, -0.0029, 1.0000, -1.9993,    0.9997,
		0.0058,         0, -0.0058, 1.0000, -1.9979,    0.9995,
		0.0116,         0, -0.0116, 1.0000, -1.9928,    0.9989,
		0.0232,         0, -0.0232, 1.0000, -1.9735,    0.9978,
		0.0464,         0, -0.0464, 1.0000, -1.8990,    0.9957,
		0.0926,         0, -0.0926, 1.0000, -1.6152,    0.9915,
		0.1842,         0, -0.1842, 1.0000, -0.6242,    0.9840,
	};
	const double filerCoefHalfOctave2[7][6] = {
		0.0029,         0, -0.0029, 1.0000, -1.9996,    0.9998,
		0.0058,         0, -0.0058, 1.0000, -1.9989,    0.9996,
		0.0116,         0, -0.0116, 1.0000, -1.9928,    0.9989,
		0.0232,         0, -0.0232, 1.0000, -1.9865,    0.9985,
		0.0464,         0, -0.0464, 1.0000, -1.9491,    0.9969,
		0.0926,         0, -0.0926, 1.0000, -1.8050,    0.9938,
		0.1842,         0, -0.1842, 1.0000, -1.2702,    0.9870,
	};
	const double filerCoefHalfOctave3[7][6] = {
		0.0026,         0, -0.0026, 1.0000, -1.9989,    0.9992,
		0.0053,         0, -0.0053, 1.0000, -1.9970,    0.9984,
		0.0106,         0, -0.0106, 1.0000, -1.9910,    0.9969,
		0.0211,         0, -0.0211, 1.0000, -1.9703,    0.9938,
		0.0420,         0, -0.0420, 1.0000, -1.8946,    0.9876,
		0.0836,         0, -0.0836, 1.0000, -1.6144,    0.9757,
		0.1657,         0, -0.1657, 1.0000, -0.6513,    0.9544,
	};
	const double filerCoefHalfOctave4[7][6] = {
		0.0026,         0, -0.0026, 1.0000, -1.9992,    0.9994,
		0.0053,         0, -0.0053, 1.0000, -1.9981,    0.9989,
		0.0106,         0, -0.0106, 1.0000, -1.9946,    0.9977,
		0.0211,         0, -0.0211, 1.0000, -1.9831,    0.9955,
		0.0420,         0, -0.0420, 1.0000, -1.9415,    0.9909,
		0.0836,         0, -0.0836, 1.0000, -1.7876,    0.9818,
		0.1657,         0, -0.1657, 1.0000, -1.2299,    0.9622,
	};
	const double filerCoefHalfOctave5[7][6] = {
		0.0021,         0, -0.0021, 1.0000, -1.9985,    0.9988,
		0.0043,         0, -0.0043, 1.0000, -1.9963,    0.9976,
		0.0086,         0, -0.0086, 1.0000, -1.9898,    0.9953,
		0.0171,         0, -0.0171, 1.0000, -1.9686,    0.9906,
		0.0340,         0, -0.0340, 1.0000, -1.8944,    0.9813,
		0.0675,         0, -0.0675, 1.0000, -1.6260,    0.9633,
		0.1336,         0, -0.1336, 1.0000, -0.7106,    0.9304,
	};
	const double filerCoefHalfOctave6[7][6] = {
		0.0021,         0, -0.0021, 1.0000, -1.9989,    0.9991,
		0.0043,         0, -0.0043, 1.0000, -1.9973,    0.9982,
		0.0086,         0, -0.0086, 1.0000, -1.9930,    0.9963,
		0.0171,         0, -0.0171, 1.0000, -1.9794,    0.9927,
		0.0340,         0, -0.0340, 1.0000, -1.9328,    0.9854,
		0.0675,         0, -0.0675, 1.0000, -1.7646,    0.9707,
		0.1336,         0, -0.1336, 1.0000, -1.1679,    0.9399,
	};
	const double filerCoefHalfOctave7[7][6] = {
		0.0015,         0, -0.0015, 1.0000, -1.9983,    0.9986,
		0.0030,         0, -0.0030, 1.0000, -1.9959,    0.9971,
		0.0059,         0, -0.0059, 1.0000, -1.9893,    0.9943,
		0.0119,         0, -0.0119, 1.0000, -1.9686,    0.9886,
		0.0236,         0, -0.0236, 1.0000, -1.8981,    0.9774,
		0.0468,         0, -0.0468, 1.0000, -1.6475,    0.9555,
		0.0925,         0, -0.0925, 1.0000, -0.7941,    0.9143,
	};
	const double filerCoefHalfOctave8[7][6] = {
		0.0015,         0, -0.0015, 1.0000, -1.9986,    0.9988,
		0.0030,         0, -0.0030, 1.0000, -1.9967,    0.9976,
		0.0059,         0, -0.0059, 1.0000, -1.9915,    0.9951,
		0.0119,         0, -0.0119, 1.0000, -1.9758,    0.9903,
		0.0236,         0, -0.0236, 1.0000, -1.9233,    0.9807,
		0.0468,         0, -0.0468, 1.0000, -1.7371,    0.9615,
		0.0925,         0, -0.0925, 1.0000, -1.0872,    0.9220,
	};
	const double filerCoefHalfOctave9[7][6] = {
		0.0009,         0, -0.0009, 1.0000, -1.9982,    0.9985,
		0.0017,         0, -0.0017, 1.0000, -1.9959,    0.9970,
		0.0035,         0, -0.0035, 1.0000, -1.9895,    0.9940,
		0.0069,         0, -0.0069, 1.0000, -1.9700,    0.9880,
		0.0137,         0, -0.0137, 1.0000, -1.9049,    0.9761,
		0.0271,         0, -0.0271, 1.0000, -1.6756,    0.9528,
		0.0536,         0, -0.0536, 1.0000, -0.8918,    0.9076,
	};
	const double filerCoefHalfOctave10[7][6] = {
		0.0009,         0, -0.0009, 1.0000, -1.9983,    0.9986,
		0.0017,         0, -0.0017, 1.0000, -1.9961,    0.9972,
		0.0035,         0, -0.0035, 1.0000, -1.9903,    0.9943,
		0.0069,         0, -0.0069, 1.0000, -1.9726,    0.9887,
		0.0137,         0, -0.0137, 1.0000, -1.9137,    0.9774,
		0.0271,         0, -0.0271, 1.0000, -1.7066,    0.9551,
		0.0536,         0, -0.0536, 1.0000, -0.9927,    0.9106,
	};

	// variables for STI extraction from IR:
	// octave filtering:
	//frequencies:
	const double fLeftOctave[7] = { 62.5, 125, 250, 500, 1000, 2000, 4000 };
	const double fRightOctave[7] = { 250, 500, 1000, 2000, 4000, 8000, 16000 };
	const double fmFullSti[14] = { 0.63, 0.8, 1, 1.25, 1.6, 2, 2.5, 3.15, 4, 5, 6.3, 8, 10, 12.5 };
	double finalFullStiMTF[7][14];

	// filter coeficeints //
	const double filerCoefOctave1[7][6] = {
	0.0125,         0, -0.0125, 1.0000, -1.9973,    0.9984,
	0.0250,         0, -0.0250, 1.0000, -1.9924,    0.9968,
	0.0500,         0, -0.0500, 1.0000, -1.9761,    0.9936,
	0.0996,         0, -0.0996, 1.0000, -1.9179,    0.9873,
	0.1974,         0, -0.1974, 1.0000, -1.7045,    0.9755,
	0.3838,         0, -0.3838, 1.0000, -0.9589,    0.9566,
	0.6999,         0, -0.6999, 1.0000,    0.9976,    0.9505,
	};
	const double filerCoefOctave2[7][6] = {
	0.0125,         0, -0.0125, 1.0000, -1.9995,    0.9996,
	0.0250,         0, -0.0250, 1.0000, -1.9990,    0.9992,
	0.0500,         0, -0.0500, 1.0000, -1.9974,    0.9984,
	0.0996,         0, -0.0996, 1.0000, -1.9927,    0.9969,
	0.1974,         0, -0.1974, 1.0000, -1.9771,    0.9937,
	0.3838,         0, -0.3838, 1.0000, -1.9211,    0.9871,
	0.6999,         0, -0.6999, 1.0000, -1.7147,    0.9713,
	};
	const double filerCoefOctave3[7][6] = {
	0.0114,         0, -0.0114, 1.0000, -1.9945,    0.9955,
	0.0227,         0, -0.0227, 1.0000, -1.9870,    0.9909,
	0.0452,         0, -0.0452, 1.0000, -1.9665,    0.9820,
	0.0899,         0, -0.0899, 1.0000, -1.9034,    0.9644,
	0.1774,         0, -0.1774, 1.0000, -1.6946,    0.9315,
	0.3441,         0, -0.3441, 1.0000, -1.0063,    0.8784,
	0.6401,         0, -0.6401, 1.0000,    0.8453,    0.8514,
	};
	const double filerCoefOctave4[7][6] = {
	0.0114,         0, -0.0114, 1.0000, -1.9987,    0.9987,
	0.0227,         0, -0.0227, 1.0000, -1.9972,    0.9975,
	0.0452,         0, -0.0452, 1.0000, -1.9938,    0.9950,
	0.0899,         0, -0.0899, 1.0000, -1.9853,    0.9900,
	0.1774,         0, -0.1774, 1.0000, -1.9614,    0.9800,
	0.3441,         0, -0.3441, 1.0000, -1.8858,    0.9592,
	0.6401,         0, -0.6401, 1.0000, -1.6255,    0.9096,
	};
	const double filerCoefOctave5[7][6] = {
	0.0092,         0, -0.0092, 1.0000, -1.9925,    0.9933,
	0.0184,         0, -0.0184, 1.0000, -1.9836,    0.9867,
	0.0366,         0, -0.0366, 1.0000, -1.9614,    0.9735,
	0.0726,         0, -0.0726, 1.0000, -1.9001,    0.9479,
	0.1430,         0, -0.1430, 1.0000, -1.7141,    0.8995,
	0.2789,         0, -0.2789, 1.0000, -1.1249,    0.8173,
	0.5409,         0, -0.5409, 1.0000, -1.4742,    0.8315,
	};
	const double filerCoefOctave6[7][6] = {
	0.0092,         0, -0.0092, 1.0000, -1.9976,    0.9977,
	0.0184,         0, -0.0184, 1.0000, -1.9950,    0.9953,
	0.0366,         0, -0.0366, 1.0000, -1.9892,    0.9907,
	0.0726,         0, -0.0726, 1.0000, -1.9755,    0.9814,
	0.1430,         0, -0.1430, 1.0000, -1.9394,    0.9629,
	0.2789,         0, -0.2789, 1.0000, -1.8324,    0.9246,
	0.5409,         0, -0.5409, 1.0000,    0.5789,    0.7447,
	};
	const double filerCoefOctave7[7][6] = {
	0.0064,         0, -0.0064, 1.0000, -1.9919,    0.9924,
	0.0128,         0, -0.0128, 1.0000, -1.9827,    0.9849,
	0.0254,         0, -0.0254, 1.0000, -1.9615,    0.9700,
	0.0503,         0, -0.0503, 1.0000, -1.9074,    0.9409,
	0.0990,         0, -0.0990, 1.0000, -1.7549,    0.8852,
	0.1946,         0, -0.1946, 1.0000, -1.2882,    0.7838,
	0.3966,         0, -0.3966, 1.0000, -1.2214,    0.7287,
	};
	const double filerCoefOctave8[7][6] = {
	0.0064,         0, -0.0064, 1.0000, -1.9961,    0.9962,
	0.0128,         0, -0.0128, 1.0000, -1.9919,    0.9925,
	0.0254,         0, -0.0254, 1.0000, -1.9828,    0.9850,
	0.0503,         0, -0.0503, 1.0000, -1.9617,    0.9701,
	0.0990,         0, -0.0990, 1.0000, -1.9073,    0.9404,
	0.1946,         0, -0.1946, 1.0000, -1.7497,    0.8796,
	0.3966,         0, -0.3966, 1.0000,    0.1837,    0.6389,
	};
	const double filerCoefOctave9[7][6] = {
	0.0037,         0, -0.0037, 1.0000, -1.9926,    0.9929,
	0.0074,         0, -0.0074, 1.0000, -1.9845,    0.9859,
	0.0147,         0, -0.0147, 1.0000, -1.9666,    0.9720,
	0.0292,         0, -0.0292, 1.0000, -1.9233,    0.9447,
	0.0574,         0, -0.0574, 1.0000, -1.8080,    0.8915,
	0.1135,         0, -0.1135, 1.0000, -1.4657,    0.7885,
	0.2395,         0, -0.2395, 1.0000, -0.8273,    0.6205,
	};
	const double filerCoefOctave10[7][6] = {
	0.0037,         0, -0.0037, 1.0000, -1.9943,    0.9945,
	0.0074,         0, -0.0074, 1.0000, -1.9881,    0.9890,
	0.0147,         0, -0.0147, 1.0000, -1.9747,    0.9780,
	0.0292,         0, -0.0292, 1.0000, -1.9433,    0.9564,
	0.0574,         0, -0.0574, 1.0000, -1.8623,    0.9139,
	0.1135,         0, -0.1135, 1.0000, -1.6268,    0.8280,
	0.2395,         0, -0.2395, 1.0000, -0.3181,    0.5788,
	};
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> groupComponent2;
    std::unique_ptr<juce::GroupComponent> groupComponent;
    std::unique_ptr<juce::TextButton> playButton;
    std::unique_ptr<juce::TextButton> stopButton;
    std::unique_ptr<juce::AudioDeviceSelectorComponent> audioDeviceComponent;
    std::unique_ptr<juce::ComboBox> comboBox;
    std::unique_ptr<juce::AudioVisualiserComponent> audioVisualiserComponent;
    std::unique_ptr<juce::TextButton> textButton;
    std::unique_ptr<juce::Slider> timeSlider;
    std::unique_ptr<juce::AudioVisualiserComponent> audioVisualiserRecord;
    std::unique_ptr<juce::TextButton> extractButton;
    std::unique_ptr<juce::TextButton> stipaButton;
    std::unique_ptr<juce::GroupComponent> groupComponent4;
    std::unique_ptr<juce::TextButton> t60Button1;
    std::unique_ptr<juce::TextButton> t60Button2;
    std::unique_ptr<juce::TextButton> t60Button3;
    std::unique_ptr<juce::TextButton> t60Button4;
    std::unique_ptr<juce::TextButton> t60Button5;
    std::unique_ptr<juce::TextButton> t60Button6;
    std::unique_ptr<juce::TextButton> stiIrButton;
    std::unique_ptr<juce::TextButton> c50Button1;
    std::unique_ptr<juce::TextButton> c50Button2;
    std::unique_ptr<juce::TextButton> c50Button3;
    std::unique_ptr<juce::TextButton> c50Button4;
    std::unique_ptr<juce::TextButton> c50Button5;
    std::unique_ptr<juce::TextButton> c50Button6;
    std::unique_ptr<juce::ToggleButton> debugToggle;
    std::unique_ptr<juce::TextButton> forceButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	state = Stopped;
	time = Short;
	testSignalName = "";
	testSignalSize = 48000; // to prevent exeption
	fifoIndex = 0;
	recording = Off;
	test = STIPA;
	validMeas = true;
	debugMode = false;
	numberOfFilters = 6; // maximum = 10
    //[/Constructor_pre]

    groupComponent2.reset (new juce::GroupComponent ("GroupComponent",
                                                     TRANS ("Measurement method")));
    addAndMakeVisible (groupComponent2.get());

    groupComponent2->setBounds (552, 8, 568, 262);

    groupComponent.reset (new juce::GroupComponent ("GroupComponent",
                                                    TRANS ("Audio I/O menu")));
    addAndMakeVisible (groupComponent.get());

    groupComponent->setBounds (16, 8, 512, 366);

    playButton.reset (new juce::TextButton ("PlayButton"));
    addAndMakeVisible (playButton.get());
    playButton->setButtonText (TRANS ("Play"));
    playButton->addListener (this);
    playButton->setColour (juce::TextButton::buttonColourId, juce::Colours::brown);
    playButton->setColour (juce::TextButton::textColourOffId, juce::Colour (0xfffff0f0));

    playButton->setBounds (584, 96, 94, 24);

    stopButton.reset (new juce::TextButton ("StopButton"));
    addAndMakeVisible (stopButton.get());
    stopButton->setButtonText (TRANS ("Stop"));
    stopButton->addListener (this);
    stopButton->setColour (juce::TextButton::buttonColourId, juce::Colours::brown);

    stopButton->setBounds (696, 96, 110, 24);

    audioDeviceComponent.reset (new juce::AudioDeviceSelectorComponent (deviceManager,0,256,0,256,false,false,false,false));
    addAndMakeVisible (audioDeviceComponent.get());
    audioDeviceComponent->setName ("AudioDeviceComponent");

    audioDeviceComponent->setBounds (40, 48, 462, 296);

    comboBox.reset (new juce::ComboBox ("ComboBox"));
    addAndMakeVisible (comboBox.get());
    comboBox->setEditableText (false);
    comboBox->setJustificationType (juce::Justification::centred);
    comboBox->setTextWhenNothingSelected (TRANS ("N/A"));
    comboBox->setTextWhenNoChoicesAvailable (TRANS ("(no choices)"));
    comboBox->addItem (TRANS ("STIPA"), 1);
    comboBox->addItem (TRANS ("IR_expSweep"), 2);
    comboBox->addListener (this);

    comboBox->setBounds (584, 56, 222, 32);

    audioVisualiserComponent.reset (new juce::AudioVisualiserComponent (1));
    addAndMakeVisible (audioVisualiserComponent.get());
    audioVisualiserComponent->setName ("AudioVisualiserComponent ");

    audioVisualiserComponent->setBounds (824, 56, 271, 56);

    textButton.reset (new juce::TextButton ("TextButton"));
    addAndMakeVisible (textButton.get());
    textButton->setButtonText (TRANS ("Waiting for next measurement"));
    textButton->addListener (this);
    textButton->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    textButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    textButton->setBounds (584, 128, 222, 48);

    timeSlider.reset (new juce::Slider ("TimeSlider"));
    addAndMakeVisible (timeSlider.get());
    timeSlider->setRange (2, 10, 4);
    timeSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    timeSlider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    timeSlider->addListener (this);

    timeSlider->setBounds (824, 224, 142, 24);

    audioVisualiserRecord.reset (new juce::AudioVisualiserComponent (1));
    addAndMakeVisible (audioVisualiserRecord.get());
    audioVisualiserRecord->setName ("AudioVisualiserRecord");

    audioVisualiserRecord->setBounds (824, 152, 271, 56);

    extractButton.reset (new juce::TextButton ("ExtractButton"));
    addAndMakeVisible (extractButton.get());
    extractButton->setButtonText (TRANS ("Extract parameters"));
    extractButton->addListener (this);
    extractButton->setColour (juce::TextButton::buttonColourId, juce::Colours::lime);
    extractButton->setColour (juce::TextButton::textColourOffId, juce::Colours::black);

    extractButton->setBounds (600, 184, 190, 24);

    stipaButton.reset (new juce::TextButton ("StipaButton"));
    addAndMakeVisible (stipaButton.get());
    stipaButton->setButtonText (TRANS ("..."));
    stipaButton->addListener (this);
    stipaButton->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    stipaButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    stipaButton->setBounds (568, 312, 222, 48);

    groupComponent4.reset (new juce::GroupComponent ("GroupComponent",
                                                     TRANS ("IR results")));
    addAndMakeVisible (groupComponent4.get());

    groupComponent4->setBounds (16, 384, 1104, 198);

    t60Button1.reset (new juce::TextButton ("T60Button1"));
    addAndMakeVisible (t60Button1.get());
    t60Button1->setButtonText (TRANS ("..."));
    t60Button1->addListener (this);
    t60Button1->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    t60Button1->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    t60Button1->setBounds (352, 448, 102, 48);

    t60Button2.reset (new juce::TextButton ("T60Button2"));
    addAndMakeVisible (t60Button2.get());
    t60Button2->setButtonText (TRANS ("..."));
    t60Button2->addListener (this);
    t60Button2->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    t60Button2->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    t60Button2->setBounds (464, 448, 102, 48);

    t60Button3.reset (new juce::TextButton ("T60Button3"));
    addAndMakeVisible (t60Button3.get());
    t60Button3->setButtonText (TRANS ("..."));
    t60Button3->addListener (this);
    t60Button3->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    t60Button3->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    t60Button3->setBounds (576, 448, 102, 48);

    t60Button4.reset (new juce::TextButton ("T60Button4"));
    addAndMakeVisible (t60Button4.get());
    t60Button4->setButtonText (TRANS ("..."));
    t60Button4->addListener (this);
    t60Button4->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    t60Button4->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    t60Button4->setBounds (688, 448, 102, 48);

    t60Button5.reset (new juce::TextButton ("T60Button5"));
    addAndMakeVisible (t60Button5.get());
    t60Button5->setButtonText (TRANS ("..."));
    t60Button5->addListener (this);
    t60Button5->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    t60Button5->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    t60Button5->setBounds (800, 448, 102, 48);

    t60Button6.reset (new juce::TextButton ("T60Button6"));
    addAndMakeVisible (t60Button6.get());
    t60Button6->setButtonText (TRANS ("..."));
    t60Button6->addListener (this);
    t60Button6->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    t60Button6->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    t60Button6->setBounds (912, 448, 102, 48);

    stiIrButton.reset (new juce::TextButton ("StiIrButton"));
    addAndMakeVisible (stiIrButton.get());
    stiIrButton->setButtonText (TRANS ("..."));
    stiIrButton->addListener (this);
    stiIrButton->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    stiIrButton->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    stiIrButton->setBounds (832, 312, 222, 48);

    c50Button1.reset (new juce::TextButton ("C50Button1"));
    addAndMakeVisible (c50Button1.get());
    c50Button1->setButtonText (TRANS ("..."));
    c50Button1->addListener (this);
    c50Button1->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    c50Button1->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    c50Button1->setBounds (350, 515, 102, 48);

    c50Button2.reset (new juce::TextButton ("C50Button2"));
    addAndMakeVisible (c50Button2.get());
    c50Button2->setButtonText (TRANS ("..."));
    c50Button2->addListener (this);
    c50Button2->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    c50Button2->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    c50Button2->setBounds (464, 512, 102, 48);

    c50Button3.reset (new juce::TextButton ("C50Button3"));
    addAndMakeVisible (c50Button3.get());
    c50Button3->setButtonText (TRANS ("..."));
    c50Button3->addListener (this);
    c50Button3->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    c50Button3->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    c50Button3->setBounds (576, 512, 102, 48);

    c50Button4.reset (new juce::TextButton ("C50Button4"));
    addAndMakeVisible (c50Button4.get());
    c50Button4->setButtonText (TRANS ("..."));
    c50Button4->addListener (this);
    c50Button4->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    c50Button4->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    c50Button4->setBounds (688, 512, 102, 48);

    c50Button5.reset (new juce::TextButton ("C50Button5"));
    addAndMakeVisible (c50Button5.get());
    c50Button5->setButtonText (TRANS ("..."));
    c50Button5->addListener (this);
    c50Button5->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    c50Button5->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    c50Button5->setBounds (800, 512, 102, 48);

    c50Button6.reset (new juce::TextButton ("C50Button6"));
    addAndMakeVisible (c50Button6.get());
    c50Button6->setButtonText (TRANS ("..."));
    c50Button6->addListener (this);
    c50Button6->setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    c50Button6->setColour (juce::TextButton::buttonOnColourId, juce::Colours::black);

    c50Button6->setBounds (912, 512, 102, 48);

    debugToggle.reset (new juce::ToggleButton ("DebugToggle"));
    addAndMakeVisible (debugToggle.get());
    debugToggle->setButtonText (TRANS ("Debug Mode (for development only)"));
    debugToggle->addListener (this);

    debugToggle->setBounds (24, 600, 286, 24);

    forceButton.reset (new juce::TextButton ("ForceButton"));
    addAndMakeVisible (forceButton.get());
    forceButton->setButtonText (TRANS ("Force harcoded extraction for debug"));
    forceButton->addListener (this);
    forceButton->setColour (juce::TextButton::buttonColourId, juce::Colours::grey);
    forceButton->setColour (juce::TextButton::textColourOffId, juce::Colours::black);

    forceButton->setBounds (24, 632, 286, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1150, 700);


    //[Constructor] You can add your own custom stuff here..
	setAudioChannels(2, 2);

	formatManager.registerBasicFormats();

	transport.addChangeListener(this);
	transport.setSource(nullptr, 0, nullptr, 0.0, 2);

	juce::Colour backgroundColour(256, 100, 100);
	audioVisualiserComponent->setColours(backgroundColour, backgroundColour.contrasting(1.0f));
	audioVisualiserRecord->setColours(backgroundColour, backgroundColour.contrasting(1.0f));

	readSignal.clear();

	//hOfilterMaker();

    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent2 = nullptr;
    groupComponent = nullptr;
    playButton = nullptr;
    stopButton = nullptr;
    audioDeviceComponent = nullptr;
    comboBox = nullptr;
    audioVisualiserComponent = nullptr;
    textButton = nullptr;
    timeSlider = nullptr;
    audioVisualiserRecord = nullptr;
    extractButton = nullptr;
    stipaButton = nullptr;
    groupComponent4 = nullptr;
    t60Button1 = nullptr;
    t60Button2 = nullptr;
    t60Button3 = nullptr;
    t60Button4 = nullptr;
    t60Button5 = nullptr;
    t60Button6 = nullptr;
    stiIrButton = nullptr;
    c50Button1 = nullptr;
    c50Button2 = nullptr;
    c50Button3 = nullptr;
    c50Button4 = nullptr;
    c50Button5 = nullptr;
    c50Button6 = nullptr;
    debugToggle = nullptr;
    forceButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	shutdownAudio();
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff2c2c2d));

    {
        int x = 582, y = 216, width = 222, height = 30;
        juce::String text (TRANS ("ExpSweep test signal time [s]:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 840, y = 24, width = 200, height = 30;
        juce::String text (TRANS ("Test Signal:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 584, y = 24, width = 200, height = 30;
        juce::String text (TRANS ("Select Test Method:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 840, y = 112, width = 200, height = 30;
        juce::String text (TRANS ("Recorded signal:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 567, y = 280, width = 200, height = 30;
        juce::String text (TRANS ("STIPA:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 40, y = 456, width = 278, height = 30;
        juce::String text (TRANS ("RT60 (measured with T30 method) [s] :"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 40, y = 416, width = 278, height = 30;
        juce::String text (TRANS ("Center frequency (results per octave) :"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 359, y = 416, width = 70, height = 30;
        juce::String text (TRANS ("250 Hz"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 471, y = 416, width = 70, height = 30;
        juce::String text (TRANS ("500 Hz"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 591, y = 416, width = 70, height = 30;
        juce::String text (TRANS ("1000 Hz"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 703, y = 416, width = 70, height = 30;
        juce::String text (TRANS ("2000 Hz"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 815, y = 416, width = 70, height = 30;
        juce::String text (TRANS ("4000 Hz"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 927, y = 416, width = 70, height = 30;
        juce::String text (TRANS ("8000 Hz"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 847, y = 280, width = 200, height = 30;
        juce::String text (TRANS ("STI(IR):"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 39, y = 520, width = 278, height = 30;
        juce::String text (TRANS ("C50 (Clarity) [s] :"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]

    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton.get())
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
		if ((state == Stopped) || (state == Paused))
		{
			transportStateChanged(Starting);
		}
		else if (state == Playing)
		{
			transportStateChanged(Pausing);
		}

        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton.get())
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
		if ((state == Paused))
		{
			transportStateChanged(Stopped);
		}
		else if (state == Playing)
		{
			transportStateChanged(Stopping);
		}

        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == textButton.get())
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == extractButton.get())
    {
        //[UserButtonCode_extractButton] -- add your button handler code here..

		////////////////////////////////////////////////////////////////////////////////////
		///////////////// EXTRACTION ALGORITHM /////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		if (validMeas == true) {
			if (test == STIPA) {
				stiSTIPA();
			}
			else {
				processIR();
			}
		}
        //[/UserButtonCode_extractButton]
    }
    else if (buttonThatWasClicked == stipaButton.get())
    {
        //[UserButtonCode_stipaButton] -- add your button handler code here..
        //[/UserButtonCode_stipaButton]
    }
    else if (buttonThatWasClicked == t60Button1.get())
    {
        //[UserButtonCode_t60Button1] -- add your button handler code here..
        //[/UserButtonCode_t60Button1]
    }
    else if (buttonThatWasClicked == t60Button2.get())
    {
        //[UserButtonCode_t60Button2] -- add your button handler code here..
        //[/UserButtonCode_t60Button2]
    }
    else if (buttonThatWasClicked == t60Button3.get())
    {
        //[UserButtonCode_t60Button3] -- add your button handler code here..
        //[/UserButtonCode_t60Button3]
    }
    else if (buttonThatWasClicked == t60Button4.get())
    {
        //[UserButtonCode_t60Button4] -- add your button handler code here..
        //[/UserButtonCode_t60Button4]
    }
    else if (buttonThatWasClicked == t60Button5.get())
    {
        //[UserButtonCode_t60Button5] -- add your button handler code here..
        //[/UserButtonCode_t60Button5]
    }
    else if (buttonThatWasClicked == t60Button6.get())
    {
        //[UserButtonCode_t60Button6] -- add your button handler code here..
        //[/UserButtonCode_t60Button6]
    }
    else if (buttonThatWasClicked == stiIrButton.get())
    {
        //[UserButtonCode_stiIrButton] -- add your button handler code here..
        //[/UserButtonCode_stiIrButton]
    }
    else if (buttonThatWasClicked == c50Button1.get())
    {
        //[UserButtonCode_c50Button1] -- add your button handler code here..
        //[/UserButtonCode_c50Button1]
    }
    else if (buttonThatWasClicked == c50Button2.get())
    {
        //[UserButtonCode_c50Button2] -- add your button handler code here..
        //[/UserButtonCode_c50Button2]
    }
    else if (buttonThatWasClicked == c50Button3.get())
    {
        //[UserButtonCode_c50Button3] -- add your button handler code here..
        //[/UserButtonCode_c50Button3]
    }
    else if (buttonThatWasClicked == c50Button4.get())
    {
        //[UserButtonCode_c50Button4] -- add your button handler code here..
        //[/UserButtonCode_c50Button4]
    }
    else if (buttonThatWasClicked == c50Button5.get())
    {
        //[UserButtonCode_c50Button5] -- add your button handler code here..
        //[/UserButtonCode_c50Button5]
    }
    else if (buttonThatWasClicked == c50Button6.get())
    {
        //[UserButtonCode_c50Button6] -- add your button handler code here..
        //[/UserButtonCode_c50Button6]
    }
    else if (buttonThatWasClicked == debugToggle.get())
    {
        //[UserButtonCode_debugToggle] -- add your button handler code here..
		debugMode = !debugMode;
        //[/UserButtonCode_debugToggle]
    }
    else if (buttonThatWasClicked == forceButton.get())
    {
        //[UserButtonCode_forceButton] -- add your button handler code here..
		debugMode = true;
		if (test == STIPA) {
			stiSTIPA();
		}
		else {
			processIR();
		}
        //[/UserButtonCode_forceButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainComponent::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]

    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
		transportStateChanged(Stopped);

		if (comboBox->getText() == "STIPA")
		{
			testSignalName = "STIPA_testSig_18s.wav";
			test = STIPA;
		}
		else if (comboBox->getText() == "IR_expSweep")
		{
			test = IR;
			selectIR();
		}
        //[/UserComboBoxCode_comboBox]
    }

    //[UsercomboBoxChanged_Post]
	if (testSignalName != "")
	{
		loadAudioFile(testSignalName);
	}

    //[/UsercomboBoxChanged_Post]
}

void MainComponent::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == timeSlider.get())
    {
        //[UserSliderCode_timeSlider] -- add your slider handling code here..
		if (timeSlider->getValue() == 2) {
			time = Short;
		}
		else if (timeSlider->getValue() == 6) {
			time = Medium;
		}
		else if (timeSlider->getValue() == 10) {
			time = Long;
		}

        //[/UserSliderCode_timeSlider]
    }

    //[UsersliderValueChanged_Post]
	selectIR();
	loadAudioFile(testSignalName);
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if (source == &transport)
	{
		if (transport.isPlaying())
		{
			transportStateChanged(Playing);
		}
		else if ((state == Stopping) || (state == Playing))
		{
			transportStateChanged(Stopped);
		}
		else if (Pausing == state)
		{
			transportStateChanged(Paused);
		}
	}
}

void MainComponent::selectIR()
{
	switch (time) {
	case Short:
		testSignalName = "sTest_2s_Schroeder.wav";
		break;

	case Medium:
		testSignalName = "sTest_6s_Schroeder.wav";
		break;

	case Long:
		testSignalName = "sTest_10s_Schroeder.wav";
		break;

	default:
		break;
	}
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// This function will be called when the audio device is started, or when
	// its settings (i.e. sample rate, block size, etc) are changed.

	// You can use this function to initialise any resources you might need,
	// but be careful - it will be called on the audio thread, not the GUI thread.

	// For more details, see the help for AudioProcessor::prepareToPlay()

	transport.prepareToPlay(samplesPerBlockExpected, sampleRate);

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	// Your audio-processing code goes here!
	fifoIndex = 0;
	// first retrieve data form audio input:
		if (recording == Recording) {

			if (bufferToFill.buffer->getNumChannels() > 0)
			{
				auto* channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);

				for (auto i = 0; i < bufferToFill.numSamples; ++i)
				{
					if ((channelData[i] > 0.99) || (fifoIndex > testSignalSize))
					{
						validMeas = false;
						break;
					}
					readSignal.push_back(channelData[i]);
					fifoIndex++;
				}
			}
			audioVisualiserRecord->pushBuffer(bufferToFill);
		}

	// ...than clear the buffer to send playback data to output:

	// Right now we are not producing any data, in which case we need to clear the buffer
	// (to prevent the output of random noise
	if (readerSource.get() == nullptr)
	{
		bufferToFill.clearActiveBufferRegion();
		return;
	}

	transport.getNextAudioBlock(bufferToFill);
	audioVisualiserComponent->pushBuffer(bufferToFill);

}

void MainComponent::releaseResources()
{
	// This will be called when the audio device stops, or when it is being
	// restarted due to a setting change.
	transport.releaseResources();
	// For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::transportStateChanged(TransportState newState)
{
	if (newState != state)
	{
		state = newState;

		switch (state) {
		case Stopped:

			recording = Off;
			fifoIndex = 0; // reset fifo index.
			transport.setPosition(0.0);
			playButton->setButtonText(TRANS("Play"));
			stopButton->setButtonText(TRANS("Stop"));
			stopButton->setEnabled(false);
			textButton->setButtonText(TRANS("Waiting for next measurement"));
			recording = Off;
			// test if record size is fine:
			if (readSignal.size() < testSignalSize * 0.99 || readSignal.size() > testSignalSize * 1.01)
				validMeas = false;
			changeButtonColor();
			break;

		case Starting:
			transport.start();
			chooseTestSignalSize();
			recording = Recording;
			validMeas = true;
			readSignal.clear();
			break;

		case Playing:
			playButton->setButtonText(TRANS("Pause"));
			stopButton->setButtonText(TRANS("Stop"));
			stopButton->setEnabled(true);
			textButton->setButtonText(TRANS("Playing..."));
			recording = Recording;
			break;

		case Pausing:
			transport.stop();
			recording = Off;
			break;

		case Paused:
			playButton->setButtonText(TRANS("Resume"));
			stopButton->setButtonText(TRANS("Return to 0"));
			textButton->setButtonText(TRANS("Paused"));
			recording = Off;
			validMeas = false;
			changeButtonColor();
			break;

		case Stopping:
			transport.stop();
			break;

		default:
			break;

		}
	}

}

void MainComponent::loadAudioFile(juce::String fileName)
{
	file = file.getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory);
	//file = file.getParentDirectory().getParentDirectory();
	file = file.getChildFile("Dizertatie")
		.getChildFile("STI JUCE")
		.getChildFile("ProjectFiles")
		.getChildFile("SpeechTransmissionIndex")
		.getChildFile("Audio");
	file = file.getChildFile(fileName);
	//file = juce::File("C:\Users\Paul\Desktop\Dizertatie\STI JUCE\ProjectFiles\SpeechTransmissionIndex\Audio");

	if (file != juce::File{})
	{
		auto* reader = formatManager.createReaderFor(file);
		if (reader != nullptr)
		{
			auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
			transport.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
			readerSource.reset(newSource.release());
		}
	}
	//DBG(transport.getLengthInSeconds());
	//int sampleSize = transport.getTotalLength();

}

void MainComponent::changeButtonColor()
{
	if (validMeas) {
		extractButton->setColour(juce::TextButton::buttonColourId, juce::Colour(0, 255, 0));
		extractButton->setEnabled(true);
	}
	else {
		extractButton->setColour(juce::TextButton::buttonColourId, juce::Colour(255, 0, 0));
		extractButton->setEnabled(false);
	}
}

void MainComponent::chooseTestSignalSize()
{

	int sampleRate = (deviceManager.getCurrentAudioDevice())->getCurrentSampleRate();

	if (test == STIPA)
		testSignalSize = 18 * sampleRate;
	else
	{
		int testSigTime = 0;
		switch (time) {
		case Short:
			testSigTime = 2;
			break;
		case Medium:
			testSigTime = 6;
			break;
		case Long:
			testSigTime = 10;
			break;
		default:
			break;
		}
		testSignalSize = testSigTime * sampleRate;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FILTER GENERATORS ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void MainComponent::hOfilterMaker() {

	juce::SingleThreadedIIRFilter iir;
	juce::IIRCoefficients coef;
	hOiirChain.clear();

	for (int k = 0; k < 7; k++)
	{
		// half octave filtering: create 10 filters with different coef and filter signal
		std::vector<juce::SingleThreadedIIRFilter> chain;

		// filter 1
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave1[k][0], filerCoefHalfOctave1[k][1], filerCoefHalfOctave1[k][2], // b0, b1, b2
			filerCoefHalfOctave1[k][3], filerCoefHalfOctave1[k][4], filerCoefHalfOctave1[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 2
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave2[k][0], filerCoefHalfOctave2[k][1], filerCoefHalfOctave2[k][2], // b0, b1, b2
			filerCoefHalfOctave2[k][3], filerCoefHalfOctave2[k][4], filerCoefHalfOctave2[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 3
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave3[k][0], filerCoefHalfOctave1[k][3], filerCoefHalfOctave3[k][2], // b0, b1, b2
			filerCoefHalfOctave3[k][3], filerCoefHalfOctave3[k][4], filerCoefHalfOctave3[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 4
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave4[k][0], filerCoefHalfOctave4[k][1], filerCoefHalfOctave4[k][2], // b0, b1, b2
			filerCoefHalfOctave4[k][3], filerCoefHalfOctave4[k][4], filerCoefHalfOctave4[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 5
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave5[k][0], filerCoefHalfOctave5[k][1], filerCoefHalfOctave5[k][2], // b0, b1, b2
			filerCoefHalfOctave5[k][3], filerCoefHalfOctave5[k][4], filerCoefHalfOctave5[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 6
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave6[k][0], filerCoefHalfOctave6[k][1], filerCoefHalfOctave6[k][2], // b0, b1, b2
			filerCoefHalfOctave6[k][3], filerCoefHalfOctave6[k][4], filerCoefHalfOctave6[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 7
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave7[k][0], filerCoefHalfOctave7[k][1], filerCoefHalfOctave7[k][2], // b0, b1, b2
			filerCoefHalfOctave7[k][3], filerCoefHalfOctave7[k][4], filerCoefHalfOctave7[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 8
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave8[k][0], filerCoefHalfOctave8[k][1], filerCoefHalfOctave8[k][2], // b0, b1, b2
			filerCoefHalfOctave8[k][3], filerCoefHalfOctave8[k][4], filerCoefHalfOctave8[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 9
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave9[k][0], filerCoefHalfOctave9[k][1], filerCoefHalfOctave9[k][2], // b0, b1, b2
			filerCoefHalfOctave9[k][3], filerCoefHalfOctave9[k][4], filerCoefHalfOctave9[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 10
		coef = juce::IIRCoefficients(
			filerCoefHalfOctave10[k][0], filerCoefHalfOctave10[k][1], filerCoefHalfOctave10[k][2], // b0, b1, b2
			filerCoefHalfOctave10[k][3], filerCoefHalfOctave10[k][4], filerCoefHalfOctave10[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		hOiirChain.push_back(chain);

	}

	// hOiirChain summary:
	// for each octave : 10 consecutive filters
}

void MainComponent::OfilterMaker() {

	juce::SingleThreadedIIRFilter iir;
	juce::IIRCoefficients coef;
	OiirChain.clear();

	for (int k = 0; k < 7; k++)
	{
		// half octave filtering: create 10 filters with different coef and filter signal
		std::vector<juce::SingleThreadedIIRFilter> chain;

		// filter 1
		coef = juce::IIRCoefficients(
			filerCoefOctave1[k][0], filerCoefOctave1[k][1], filerCoefOctave1[k][2], // b0, b1, b2
			filerCoefOctave1[k][3], filerCoefOctave1[k][4], filerCoefOctave1[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 2
		coef = juce::IIRCoefficients(
			filerCoefOctave2[k][0], filerCoefOctave2[k][1], filerCoefOctave2[k][2], // b0, b1, b2
			filerCoefOctave2[k][3], filerCoefOctave2[k][4], filerCoefOctave2[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 3
		coef = juce::IIRCoefficients(
			filerCoefOctave3[k][0], filerCoefOctave1[k][3], filerCoefOctave3[k][2], // b0, b1, b2
			filerCoefOctave3[k][3], filerCoefOctave3[k][4], filerCoefOctave3[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 4
		coef = juce::IIRCoefficients(
			filerCoefOctave4[k][0], filerCoefOctave4[k][1], filerCoefOctave4[k][2], // b0, b1, b2
			filerCoefOctave4[k][3], filerCoefOctave4[k][4], filerCoefOctave4[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 5
		coef = juce::IIRCoefficients(
			filerCoefOctave5[k][0], filerCoefOctave5[k][1], filerCoefOctave5[k][2], // b0, b1, b2
			filerCoefOctave5[k][3], filerCoefOctave5[k][4], filerCoefOctave5[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 6
		coef = juce::IIRCoefficients(
			filerCoefOctave6[k][0], filerCoefOctave6[k][1], filerCoefOctave6[k][2], // b0, b1, b2
			filerCoefOctave6[k][3], filerCoefOctave6[k][4], filerCoefOctave6[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 7
		coef = juce::IIRCoefficients(
			filerCoefOctave7[k][0], filerCoefOctave7[k][1], filerCoefOctave7[k][2], // b0, b1, b2
			filerCoefOctave7[k][3], filerCoefOctave7[k][4], filerCoefOctave7[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 8
		coef = juce::IIRCoefficients(
			filerCoefOctave8[k][0], filerCoefOctave8[k][1], filerCoefOctave8[k][2], // b0, b1, b2
			filerCoefOctave8[k][3], filerCoefOctave8[k][4], filerCoefOctave8[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 9
		coef = juce::IIRCoefficients(
			filerCoefOctave9[k][0], filerCoefOctave9[k][1], filerCoefOctave9[k][2], // b0, b1, b2
			filerCoefOctave9[k][3], filerCoefOctave9[k][4], filerCoefOctave9[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		// filter 10
		coef = juce::IIRCoefficients(
			filerCoefOctave10[k][0], filerCoefOctave10[k][1], filerCoefOctave10[k][2], // b0, b1, b2
			filerCoefOctave10[k][3], filerCoefOctave10[k][4], filerCoefOctave10[k][5]  // a0, a1, a2
		);
		iir.setCoefficients(coef);
		chain.push_back(iir);

		OiirChain.push_back(chain);
	}

	// OiirChain summary:
	// for each octave : 10 consecutive filters
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// PARAMETERS EXTRACTION STIPA ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void MainComponent::stiSTIPA() {

	// prepare signal : crop the 18 seconds needed
	double sampleRate = (deviceManager.getCurrentAudioDevice())->getCurrentSampleRate();
	testSignalSize = 18 * sampleRate; // set the size again, just to be shure...
	//chooseTestSignalSize();

	// hardcode meas for debug:

	if (debugMode) {
		file = file.getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory);
		//file = file.getParentDirectory().getParentDirectory();
		file = file.getChildFile("Dizertatie")
			.getChildFile("STI JUCE")
			.getChildFile("ProjectFiles")
			.getChildFile("SpeechTransmissionIndex")
			.getChildFile("Audio")
			.getChildFile("STIPA_exemple")
			.getChildFile("STIPA_A2_studio.wav");
		readSignal.clear();

		fifoIndex = 0;
		readSignal.clear();
		if (file != juce::File{})
		{
			auto* reader = formatManager.createReaderFor(file);
			if (reader != nullptr)
			{
				auto* reader = formatManager.createReaderFor(file);
				juce::AudioBuffer<float> audioBuffer;
				audioBuffer.setSize(reader->numChannels, reader->lengthInSamples);
				reader->read(&audioBuffer, 0, reader->lengthInSamples, 0, true, true);

				auto* channelData = audioBuffer.getReadPointer(0);


				for (auto i = 0; i < reader->lengthInSamples; ++i)
				{
					if (fifoIndex < testSignalSize)
					{
						readSignal.push_back(channelData[i]);
						fifoIndex++;

					}
					else
					{
						break;
					}
				}
			}
		}
	}

	double max = -10;
	for (int it = 0; it < testSignalSize; it++) {
		if (readSignal[it] > max)
			max = readSignal[it];
	}

	for (int it = 0; it < testSignalSize; it++) {
		readSignal[it] = readSignal[it] / max;
	}
	///////////////////////////////////////////////////////////////////////////

	// begin processing finally....

	// analysis per every half octave

	hOiirChain.clear();
	hOfilterMaker();
	double outputMTF[7][2];
	numberOfFilters = 9;

	for (int k = 0; k < 7; k++)
	{
		// create containers for filtered signal:
		// use 2 of them to prevent data handleing errors:
		std::vector<double> filteredSignal = readSignal;

		// get filtered signal: -> pass through the full 10 filter chain
		// update : full filtering takes too much time ( > 800 ms )
		// todo: use a variable for different filter order - to be set in GUI

		for (int j = 0; j <= numberOfFilters; j++)
		{
			// get the filter from the chain:
			auto iir = hOiirChain[k][j];

			/////////////////////////////////
			//juce::SingleThreadedIIRFilter iirL;
			//iirL.setCoefficients(juce::IIRCoefficients().makeLowPass(sampleRate, fLeftHalfOctave[k], 20));
			//juce::SingleThreadedIIRFilter iirR;
			//iirR.setCoefficients(juce::IIRCoefficients().makeHighPass(sampleRate, fRightHalfOCtave[k], 20));

			////////////////////////////////////////

			// rebuild the vector with the filtered samples:
			for (int it = 0; it < filteredSignal.size(); it++) {
				//filteredSignal[it] = iirL.processSingleSampleRaw(filteredSignal[it]);
				//filteredSignal[it] = iirR.processSingleSampleRaw(filteredSignal[it]);
				filteredSignal[it] = iir.processSingleSampleRaw(filteredSignal[it]);
			}

		}

		// fully filtered signal should now be saved in filteredSignal and ready for processing...

		// envelope extraction using a low pass filter next:
		for (int it = 0; it < filteredSignal.size(); it++) {
			filteredSignal[it] = filteredSignal[it] * filteredSignal[it];
		}

		std::vector<double> envelope;
		envelope.clear();

		juce::SingleThreadedIIRFilter iirLpf;
		iirLpf.setCoefficients(juce::IIRCoefficients().makeLowPass(sampleRate, 100, 1));

		for (int it = 0; it < filteredSignal.size(); it++) {
			envelope.push_back(iirLpf.processSingleSampleRaw(filteredSignal[it]));
		}


		double Time = 0;
		double const pi = 3.141592653589793238;
		double SumSinf1(0), SumSinf2(0), SumCosf1(0), SumCosf2(0), Sum1(0), Sum2(0);

		for (int it = 0; it < envelope.size(); it++) {
			Time = it / sampleRate;
			if (Time > Tstart1[k] && Time < Tstop1[k]) {
				SumSinf1 = SumSinf1 + sin(2 * Time * pi * fm1STIPA[k]) * envelope[it];
				SumCosf1 = SumCosf1 + cos(2 * Time * pi * fm1STIPA[k]) * envelope[it];
				Sum1 = Sum1 + envelope[it];
			}

			if (Time > Tstart2[k] && Time < Tstop2[k]) {
				SumSinf2 = SumSinf2 + sin(2 * Time * pi * fm2STIPA[k]) * envelope[it];
				SumCosf2 = SumCosf2 + cos(2 * Time * pi * fm2STIPA[k]) * envelope[it];
				Sum2 = Sum2 + envelope[it];
			}
		}

		envelope.clear();
		filteredSignal.clear();

		outputMTF[k][0] = sqrt(SumSinf1 * SumSinf1 + SumCosf1 * SumCosf1) / Sum1;
		if (outputMTF[k][0] < 0.0001)
			outputMTF[k][0] = 0.0001;
		outputMTF[k][1] = sqrt(SumSinf2 * SumSinf2 + SumCosf2 * SumCosf2) / Sum2;
		if (outputMTF[k][1] < 0.0001)
			outputMTF[k][1] = 0.0001;

		finalMTF[k][0] = outputMTF[k][0] / inputMTF[k][0];
		finalMTF[k][1] = outputMTF[k][1] / inputMTF[k][1];
	}

	// begin MTF processing:

	double Lvoce[7] = { -2.5, 0.5, 0, -6, -12, -18, -24 };
	double masking[7] = { 0.9781, 0.9996, 0.9986, 0.9959, 0.9989, 0.9993, 0.9985 };
	double qk[7];

	double snrEff[7][2], TI[7][2];
	double MTI[7];

	for (int k = 0; k < 7;k++) {

		qk[k] = Lvoce[k] + 65 - snr[k];

		// masking and SNR compensation
		finalMTF[k][0] = finalMTF[k][0] / (1 + pow(10, -qk[k])) * masking[k];
		finalMTF[k][1] = finalMTF[k][1] / (1 + pow(10, -qk[k])) * masking[k];

		if (finalMTF[k][0] >= 1) {
			finalMTF[k][0] = 0.97;
		}
		if (finalMTF[k][1] >= 1) {
			finalMTF[k][1] = 0.97;
		}

		snrEff[k][0] = 10 * log10(finalMTF[k][0] / (1 - finalMTF[k][0]));
		snrEff[k][1] = 10 * log10(finalMTF[k][1] / (1 - finalMTF[k][1]));

		TI[k][0] = (snrEff[k][0] + 15) / 30;
		TI[k][1] = (snrEff[k][1] + 15) / 30;

		MTI[k] = (TI[k][0] + TI[k][1]) / 2;
	}

	double alfa[7] = { 0.085, 0.127, 0.23, 0.233, 0.309, 0.224, 0.173 };
	double beta[7] = { 0.085, 0.078, 0.065, 0.011, 0.047, 0.095, 0 };

	double Salfa(0), Sbeta(0);

	for (int k = 0; k < 7;k++) {
		Salfa = Salfa + MTI[k] * alfa[k];
	}

	for (int k = 0; k < 6;k++) {
		Sbeta = Sbeta + sqrt(abs(MTI[k] * MTI[k + 1])) * beta[k];
	}

	double STI = Salfa - Sbeta;

	stipaButton->setButtonText(TRANS(juce::String(STI)));
	readSignal.clear();

}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// PARAMETERS EXTRACTION IR //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void MainComponent::processIR() {

	// prepare signal : crop the 18 seconds needed
	double sampleRate = (deviceManager.getCurrentAudioDevice())->getCurrentSampleRate();
	static constexpr auto fftOrder = 21;
	static constexpr auto fftSize = 1 << fftOrder;
	fifoIndex = 0;

	// hardcode meas for debug:
	juce::Array<float> readDataArray;

	if (debugMode) {
		testSignalSize = 10 * sampleRate;
		time = Long;
		fifoIndex = 0;
		file = file.getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory);
		//file = file.getParentDirectory().getParentDirectory();
		file = file.getChildFile("Dizertatie")
			.getChildFile("STI JUCE")
			.getChildFile("ProjectFiles")
			.getChildFile("SpeechTransmissionIndex")
			.getChildFile("Audio")
			.getChildFile("IR_exemple")
			.getChildFile("IR_A3_studio.wav");
		readSignal.clear();

		if (file != juce::File{})
		{
			auto* reader = formatManager.createReaderFor(file);
			if (reader != nullptr)
			{
				auto* reader = formatManager.createReaderFor(file);
				juce::AudioBuffer<float> audioBuffer;
				audioBuffer.setSize(reader->numChannels, reader->lengthInSamples);
				reader->read(&audioBuffer, 0, reader->lengthInSamples, 0, true, true);

				auto* channelData = audioBuffer.getReadPointer(0);

				for (auto i = 0; i < reader->lengthInSamples; ++i)
				{
					if (fifoIndex < testSignalSize)
					{
						readSignal.push_back(channelData[i]);
						fifoIndex++;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	chooseTestSignalSize();
	for (int it = 0; it < testSignalSize; it++) {
		readDataArray.set(it, readSignal[it]);
	}

	double max = -10;
	for (int it = 0; it < readDataArray.size(); it++) {
		if (readDataArray[it] > max)
			max = readDataArray[it];
	}

	for (int it = 0; it < readDataArray.size(); it++) {
		readDataArray.set(it, readDataArray[it] / max);
	}

	/////////////////////////////////////// IR extraction //////////////////////////////////////////
	// load inversion filter:
	file = file.getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory);

	switch (time){
	case Short:
		testSignalSize = 2 * sampleRate;
		file = file.getChildFile("Dizertatie")
			.getChildFile("STI JUCE")
			.getChildFile("ProjectFiles")
			.getChildFile("SpeechTransmissionIndex")
			.getChildFile("Audio")
			.getChildFile("IR_Filtre_inversare")
			.getChildFile("filtru_inv_2s.wav");
		break;
	case Medium:
		testSignalSize = 6 * sampleRate;
		file = file.getChildFile("Dizertatie")
			.getChildFile("STI JUCE")
			.getChildFile("ProjectFiles")
			.getChildFile("SpeechTransmissionIndex")
			.getChildFile("Audio")
			.getChildFile("IR_Filtre_inversare")
			.getChildFile("filtru_inv_6s.wav");
		break;
	case Long:
		testSignalSize = 10 * sampleRate;
		file = file.getChildFile("Dizertatie")
			.getChildFile("STI JUCE")
			.getChildFile("ProjectFiles")
			.getChildFile("SpeechTransmissionIndex")
			.getChildFile("Audio")
			.getChildFile("IR_Filtre_inversare")
			.getChildFile("filtru_inv_10s.wav");
		break;
	}
	int finvIndex = 0;
	juce::Array<float> fInv;

	if (file != juce::File{})
	{

		auto* reader = formatManager.createReaderFor(file);
		if (reader != nullptr)
		{
			auto* reader = formatManager.createReaderFor(file);
			juce::AudioBuffer<float> audioBuffer;
			audioBuffer.setSize(reader->numChannels, reader->lengthInSamples);
			reader->read(&audioBuffer, 0, reader->lengthInSamples, 0, true, true);

			auto* channelData = audioBuffer.getReadPointer(0);
			for (auto i = 0; i < reader->lengthInSamples; ++i)
			{
				if (finvIndex < testSignalSize) // same size as test signal so its fine
				{
					fInv.set(finvIndex, channelData[i]);
					finvIndex++;
				}
				else
				{
					break;
				}
			}

		}
	}

	for (int it = readDataArray.size(); it <= 2 * fftSize; it++) {
		readDataArray.set(it, 0);
		fInv.set(it, 0);
	}

	// obtain IR with convolution
	juce::Array<float> impulseResponse;

	juce::dsp::FFT FFT(fftOrder);
	FFT.performRealOnlyForwardTransform(readDataArray.getRawDataPointer(), true);
	FFT.performRealOnlyForwardTransform(fInv.getRawDataPointer(), true);

	for (int it = 0; it <= 2 * fftSize; it++) {
		impulseResponse.set(it, readDataArray[it] * fInv[it]);
	}
	FFT.performRealOnlyInverseTransform(impulseResponse.getRawDataPointer());

	// begin processing finally....
	std::vector<float> filteredSignal;

	int processSignalSize = testSignalSize / 4;
	OiirChain.clear();
	OfilterMaker();
	numberOfFilters = 9;
	std::vector<float> T30;
	std::vector<float> C50;

	for (int k = 0; k < 7; k++)
	{
		// analysis per every octave
		//
		// - > for T30, C50 - > need envelope
		// - > for STI -> get MTF
		// - > process MTF separatly at the end...

		filteredSignal.clear();

		// first isolate the right data (size a quarter of test signal size should be enough) seconds should be enough
		for (int it = testSignalSize; it < testSignalSize + processSignalSize; it++) {
			filteredSignal.push_back(impulseResponse[it]);
		}

		for (int j = 0; j <= numberOfFilters; j++)
		{
			// get the filter from the chain:
			auto iir = OiirChain[k][j];

			// rebuild the vector with the filtered samples:
			for (int it = 0; it < filteredSignal.size(); it++) {
				filteredSignal[it] = iir.processSingleSampleRaw(filteredSignal[it]);
			}
		}
		// normalize:
		float max = -10;
		for (int it = 0; it < processSignalSize; it++) {
			if (filteredSignal[it] > max)
				max = filteredSignal[it];
		}
		for (int it = 0; it < processSignalSize; it++) {
			filteredSignal[it] = filteredSignal[it] / max;
		}

		/////////////////////// Envelope Extraction for T30 ///////////////////////////////////

		// Schroeder method:
		std::vector<float> eSchr;

		for (int it = 0;it < processSignalSize;it++) {
			eSchr.push_back(0);
		}
		for (int it = processSignalSize - 2; it > 0; it--) {
			eSchr[it] = eSchr[it + 1] + filteredSignal[it] * filteredSignal[it];
		}
		max = -10;
		for (int it = 1; it < processSignalSize; it++) {
			if (eSchr[it] > max)
				max = eSchr[it];
		}

		for (int it = 1; it < eSchr.size(); it++) {
			eSchr[it] = 10 * log10(abs(eSchr[it]) / max);
		}

		int index5 = 1;
		while (eSchr[index5] > -5) {
			index5 = index5 + 1;
		}
		int index35 = 1;
		while (eSchr[index35] > -35) {
			index35 = index35 + 1;
		}

		T30.push_back(2 * (index35 - index5) / sampleRate);
		//float T30 = -60/a;

		/////////////////////// Envelope Extraction for C50 ///////////////////////////////////

		int index1 = 1;
		while (20 * log10(abs(filteredSignal[index1])) < -20) {
			index1++;
		}

		int interval = 1.6;
		if (time == Short)
		{
			interval = 0.8;
		}

		int indexEnd = index1 + interval * sampleRate;
		int index05 = 0.05 * sampleRate + index1;

		float i1 = 0;
		for (int it = index1; it < index05; it++) {
			i1 = i1 + filteredSignal[it] * filteredSignal[it];
		}

		float i2 = 0;
		for (int it = index05; it < indexEnd; it++) {
			i2 = i2 + filteredSignal[it] * filteredSignal[it];
		}

		if (i2 * i1 != 0) {
			C50.push_back(10 * log10(i1 / i2));
		}
		else {
			C50.push_back(0);
		}

		/////////////////////////////// MTF extraction /////////////////////////////////

		juce::Array<float> time;
		for (int it = 0; it < processSignalSize; it++) {
			time.set(it, it / sampleRate);
		}
		float Ek = 0;
		std::complex<double> Sk = 0;
		const std::complex<double> i(0.0, 1.0);
		double const pi = 3.141592653589793238;
		const float qk[7] = { 86.7, 75.8, 71.6, 65, 66, 67.6, 66.7}; // SNR


		for (int fm = 0; fm < 14; fm++) {

			for (int tau = processSignalSize - 1; tau > 0; tau --) {

				Ek = Ek + filteredSignal[tau] * filteredSignal[tau];

				std::complex<double> product(filteredSignal[tau] * filteredSignal[tau], 0);
				Sk = Sk + product * exp(-2 * pi * fmFullSti[fm] * time[tau] * i );
			}

			finalFullStiMTF[k][fm] = abs(Sk) / abs(Ek);

		}

	}

	/////////////////////////////////////// STI from MTF //////////////////////////////////////////

	double Lvoce[7] = { -2.5, 0.5, 0, -6, -12, -18, -24 };
	double masking[7] = { 0.9781, 0.9996, 0.9986, 0.9959, 0.9989, 0.9993, 0.9985 };

	double snrEff[7][14], TI[7][14];
	double MTI[7];

	for (int k = 0; k < 7;k++) {

		double sum = 0;
		for (int fm = 0; fm < 14; fm++) {

			snrEff[k][fm] = 10 * log10(finalFullStiMTF[k][fm] / (1 - finalFullStiMTF[k][fm]));

			TI[k][fm] = (snrEff[k][fm] + 15) / 30;

			sum = sum + TI[k][fm];
		}

		MTI[k] = sum / 14;
	}

	double alfa[7] = { 0.085, 0.127, 0.23, 0.233, 0.309, 0.224, 0.173 };
	double beta[7] = { 0.085, 0.078, 0.065, 0.011, 0.047, 0.095, 0 };

	double Salfa(0), Sbeta(0);

	for (int k = 0; k < 7;k++) {
		Salfa = Salfa + MTI[k] * alfa[k];
	}

	for (int k = 0; k < 6;k++) {
		Sbeta = Sbeta + sqrt(abs(MTI[k] * MTI[k + 1])) * beta[k];
	}

	double STI = Salfa - Sbeta;
	stiIrButton->setButtonText(TRANS(juce::String(STI)));

	/////////////////////////////////////// Show results: //////////////////////////////////////////

	t60Button1->setButtonText(TRANS(juce::String(T30[1])));
	t60Button2->setButtonText(TRANS(juce::String(T30[2])));
	t60Button3->setButtonText(TRANS(juce::String(T30[3])));
	t60Button4->setButtonText(TRANS(juce::String(T30[4])));
	t60Button5->setButtonText(TRANS(juce::String(T30[5])));
	t60Button6->setButtonText(TRANS(juce::String(T30[6])));

	c50Button1->setButtonText(TRANS(juce::String(C50[1])));
	c50Button2->setButtonText(TRANS(juce::String(C50[2])));
	c50Button3->setButtonText(TRANS(juce::String(C50[3])));
	c50Button4->setButtonText(TRANS(juce::String(C50[4])));
	c50Button5->setButtonText(TRANS(juce::String(C50[5])));
	c50Button6->setButtonText(TRANS(juce::String(C50[6])));
	readSignal.clear();

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public juce::AudioAppComponent, public juce::ChangeListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="1150"
                 initialHeight="700">
  <BACKGROUND backgroundColour="ff2c2c2d">
    <TEXT pos="582 216 222 30" fill="solid: ffffffff" hasStroke="0" text="ExpSweep test signal time [s]:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="840 24 200 30" fill="solid: ffffffff" hasStroke="0" text="Test Signal:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="584 24 200 30" fill="solid: ffffffff" hasStroke="0" text="Select Test Method:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="840 112 200 30" fill="solid: ffffffff" hasStroke="0" text="Recorded signal:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="33" typefaceStyle="Bold"/>
    <TEXT pos="567 280 200 30" fill="solid: ffffffff" hasStroke="0" text="STIPA:"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="40 456 278 30" fill="solid: ffffffff" hasStroke="0" text="RT60 (measured with T30 method) [s] :"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="40 416 278 30" fill="solid: ffffffff" hasStroke="0" text="Center frequency (results per octave) :"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="359 416 70 30" fill="solid: ffffffff" hasStroke="0" text="250 Hz"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="471 416 70 30" fill="solid: ffffffff" hasStroke="0" text="500 Hz"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="591 416 70 30" fill="solid: ffffffff" hasStroke="0" text="1000 Hz"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="703 416 70 30" fill="solid: ffffffff" hasStroke="0" text="2000 Hz"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="815 416 70 30" fill="solid: ffffffff" hasStroke="0" text="4000 Hz"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="927 416 70 30" fill="solid: ffffffff" hasStroke="0" text="8000 Hz"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
    <TEXT pos="847 280 200 30" fill="solid: ffffffff" hasStroke="0" text="STI(IR):"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="36" typefaceStyle="Bold"/>
    <TEXT pos="39 520 278 30" fill="solid: ffffffff" hasStroke="0" text="C50 (Clarity) [s] :"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="1"
          italic="0" justification="34" typefaceStyle="Bold"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="GroupComponent" id="ee3884d1a6a614ee" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="552 8 568 262" title="Measurement method"/>
  <GROUPCOMPONENT name="GroupComponent" id="de893fd7b7213677" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="16 8 512 366" title="Audio I/O menu"/>
  <TEXTBUTTON name="PlayButton" id="abdd13a59536b731" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="584 96 94 24" bgColOff="ffa52a2a"
              textCol="fffff0f0" buttonText="Play" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="StopButton" id="87c179e05a8a8ffb" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="696 96 110 24" bgColOff="ffa52a2a"
              buttonText="Stop" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="AudioDeviceComponent" id="604814e8a7a66c8f" memberName="audioDeviceComponent"
                    virtualName="" explicitFocusOrder="0" pos="40 48 462 296" class="juce::AudioDeviceSelectorComponent"
                    params="deviceManager,0,256,0,256,false,false,false,false"/>
  <COMBOBOX name="ComboBox" id="caaf166fe2e29eda" memberName="comboBox" virtualName=""
            explicitFocusOrder="0" pos="584 56 222 32" editable="0" layout="36"
            items="STIPA&#10;IR_expSweep" textWhenNonSelected="N/A" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="AudioVisualiserComponent " id="90b91f704fab52b3" memberName="audioVisualiserComponent"
                    virtualName="" explicitFocusOrder="0" pos="824 56 271 56" class="juce::AudioVisualiserComponent"
                    params="1"/>
  <TEXTBUTTON name="TextButton" id="58b2c5afafde68a3" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="584 128 222 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="Waiting for next measurement"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="TimeSlider" id="f61638f0a3ebb1e7" memberName="timeSlider"
          virtualName="" explicitFocusOrder="0" pos="824 224 142 24" min="2.0"
          max="10.0" int="4.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <GENERICCOMPONENT name="AudioVisualiserRecord" id="de0100cb57a28e50" memberName="audioVisualiserRecord"
                    virtualName="" explicitFocusOrder="0" pos="824 152 271 56" class="juce::AudioVisualiserComponent"
                    params="1"/>
  <TEXTBUTTON name="ExtractButton" id="f1be8e1bda8d33c2" memberName="extractButton"
              virtualName="" explicitFocusOrder="0" pos="600 184 190 24" bgColOff="ff00ff00"
              textCol="ff000000" buttonText="Extract parameters" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="StipaButton" id="fc1a9d7df97c94a6" memberName="stipaButton"
              virtualName="" explicitFocusOrder="0" pos="568 312 222 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <GROUPCOMPONENT name="GroupComponent" id="46467fc268bb0573" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="16 384 1104 198" title="IR results"/>
  <TEXTBUTTON name="T60Button1" id="bdf2826f3c037520" memberName="t60Button1"
              virtualName="" explicitFocusOrder="0" pos="352 448 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="T60Button2" id="b976efcdab439067" memberName="t60Button2"
              virtualName="" explicitFocusOrder="0" pos="464 448 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="T60Button3" id="7b2ba865251fd940" memberName="t60Button3"
              virtualName="" explicitFocusOrder="0" pos="576 448 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="T60Button4" id="1260d4ac576858d6" memberName="t60Button4"
              virtualName="" explicitFocusOrder="0" pos="688 448 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="T60Button5" id="77fd6baa0985e78f" memberName="t60Button5"
              virtualName="" explicitFocusOrder="0" pos="800 448 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="T60Button6" id="e675669eaf44d945" memberName="t60Button6"
              virtualName="" explicitFocusOrder="0" pos="912 448 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="StiIrButton" id="8dd7c446a46b7938" memberName="stiIrButton"
              virtualName="" explicitFocusOrder="0" pos="832 312 222 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="C50Button1" id="73cc69a96a38468f" memberName="c50Button1"
              virtualName="" explicitFocusOrder="0" pos="350 515 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="C50Button2" id="3cd7516cbd3d3db5" memberName="c50Button2"
              virtualName="" explicitFocusOrder="0" pos="464 512 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="C50Button3" id="b865c400394e1348" memberName="c50Button3"
              virtualName="" explicitFocusOrder="0" pos="576 512 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="C50Button4" id="b00c808d38e06f93" memberName="c50Button4"
              virtualName="" explicitFocusOrder="0" pos="688 512 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="C50Button5" id="5e3770347f6c6386" memberName="c50Button5"
              virtualName="" explicitFocusOrder="0" pos="800 512 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="C50Button6" id="e2dffa671ca8f211" memberName="c50Button6"
              virtualName="" explicitFocusOrder="0" pos="912 512 102 48" bgColOff="ff000000"
              bgColOn="ff000000" buttonText="..." connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TOGGLEBUTTON name="DebugToggle" id="da78534dc933e6a4" memberName="debugToggle"
                virtualName="" explicitFocusOrder="0" pos="24 600 286 24" buttonText="Debug Mode (for development only)"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="ForceButton" id="c68db77f547790b8" memberName="forceButton"
              virtualName="" explicitFocusOrder="0" pos="24 632 286 24" bgColOff="ff808080"
              textCol="ff000000" buttonText="Force harcoded extraction for debug"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


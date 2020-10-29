MainWindow::MainWindow (const String& name) :
    DocumentWindow (name,
                    Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
                    DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new MainComponent(), true);

   #if JUCE_IOS || JUCE_ANDROID
    setFullScreen (true);
   #elif JUCE_STANDALONE_APPLICATION
    setResizable (true, true);
    centreWithSize (getWidth(), getHeight());
   #else
    setResizable (true, false);
   #endif

    setResizeLimits (400, 400, std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

    setOpaque (true);
    setVisible (true);

    Desktop::getInstance().setDefaultLookAndFeel (globalLookAndFeel);
}

MainWindow::~MainWindow()
{
    //Only kill off the L&F once we reach a point where this is the only instance:
    if (globalLookAndFeel.getReferenceCount() <= 1)
        Desktop::getInstance().setDefaultLookAndFeel (nullptr);
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

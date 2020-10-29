class JUCEProjectTemplateApplication final : public JUCEApplication
{
public:
    JUCEProjectTemplateApplication() { }

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return false; }

    void initialise (const String&) override
    {
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void anotherInstanceStarted (const String&) override
    {
    }

    void shutdown() override { mainWindow = nullptr; }
    void systemRequestedQuit() override { quit(); }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION (JUCEProjectTemplateApplication)
